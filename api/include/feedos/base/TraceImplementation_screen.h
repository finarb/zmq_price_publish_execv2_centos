
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TRACE_IMPLEMENTATION_SCREEN_H
#define FEEDOS_BASE_TRACE_IMPLEMENTATION_SCREEN_H

#include "trace.h"

namespace FeedOS {

	// implementation of Trace Facility : log messages in a file
	class TraceImplementation_screen: public TraceImplementation
	{
	public:
		TraceImplementation_screen (// TODO: have different "modes" (stderr, curses, ...)
									bool	print_error		= true,
									bool	print_warning	= true,
									bool	print_info		= false,
									bool	print_debug		= false,
									bool	print_scope		= false
									);
	private:
		virtual void perform_log (unsigned int area, int level, std::string const & msg);
		virtual void perform_scope (bool entering, unsigned int area, char const * where);

		virtual void hook_shutdown();
		virtual void hook_enable();
		virtual void hook_disable();
		virtual void hook_register_area (unsigned int area, std::string area_name);
		virtual void hook_register_level(int level, std::string level_name);

		bool	m_print_error;
		bool	m_print_warning;
		bool	m_print_info;
		bool	m_print_debug;
		bool	m_print_scope;
	};

}

#endif

