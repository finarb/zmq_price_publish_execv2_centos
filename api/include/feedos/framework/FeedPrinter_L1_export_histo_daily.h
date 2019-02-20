/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2013      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FEED_PRINTER_L1_EXPORT_HISTO_DAILY_H
#define FEEDOS_FEED_PRINTER_L1_EXPORT_HISTO_DAILY_H

#include "FeedPrinter_base.h"

#include "InstrumentQuotationData_2.h"

#include <fstream>

namespace FeedOS {

	class FeedPrinter_L1_export_daily_histo
		: public FeedPrinter_base
		, public FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
	public:
		FeedPrinter_L1_export_daily_histo(std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();
		virtual void shutdown ();

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming

	private:
		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSInstrumentCode, InstrumentQuotationData_2, FOSInstrumentCode::Hash> InstrDataMap;
		InstrDataMap m_instr_data_map;

		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSInstrumentCode, std::ofstream*, FOSInstrumentCode::Hash> FileMap;
		FileMap m_file_map;

		bool m_opt_header;

		void flush_instr_values (MappedInstrumentCode const & instr_code, InstrumentQuotationData_2 const & instr_data);
		void print_header(std::ostream & outstream);
	};
}

#endif /* FEEDOS_FEED_PRINTER_L1_EXPORT_HISTO_DAILY_H */
