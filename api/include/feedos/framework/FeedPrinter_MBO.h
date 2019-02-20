
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_MBO_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_MBO_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

namespace FeedOS {

	class FeedPrinter_MBO_base:	public FeedPrinter_base
	{
	public:
		static bool const DEFAULT_output_format_opt_header						= false;	// print header line

		FeedPrinter_MBO_base (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();

		// change the default output format
		void set_output_format (	TimestampMode recv_timestamp_mode		= DEFAULT_output_format_recv_timestamp_mode, 
									bool opt_f								= DEFAULT_output_format_opt_f,
									bool opt_header							= DEFAULT_output_format_opt_header,
									bool opt_print_numeric					= DEFAULT_output_print_numeric
								);

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming

		void print_snapshot (FOSInstrumentCode const & inCode,
							 Timestamp const & inServerUTCTimestamp,
							 Timestamp const & inMarketUTCTimestamp,
							 Types::MarketSheet const & inSnapshot,
							 Types::ListOfQuotationVariable const & inValues);

	private:
		bool				m_opt_header;

	};



	class FeedPrinter_MBO_all:	public FeedPrinter_MBO_base,
								public FeedOS::INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
	{
	public:
		FeedPrinter_MBO_all (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_MBO_base (outstream, feed_is_realtime)
		{}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
	};


	class FeedPrinter_MBO_one_instrument:	public FeedPrinter_MBO_base,
											public FeedOS::INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming
	{
	public:
		FeedPrinter_MBO_one_instrument (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_MBO_base (outstream, feed_is_realtime)
		{}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming
	};


}


#endif


