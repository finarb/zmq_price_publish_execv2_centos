/*******************************/
/** FeedOS sample client code **/
/**                           **/
/** copyright QuantHouse      **/
/*******************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;
using namespace FeedOS::Types;

//![snippet_dl_and_sub_intraday_ext_receiver]
struct IntradayExtendedPrinter :
		public INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming
//![snippet_dl_and_sub_intraday_ext_receiver]
{
	IntradayExtendedPrinter(std::ostream & output) : m_output(output) {}

	FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming

private:
	std::ostream & m_output;
};

//![snippet_dl_and_sub_intraday_ext_started]
void IntradayExtendedPrinter::response_QUOTATION_DownloadHistoryIntradayExtended_Started(
		FeedOS::Types::ListOfFOSInstrumentCode const & inCodes)
{
	m_output << "download started for: " << inCodes.size() << " instruments" << std::endl;
}
//![snippet_dl_and_sub_intraday_ext_started]

//![snippet_dl_and_sub_intraday_ext_failed]
void IntradayExtendedPrinter::response_QUOTATION_DownloadHistoryIntradayExtended_Failed(
		ReturnCode rc)
{
	m_output << "request failed: rc=" << error_string(rc) << std::endl;
}
//![snippet_dl_and_sub_intraday_ext_failed]

//![snippet_dl_and_sub_intraday_ext_aborted]
void IntradayExtendedPrinter::aborted_QUOTATION_DownloadHistoryIntradayExtended(
		ReturnCode rc)
{
	if (rc == RC_OK)
	{
		m_output << "download complete" << std::endl;
	}
	else
	{
		m_output << " download aborted by server, rc=" << error_string(rc) << std::endl;
	}
}
//![snippet_dl_and_sub_intraday_ext_aborted]

//![snippet_dl_and_sub_intraday_ext_iext]
void IntradayExtendedPrinter::notif_IntradayExtended(
		FeedOS::Types::ListOfIntradayHistoryDataExtended const & inTrades)
{
	for (ListOfIntradayHistoryDataExtended::const_iterator it(inTrades.begin()); it != inTrades.end(); ++it)
	{
		m_output << "TE " << it->getInstrCode() << " " << it->getTradeId() << " "
				<< it->getIntradayPointExtended().getMarketUTCTimestamp() << " "
				<< it->getIntradayPointExtended().getPrice() << "x"
				<< it->getIntradayPointExtended().getLastTradeQty() << std::endl;
	}
}
//![snippet_dl_and_sub_intraday_ext_iext]

//![snippet_dl_and_sub_intraday_ext_cancel]
void IntradayExtendedPrinter::notif_Cancel(
		FeedOS::Types::IntradayHistoryCancel const & inCancel)
{
	m_output << "CA " << inCancel.getInstrCode() << " " << inCancel.getTradeId()
			<< " " << inCancel.getOriginalMarketTimestamp() << std::endl;
}
//![snippet_dl_and_sub_intraday_ext_cancel]

//![snippet_dl_and_sub_intraday_ext_correction]
void IntradayExtendedPrinter::notif_Correction(
		FeedOS::Types::IntradayHistoryCorrection const & inCorrection)
{
	m_output << "CO " << inCorrection.getInstrCode() << " "
			<< inCorrection.getTradeId() << " "
			<< inCorrection.getOriginalMarketTimestamp() << " "
			<< inCorrection.getTrade().getPrice() << "x"
			<< inCorrection.getTrade().getQuantity() << std::endl;
}
//![snippet_dl_and_sub_intraday_ext_correction]

/** \cond refguide
 * This sample demonstrates how to use the \c DownloadHistoryIntradayExtended
 * subscription to download or download then subscribe to intraday historical
 * data. This request also gives access to trade cancels and corrections.
 *
 * <ol><li>First, implement the \c INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming
 * interface whose virtual methods are called when the events are received:</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_receiver
 *
 * <ol><li>The started callback is called when the server accepts the request.
 * </li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_started
 *
 * <ol><li>The failed callback is called if the server rejects the request. The
 * return code indicates the reason of the rejection.</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_failed
 *
 * <ol><li>The aborted callback is called when the download is completed (RC_OK)
 * or when an error occurs (the return code indicates the error).</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_aborted
 *
 * <ol><li>The \c IntradayExtended callback conveys historical or real-time
 * data.</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_iext
 *
 * <ol><li>The \c Cancel callback conveys a trade cancel. It refers necessarily
 * to a previously sent trade.</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_cancel
 *
 * <ol><li>The \c Correction callback conveys a trade correction. It refers
 * necessarily to a previously sent trade.</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_correction
 *
 * <ol><li>Create a delegate object giving it an instance of the receiver class.
 * Set the input parameters as needed: list of instruments, begin and end
 * timestamp, number of points, whether or not trade cancels and corrections
 * must be also downloaded. Refer to the request documentation for a
 * comprehensive explanation of these parameters.
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_request
 *
 * <ol><li>Even if we called \c sync_start, only the response (success of
 * failure) is synchronous. The other callbacks are handled asynchronously. So
 * users have to implement a mechanism to wait for the end of the download. Or,
 * if a subscription to real-time was requested, the subscription never ends
 * (except in case of errors) and users will stop the subscription themselves by
 * calling \c stop on the delegate object.</li></ol>
 * \snippet perform_dl_and_sub_histo_intraday_extended.cpp snippet_dl_and_sub_intraday_ext_wait
 *
 * \endcond
 */
void perform_dl_and_sub_histo_intraday_extended(API::Connection & connection, int argc, char * argv[])
{
	FEEDOS_SCOPER(User, "perform_dl_and_sub_histo_intraday_extended");

	// Parse args
	if (argc < 6)
	{
		std::cerr <<"? BEGIN_TIMESTAMP END_TIMESTAMP NB_POINTS WITH_TCC INSTRUMENTS..." << std::endl;
		return;
	}

	Timestamp begin_ts;
	if (!begin_ts.set_from_string(argv[1]))
	{
		std::cerr << "syntax error for begin timestamp: " << argv[1] << std::endl;
		return;
	}

	Timestamp end_ts;
	if (!end_ts.set_from_string(argv[2]))
	{
		std::cerr << "syntax error for end timestamp: " << argv[2] << std::endl;
		return;
	}

	int nb_points = ::atoi(argv[3]);

	std::string with_tcc_str = argv[4];
	if (with_tcc_str != "true" && with_tcc_str != "false")
	{
		std::cerr << "syntax error for with_tcc: only 'true' and 'false' accepted" << std::endl;
		return;
	}
	bool with_tcc = (with_tcc_str == "true") ? true : false;

	ListOfPolymorphicInstrumentCode codes;
	for (int i = 5; i < argc; ++i)
	{
		codes.push_back(PolymorphicInstrumentCode());
		if (!codes.back().read_from_string(argv[i]))
		{
			std::cerr << "syntax error while for instrument code: " << argv[i] << std::endl;
			return;
		}
	}

	//![snippet_dl_and_sub_intraday_ext_request]
	IntradayExtendedPrinter printer(std::cout);
	API_QUOTATION_DownloadHistoryIntradayExtended_delegate req(printer);
	ReturnCode const rc = req.sync_start(connection, codes, begin_ts, end_ts,
			nb_points, with_tcc);
	//![snippet_dl_and_sub_intraday_ext_request]

	//![snippet_dl_and_sub_intraday_ext_wait]
	if (rc != RC_OK)
	{
		std::cerr << "sync_start error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		while (req.subscription_is_in_progress())
		{
			API::msleep(1000);
		}
	}
	//![snippet_dl_and_sub_intraday_ext_wait]
}
