
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TRACE_IMPLEMENTATION_AGGREGATOR_H
#define FEEDOS_BASE_TRACE_IMPLEMENTATION_AGGREGATOR_H

#include "trace.h"
#include <vector>

namespace FeedOS {

	// implementation of Trace Facility : log messages in a file
	class TraceImplementation_aggregator: public TraceImplementation
	{
	public:
		TraceImplementation_aggregator ();

		void add_implementation (TraceImplementation & impl);

	private:
		virtual void perform_log (unsigned int area, int level, std::string const & msg);
		virtual void perform_scope (bool entering, unsigned int area, char const * where);

		virtual void hook_shutdown();
		virtual void hook_enable();
		virtual void hook_disable();
		virtual void hook_register_area (unsigned int area, std::string area_name);
		virtual void hook_register_level(int level, std::string level_name);

		typedef std::vector<TraceImplementation*>	ImplList;
		ImplList	m_impl_list;

	};

}

#endif

