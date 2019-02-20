
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_L2_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_L2_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_ORDER_BOOK_DATA_H
#	include "InstrumentOrderBookData.h"
#endif

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_MBL_DATA_H
#	include "InstrumentMBLData.h"
#endif

#ifndef FEEDOS_deprecated_NOTIF_OrderBookRefresh_H
#	include "../deprecated/deprecated_notif_OrderBookRefresh.h"
#endif


namespace FeedOS {

	class FeedPrinter_L2_base:	public FeedPrinter_base,
								public FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_NEW_NOTIF
	{
	public:
		static bool const DEFAULT_output_format_opt_header				= false;	// print header line
		static bool const DEFAULT_output_format_opt_cache_book			= false;	// true: print entire book after each update
		static int  const DEFAULT_output_format_opt_order_book_depth	= -1;		// means "dump all levels"
		static bool const DEFAULT_output_format_opt_split_into_delta	= false;	// true: split refresh into delta refresh
		static bool const DEFAULT_output_print_user_mapping	= false;	// true: use a tabulated text correspondance file to display instrument identifier 

		static int const CUSTOM_OrderBookDeltaAction_BidOverlapAtLevel = 98;
		static int const CUSTOM_OrderBookDeltaAction_AskOverlapAtLevel = 99;

		FeedPrinter_L2_base (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();

		// change the default output format
		void set_output_format (	TimestampMode recv_timestamp_mode	= DEFAULT_output_format_recv_timestamp_mode, 
									bool opt_f							= DEFAULT_output_format_opt_f,
									bool opt_header						= DEFAULT_output_format_opt_header,
									bool opt_cache_book					= DEFAULT_output_format_opt_cache_book,
									int  opt_order_book_depth			= DEFAULT_output_format_opt_order_book_depth,
									bool opt_split_into_delta			= DEFAULT_output_format_opt_split_into_delta,
									bool opt_print_numeric				= DEFAULT_output_print_numeric
									);

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

		void set_output_format_CACHE_BOOK (bool opt_cache_book)
		{
			m_opt_cache_book=opt_cache_book;
		}

		void set_output_format_ORDER_BOOK_DEPTH(int opt_order_book_depth)
		{
			m_opt_order_book_depth=opt_order_book_depth;
		}

		void set_output_format_DELTA_ONLY(bool opt_split_into_delta)
		{
			m_opt_split_into_delta=opt_split_into_delta;
		}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_NEW_NOTIF

	private:
		bool				m_opt_header;
		bool				m_opt_cache_book;
		int					m_opt_order_book_depth;
		bool				m_opt_split_into_delta;
		
		inline
		void print_tab_and_timestamps_and_instrument_and_layer (FeedOS::UTCTimestamps const & timestamps, OrderBookLayerId const & layer_id, MappedInstrumentCode const & inCode) const
		{
			print_tab_and_timestamps_and_instrument (timestamps.getServer(), timestamps.getMarket(), inCode);
			m_outstream << '\t' << layer_id;
		}

		// New MBL
		inline void notif_MBLRefresh_print_one_side (	char const *	side,
															FeedOS::FOSInteger const & inChangeIndicator, 
															FeedOS::Types::ListOfMBLOrderBookEntry const & inLimits,
															bool dump_values = true
														);

		inline void CUSTOM_notif_MBLDeltaRefresh (MappedInstrumentCode const & mappedCode, FeedOS::Types::MBLDeltaRefresh const & inDelta);

		typedef std::map<FOSLowLevelInstrumentCode, InstrumentMBLData*> MBLCacheMap;
		MBLCacheMap			m_cache_mbl;

		inline InstrumentMBLData & get_or_create_cached_mbl(FOSInstrumentCode inInternalCode);
		inline void print_mbl_layer (MappedInstrumentCode const & inCode, Types::MBLLayer const & layer);
		inline void print_MBL_VUO (	UTCTimestamps const & timestamps,
									OrderBookLayerId layer_id,
									MappedInstrumentCode const & inCode,
									ListOfQuotationVariable const & other_values);
	};


	class FeedPrinter_L2_all:	public FeedPrinter_L2_base
	{
	public:
		FeedPrinter_L2_all (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_L2_base (outstream, feed_is_realtime)
		{}

	};


	class FeedPrinter_L2_instruments:	public FeedPrinter_L2_base,
										virtual public FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming,
										virtual public FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
	{
	public:
		FeedPrinter_L2_instruments (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_L2_base (outstream, feed_is_realtime)
		{}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
	};

}

#endif
