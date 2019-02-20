
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to feed status              **/
/**                                         **/
/** QuantHouse 2009                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;
using namespace FeedOS::Types;

//![snippet_feed_status_receiver]
class FeedStatusPrinter:
		public virtual INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
//![snippet_feed_status_receiver]
{
	typedef std::map<std::string, FeedStatus> MapOfFeedStatus;	// indexed by Feed name
	MapOfFeedStatus	m_map_of_feed_status_by_name;

	static char const * data_quality_str(FeedState feed_state)
	{
		switch (feed_state) {
		case FeedState_Active:					return "Active"; break;
		case FeedState_ProbablyNormal:			return "ProbablyNormal"; break;
		case FeedState_ProbablyDisrupted:		return "ProbablyDisrupted"; break;
		case FeedState_Disrupted_TechnicalLevel:	return "Disrupted_TechnicalLevel"; break;
		case FeedState_Disrupted_ExchangeLevel:	return "Disrupted_ExchangeLevel"; break;
		default:
			FEEDOS_LOG(User, Critical, "FeedStatusPrinter: unexpected FeedState value: "<<feed_state);
			return "?";
		}
	}

	void print_feed_description (FeedDescription const & v) const
	{
		std::cout << "feed name: "<< v.getFeedName()<<'\n';
		{
			// list of "internal source id" related to this feed (as set in TAG_InternalSourceId)
			std::cout << "internal source id: ";
			ListOfFeedInternalSourceID const & ids =  v.getInternalSourceIDs();
			for (unsigned int i=0; i<ids.size(); ++i) {
				if (i!=0) {
					std::cout << ',';
				}
				std::cout << ids[i];
			}
			std::cout << '\n'; 
		}
	}

	void print_feed_status (FeedStatus const & v) const
	{
		FeedUsability const & usability = v.getOverallUsability();

		// [pretty] name of the feed
		print_feed_description (v.getFeed());
		std::cout << "    feed state         : "<< data_quality_str (usability.getState())			<<'\n';
		std::cout << "    latency penalty    : "<< std::boolalpha<<usability.getLatencyPenalty()	<<'\n';
		std::cout << "    out of date values : "<< std::boolalpha<<usability.getOutOfDateValues()	<<'\n';
		std::cout << "    bad data quality   : "<< std::boolalpha<<usability.getBadDataQuality()	<<'\n';
	}

	void fill_status_map_and_print(FeedStatus const & v)
	{
		// update internal image
		m_map_of_feed_status_by_name[v.getFeed().getFeedName()] = v;

		// print this value
		print_feed_status (v);
	}

public:

	FeedStatusPrinter ()
	{}

	//![snippet_feed_status_started]
	void response_CONNECTION_SubscribeToFeedStatus_Started(
			ListOfFeedStatus const & inFullSnapshot)
	{
		std::cout << "\n*** Initial Snapshot\n"; 

		for (unsigned int i=0; i<inFullSnapshot.size(); ++i)
		{
			FeedStatus const & v = inFullSnapshot[i];
			fill_status_map_and_print(v);
		}
	}
	//![snippet_feed_status_started]

	//![snippet_feed_status_failed]
	void response_CONNECTION_SubscribeToFeedStatus_Failed(ReturnCode rc)
	{
		std::cerr << "SubscribeToFeedStatus_Failed, rc=" << rc << std::endl;
	}
	//![snippet_feed_status_failed]

	//![snippet_feed_status_aborted]
	void aborted_CONNECTION_SubscribeToFeedStatus(ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeToFeedStatus, rc=" << rc << std::endl;
	}
	//![snippet_feed_status_aborted]

	//![snippet_feed_status_fsu]
	void notif_FeedStatusUpdate(
			String const & inSender,
			Timestamp const & inSenderUTCTimestamp,
			FeedStatus const & inStatus)
	{
		std::cout << "\n*** FeedStatusUpdate sender=" << inSender <<
				" timestamp=" << inSenderUTCTimestamp << "\n";
		fill_status_map_and_print(inStatus);
	}
	//![snippet_feed_status_fsu]

	//![snippet_feed_status_fse]
	void notif_FeedStatusEvent(
			String const & inSender,
			Timestamp const & inSenderUTCTimestamp,
			FeedStatusEvent const & inEvent)
	{
		std::cout << "\n*** FeedStatusEvent sender=" << inSender <<
				" timestamp=" << inSenderUTCTimestamp << "\n";
		print_feed_description(inEvent.getFeed());
		std::cout << "  event type: " << inEvent.getEventType() << '\n';
		ListOfString const & details = inEvent.getEventDetails();
		if (!details.empty())
		{
			std::cout << "  details:\n";
			for (size_t i = 0; i<details.size(); ++i)
			{
				std::cout << "    "<< details[i] << '\n';
			}
		}
	}
	//![snippet_feed_status_fse]

	void dump_current_set_of_status () const
	{
		std::cout << "\n*** Current set of Feed Status\n"; 
		for (MapOfFeedStatus::const_iterator it = m_map_of_feed_status_by_name.begin(); it != m_map_of_feed_status_by_name.end(); ++it) {
			FeedStatus const & v = it->second;
			print_feed_status (v);
		}
	}
};

/** \cond refguide
 * This sample illustrates how to implement the feed status subscription to
 * be informed of servers and feed states, in real-time.
 *
 * <ol><li>Implement the \c INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
 * interface whose virtual methods are called when the events are received:
 * </li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_receiver
 *
 * <ol><li>The started callback is called when the server has accepted the
 * request; it contains the current snapshot of all states available on the
 * server:</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_started
 *
 * <ol><li>The failed callback is called if the server rejects the request. The
 * given return code indicates the rejection reason; the subscription was not
 * started:</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_failed
 *
 * <ol><li>The aborted callback is called when an error occurs; the return code
 * indicates which error occurred. The subscription is now over.</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_aborted
 *
 * <ol><li>The \c FeedStatusUpdate callback transports an update of the feed
 * status for one or more sources. If you are not interested in all sources
 * available on the server you are connected to, it is the place to filter by
 * source and/or feed name:</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_fsu
 *
 * <ol><li>The \c FeedStatusEvent transports a human readable update of
 * a feed status:</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_fse
 *
 * <ol><li>Now that the receiver is implemented, instantiate the delegate that
 * will handle the request, giving it an instance of your callbacks handler:
 * </li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_delegate
 *
 * <ol><li>Start the request. If it succeeds, the subscription is now on. Here
 * we just wait for a user input to stop it through the delegate object.</li></ol>
 * \snippet perform_subscribe_feed_status.cpp snippet_feed_status_request
 *
 * \endcond
 */
void perform_subscribe_feed_status(API::Connection & connection, int /*argc*/, char * /*argv*/[])
{
	// data consumer (just prints on STDOUT)
	FeedStatusPrinter printer;

	// Build the request object (responsible for maintaining the data transfer).
	//![snippet_feed_status_delegate]
	API_CONNECTION_SubscribeToFeedStatus_delegate req(printer);
	//![snippet_feed_status_delegate]

	// start the subscription (synchronous version)
	//![snippet_feed_status_request]
	ReturnCode rc = req.sync_start(connection);

	if (rc != RC_OK) {
		std::cerr << "sync_start error, rc=" << error_string(rc) << std::endl;
	} else {
		getchar();
	}
	req.stop();
	//![snippet_feed_status_request]

	// finally, dump latest status
	printer.dump_current_set_of_status();
}
