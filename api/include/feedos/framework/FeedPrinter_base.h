
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H
#define FEEDOS_FRAMEWORK_FEED_PRINTER_BASE_H

#ifndef FEEDOS_FRAMEWORK_REVERSE_INSTRUMENT_CODE_MAP_H
#  include "ReverseInstrumentCodeMap.h"
#endif

namespace FeedOS {

	class FeedPrinter_base
	{
	public:
		typedef std::map<FOSLowLevelInstrumentCode,std::string>	FOSInstrumentMapping;

		typedef enum {
			None,
			SecondsSinceUnixEpoch,
			FullDate
		} TimestampMode;

		static TimestampMode	const DEFAULT_output_format_recv_timestamp_mode	= None;	// don't print the receive timestamp
		static TimestampMode	const DEFAULT_output_format_server_timestamp_mode	= FullDate;
		static TimestampMode	const DEFAULT_output_format_market_timestamp_mode	= FullDate;
		static bool				const DEFAULT_output_format_opt_f			= false;	// print price and qty using printf("%f")
		static bool				const DEFAULT_output_print_numeric			= true;
		static bool				const DEFAULT_feed_is_realtime				= true;

		FeedPrinter_base (std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);
		virtual ~FeedPrinter_base() {}

		// call this to signal that some feed is coming
		virtual void init () { m_init_performed = true; }

		// call this to signal that incoming feed is no more coming
		virtual void shutdown () { m_init_performed = false; }

		// change the default output format
		void set_output_format (	TimestampMode recv_timestamp_mode	= DEFAULT_output_format_recv_timestamp_mode, 
									bool opt_f							= DEFAULT_output_format_opt_f,
									bool opt_print_numeric				= DEFAULT_output_print_numeric
								);

		void set_output_format_PRINT_NUMERIC_INSTR_CODES (bool print_numeric);

		void set_output_format_ALL_TIMESTAMPS (TimestampMode all_timestamps_mode);

		void set_output_format_RECV_TIMESTAMP (TimestampMode recv_timestamp_mode);

		// if realtime then the printer will take a "receive timestamp" in every callback
		void set_feed_is_realtime (bool v = DEFAULT_feed_is_realtime);

		// call this to forcibly set the "reception timestamp" (can be used by FeedReplay stuff)
		void force_recv_timestamp (FeedOS::Timestamp const & recv_timestamp_date)
		{
			m_recv_timestamp_date		= recv_timestamp_date;
		}

		FeedOS::Timestamp	const &	get_recv_timestamp() const { return m_recv_timestamp_date; }

		// enable translation of internal instrument codes
		// (by default, unknown instruments are skipped)
		void set_reverse_instr_code_map (ReverseInstrumentCodeMap const & reverse_instr_code_map, bool skip_unknown_instruments = true);

		// cancel translation of internal instrument codes
		void unset_reverse_instr_code_map ();

		// when instr_code_mapping is in effect: number of events filtered out because of unknown instrument code
		unsigned int get_reverse_instr_code_map_failures () const { return m_reverse_instr_code_map_nb_events_with_mapping_failure; }

		class MappedInstrumentCode
		{
		public:
			MappedInstrumentCode ()
			{}

			MappedInstrumentCode (FOSInstrumentCode const & numeric_code, std::string const & mapped_code)
				:m_numeric_code(numeric_code)
				,m_mapped_code(mapped_code)
			{}

			MappedInstrumentCode const & operator= (MappedInstrumentCode const & v)
			{
				m_numeric_code = v.m_numeric_code;
				m_mapped_code = v.m_mapped_code;
				return *this;
			}

			FOSInstrumentCode const &	get_internal_code() const { return m_numeric_code; }
			std::string const &			get_mapped_code() const { return m_mapped_code; }

			bool	has_mapping () const { return !m_mapped_code.empty(); }

		private:
			FOSInstrumentCode	m_numeric_code;
			std::string			m_mapped_code;
		};

		// status of the subscription (after it has been accepted/refused or aborted)
		ReturnCode			get_last_return_code () const { return m_last_return_code; }

		inline void print_tab_and_timestamps_and_instrument (FeedOS::Timestamp const & serverUTCTimestamp, FeedOS::Timestamp const & marketUTCTimestamp, MappedInstrumentCode const & inCode) const
		{
			print_tab_and_timestamps(serverUTCTimestamp,marketUTCTimestamp);
			print_instrument_code (inCode);
		}

	protected:
		bool				m_init_performed;
		std::ostream &		m_outstream;
		bool				m_opt_f;
		bool				m_opt_print_numeric;

		void				set_last_return_code (ReturnCode rc);

		// return false if this instrument should be ignored
		bool translate_instr_code (FOSInstrumentCode const & inCode, MappedInstrumentCode & outCode);

		inline void print_value						(double v) const { print_price (m_outstream, v, false, m_opt_f); }
		inline void print_fosprice					(FeedOS::FOSPrice const & v) const { print_price (m_outstream, v.get(), false, m_opt_f); }

		inline void print_tab_and_value			(double v) const {m_outstream  << '\t'; print_value (v); }
		inline void print_tab_and_timestamps	(FeedOS::Timestamp const & serverUTCTimestamp, FeedOS::Timestamp const & marketUTCTimestamp) const
		{
			print_tab_and_timestamp (m_recv_timestamp_date, m_recv_timestamp_mode);
			print_tab_and_timestamp (serverUTCTimestamp,	m_server_timestamp_mode);
			print_tab_and_timestamp (marketUTCTimestamp,	m_market_timestamp_mode);
		}		

		inline void print_tab_and_timestamps(FeedOS::Timestamp const & server_timestamp) const
		{
			print_tab_and_timestamp (m_recv_timestamp_date, m_recv_timestamp_mode);
			print_tab_and_timestamp (server_timestamp,	m_server_timestamp_mode);
		}

		void print_tab_and_timestamps_legend	() const;

		inline
		void print_instrument_code (MappedInstrumentCode const & inCode) const
		{
			if (inCode.has_mapping()) {
				// print user-defined string
				m_outstream << '\t' << inCode.get_mapped_code();
			} else {
				if (m_opt_print_numeric) {
					// print internal code as a "big integer"
					m_outstream << '\t' << inCode.get_internal_code().get_numeric();
				} else {
					// print internal code the normal way: X/Y
					m_outstream << '\t' << inCode.get_internal_code();
				}
			}
		}

		// If mode is "realtime" then set the recv_timestamp to "now".
		// Call this from all API callbacks.
		void auto_set_recv_timestamp_if_realtime()
		{
			if (m_feed_is_realtime && (m_recv_timestamp_mode != None)) {
				m_recv_timestamp_date.set_to_now_utc();
			}
		}

		inline void print_tab_and_timestamp		(FeedOS::Timestamp const & t, TimestampMode m) const
		{
			switch (m) {
			case None:
				break;
			case FullDate:
				m_outstream << '\t';
				{
					t.dump_full_allow_microsec (m_outstream);
				}
				break;
			case SecondsSinceUnixEpoch:
				m_outstream << '\t';
				{
					unsigned int sec, millisec, microsec;
					t.get_timet (sec, millisec, microsec);
					double const sec_since_epoch = sec + ( millisec + (microsec / 1000.) ) / 1000.;
					m_outstream << sec_since_epoch;
				}
				break;
			}
		}

		void print_tab_and_list_of_values(FeedOS::Types::ListOfQuotationVariable const & values) const;

	private:

		ReturnCode							m_last_return_code;
		bool								m_feed_is_realtime;
		Timestamp							m_recv_timestamp_date;

	protected:
		TimestampMode						m_recv_timestamp_mode;
		TimestampMode						m_server_timestamp_mode;
		TimestampMode						m_market_timestamp_mode;

	private:
		ReverseInstrumentCodeMap const *	m_reverse_instr_code_map;
		bool								m_reverse_instr_code_map_should_serve_as_a_filter;
		unsigned int						m_reverse_instr_code_map_nb_events_with_mapping_failure;
	};


}


#endif


