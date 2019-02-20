
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TRACE_CONFIGURATION_BASIC_H
#define FEEDOS_BASE_TRACE_CONFIGURATION_BASIC_H

#include "trace.h"

namespace FeedOS {

	// offers basic configuration of TraceFacility
	class TraceConfiguration_basic: public TraceConfiguration
	{
	public:
		TraceConfiguration_basic ();

		static void set_levels_for_area (	unsigned int area,
											bool enable_error_levels	= true,
											bool enable_warning_level	= true,
											bool enable_info_level		= true, 
											bool enable_debug_levels	= false,
											bool enable_scope_level		= false
											);

		static void set_levels_for_areas (	std::set<unsigned int> const & areas,
											bool enable_error_levels	= true,
											bool enable_warning_level	= true,
											bool enable_info_level		= true, 
											bool enable_debug_levels	= false,
											bool enable_scope_level		= false
											);

		static void set_levels_for_areas (	bool enabled,
											std::set<unsigned int> const & areas,
											std::set<int> const & levels
											);

		static void set_levels_for_registered_areas (	bool enable_error_levels	= true,
														bool enable_warning_level	= true,
														bool enable_info_level		= true, 
														bool enable_debug_levels	= false, 
														bool enable_scope_level		= false
														);

		static void set_level_for_registered_areas (	int level,
														bool enable = true
														);

	private:
		virtual void hook_shutdown();
		virtual void hook_enable();
		virtual void hook_disable();
		virtual void hook_register_area (unsigned int area, std::string area_name);
		virtual void hook_register_level(int level, std::string level_name);
	};

}

#endif

