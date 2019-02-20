
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_EXCEPTIONS_H
#define FEEDOS_COMM_EXCEPTIONS_H

#include <stdexcept>

namespace FeedOS {

	class Exception: public std::exception
	{
	public:
		Exception (std::string const & s) : m_what(s) {}
		virtual ~Exception () throw () {}
		virtual const char *what() const throw () { return m_what.c_str(); }
	private:
		std::string	m_what;
	};

	class ProtocolError: public Exception
	{
	public:
		ProtocolError (std::string const & s) : Exception(s) {}
	};


}


#endif

