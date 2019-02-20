
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_L1_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_L1_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

#define FEEDOS_FEED_PRINTER_L1_USE_COMPAT_CLASS	0

#ifndef FEEDOS_deprecated_NOTIF_TradeEvent_H
#	include "../deprecated/deprecated_notif_TradeEvent.h"
#endif

namespace FeedOS {

	class FeedPrinter_L1_base:	public FeedPrinter_base
	{
	public:
		static bool const DEFAULT_output_format_opt_header						= false;	// print header line
		static bool const DEFAULT_output_format_opt_best_limits_cache			= false;	// always print latest ask/bid
		static bool const DEFAULT_output_format_opt_nosignal					= false;	// disable SI lines							
		static bool const DEFAULT_output_format_opt_trade_context_print_raw		= true;		// print raw values in trade "context flags"
		static bool const DEFAULT_output_format_opt_trade_context_print_verbose	= true;		// print verbose values in trade "context flags"
		static bool const DEFAULT_output_format_opt_content_mask				= true;		// print the content mask flags "OCHL"
		static Types::QuotationContentMask const DEFAULT_notif_TradeEventExt_contentmask_filter = Types::QuotationContentMask_EVERYTHING;	// default is to print all events

		FeedPrinter_L1_base (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();

		// change the default output format
		void set_output_format (	TimestampMode recv_timestamp_mode		= DEFAULT_output_format_recv_timestamp_mode, 
									bool opt_f								= DEFAULT_output_format_opt_f,
									bool opt_header							= DEFAULT_output_format_opt_header,
									bool opt_best_limits_cache				= DEFAULT_output_format_opt_best_limits_cache,
									bool opt_nosignal						= DEFAULT_output_format_opt_nosignal,
									bool opt_trade_context_print_raw		= DEFAULT_output_format_opt_trade_context_print_raw,
									bool opt_trade_context_print_verbose	= DEFAULT_output_format_opt_trade_context_print_verbose,
									bool opt_print_numeric					= DEFAULT_output_print_numeric,
									bool opt_content_mask					= DEFAULT_output_format_opt_content_mask
								);

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

		void set_notif_TradeEventExt_contentmask_filter (Types::QuotationContentMask filter = DEFAULT_notif_TradeEventExt_contentmask_filter)
		{
			m_content_mask_filter = filter;
		}

		static inline bool is_realtime_data_present(FeedOS::Types::QuotationTradeEventExt const & inData)
		{
			return 0 != (inData.getContentMask() & ~ (QuotationContentBit_OtherValues|QuotationContentBit_TradingStatus));
		}

		void print_event_type(MappedInstrumentCode const& mappedCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::QuotationTradeEventExt const & inData);
		void print_price_and_last_quantity(FeedOS::Types::QuotationTradeEventExt const &inData);
		void print_best_limits(FeedOS::FOSInstrumentCode const& inInternalCode, FeedOS::Types::QuotationTradeEventExt const &inData);
		void print_content_mask_and_context(FeedOS::Types::QuotationTradeEventExt const & inData);
		void print_values_update(FeedOS::Types::QuotationTradeEventExt const &inData, MappedInstrumentCode const& mappedCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp);


		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming

	private:
		bool				m_opt_header;
		bool				m_opt_best_limits_cache;
		bool				m_opt_nosignal;
		bool				m_opt_trade_context_print_raw;
		bool				m_opt_trade_context_print_verbose;
		bool				m_opt_content_mask;

		Types::QuotationContentMask	m_content_mask_filter;
		bool				m_force_old_TE_kind;
		bool				m_force_old_VU_kind;

		inline
		void print_best_limits_one_side (FeedOS::Types::OrderBookEntryExt const & e);		

		void process_TradeEventExt_signal  (	MappedInstrumentCode const & mappedCode, 
												Timestamp const & inServerUTCTimestamp,
												Timestamp const & inMarketUTCTimestamp,  		
												FeedOS::Types::QuotationTradeEventExt const & inData
											);

		void process_ValuesUpdate (		MappedInstrumentCode const & mappedCode, 
										Timestamp const & inServerUTCTimestamp, 
										Timestamp const & inMarketUTCTimestamp, 
//										QuotationContentMask mask,
										FeedOS::Types::ListOfQuotationVariable const & values
									);
		
		typedef std::/*hash_*/map<FOSLowLevelInstrumentCode, OrderBookBestLimitsExt>	BestLimitsCacheMap;
		BestLimitsCacheMap			m_cache_best_limits;
	};


	class FeedPrinter_L1_all:	public FeedPrinter_L1_base,
#if FEEDOS_FEED_PRINTER_L1_USE_COMPAT_CLASS
							public FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming_COMPATIBILITY_v14
#else
							public FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
#endif
	{
	public:
		FeedPrinter_L1_all (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_L1_base (outstream, feed_is_realtime)
		{}
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	};


	class FeedPrinter_L1_instruments:	
							public FeedPrinter_L1_base,
							public FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming
	{
	public:
		FeedPrinter_L1_instruments (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_L1_base (outstream, feed_is_realtime)
		{}
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming
	};

}


#endif


