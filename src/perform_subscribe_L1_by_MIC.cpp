
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to quotation events         **/
/** for several MIC                         **/
/**                                         **/
/** QuantHouse 2007                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>
#include <feedos/generated/gen_api_QUOTATION_SubscribeMarketsDataAndStatus.h>	// aka "Level 1", which is everything but order books
#include <feedos/framework/QuotationContext.h>


class TradeEventPrinter_ByMIC: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming
{
public:
	TradeEventPrinter_ByMIC ()
	{}

	void response_QUOTATION_SubscribeMarketsDataAndStatus_Started (FeedOS::Types::ListOfMarketStatus const & /*inMarketsStatus*/)
	{
		std::cerr << "SubscribeMarketsDataAndStatus_Started"<<std::endl;
		// the response data should be ignored, as it's rarely filled.
		// To get informed of feed status events see perform_subscribe_feed_status.cpp
	}

	void response_QUOTATION_SubscribeMarketsDataAndStatus_Failed (FeedOS::ReturnCode rc)
	{
		std::cerr << "SubscribeMarketsDataAndStatus_Failed, rc="<<rc<<std::endl;
	}

	void aborted_QUOTATION_SubscribeMarketsDataAndStatus (FeedOS::ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeMarketsDataAndStatus, rc="<<rc<<std::endl;
	}

	// these 3 callbacks are obsolete
	virtual void notif_TradeEvent	(FeedOS::FOSInstrumentCode /*inCode*/, FeedOS::Timestamp const & /*inMarketUTCTimestamp*/,  FeedOS::Types::QuotationTradeEvent const & /*inData*/) {}
	virtual void notif_ValuesUpdate	(FeedOS::FOSInstrumentCode /*inCode*/, FeedOS::Timestamp const & /*inMarketUTCTimestamp*/,  FeedOS::Types::QuotationValuesUpdate const & /*inData*/) {}
	virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & /*inStatus*/) {}

	// this callback carries a "market news". See perform_market_status.cpp
	virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & /*inNews*/)
	{
	}
	
	// this callback carries a "trade cancel/correction" event for an instrument. See perform_subscribe.cpp
	void notif_TradeCancelCorrection	(FeedOS::FOSInstrumentCode inCode, 
										FeedOS::Timestamp const & inServerTimestamp,  
										FeedOS::Types::QuotationTradeCancelCorrection const & inData)
	{
		if (inData.getContentMask() & FeedOS::Types::TradeCancelCorrectionContentBit_IsCorrection)
		{
			std::cout << "TRADE CORRECTION for instrument : ";
		}
		else
		{
			std::cout << "TRADE CANCEL for instrument : ";
		}
		std::cout << inCode << " server_timestamp=" << inServerTimestamp << std::endl;

		if (inData.getTradingSessionId() != 0)
		{
			std::cout << "TradingSessionId: " << inData.getTradingSessionId() << " ";
		}
		if (inData.getContentMask() & FeedOS::Types::TradeCancelCorrectionContentBit_CurrentSession)
		{
			std::cout << "[current session]";
		}
		std::cout << std::endl;

		std::cout << "original trade: ID " << inData.getOriginalTrade().getTradeId()
				<< ", " << inData.getOriginalTrade().getPrice()
				<< " x " << inData.getOriginalTrade().getQuantity()
				<< std::endl;

		if (inData.getContentMask() & FeedOS::Types::TradeCancelCorrectionContentBit_IsCorrection)
		{
			std::cout << "corrected trade: ID " << inData.getCorrectedTrade().getTradeId()
					<< ", " << inData.getCorrectedTrade().getPrice()
					<< " x " << inData.getCorrectedTrade().getQuantity()
					<< std::endl;
		}

		if ((inData.getContentMask() & FeedOS::Types::TradeCancelCorrectionContentBit_CorrectedValues)
				&& (!inData.getCorrectedValues().empty()))
		{
			std::cout << "CorrectedValues: " << std::endl;
			dump_quot_variables(inData.getCorrectedValues());
		}
	}

	// this callback carries a Level 1 event for an instrument. See perform_subscribe.cpp
	virtual void notif_TradeEventExt (	FeedOS::FOSInstrumentCode inCode, 
										FeedOS::Timestamp const & inServerUTCTimestamp,
										FeedOS::Timestamp const & inMarketUTCTimestamp, 
										FeedOS::Types::QuotationTradeEventExt const & inData
									)
	{
		// TODO: put your code here

		std::cout << "TRADE EVENT for instrument : "<< inCode << " server_timestamp="<<inServerUTCTimestamp<<" market_timestamp="<<inMarketUTCTimestamp<< std::endl;

		if (inData.getContentMask() & FeedOS::QuotationContentBit_Bid) {
			dump_one_side_limit	(inData.getBestBid(), "bid");
		}
		if (inData.getContentMask() & FeedOS::QuotationContentBit_Ask) {
			dump_one_side_limit	(inData.getBestAsk(), "ask");
		}

		if (inData.getContentMask() & FeedOS::QuotationContentBit_LastPrice)
		{
			// there's a price
			if (inData.getContentMask() & FeedOS::QuotationContentBit_LastTradeQty)
			{
				// there's a qty: it's a trade
				if(inData.getContentMask() & FeedOS::QuotationContentBit_OffBookTrade)
				{
					// the trade is an off book trade (otc, trade report)
					std::cout << "OFF BOOK TRADE: "<<inData.getPrice() << " x "<< inData.getLastTradeQty()<<std::endl;
				}
				else
				{
					// normal trade
					std::cout << "TRADE: "<<inData.getPrice() << " x "<< inData.getLastTradeQty()<<std::endl;
				}
			}
			else
			{
				std::cout << "PRICE: "<<inData.getPrice()<<std::endl;				
			}
		}

		if (!inData.getContext().empty()) {
			// there are "context flags" (usually TradeConditions)
			// => dump all the tags received (see list in api/tags_quotation_context.hpp)
			//    different tags are available depending on market
			FeedOS::QuotationContext c;
			c.load (inData.getContext());
			std::cout << "CONTEXT:\t";
			c.print_content (std::cout, true, false, "\n\t\t","+",":\t");
			std::cout << "\n";
		}

		if (!inData.getValues().empty()) {
			//
			// additional values are present (usually sent as a side-effect of the realtime trade event)
			//
			// However it should be noted that DailyTotalVolumeTraded will normally NOT be sent.
			// Should client application need that, it has to compute it by continuously adding the traded quantites
			// see " FeedOS_quotation_tags_lifecycle.xls"
			//
			dump_quot_variables (inData.getValues());
		}

	}

};



void perform_subscribe_L1_by_MIC (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_L1_by_MIC");	

	if (argc<2) {
		std::cerr <<"? MIC..."<<std::endl;
		return;
	}

	FeedOS::Types::ListOfFOSMarketId	input_MICs;

	// list of instruments we are interested into
	if (!extract_MICs (input_MICs, argc, argv))	// read them from command-line arguments
		return;

	TradeEventPrinter_ByMIC	printer;
	FeedOS::API_QUOTATION_SubscribeMarketsDataAndStatus_delegate req (printer);

	// start the subscription (synchronous version)
	FeedOS::ReturnCode rc = req.sync_start (connection, input_MICs);

	if (rc != FeedOS::RC_OK) {
		std::cerr << "sync_start error, rc="<< FeedOS::error_string(rc) <<std::endl;
	} else {
		getchar(); // wait for user input
	}
	req.stop (); // stop subscription
}
