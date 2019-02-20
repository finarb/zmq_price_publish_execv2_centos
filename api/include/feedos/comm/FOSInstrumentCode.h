
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_INSTRUMENT_CODE_H
#define FEEDOS_COMM_INSTRUMENT_CODE_H

#ifndef FEEDOS_COMM_MARKET_ID_H
#	include "FOSMarketId.h"
#endif

#include <string>

namespace FeedOS {

	typedef uint32	FOSLowLevelInstrumentCode;
	static FOSLowLevelInstrumentCode const	INVALID_INSTRUMENT_CODE = 0;

	static unsigned int const				INSTRUMENT_CODE_RESERVED_BITS	= 2;	
	static unsigned int const				INSTRUMENT_CODE_RESERVED_POS	= 30;
	static FOSLowLevelInstrumentCode const	INSTRUMENT_CODE_RESERVED_MASK	= 0xC0000000;

	static unsigned int const				INSTRUMENT_CODE_MARKET_BITS		= 9;	
	static unsigned int const				INSTRUMENT_CODE_MARKET_POS		= 21;
	static FOSLowLevelInstrumentCode const	INSTRUMENT_CODE_MARKET_MASK		= 0x3FE00000;

	static unsigned int const				INSTRUMENT_CODE_LOCALCODE_BITS	= 21;
	static unsigned int const				INSTRUMENT_CODE_LOCALCODE_POS	= 0;
	static FOSLowLevelInstrumentCode const	INSTRUMENT_CODE_LOCALCODE_MASK	= 0x001FFFFF;

	class FOSInstrumentCode
	{
	public:

		inline FOSInstrumentCode() : m_code (INVALID_INSTRUMENT_CODE) {}
		inline FOSInstrumentCode(FOSLowLevelInstrumentCode c) : m_code (c) { check_code(); }
		inline FOSInstrumentCode(FOSInstrumentCode const & c) : m_code (c.m_code) { check_code(); }
/*		inline FOSInstrumentCode(FOSMarketId market_id, unsigned int local_code_num) : 
			m_code (build_from_market_and_numeric_local_code (market_id,local_code_num)  ) 
		{}
		inline void split (FOSMarketId & market_id, unsigned int & local_code_num) const 
		{
			FOSLowLevelInstrumentCode c=m_code;
			market_id = (FOSMarketId) ((c & INSTRUMENT_CODE_MARKET_MASK)>> INSTRUMENT_CODE_LOCALCODE_BITS);
			local_code_num = c & INSTRUMENT_CODE_LOCALCODE_MASK;
		}
*/
		FOSLowLevelInstrumentCode get_numeric() const { return m_code; }
		operator FOSLowLevelInstrumentCode const & () const { return m_code; }
//		operator FOSLowLevelInstrumentCode & () { return m_code; }

		FOSInstrumentCode const & operator= (FOSLowLevelInstrumentCode const & c) { m_code = c; check_code(); return *this; }
		bool operator== (FOSLowLevelInstrumentCode const & c) const		{ return m_code == c; }
		bool operator!= (FOSLowLevelInstrumentCode const & c) const		{ return ! operator== (c); }
		bool operator<  (FOSLowLevelInstrumentCode const & c) const		{ return m_code < c; }

		FOSInstrumentCode const & operator= (FOSInstrumentCode const & other) { m_code = other.m_code; return *this; }
		bool operator== (FOSInstrumentCode const & other) const		{ return m_code == other.m_code; }
		bool operator!= (FOSInstrumentCode const & other) const		{ return ! operator== (other.m_code); }
		bool operator<  (FOSInstrumentCode const & other) const		{ return m_code <  other.m_code; }

		struct Hash { size_t operator()(FOSInstrumentCode const & s) const { return (FOSLowLevelInstrumentCode)s; } };

		inline bool is_valid () const { return m_code != INVALID_INSTRUMENT_CODE; }
		inline void set_invalid () { m_code = INVALID_INSTRUMENT_CODE; }
		inline bool set (FOSLowLevelInstrumentCode c) { m_code = c; return check_code (); }

		FOSMarketId	get_market_id		() const { return static_cast<FeedOS::FOSLowLevelMarketId> (extract_market (m_code)); }

		static char text_separator () { return '/'; }

		// dump in format:   <market_id>/<local_code>
		void dump (std::ostream & os) const;
		std::string to_str() const;

		// format expected:   <market_id>/<local_code>
		bool read_from_string (std::string const & s);

		static void get_code_range_for_market (FOSMarketId market_id, unsigned int & first_code, unsigned int & last_code)
		{
			first_code = build (market_id, 0);
			last_code  = build (static_cast<FeedOS::FOSLowLevelMarketId> (market_id+1), 0)-1;
		}

	private:
		FEEDOS_INLINE bool check_code();
		void logInvalidInternalCode() const;

	private:
		FOSLowLevelInstrumentCode	m_code;

	public:
		static FOSLowLevelInstrumentCode build (FOSMarketId market_id, unsigned int local_code_num, unsigned int reserved=0) {
			return 
				(reserved		<< INSTRUMENT_CODE_RESERVED_POS) | 
				(market_id		<< INSTRUMENT_CODE_MARKET_POS) | 
				(local_code_num	<< INSTRUMENT_CODE_LOCALCODE_POS);
		}
		static unsigned int extract_reserved	(FOSLowLevelInstrumentCode c) { return (c & INSTRUMENT_CODE_RESERVED_MASK)	>> INSTRUMENT_CODE_RESERVED_POS; }
		static unsigned int extract_market		(FOSLowLevelInstrumentCode c) { return (c & INSTRUMENT_CODE_MARKET_MASK)	>> INSTRUMENT_CODE_MARKET_POS; }
		static unsigned int extract_localcode	(FOSLowLevelInstrumentCode c) { return (c & INSTRUMENT_CODE_LOCALCODE_MASK) >> INSTRUMENT_CODE_LOCALCODE_POS; }
	};

#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/FOSInstrumentCode.inl"
#endif

}


inline std::ostream & operator<< (std::ostream & os, FeedOS::FOSInstrumentCode const & v)
{
	v.dump (os);
	return os; 
}


inline std::istream & operator>> (std::istream & is, FeedOS::FOSInstrumentCode & v) 
{
	std::string s;
	is >> s;
	v.read_from_string (s);
	return is;
}


#endif
