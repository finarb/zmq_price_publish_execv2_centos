
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_POLYMORPHIC_INSTRUMENT_CODE_H
#define FEEDOS_COMM_POLYMORPHIC_INSTRUMENT_CODE_H

#ifndef FEEDOS_COMM_INSTRUMENT_CODE_H
#	include "FOSInstrumentCode.h"
#endif
#ifndef FEEDOS_COMM_LOCAL_INSTRUMENT_CODE_H
#	include "LocalInstrumentCode.h"
#endif

#include <iostream>

namespace FeedOS {

	class PolymorphicInstrumentCode
	{
	public:

		// both forms are invalid
		PolymorphicInstrumentCode()	{}

		// form "internal" is valid
		PolymorphicInstrumentCode (FOSLowLevelInstrumentCode c) :
			m_internal_code (c)
		{}

		// form "internal" is valid
		PolymorphicInstrumentCode (FOSInstrumentCode c) :
			m_internal_code (c)
		{}

		// form "local code" is valid
		PolymorphicInstrumentCode (LocalInstrumentCode const & lc) :
			m_local_code (lc)
		{}

		// both forms are valid
		PolymorphicInstrumentCode (FOSLowLevelInstrumentCode c, LocalInstrumentCode const & lc) :
			m_internal_code (c),
			m_local_code (lc)
		{}

		FOSInstrumentCode const &		get_internal_code() const	{ return m_internal_code; }
		FOSInstrumentCode &				get_internal_code()			{ return m_internal_code; }
		LocalInstrumentCode const &		get_local_code() const	{ return m_local_code; }
		LocalInstrumentCode &			get_local_code()		{ return m_local_code; }

		FOSMarketId	get_market_id		() const 
		{
			if (m_internal_code.is_valid())		return m_internal_code.get_market_id(); 
			else if (m_local_code.is_valid())	return m_local_code.get_market_id();
			else								return MARKET_ID_unknown;
		}

		void set_invalid ()			{ m_internal_code.set_invalid(); m_local_code.set_invalid(); }
		bool is_valid () const		{ return m_internal_code.is_valid() || m_local_code.is_valid(); }

		// assign a value in "internal" form
		void set (FOSLowLevelInstrumentCode c)
		{
			m_internal_code = c;
			get_local_code().set_invalid();
		}

		// assign a value in "local code" form
		void set (LocalInstrumentCode const & lc)
		{
			m_local_code = lc;
			get_internal_code().set_invalid();
		}

		// set both forms at once
		void set (FOSLowLevelInstrumentCode c, LocalInstrumentCode const & lc)
		{
			m_internal_code = c;
			m_local_code = lc;
			check_market_consistency ();
		}

		// set the "local code" form that matches the actual "internal" form
		void merge_local_code (LocalInstrumentCode const & lc)
		{
			if (m_internal_code.is_valid()) {
				m_local_code = lc;
				check_market_consistency ();
			} else {
				set (lc);
			}
		}

		// set the "internal" form that matches the actual "local code" form
		void merge_internal (FOSLowLevelInstrumentCode c)
		{
			if (m_local_code.is_valid()) {
				m_internal_code = c;
				check_market_consistency ();
			} else {
				set (c);
			}
		}

		PolymorphicInstrumentCode const & operator= (PolymorphicInstrumentCode const & v)
		{
			m_internal_code	= v.m_internal_code;
			m_local_code	= v.m_local_code;
			return *this; 
		}

		// warning: INVALID instrument codes cannot be compared
		bool operator< (PolymorphicInstrumentCode const & c) const
		{
			if (m_internal_code.		is_valid() && c.m_internal_code.		is_valid())	
				return m_internal_code	< c.m_internal_code;	// compare both internal forms
			bool ME =   m_local_code.is_valid();
			bool IT = c.m_local_code.is_valid();
			if (ME) {
				if (IT)	{
					return m_local_code	< c.m_local_code;	// compare both local_code forms
				} else {
					return true;
				}
			} else {
				return !IT;
			}
		}

		// warning: INVALID instrument codes are NOT equal 
		bool operator== (PolymorphicInstrumentCode const & c) const
		{
			if (m_internal_code.		is_valid() && c.m_internal_code.		is_valid())	
				return m_internal_code	== c.m_internal_code;	// compare both internal forms
			bool ME =   m_local_code.is_valid();
			bool IT = c.m_local_code.is_valid();
			if (ME && IT)	
				return m_local_code	== c.m_local_code;	// compare both local_code forms
//			if (!ME && !IT)	
//				return m_internal	== c.m_internal;	// return true if both are invalid
			return false;
		}
		bool operator== (FOSInstrumentCode const & c) const
		{
			return m_internal_code.is_valid() && (m_internal_code == c);
		}
		bool operator== (LocalInstrumentCode const & c) const
		{
			return m_local_code.is_valid() && (m_local_code == c);
		}

		template<typename T>
		bool operator!= (T const & c) const { return ! operator== (c); }

		// warning: INVALID instrument codes are NOT equal 
		bool operator== (FOSLowLevelInstrumentCode const & c) const
		{
			return (m_internal_code.is_valid() /*|| !m_local_code.is_valid()*/) && (get_internal_code() == c);
		}

		// dump in format:   
		//					<market_id>:<str_local_code>			when local_code_is_valid()
		//					<market_id>/<num_local_code>			else
		void dump (std::ostream & os) const;

		std::string to_str() const;

		// format expected: 
		//	(PREFERRED)		<market_id>:<str_local_code>			=> [numeric]market + string
		//					<market_id>/<num_local_code>			=> [numeric]market + numeric
		//					<full_numeric_code>						=> int
		bool read_from_string (std::string const & s);

		static PolymorphicInstrumentCode build_from_string (std::string const & s);
		/*
		// for use with hash maps
		struct Hash {
			size_t operator () (PolymorphicInstrumentCode const & c) const {
				LocalInstrumentCode::Hash h;
				return c.get_internal_code() ^ h (c.get_local_code());
			}
		};
		*/
	private:
		void do_check_market_consistency ();
#if FEEDOS_ENABLE_PARANOID_CHECKS || !defined FEEDOS_COMPAT_INCLUDE
		inline void check_market_consistency () { do_check_market_consistency(); }
#else
		inline void check_market_consistency () {}
#endif

		FOSInstrumentCode		m_internal_code;
		LocalInstrumentCode		m_local_code;
	};

}


inline std::ostream & operator<< (std::ostream & os, FeedOS::PolymorphicInstrumentCode const & v)
{
	v.dump (os);
	return os; 
}


#endif
