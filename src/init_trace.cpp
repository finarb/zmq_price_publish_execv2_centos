#include <feedos/base/TraceConfiguration_basic.h>
#include <feedos/base/TraceImplementation_aggregator.h>
#include <feedos/base/TraceImplementation_file.h>
#include <feedos/base/TraceImplementation_screen.h>



// this piece of code enables the (optional) FeedOS TraceFacility
//
// - all trace messages are written to file "sample.log"
// - warning/error messages are written to screen, too (on stderr)
//

void init_trace()
{
	// what "severity levels" are enabled
	bool enable_error_levels	= true;	
	bool enable_warning_level	= true;	
	bool enable_info_level		= true;
	bool enable_debug_levels	= true; 
	bool enable_scope_level		= true;

	// what "severity levels" means writing to screen
	bool	screen_print_error		= true;
	bool	screen_print_warning	= true;
	bool	screen_print_info		= false;
	bool	screen_print_debug		= false;
	bool	screen_print_scope		= false;

	// configuration of log file
	char const * logfile_name = "sample.log";
	bool	append_to_existing_logfile	=	false;
	bool	flush_every_line_in_logfile	=	true;

	static FeedOS::TraceImplementation_screen trace_impl_screen (
																screen_print_error,
																screen_print_warning,
																screen_print_info,	
																screen_print_debug,	
																screen_print_scope
																);

	static FeedOS::TraceImplementation_file trace_impl_file (logfile_name, 
															append_to_existing_logfile,
															flush_every_line_in_logfile
															);

	static FeedOS::TraceImplementation_aggregator trace_impl; 
	trace_impl.add_implementation (trace_impl_screen);
	trace_impl.add_implementation (trace_impl_file);

	static FeedOS::TraceConfiguration_basic trace_config;

	FeedOS::TraceFacility::init (trace_config, trace_impl);
	trace_config.set_levels_for_registered_areas (	enable_error_levels,
													enable_warning_level,
													enable_info_level,	
													enable_debug_levels,
													enable_scope_level 
												);

	{
		// no need to dump low-level data going through the network
		std::set<unsigned int>	areas;
		areas.insert (FEEDOS_TRACE_AREA_NetworkIncomingData);
		areas.insert (FEEDOS_TRACE_AREA_NetworkOutgoingData);
		std::set<int> levels;
		levels.insert (FEEDOS_TRACE_LEVEL_MoreDebug);
		levels.insert (FEEDOS_TRACE_LEVEL_FullDebug);
		trace_config.set_levels_for_areas (false, areas, levels);
	}


	//////////////////////////////////////////////////////////////////
	//
	// an example of defining a new AREA (for user code)
	//
	//////////////////////////////////////////////////////////////////
	static unsigned int const FEEDOS_TRACE_AREA_Foo = FEEDOS_TRACE_AREA_User + 1;	// this should be put in some header file

	FeedOS::TraceFacility::register_area (FEEDOS_TRACE_AREA_Foo, "USER_MAIN");
	trace_config.set_levels_for_area (	FEEDOS_TRACE_AREA_Foo,
										true,
										true,	
										true,
										true 
									);
	//////////////////////////////////////////////////////////////////



	FeedOS::TraceFacility::enable();
	FEEDOS_LOG (Foo, Info, "init_trace() called ... testing newly-defined trace area");
}
