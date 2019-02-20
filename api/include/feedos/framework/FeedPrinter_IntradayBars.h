
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_INTRADAYBARS_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_INTRADAYBARS_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

namespace FeedOS {

	class FeedPrinter_IntradayBars:	public FeedPrinter_base,
									public FeedOS::INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming
	{
	public:
		static bool const DEFAULT_output_format_opt_header						= false;	// print header line

		FeedPrinter_IntradayBars (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

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

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming

	private:
		bool				m_opt_header;

		void print_bar(std::string const & header, MappedInstrumentCode const & mapped_code, QuotationIntradayBar const & bar);
	};

}


#endif


