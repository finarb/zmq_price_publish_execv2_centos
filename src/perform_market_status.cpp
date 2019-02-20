
/*********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to market status            **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/


#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

// uncomment the following "using" statements to simplify code
using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;



class MarketStatusPrinter: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeMarketsStatus_streaming
{
public:
	// use to remember previous status
	std::map<FOSMarketId, FeedOS::Types::FIXTradSesStatus>	m_market_status_map;

	void response_QUOTATION_SubscribeMarketsStatus_Started (FeedOS::Types::ListOfMarketStatus const & inSnapshot)
	{
		std::cout << "SubscribeMarketsStatus OK. Hit <ENTER> to stop"<<std::endl;

		for (unsigned int i=0; i<inSnapshot.size(); ++i) {
			MarketStatus const & s = inSnapshot[i];
			FOSMarketId market_id = s.getMarketId();
			FeedOS::Types::FIXTradSesStatus session_status = s.getCurrentSessionStatus().getTradSesStatusEnum();

			cout << "market # "<<market_id<< " = "<< market_id.to_str() << "\tstatus = "<<session_status<<endl;

			// remember the current session status for each market
			m_market_status_map[market_id] = session_status;
		}
	}

	void response_QUOTATION_SubscribeMarketsStatus_Failed (FeedOS::ReturnCode rc)
	{
		std::cout << "SubscribeMarketsStatus_Failed, rc="<<rc<<std::endl;
	}

	void aborted_QUOTATION_SubscribeMarketsStatus (FeedOS::ReturnCode rc)
	{
		std::cout << "aborted_SubscribeMarketsStatus, rc="<<rc<<std::endl;
	}

	void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus)
	{
		FOSMarketId market_id = inStatus.getMarketId();
		FeedOS::Types::FIXTradSesStatus session_status = inStatus.getCurrentSessionStatus().getTradSesStatusEnum();

		if (m_market_status_map[market_id] != session_status) {
			m_market_status_map[market_id] = session_status;
			cout << "market # "<<market_id<< " = "<< market_id.to_str() << "\tNEW STATUS = "<<session_status<<endl;
		}
	}

	void notif_MarketNews (FeedOS::Types::MarketNews const & inNews)
	{
		FOSMarketId market_id = inNews.getOrigMarketId();
		std::string const & headline = inNews.getHeadline();

		cout << "market # "<<market_id<< " = "<< market_id.to_str() << "\tNEWS = "<<headline<<endl;
	}

};



void perform_market_status (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_market_status");	

	if (argc<2) {
		std::cerr <<"? MICs..."<<std::endl;
		return;
	}

	// list of markets we are interested into
	FeedOS::ListOfFOSMarketId market_ids;
	extract_MICs (market_ids, argc, argv);	// read them from command-line arguments

	// Build the request object (responsible for maintaining the data transfer).
	// This one is of kind "delegate" thus it requires an external object to handle the incoming data
	MarketStatusPrinter	printer;
	FeedOS::API_QUOTATION_SubscribeMarketsStatus_delegate req (printer);

	// start the subscription (synchronous version)
	FeedOS::ReturnCode rc = req.sync_start (connection, market_ids);

	if (rc != FeedOS::RC_OK) {
		std::cerr << "SubscribeMarketsStatus error, rc="<< FeedOS::error_string(rc) <<std::endl;
	} else {
		getchar();
	}
	req.stop ();
}
