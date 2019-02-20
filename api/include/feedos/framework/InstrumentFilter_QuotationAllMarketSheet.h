
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_MARKET_SHEET_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_MARKET_SHEET_H

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "../generated/gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#	include "../comm/MulticastFeedTools.h"
#endif

namespace FeedOS {

	class InstrumentFilter_QuotationAllMarketSheet : public FeedOS::INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
	{
	public:
		InstrumentFilter_QuotationAllMarketSheet (	FeedFilterInstrumentSet &		instr_filter,
													INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming & consumer);
		virtual ~InstrumentFilter_QuotationAllMarketSheet ();
			
		// accessor for target object
		inline INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming &	get_consumer() { return m_consumer; }
		
		// accessor for filter object
		inline FeedFilterInstrumentSet &	get_filterInstrumentsSet() { return m_filteredInstruments; }

	private:
		InstrumentFilter_QuotationAllMarketSheet(InstrumentFilter_QuotationAllMarketSheet const &);
		InstrumentFilter_QuotationAllMarketSheet const & operator=(InstrumentFilter_QuotationAllMarketSheet const &);
	
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
		INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming &	m_consumer;

		FeedFilterInstrumentSet &		m_filteredInstruments;
	};
} // namespace FeedOS

#endif // FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_DATA_AND_STATUS_H
