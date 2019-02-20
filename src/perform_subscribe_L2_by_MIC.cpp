
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to orderbook events         **/
/** for several MIC                         **/
/**                                         **/
/** QuantHouse 2010                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>
#include <feedos/generated/gen_api_QUOTATION_SubscribeMarketsOrderBook.h>	// aka "Level 2", which is MarketByLevel (orders aggregated by price)
#include <feedos/framework/QuotationContext.h>


class OrderBookEventPrinter_ByMIC: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming
{
public:
	OrderBookEventPrinter_ByMIC ()
	{}

	void response_QUOTATION_SubscribeMarketsOrderBook_Started ()
	{
		std::cerr << "SubscribeMarketsOrderBook_Started"<<std::endl;
	}

	void response_QUOTATION_SubscribeMarketsOrderBook_Failed (FeedOS::ReturnCode rc)
	{
		std::cerr << "SubscribeMarketsOrderBook_Failed, rc="<<rc<<std::endl;
	}

	void aborted_QUOTATION_SubscribeMarketsOrderBook (FeedOS::ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeMarketsOrderBook, rc="<<rc<<std::endl;
	}


	//////////////////////////////////////
	///////////////////
	/////////////////// deprecated notifications
	///////////////////
	//////////////////////////////////////

	void notif_OrderBookRefresh	(FeedOS::FOSInstrumentCode inCode, FeedOS::Timestamp const & inServerUTCTimestamp, FeedOS::int8 /*inBidChangeIndicator*/, FeedOS::int8 /*inAskChangeIndicator*/,  FeedOS::Types::ListOfOrderBookEntry const & /*inBidLimits*/,  FeedOS::Types::ListOfOrderBookEntry const & /*inAskLimits*/)
	{
		std::cout << "OrderBookRefresh for instrument : "<< inCode << " server_timestamp="<<inServerUTCTimestamp/*<<" market_timestamp="<<inMarketUTCTimestamp*/<< std::endl;

		// TODO: put your code here
	}

	void notif_OrderBookDeltaRefresh	(FeedOS::FOSInstrumentCode inCode, FeedOS::Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & /*inDelta*/)
	{
		std::cout << "OrderBookDeltaRefresh for instrument : "<< inCode << " server_timestamp="<<inServerUTCTimestamp/*<<" market_timestamp="<<inMarketUTCTimestamp*/<< std::endl;

		// TODO: put your code here
	}

	void notif_OrderBookMaxVisibleDepth	(FeedOS::FOSInstrumentCode inCode, FeedOS::int8 inMaxVisibleDepth)
	{
		std::cout << "OrderBookMaxVisibleDepth="<< inMaxVisibleDepth <<" for instrument : "<< inCode << std::endl;

		// TODO: put your code here
	}


	//////////////////////////////////////
	///////////////////
	/////////////////// newer notifications
	/////////////////// (see perform_subscribe_MBL.cpp)
	///////////////////
	//////////////////////////////////////

	void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData)
	{
		for (unsigned int i=0; i < inData.size(); ++i)
		{
			FeedOS::Types::MBLSnapshot const & instrSnapshot = inData[i];
			std::cout << "MBLFullRefresh for instrument : " << instrSnapshot.getCode() << std::endl;
		}
	}

	
	void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData)
	{
		std::cout << "MBLOverlapRefresh for instrument : "<< inData.getCode() << " server_timestamp="<<inData.getTimestamps().getServer() <<" market_timestamp="<<inData.getTimestamps().getMarket()<< std::endl;

		// TODO: put your code here

	}

	virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData)
	{
		std::cout << "MBLDeltaRefresh for instrument : "<< inData.getCode() << " server_timestamp="<<inData.getTimestamps().getServer() <<" market_timestamp="<<inData.getTimestamps().getMarket()<< std::endl;

		// TODO: put your code here
	}

	virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData)
	{
		std::cout << "MBLMaxVisibleDepth="<< inData.getMaxVisibleDepth() <<" for instrument : "<< inData.getCode() << std::endl;

		// TODO: put your code here
	}
};



void perform_subscribe_L2_by_MIC (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_L2_by_MIC");	

	if (argc<2) {
		std::cerr <<"? MIC..."<<std::endl;
		return;
	}

	FeedOS::Types::ListOfFOSMarketId	input_MICs;

	// list of instruments we are interested into
	if (!extract_MICs (input_MICs, argc, argv))	// read them from command-line arguments
		return;

	OrderBookEventPrinter_ByMIC	printer;
	FeedOS::API_QUOTATION_SubscribeMarketsOrderBook_delegate req (printer);

	// start the subscription (synchronous version)
	FeedOS::ReturnCode rc = req.sync_start (connection, input_MICs);

	if (rc != FeedOS::RC_OK) {
		std::cerr << "sync_start error, rc="<< FeedOS::error_string(rc) <<std::endl;
	} else {
		getchar(); // wait for user input
	}
	req.stop (); // stop subscription
}
