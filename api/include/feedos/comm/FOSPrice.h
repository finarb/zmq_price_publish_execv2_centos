
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_PRICE_H
#define FEEDOS_COMM_PRICE_H

#ifndef FEEDOS_BASE_BASE_H
#	include "../base/base.h"
#endif

#include <iostream>

namespace FeedOS {

	namespace Types {
		static double const UNQUOTED						= 666666.666;	// used when price or quantity is unknown (in history requests)
		static double const ORDERBOOK_MAGIC_PRICE_AT_BEST	= 999999.999;
		static double const ORDERBOOK_MAGIC_PRICE_AT_OPEN	= 999999.989;
		static double const ORDERBOOK_MAGIC_PRICE_AT_CLOSE	= 999999.988;
		static double const ORDERBOOK_MAGIC_PRICE_PEG		= 999999.979;
	}

	typedef float64	FOSLowLevelPrice;

	class FOSPrice
	{
	public:
		inline FOSPrice() : m_num (0) {}
		inline FOSPrice(FOSLowLevelPrice const & v) : m_num (v) {}
		inline FOSPrice(FOSPrice const & v) : m_num (v.m_num) {}
		inline FOSPrice const & operator= (FOSPrice const & v) { m_num = v.m_num; return *this; }
		inline FOSPrice const & operator= (FOSLowLevelPrice const & v) { m_num = v; return *this; }
		operator FOSLowLevelPrice () const { return m_num; }

		bool operator== (FOSLowLevelPrice const & v) const		{ return m_num == v; }
		bool operator!= (FOSLowLevelPrice const & v) const		{ return m_num != v; }
		bool operator<  (FOSLowLevelPrice const & v) const		{ return m_num <  v; }
		bool operator<= (FOSLowLevelPrice const & v) const		{ return m_num <= v; }
		bool operator>  (FOSLowLevelPrice const & v) const		{ return m_num >  v; }
		bool operator>= (FOSLowLevelPrice const & v) const		{ return m_num >= v; }

		inline void set (FOSLowLevelPrice v) { m_num = v; }
		inline FOSLowLevelPrice get () const { return m_num; }

		inline bool is_orderbook_at_best () const { return m_num == Types::ORDERBOOK_MAGIC_PRICE_AT_BEST;}
		inline bool is_orderbook_at_open () const { return m_num == Types::ORDERBOOK_MAGIC_PRICE_AT_OPEN;}
		inline bool is_orderbook_at_close () const { return m_num == Types::ORDERBOOK_MAGIC_PRICE_AT_CLOSE;}
		inline bool is_orderbook_peg_price () const { return m_num == Types::ORDERBOOK_MAGIC_PRICE_PEG;}

		inline bool isMagic () const {
			return (   is_orderbook_at_best ()
					|| is_orderbook_at_open ()
					|| is_orderbook_at_close ()
					|| is_orderbook_peg_price ());
		}

		inline static bool isMagic (FOSLowLevelPrice price) {
			return (FOSPrice (price).isMagic ());
		}

		void dump (std::ostream & os) const;
		std::string to_str() const;

		bool read_from_string (std::string const & s);

		static FOSPrice	build_from_string (std::string const & v);

	private:
		FOSLowLevelPrice	m_num;
	};

}


inline
std::ostream & operator<< (std::ostream & os, FeedOS::FOSPrice const & v)
{
	v.dump(os);
	return os;
}


#endif
