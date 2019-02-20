
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_FEEDSTATUS_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_FEEDSTATUS_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

namespace FeedOS {

	class FeedPrinter_FeedStatus_base:	public FeedPrinter_base
	{
	public:
		static bool const DEFAULT_output_format_opt_header	= false;	// print header line

		FeedPrinter_FeedStatus_base (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();

		// change the default output format
		void set_output_format (	TimestampMode recv_timestamp_mode		= DEFAULT_output_format_recv_timestamp_mode, 
									bool opt_header							= DEFAULT_output_format_opt_header
								);

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

//		FEEDOS_GEN_DECL_INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming

	private:
		bool				m_opt_header;

	};



	class FeedPrinter_FeedStatus:	public FeedPrinter_FeedStatus_base,
									public FeedOS::INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
	{
	public:
		FeedPrinter_FeedStatus (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime)
			: FeedPrinter_FeedStatus_base (outstream, feed_is_realtime)
		{}

		FEEDOS_GEN_DECL_INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
	};


}


#endif


