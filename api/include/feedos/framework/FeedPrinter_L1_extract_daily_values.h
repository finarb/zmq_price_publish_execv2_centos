
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2012      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_L1_EXTRACT_DAILY_VALUES_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_L1_EXTRACT_DAILY_VALUES_H

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#	include "FeedPrinter_base.h"
#endif

#ifndef FEEDOS_deprecated_NOTIF_TradeEvent_H
#	include "../deprecated/deprecated_notif_TradeEvent.h"
#endif

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_2_H
#	include "InstrumentQuotationData_2.h"
#endif

namespace FeedOS {

	class FeedPrinter_L1_extract_daily_values
		: public FeedPrinter_base
		, public FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
	public:
		static bool const DEFAULT_output_format_opt_header						= false;	// print header line

		FeedPrinter_L1_extract_daily_values (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		virtual void init ();
		virtual void shutdown ();

		// change the default output format
		void set_output_format (	bool opt_f								= DEFAULT_output_format_opt_f,
									bool opt_header							= DEFAULT_output_format_opt_header,
									bool opt_print_numeric					= DEFAULT_output_print_numeric
								);

		void set_output_format_HEADER (bool opt_header)
		{
			m_opt_header=opt_header;
		}

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming

	private:
		bool				m_opt_header;

		class MyInstrumentQuotationData: public InstrumentQuotationData_2
		{
		public:
			MyInstrumentQuotationData ()
				:InstrumentQuotationData_2()
				,m_nb_trades(0)
				,m_offbook_nb_trades(0)
			{
			}

			double	m_nb_trades;
			double	m_offbook_nb_trades;
		};

		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSLowLevelInstrumentCode, MyInstrumentQuotationData> InstrDataMap;
		InstrDataMap		m_instr_data_map;

		void flush_instr_values (MappedInstrumentCode const & instr_code, MyInstrumentQuotationData const & instr_data);

	};
}


#endif


