
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_MIXED_L1L2_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_MIXED_L1L2_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_DATA_AND_STATUS_H
#	include "InstrumentFilter_QuotationAllDataAndStatus.h"
#endif

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_ORDER_BOOK_H
#	include "InstrumentFilter_QuotationAllOrderBook.h"
#endif

namespace FeedOS {

	class InstrumentFilter_QuotationAllMixedL1L2 :	public InstrumentFilter_QuotationAllDataAndStatus,
													public InstrumentFilter_QuotationAllOrderBook
	{
	public:

		template<typename T>
		InstrumentFilter_QuotationAllMixedL1L2 (	FeedFilterInstrumentSet &		instr_filter,
													T & consumer_L1_L2)
			:InstrumentFilter_QuotationAllDataAndStatus	(instr_filter, consumer_L1_L2)
			,InstrumentFilter_QuotationAllOrderBook		(instr_filter, consumer_L1_L2)
		{}

		InstrumentFilter_QuotationAllMixedL1L2 (	FeedFilterInstrumentSet &		instr_filter,
													INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & consumer_L1,
													INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer_L2)
			:InstrumentFilter_QuotationAllDataAndStatus	(instr_filter, consumer_L1)
			,InstrumentFilter_QuotationAllOrderBook		(instr_filter, consumer_L2)
		{}
			
		// accessor for target objects
		inline INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming &	get_consumer_L1() { return InstrumentFilter_QuotationAllDataAndStatus::get_consumer(); }
		inline INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming &		get_consumer_L2() { return InstrumentFilter_QuotationAllOrderBook::get_consumer(); }
		
		// accessor for filter object
		inline FeedFilterInstrumentSet &	get_filterInstrumentsSet() { return InstrumentFilter_QuotationAllDataAndStatus::get_filterInstrumentsSet(); }

	};
} // namespace FeedOS

#endif // FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_DATA_AND_STATUS_H
