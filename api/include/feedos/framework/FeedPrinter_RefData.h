
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2013      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_REF_DATA_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_REF_DATA_H

#include "FeedPrinter_base.h"

namespace FeedOS
{
	class FeedPrinter_RefData: public FeedPrinter_base,
							   public INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming
	{
	public:
		static bool const DEFAULT_output_format_opt_header = false;

		FeedPrinter_RefData(std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		void init();

		void set_output_format(TimestampMode recv_timestamp_mode = DEFAULT_output_format_recv_timestamp_mode, 
							   bool opt_f = DEFAULT_output_format_opt_f,
							   bool opt_header = DEFAULT_output_format_opt_header,
							   bool opt_print_numeric = DEFAULT_output_print_numeric);

		void set_output_format_HEADER(bool opt_header)
		{
			m_OptHeader = opt_header;
		}

		FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming

	protected:
		void print_list_of_instrument_characteristics(std::string const & event_type, ListOfInstrumentCharacteristics const & inInstruments);

	private:
		bool	m_OptHeader;
	};

}

#endif


