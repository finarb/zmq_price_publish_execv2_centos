
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_deprecated_NOTIF_TradeEvent_H
#define FEEDOS_deprecated_NOTIF_TradeEvent_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	include "../generated/gen_interface_QUOTATION.h"
#	include "../api/tags.h"
#	include "../api/generated_types.h"
#endif

namespace FeedOS {

	template <typename T>
	void notif_TradeEvent_into_TradeEventExt (
														T & target_object,
														FOSInstrumentCode inCode, 
														Timestamp const & inMarketUTCTimestamp,  
														Types::QuotationTradeEvent const & inData,
														Timestamp const & inPseudoServerUTCTimestamp = Timestamp::now_utc()
													)
	{
		Types::ListOfQuotationVariable values;

		if (FEEDOS_QUOT_UPD_CONTENT_HAS(inData.getContentMask(),TradingStatus)) {
			values.push_back ( Types::TagNumAndValue (TAG_TradingStatus, Any((Enum) inData.getTradingStatus())) );
		}

		Types::QuotationTradeEventExt new_data
					(
							inData.getContentMask(),
							convert_basic2ext (inData.getBestBid()),
							convert_basic2ext (inData.getBestAsk()),
							inData.getLastTradeQty(),
							inData.getPrice(),
							Types::ListOfQuotationContextFlag(),
							values
					);

		target_object.notif_TradeEventExt (inCode, inPseudoServerUTCTimestamp, inMarketUTCTimestamp, new_data);
	}


	template <typename T>
	void notif_ValuesUpdate_into_TradeEventExt (
														T & target_object,
														FOSInstrumentCode inCode, 
														Timestamp const & inMarketUTCTimestamp,  
														Types::QuotationValuesUpdate const & inData,
														Timestamp const & inPseudoServerUTCTimestamp = Timestamp::now_utc()
													)
	{
		static Types::OrderBookEntryExt					const dummy_best_limits;
		static Types::ListOfQuotationContextFlag		const dummy_flags;
		static FeedOS::Types::ListOfQuotationVariable	const dummy_variables;
		Types::QuotationTradeEventExt new_data
					(
						Types::QuotationContentBit_OtherValues,
						dummy_best_limits,
						dummy_best_limits,
						0,
						0,
						dummy_flags,
						inData.getValues()
					);

		target_object.notif_TradeEventExt (inCode, inPseudoServerUTCTimestamp, inMarketUTCTimestamp, new_data);
	}


	template <typename T>
	void notif_TradeEventExt_into_TradeEvent (
												T & target_object,
												FOSInstrumentCode inCode,  
												Timestamp const &,
												Timestamp const & inMarketUTCTimestamp,  
												Types::QuotationTradeEventExt const & inData
											)
	{
		Types::QuotationContentMask contentmask = inData.getContentMask();
		contentmask &= ~Types::QuotationContentBit_TradingStatus;

		Types::QuotationTradeEvent old_data
						(
							contentmask,
							Types::FIXSecurityTradingStatus_UNKNOWN,
							convert_ext2basic (inData.getBestBid()),
							convert_ext2basic (inData.getBestAsk()),
							inData.getLastTradeQty(), 
							inData.getPrice()
						);

		target_object.notif_TradeEvent (inCode, inMarketUTCTimestamp, old_data);

		if (!inData.getValues().empty()) {
			target_object.notif_ValuesUpdate (inCode, inMarketUTCTimestamp, Types::QuotationValuesUpdate (inData.getContentMask(), inData.getValues()));
		}
	}


#ifndef FEEDOS_COMPAT_INCLUDE
	class INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming_v14_USE_NEW_NOTIF: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
		// wrapper that calls notif_TradeEventExt()
		void notif_TradeEvent (
								FOSInstrumentCode inCode, 
								Timestamp const & inMarketUTCTimestamp,  
								Types::QuotationTradeEvent const & inData
							)
		{
			notif_TradeEvent_into_TradeEventExt (*this, inCode, inMarketUTCTimestamp, inData);	// use default behaviour for "internal timestamp"
		}
	};

	class INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming_v14_USE_OLD_NOTIF: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
		// wrapper that calls notif_TradeEvent()
		void notif_TradeEventExt (
											FOSInstrumentCode inCode, 
											Timestamp const & inServerUTCTimestamp,
											Timestamp const & inMarketUTCTimestamp,  
											Types::QuotationTradeEventExt const & inData
										)
		{
			notif_TradeEventExt_into_TradeEvent (*this, inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inData);
		}
	};
#endif


}


#endif
