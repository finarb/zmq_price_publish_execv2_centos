
/******************************/
/** FeedOS C++ Client API				**/
/**												**/
/** copyright QuantHouse 2005-2009	**/
/**												**/
/******************************/

#ifndef FEEDOS_COMM_INTEGER_H
#define FEEDOS_COMM_INTEGER_H

#ifndef FEEDOS_BASE_BASE_H
#	include "../base/base.h"
#endif

#include <iostream>

namespace FeedOS {

	typedef int64 FOSLowLevelInteger;

	class FOSInteger
	{
	public:
		inline FOSInteger() : m_num (0) {}
		inline FOSInteger(FOSLowLevelInteger const & v) : m_num (v) {}
		inline FOSInteger(FOSInteger const & v) : m_num (v.m_num) {}
		inline FOSInteger const & operator= (FOSInteger const & v) { m_num = v.m_num; return *this; }
		inline FOSInteger const & operator= (FOSLowLevelInteger const & v) { m_num = v; return *this; }
		operator FOSLowLevelInteger () const { return m_num; }

		bool operator== (FOSLowLevelInteger const & v) const		{ return m_num == v; }
		bool operator!= (FOSLowLevelInteger const & v) const		{ return m_num != v; }
		bool operator<  (FOSLowLevelInteger const & v) const		{ return m_num <  v; }
		bool operator<= (FOSLowLevelInteger const & v) const		{ return m_num <= v; }
		bool operator>  (FOSLowLevelInteger const & v) const		{ return m_num >  v; }
		bool operator>= (FOSLowLevelInteger const & v) const		{ return m_num >= v; }

		FOSLowLevelInteger operator+= (FOSLowLevelInteger const & v){ return m_num += v; }
		FOSLowLevelInteger operator-= (FOSLowLevelInteger const & v){ return m_num -= v; }
		FOSLowLevelInteger operator*= (FOSLowLevelInteger const & v){ return m_num *= v; }

		inline void set (FOSLowLevelInteger v) { m_num = v; }
		inline FOSLowLevelInteger get () const { return m_num; }
		inline FOSLowLevelInteger & ref () { return m_num; }

		void dump (std::ostream & os) const { os << m_num; }

		bool read_from_string (std::string const & s);

	private:
		FOSLowLevelInteger	m_num;
	};

}


inline
std::ostream & operator<< (std::ostream & os, FeedOS::FOSInteger const & v)
{
	v.dump(os);
	return os;
}


#endif
