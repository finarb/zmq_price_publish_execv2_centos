
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_TYPES_H
#define FEEDOS_COMM_TYPES_H

#ifndef FEEDOS_BASE_DATE_H
#	include "../base/date.h"
#endif

#ifndef FEEDOS_COMM_ERRORS_H
#	include "errors.h"
#endif

#ifndef FEEDOS_COMM_POLYMORPHIC_INSTRUMENT_CODE_H
#	include "PolymorphicInstrumentCode.h"
#endif

#ifndef FEEDOS_COMM_INTEGER_H
#	include "FOSInteger.h"
#endif

#ifndef FEEDOS_COMM_QTY_H
#	include "FOSQty.h"
#endif

#ifndef FEEDOS_COMM_PRICE_H
#	include "FOSPrice.h"
#endif

#ifndef FEEDOS_BASE_REF_COUNT_BUFFER_H
#	include "../base/refcount_buffer.h"
#endif


namespace FeedOS {

	// used to uniquely identify a sequence of related messages (request/response/[notifs])
	typedef unsigned int RequestNumber;

	// for enumerated values
	class Enum
	{
	public:
		Enum () : m_value(0) {}
		explicit Enum (unsigned int v) : m_value(v) {}
		Enum (Enum const & v) : m_value(v.m_value) {}
		Enum const& operator= (unsigned int v) { m_value=v; return *this; }
		Enum const& operator= (Enum const & v) { m_value=v.m_value; return *this; }
		operator unsigned int () const { return m_value; }
		bool operator== (Enum const & v) const { return m_value==v.m_value; }
		bool operator!= (Enum const & v) const { return m_value!=v.m_value; }
		bool operator<  (Enum const & v) const { return m_value<v.m_value; }
	private:
		unsigned int m_value;
	};

	// string type
	typedef std::string String;

	// binary buffer: not supported here
	typedef refcount_buffer BinaryBuffer;
}


#endif


#ifndef FEEDOS_COMM_ANY_H
#	include "Any.h"
#endif
