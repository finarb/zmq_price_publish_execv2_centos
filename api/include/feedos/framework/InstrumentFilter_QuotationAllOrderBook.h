
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_ORDER_BOOK_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_ORDER_BOOK_H

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "../generated/gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#	include "../comm/MulticastFeedTools.h"
#endif

namespace FeedOS {

	class InstrumentFilter_QuotationAllOrderBook : public FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming
	{
	public:
		InstrumentFilter_QuotationAllOrderBook (	FeedFilterInstrumentSet &		instr_filter,
													INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer);
		virtual ~InstrumentFilter_QuotationAllOrderBook ();
			
		// accessor for target object
		inline INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming &	get_consumer() { return m_consumer; }
		
		// accessor for filter object
		inline FeedFilterInstrumentSet &	get_filterInstrumentsSet() { return m_filteredInstruments; }

	private:
		InstrumentFilter_QuotationAllOrderBook(InstrumentFilter_QuotationAllOrderBook const &);
		InstrumentFilter_QuotationAllOrderBook const & operator=(InstrumentFilter_QuotationAllOrderBook const &);

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming
		INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming &	m_consumer;

		FeedFilterInstrumentSet &		m_filteredInstruments;
	};
	
} // namespace FeedOS

#endif // FEEDOS_FRAMEWORK_INSTRUMENT_FILTER_QUOTATION_ALL_ORDER_BOOK_H
