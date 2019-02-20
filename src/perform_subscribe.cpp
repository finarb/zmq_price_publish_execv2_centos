
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to quotation events         **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>
#include <feedos/framework/ReverseInstrumentCodeMap.h>		// used to translate instrument codes (internal numeric => Polymorphic)
#include <feedos/framework/QuotationContext.h>
#include <feedos/framework/InstrumentQuotationData_2.h>
#include <iomanip>
#include <limits>

namespace FeedOS { namespace Types {
	extern char const * getFIXSecurityTradingStatusString(FIXSecurityTradingStatus value);
}}

// list of instrument codes
static FeedOS::Types::ListOfPolymorphicInstrumentCode	input_codes;


// this is used to convert a "internal numeric instr code" into a "polymorphic" (hopefully of the form MIC@LOCALCODE_STR)
static FeedOS::ReverseInstrumentCodeMap		reverse_instr_map;

//![snippet_sub_L1_subclass]
class TradeEventPrinter:
		public virtual FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming
//![snippet_sub_L1_subclass]
{
	bool				m_opt_time;
	FeedOS::Timestamp	m_serverUTCTimestamp;
	FeedOS::Timestamp	m_MarketUTCTimestamp;

	inline void dump_time ()
	{
		if (m_opt_time) {
			std::cout << m_serverUTCTimestamp << '\t' << m_MarketUTCTimestamp << '\t';
		}
	}

public:
	FeedOS::uint32 m_ticket;

	TradeEventPrinter (bool opt_time)
		:m_opt_time (opt_time)
		,m_ticket	(0)
	{
		std::cout << std::setprecision(std::numeric_limits<double>::digits10);
	}

	//![snippet_sub_L1_cb_started]
	void response_QUOTATION_SubscribeInstrumentsL1_Started(
			FeedOS::uint32 inTicket,
			FeedOS::Types::ListOfInstrumentStatusL1 const & inSnapshot)
	{
		std::cout << "SubscribeInstrumentsL1 OK. Hit <ENTER> to stop"
				<< std::endl;

		// Store the "ticket" associated to the ongoing subscription.
		// It is required to modify the subscription "profile".
		// (instruments/mask/values)
		m_ticket=inTicket;

		// Dump the current values
		dump_instr_status (inSnapshot);

		// Update the list of instrument codes (to store the "internal" flavour)
		for (unsigned int i=0; i<inSnapshot.size(); ++i)
		{
			// The instrument code, as passed in the request
			FeedOS::PolymorphicInstrumentCode const & instr_code =
					input_codes[i];
			// The instrument code, in internal numeric format
			FeedOS::FOSInstrumentCode internal_code = inSnapshot[i].getCode();
			std::cout << "local_code " << instr_code
					<< " has internal value: " << internal_code << std::endl;

			reverse_instr_map.load (internal_code, instr_code.to_str());
		}
	}
	//![snippet_sub_L1_cb_started]

	//![snippet_sub_L1_cb_failed]
	void response_QUOTATION_SubscribeInstrumentsL1_Failed(FeedOS::ReturnCode rc)
	{
		std::cerr << "SubscribeInstrumentsL1_Failed, rc=" << rc << std::endl;
	}
	//![snippet_sub_L1_cb_failed]

	//![snippet_sub_L1_cb_aborted]
	void aborted_QUOTATION_SubscribeInstrumentsL1(FeedOS::ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeInstrumentsL1, rc=" << rc << std::endl;
	}
	//![snippet_sub_L1_cb_aborted]

	//![snippet_sub_L1_cb_tcc]
	void notif_TradeCancelCorrection(
			FeedOS::FOSInstrumentCode inCode,
			FeedOS::Timestamp const & inServerTimestamp,
			FeedOS::Types::QuotationTradeCancelCorrection const & inData)
	{
#define TRADE_CANCEL_CORRECTION_IMPLEMENTATION
/* Implementing this callback is not mandatory if you are only interested in
 * real-time events, or if you are interested in markets that do not support
 * such events.
 *
 * On the contrary if you are interested in cancel/corrections, or if you need
 * accurate end-of-day data (especially volumes), you will have to implement
 * this properly.
 */
#ifdef TRADE_CANCEL_CORRECTION_IMPLEMENTATION
		std::string translated_instr_code =
				reverse_instr_map.translate_instr_code(inCode);

		if (inData.getContentMask() &
				FeedOS::Types::TradeCancelCorrectionContentBit_IsCorrection)
		{
			std::cout << "TRADE CORRECTION for instrument : "
					<< translated_instr_code << std::endl;
		}
		else
		{
			std::cout << "TRADE CANCEL for instrument : "
					<< translated_instr_code << std::endl;
		}
		std::cout << "internal  (server)  time is: "<< inServerTimestamp
				<< std::endl;

		if (inData.getTradingSessionId() != 0)
		{
			std::cout << "TradingSessionId: " << inData.getTradingSessionId()
					<< " ";
		}
		if (inData.getContentMask() &
				FeedOS::Types::TradeCancelCorrectionContentBit_CurrentSession)
		{
			std::cout << "[current session]";
		}
		std::cout << std::endl;

		std::cout << "original trade: ID "
				<< inData.getOriginalTrade().getTradeId()
				<< ", " << inData.getOriginalTrade().getPrice()
				<< " x " << inData.getOriginalTrade().getQuantity()
				<< std::endl;

		if (inData.getContentMask() &
				FeedOS::Types::TradeCancelCorrectionContentBit_IsCorrection)
		{
			std::cout << "corrected trade: ID "
					<< inData.getCorrectedTrade().getTradeId()
					<< ", " << inData.getCorrectedTrade().getPrice()
					<< " x " << inData.getCorrectedTrade().getQuantity()
					<< std::endl;
		}

		if ((inData.getContentMask() &
				FeedOS::Types::TradeCancelCorrectionContentBit_CorrectedValues)
				&& (!inData.getCorrectedValues().empty()))
		{
			std::cout << "CorrectedValues: " << std::endl;
			dump_quot_variables(inData.getCorrectedValues());
		}
#endif
	}
	//![snippet_sub_L1_cb_tcc]

	//![snippet_sub_L1_cb_tde]
	void notif_TradeEventExt(
			FeedOS::FOSInstrumentCode inCode,
			FeedOS::Timestamp const & inServerUTCTimestamp,
			FeedOS::Timestamp const & inMarketUTCTimestamp,
			FeedOS::Types::QuotationTradeEventExt const & inData)
	{
#if FEEDOS_PROXY_MEASURE_LATENCY
		FeedOS::Proxy::perform_latency_measure ("sample_cli/notif_TradeEvent");
#endif
		m_serverUTCTimestamp = inServerUTCTimestamp;
		m_MarketUTCTimestamp = inMarketUTCTimestamp;

		std::string translated_instr_code =
				reverse_instr_map.translate_instr_code(inCode);

		std::cout << "TRADE EVENT for instrument : " << translated_instr_code
				<< std::endl;
		std::cout << "official market UTC time is: " << m_MarketUTCTimestamp
				<< std::endl;
		std::cout << "internal  (server)  time is: " << m_serverUTCTimestamp
				<< std::endl;

		if (inData.getContentMask() &
				FeedOS::QuotationContentBit_ChangeBusinessDay)
		{
			std::cout << "/!\\ CHANGE BUSINESS DAY /!\\" << std::endl;
		}

		if (inData.getContentMask() & FeedOS::QuotationContentBit_Bid)
		{
			dump_time ();
			dump_one_side_limit	(inData.getBestBid(), "bid");
		}
		if (inData.getContentMask() & FeedOS::QuotationContentBit_Ask)
		{
			dump_time ();
			dump_one_side_limit	(inData.getBestAsk(), "ask");
		}
		//![snippet_sub_L1_cb_tde]

		if (inData.getContentMask() & FeedOS::QuotationContentBit_TradingStatus)
		{
			FeedOS::Types::ListOfQuotationVariable const & values =
					inData.getValues();
			bool found = false;
			for (FeedOS::Types::ListOfQuotationVariable::const_iterator it =
					values.begin(); it != values.end(); ++it)
			{
				unsigned int tag_num = it->getNum();

				if (tag_num == FeedOS::TAG_TradingStatus)
				{
					found = true;
					FeedOS::Types::FIXSecurityTradingStatus status_num =
							static_cast<FeedOS::Types::FIXSecurityTradingStatus>((it->getValue()).get_Enum());
					switch (status_num)
					{
					case FeedOS::Types::FIXSecurityTradingStatus_ReadyToTrade:
						std::cout << "trading status: ReadyToTrade" << std::endl;
						break;
					case FeedOS::Types::FIXSecurityTradingStatus_NotAvailableForTrading:
						std::cout << "trading status: NotAvailableForTrading" << std::endl;
						break;
					default:
						std::cout << "trading status: "
								<< FeedOS::Types::getFIXSecurityTradingStatusString(status_num)
								<< std::endl;
						break;
					}
					break;
				}
			}
			if (!found)
			{
				std::cout << "TradingStatus missing" << std::endl;
			}
		}

		std::stringstream event_flags;
		if (inData.getContentMask() & FeedOS::QuotationContentBit_Open)
		{
			if (inData.getContentMask() & FeedOS::QuotationContentBit_OCHL_daily)
			{
				event_flags << "<daily> ";
			}
			if (inData.getContentMask() & FeedOS::QuotationContentBit_Session)
			{
				FeedOS::Types::ListOfQuotationVariable const & values = inData.getValues();
				for (FeedOS::Types::ListOfQuotationVariable::const_iterator it = values.begin(); it != values.end(); ++it)
				{
					unsigned int tag_num = it->getNum();
					switch(tag_num)
					{
					case FeedOS::TAG_TradingSessionId:
						// If Tag TradingSessionId is present in OtherValues and has a valid value, a new TradingSession begins
						if (FeedOS::Syntax_UNKNOWN != it -> getValue().get_syntax())
						{
							FeedOS::int8 const trading_session_id = it->getValue().get_int8();
							if (FeedOS::InstrumentQuotationData_2::is_session_regular(trading_session_id))
							{
								event_flags << "<new session #" << trading_session_id << "> ";
							}
							else if (FeedOS::InstrumentQuotationData_2::is_session_extended(trading_session_id))
							{
								event_flags << "<new extended session #" << trading_session_id << "> ";
							}
							else
							{
								//0: invalid value, never sent in the protocol
							}
						}
					default:
						break;
					}
				}
			}
			event_flags << "OPEN ";
		}
		if (inData.getContentMask() & FeedOS::QuotationContentBit_Close)
		{
			if (inData.getContentMask() & FeedOS::QuotationContentBit_OCHL_daily) { event_flags << "<daily> "; }
			else { event_flags << "<end session> "; }
			event_flags << "CLOSE ";
		}
		if (inData.getContentMask() & FeedOS::QuotationContentBit_High)
		{
			if (inData.getContentMask() & FeedOS::QuotationContentBit_OCHL_daily) { event_flags << "<daily> "; }
			else { event_flags << "<session> "; }
			event_flags << "HIGH ";
		}

		if (inData.getContentMask() & FeedOS::QuotationContentBit_Low)
		{
			if (inData.getContentMask() & FeedOS::QuotationContentBit_OCHL_daily) { event_flags << "<daily> "; }
			else { event_flags << "<session> "; }
			event_flags << "LOW ";
		}

		if (!event_flags.str().empty()) {
			std::cout << "event_flags: "<< event_flags.str() << std::endl;
		}

		if (inData.getContentMask() & FeedOS::QuotationContentBit_LastPrice) {
			dump_time ();
			if (inData.getContentMask() & FeedOS::QuotationContentBit_Session && inData.getContentMask() & FeedOS::QuotationContentBit_Context)
			{
				for (FeedOS::Types::ListOfQuotationVariable::const_iterator it = inData.getContext().begin(); it != inData.getContext().end(); ++it)
				{
					FeedOS::Types::TagNumber const tag_num = it->getNum();

					if (tag_num == FeedOS::TAG_ActualTradingSessionId)
					{
						FeedOS::Any const & tag_value = it->getValue();
						if (tag_value.get_syntax() != FeedOS::Syntax_UNKNOWN)
						{
							std::cout << "impacted session: " << static_cast<int>(tag_value.get_int8()) << std::endl;
						}
						break;
					}
				}
			}
			if (inData.getContentMask() & FeedOS::QuotationContentBit_LastTradeQty) {

				if(inData.getContentMask() & FeedOS::QuotationContentBit_OffBookTrade)
				{
					// the trade is an off book trade (otc, trade report)
					std::cout << "OFF BOOK TRADE: "
							  << inData.getPrice() << " x " << inData.getLastTradeQty()
							  << std::endl;
				}
				else
				{
					// the match happened in real time
					std::cout << "TRADE: "
							  << inData.getPrice() << " x "<< inData.getLastTradeQty()
							  << std::endl;
				}

				if (inData.getContentMask() & FeedOS::QuotationContentBit_Context) {
					for (FeedOS::Types::ListOfQuotationVariable::const_iterator it = inData.getContext().begin(); it != inData.getContext().end(); ++it)
					{
						FeedOS::Types::TagNumber const tag_num = it->getNum();

						if (tag_num == FeedOS::TAG_TradeImpactIndicator)
						{
							FeedOS::Any const & tag_value = it->getValue();
							if (tag_value.get_syntax() == FeedOS::Syntax_uint32)
							{
								FeedOS::QuotationTradeImpactIndicatorMask const tii = tag_value.get_uint32();

								if (((tii & FeedOS::TradeImpactIndicatorBit_HasVolume) && (tii & FeedOS::TradeImpactIndicatorBit_Volume))
									|| ((tii & !FeedOS::TradeImpactIndicatorBit_HasVolume) // by default, on-book trades only impact volume
										&& !(inData.getContentMask() & FeedOS::QuotationContentBit_OffBookTrade))
									)
								{
									std::cout << "This trade impacts volume." << std::endl;
								}
								// same info exists for OffbookVolume and VWAP

								std::string eligibility = "This trade is eligible to: ";
								if ((tii & FeedOS::TradeImpactIndicatorBit_HasLast) && (tii & FeedOS::TradeImpactIndicatorBit_Last))
								{
									eligibility += "last price, ";
								}
								if ((tii & FeedOS::TradeImpactIndicatorBit_HasHighLow) && (tii & FeedOS::TradeImpactIndicatorBit_HighLow))
								{
									eligibility += "high/low, ";
								}
								if ((tii & FeedOS::TradeImpactIndicatorBit_HasOpen) && (tii & FeedOS::TradeImpactIndicatorBit_Open))
								{
									eligibility += "open, ";
								}
								std::cout << eligibility << std::endl;
							}
							break;
						}
					}
				}
			} else {
				std::cout << "PRICE: "<< inData.getPrice() << std::endl;
			}

		} else {
			if (!event_flags.str().empty()) {
				// no "last price" present, however some flags are referring to a price value.
				// This could be:
				// 1) a CLOSE with no associated trade
				// 2) an Indicative OPENing: isSetOpen() && isSetTradingStatus() && trading_status==PreOpen
				// ... other cases (market dependent)
				std::cout << "OCHL value: " << inData.getPrice() << std::endl;
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

			// example for handling generic (FIX-protocol) flags
			{
				if (c.is_value_present_for_tag (FeedOS::Types::TradeCondition_X_crossed, FeedOS::TAG_TradeCondition)) {
					std::cout << "	FIX trade condition: CROSSED"<<std::endl;
				}
			}

			// example for handling market-specific flags
			{
				if (c.is_value_present_for_tag (FeedOS::LSE::TradeTypeIndicator_OTCTrade, FeedOS::TAG_MARKET_LSE_TradeTypeIndicator)) {
					std::cout << "	LSE-specific trade type: OTCTrade"<<std::endl;
				}

				if (c.is_value_present_for_tag (FeedOS::LSE::BargainConditionIndicator_Yes, FeedOS::TAG_MARKET_LSE_BargainConditionIndicator)) {
					std::cout << "	LSE-specific: BargainCondition indicator"<<std::endl;
				}

				if (c.is_value_present_for_tag (FeedOS::LSE::TradeTimeIndicator_Late, FeedOS::TAG_MARKET_LSE_TradeTimeIndicator)) {
					std::cout << "	LSE-specific: LateTrade"<<std::endl;
				} else if (c.is_value_present_for_tag (FeedOS::LSE::TradeTimeIndicator_Overnight, FeedOS::TAG_MARKET_LSE_TradeTimeIndicator)) {
					std::cout << "	LSE-specific: OvernightTrade"<<std::endl;
				}
			}
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

#if FEEDOS_PROXY_MEASURE_LATENCY
		FeedOS::Proxy::enable_next_latency_measure ();
#endif
	}

};

struct FeatureAddRemoveInstrumentsDemonstrator
{
	//
	// demonstrates modification of an on-going subscription on-the-fly, removing all instruments then adding whole instruments' list
	// - inSubTicket: subscription's identifier that will be modified twice hereunder
	// - inInstruments: list of instrument codes to remove and add
	// - inIgnoreInvalidCodes: option controlling request behavior when invalid/unknown codes are used
	FeatureAddRemoveInstrumentsDemonstrator(FeedOS::uint32 inSubTicket,
									   FeedOS::Types::ListOfPolymorphicInstrumentCode const & inInstruments,
									   bool inIgnoreInvalidCodes):
			m_SubTicket(inSubTicket),m_Instruments(inInstruments),m_IgnoreInvalidCodes(inIgnoreInvalidCodes)
	{
	}

	FeedOS::ReturnCode demonstrate(FeedOS::API::Connection & inConnection) {

		FeedOS::ReturnCode rc = FeedOS::RC_ERROR;
		FeedOS::API::sleep(5);
		std::cout << "Removing instruments" << std::endl;
		// Remove instrument's codes listed in m_Instruments from subscription identified by m_SubTicket
		rc = FeedOS::API_QUOTATION_ChgSubscribeInstrumentsL1Remove(inConnection, m_SubTicket, m_Instruments);
		if (FeedOS::RC_OK != rc ) {
			std::cerr << "API_QUOTATION_ChgSubscribeInstrumentsL1Remove error, rc="<< FeedOS::error_string(rc) <<std::endl;
			return rc;
		}

		FeedOS::API::sleep(5);
		std::cout << "Adding instruments" << std::endl;
		// Add instrument's codes listed in m_Instruments in subscription identified by m_SubTicket
		// m_AddedInstrumentsSnapshots will be populated with L1 snapshots for those newly subscribed instruments' codes
		rc = FeedOS::API_QUOTATION_ChgSubscribeInstrumentsL1Add(inConnection,
														m_AddedInstrumentsSnapshots,
														m_SubTicket,
														m_Instruments,
														m_IgnoreInvalidCodes);
		if (FeedOS::RC_OK != rc ) {
			std::cerr << "API_QUOTATION_ChgSubscribeInstrumentsL1Add error, rc="<< FeedOS::error_string(rc) <<std::endl;
			return rc;
		}

		FeedOS::API::sleep(5);
		// Print snapshots
		dump_instr_status (m_AddedInstrumentsSnapshots);
		return rc;
	}

private:
	// "Input parameters"
	FeedOS::uint32 const									m_SubTicket;
	FeedOS::Types::ListOfPolymorphicInstrumentCode const	m_Instruments;
	bool const												m_IgnoreInvalidCodes;

	// "Snapshots" recieved after instruments have been added
	FeedOS::Types::ListOfInstrumentStatusL1					m_AddedInstrumentsSnapshots;
};

/** \cond refguide
 * To perform a Level 1 instrument subscription in FeedOS API C++, you need to implement an
 * interface and several callbacks that handle the request and responses, as described in the
 * procedure below:
 *
 * <ol><li>Implement the \c FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming interface
 * whose virtual methods are called when the events are received:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_subclass
 *
 * <ol><li>Implement the started callback that is called when the server acknowledges the query,
 * as shown below:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_cb_started
 *
 * <ol><li>Implement the failed callback to be called if there is an error during the query:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_cb_failed
 *
 * <ol><li>Implement the aborted callback to be called when the subscription completes
 * (return code is \c RC_OK) or if an error occurs:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_cb_aborted
 *
 * <ol><li>Implement the \c TradeEventExt callback to be called with real-time events:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_cb_tde
 *
 * <ol><li>Customize the L1 subscription, by using the event mask and other values:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_custom
 *
 * <ol><li>Perform the request:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_req
 *
 * <ol><li>When done, stop the subscription:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_L1_stop
 *
 * **The following describes the tracking features of tag updates**
 *
 * <ol><li>To activate the tracking feature:</li></ol>
 * \snippet perform_subscribe_L1.cpp snippet_sub_L1_track_init
 *
 * <ol><li>Reset the tracking cache before processing trade events:</li></ol>
 * \snippet perform_subscribe_L1.cpp snippet_sub_L1_track_process
 *
 * <ol><li>Then, after updating the instrument's data cache, get only tags of interest:</li></ol>
 * \snippet perform_subscribe_L1.cpp snippet_sub_L1_track_use
 *
 * **The following describes the use of generic tags** (:ref:`generic tags <GenericTags>`) **:**
 *
 * <ol><li>As for :ref:`generic tags <GenericTags>`, here's how you can access the name
 * and description the received values refer to:</li></ol>
 * \snippet perform_subscribe_L1.cpp snippet_sub_L1_generic_tags
 *
 * <ol><li>Here how to access to the :ref:`entry id <GenericTags_Example_1>`, the name and description by :ref:`source id <GenericTags_Example_1>` of the received values:</li></ol>
 * \snippet perform_get_generic_tag_by_source_id.cpp snippet_sub_L1_generic_tags_entry_id_by_source_id
 * \endcond
 */
void perform_subscribe (FeedOS::API::Connection & connection, int argc, char * argv[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe");

	bool opt_time = false;
	if ( (argc > 1) && !strcmp(argv[1],"-t") ) {
		opt_time=true;
		++argv;
		--argc;
	}

	if (argc<2) {
		std::cerr << "? CODES..." << std::endl;
		return;
	}

	// list of instruments we are interested into
	if (!extract_codes (input_codes, argc, argv))	// read them from command-line arguments
		return;

	//![snippet_sub_L1_custom]
	// The list of "other values" that you are interested in (none at this time)
	FeedOS::Types::ListOfQuotationTagNumber otherValues;

	// Declare the events that you are interested in (combination of bits).
	// Use FeedOS::Types::QuotationContentBit_LastPrice to receive only the
	// "last price" events (mainly trades).
	// Use FeedOS::Types::QuotationContentBit_LastTradeQty to receive only the
	// trades. Use | QuotationContentBit_BidOrAsk to add the "best bid" /
	// "best ask" events.
	FeedOS::Types::QuotationContentMask contentMask =
		FeedOS::Types::QuotationContentMask_EVERYTHING;
	//![snippet_sub_L1_custom]

	// "relaxed" behaviour ... don't fail if some codes are invalid
	// (however if only 1 code is provided and it is invalid then the server will refuse the request)
	bool ignoreInvalidCodes=true;

	//![snippet_sub_L1_req]
	// Build the request object (responsible for maintaining the data transfer).
	// The object type is "delegate"; hence it requires an external object to
	// handle the incoming data.
	TradeEventPrinter printer(opt_time);
	FeedOS::API_QUOTATION_SubscribeInstrumentsL1_delegate req(printer);

	// Start the subscription (synchronous version).
	FeedOS::ReturnCode rc = req.sync_start(connection, input_codes, otherValues,
			contentMask, ignoreInvalidCodes);
	//![snippet_sub_L1_req]

// Uncomment to see how to modify an on-going L1 subscription
//#define FEEDOS_DEMONSTRATE_CHG_ADD_REMOVE
#ifdef FEEDOS_DEMONSTRATE_CHG_ADD_REMOVE
	if (FeedOS::RC_OK == rc ) {

		FeatureAddRemoveInstrumentsDemonstrator add_remove_demo(printer.m_ticket, input_codes, ignoreInvalidCodes);
		rc = add_remove_demo.demonstrate(connection);
		if (FeedOS::RC_OK != rc)
		{
			req.stop (); // stop subscription
			return ;
		}
	}
#endif

	//![snippet_sub_L1_stop]
	if (FeedOS::RC_OK != rc )
	{
		std::cerr << "sync_start error, rc=" << FeedOS::error_string(rc)
		<< std::endl;
	}
	else
	{
		getchar(); // Wait for user input.
	}
	req.stop (); // Stop the subscription.
	//![snippet_sub_L1_stop]
}
