
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_LOCAL_INSTRUMENT_CODE_H
#define FEEDOS_COMM_LOCAL_INSTRUMENT_CODE_H

#ifndef FEEDOS_COMM_MARKET_ID_H
#	include "FOSMarketId.h"
#endif

#include <string>


namespace FeedOS {

	class LocalInstrumentCode
	{
	public:

		// invalid
		LocalInstrumentCode() : 
			m_market_id (MARKET_ID_unknown)
		{}

		LocalInstrumentCode (FOSMarketId market_id, std::string const & local_code_str) :
			m_market_id (market_id),
			m_local_code_str (local_code_str)
		{
			check_market_id();
		}

		inline void set_invalid()		{	m_market_id = MARKET_ID_unknown; m_local_code_str.clear(); }
		inline bool is_valid() const	{ return !m_local_code_str.empty(); }

		inline bool set (FOSMarketId market_id, std::string const & local_code_str)
		{
			m_market_id = market_id;
			m_local_code_str = local_code_str;
			return check_market_id();
		}

		inline void get (FOSMarketId & market_id, std::string & local_code_str) const
		{
			market_id  = m_market_id;
			local_code_str = m_local_code_str;
		}

		inline FOSMarketId get_market_id () const { return m_market_id; }
		inline std::string get_local_code_str () const { return m_local_code_str; }

		LocalInstrumentCode const & operator= (LocalInstrumentCode const & v)
		{
			m_market_id		= v.m_market_id;
			m_local_code_str	= v.m_local_code_str;
			return *this; 
		}

		inline bool operator< (LocalInstrumentCode const & c) const
		{
			if (m_market_id < c.m_market_id) return true;
			if (m_market_id > c.m_market_id) return false;
			return (m_local_code_str < c.m_local_code_str);
		}

		inline bool operator== (LocalInstrumentCode const & c) const
		{
			return (m_market_id == c.m_market_id) && (m_local_code_str == c.m_local_code_str);
		}
		inline bool operator!= (LocalInstrumentCode const & c) const { return ! operator== (c); }

		static char text_separator () { return '@'; }

		// dump in format:   
		//					<market_id>@<str_local_code>
		void dump (std::ostream & os) const;
		std::string to_str() const;

		// format expected: 
		//					<market_id>@<str_local_code>			=> [numeric]market + string
		bool read_from_string (std::string const & s);

		// for use with hash maps
		struct Hash {
			size_t operator () (LocalInstrumentCode const & c) const {
				FEEDOS_STLEXT_NAMESPACE::hash<std::string> hasher;
				return ((size_t) c.get_market_id()) ^ hasher (c.get_local_code_str());
			}
		};

	private:
		bool check_market_id();

		FOSMarketId		m_market_id;
		std::string		m_local_code_str;
	};

}


inline std::ostream & operator<< (std::ostream & os, FeedOS::LocalInstrumentCode const & v)
{
	v.dump (os);
	return os; 
}


#endif
