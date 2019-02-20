
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TRACE_IMPLEMENTATION_FILE_H
#define FEEDOS_BASE_TRACE_IMPLEMENTATION_FILE_H

#include "trace.h"
#include "lock.h"
#include <stdio.h>

namespace FeedOS {

	// implementation of Trace Facility : log messages in a file
	class TraceImplementation_file: public TraceImplementation
	{
	public:
		TraceImplementation_file (	char const *	logfile,
									bool			append_mode, 
									bool			flush_every_line = true
								);
	private:
		inline void write_sync (unsigned int area, char const * level_str, char const * msg_str);
		void roll_files();
		
		virtual void perform_log (unsigned int area, int level, std::string const & msg);
		virtual void perform_scope (bool entering, unsigned int area, char const * where);

		virtual void hook_shutdown();
		virtual void hook_enable();
		virtual void hook_disable();
		virtual void hook_register_area (unsigned int area, std::string area_name);
		virtual void hook_register_level(int level, std::string level_name);
		
		std::string			m_logfile_path;
		ExclusiveLock		m_logfile_lock;
		FILE *				m_logfile;
		bool				m_flush_every_line;
		std::size_t			m_current_file_size_b;
		unsigned int const	m_roll_file_size_mb;
		unsigned int const	m_roll_max_files;
		bool const			m_do_roll;
	};

}

#endif

