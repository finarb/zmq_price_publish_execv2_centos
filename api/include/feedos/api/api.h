
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_API_H
#define FEEDOS_API_API_H

#ifndef FEEDOS_BASE_BASE_H
#  include "../base/base.h"
#endif

#ifndef FEEDOS_API_TAGS_H
#  include "tags.h"
#endif

#ifndef FEEDOS_API_API_VERSION_H
#  include "api_version.h"
#endif

#ifndef FEEDOS_API_TCP_PROXY_SERVER_H
#  include "TCPProxyServer.h"
#endif

#ifndef FEEDOS_API_SIMPLE_PROXY_SERVER_H
#  include "SimpleProxyServer.h"
#endif

#ifndef FEEDOS_BASE_TRACE_H
#  include "../base/trace.h"			// for macros FEEDOS_LOG and FEEDOS_SCOPER
#endif

#ifndef FEEDOS_API_REFERENTIAL_H
#  include "api_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_QUOTATION_H
#  include "api_QUOTATION.h"
#endif

#ifndef FEEDOS_API_CONNECTION_H
#  include "api_CONNECTION.h"
#endif

#ifndef FEEDOS_API_RISK_H
#  include "api_RISK.h"
#endif

#ifndef FEEDOS_API_NEWS_H
#  include "api_NEWS.h"
#endif

namespace FeedOS {

	namespace API {

		// short names for the classes used to establish network connection
		typedef TCPProxyServer Connection;
		typedef SimpleProxyServer SimpleConnection;

		// init the API.
		// Requires the name of the current application
		ReturnCode init (char const * user_application_name);

		// shutdown the API
		void shutdown ();

		// load metadata form server and register tags and enums
		// synhronous request/response
		ReturnCode sync_download_metadata(ProxyServer & s);
		// asynhronous request/response
		void async_download_metadata(ProxyServer & s);

		// make current thread to sleep (in milliseconds)
		void msleep (unsigned int millisec);

		// make current thread to sleep (in seconds)
		void sleep  (unsigned int sec);

		// OPTIONAL: enable rolling of logging files
		void init_trace_file_rolling(unsigned int log_max_file_size_mb, unsigned int log_max_nb_files);
		
		// OPTIONAL: init trace facility (simple configuration: dump "errors" and "info" messages in a file)
		ReturnCode init_trace_all_areas (	std::string const & logfile,
											bool append_mode			= true, 
											bool flush_every_line		= true,
											bool enable_error_levels	= true,
											bool enable_warning_level	= true,
											bool enable_info_level		= true, 
											bool enable_debug_levels	= false, 
											bool enable_scope_level		= false
										);

		// OPTIONAL: trace facility: setup specific config for USER area
		ReturnCode init_trace_user_area (	bool enable_error_levels	= true,
											bool enable_warning_level	= true,
											bool enable_info_level		= true, 
#ifdef _DEBUG
											bool enable_debug_levels	= true, 
											bool enable_scope_level		= true
#else
											bool enable_debug_levels	= false, 
											bool enable_scope_level		= false
#endif
										);

	}
}


#endif
