
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TRACE_H
#define FEEDOS_BASE_TRACE_H

#ifndef FEEDOS_BASE_DATE_H
#  include "date.h"
#endif

#include <sstream>
#include <set>

namespace FeedOS {

	class TraceFacilityDelegate;
	class TraceConfiguration;
	class TraceImplementation;

	// trace facility
	//
	// initially disabled & not implemented. To use this you have to :
	//
	//STEP	CATEGORY		METHODS TO CALL
	//
	// 1)	(startup)		init()
	// 2)	(config-code)	register_area() x N				(optional)
	// 3)	(config-code)	register_level() x N			(optional)
	// 4)	(config-user)	enable_area_and_level() x N
	// 5)	(runtime)		enable()/disable()/FEEDOS_LOG()/FEEDOS_SCOPER()
	// 6)	(exit)			shutdown() 
	



	////////////////////////////   utility classes (delegates Configuration/Implementation)

	class TraceFacilityDelegate
	{
	public:
		TraceFacilityDelegate (std::string const & name) : m_name (name) {}
		virtual ~TraceFacilityDelegate() {}

		std::string	const & get_name () const { return m_name; }

		// config-code events
		virtual void hook_register_area (unsigned int area, std::string area_name) = 0;
		virtual void hook_register_level(int level, std::string level_name) = 0;

		// runtime events
		virtual void hook_shutdown() = 0;
		virtual void hook_enable() = 0;
		virtual void hook_disable() = 0;

	private:
		std::string	m_name;
	};


	class TraceConfiguration: public TraceFacilityDelegate
	{
	public:
		TraceConfiguration (std::string const & name) : TraceFacilityDelegate (name) {}
	};


	class TraceImplementation: public TraceFacilityDelegate
	{
	public:
		TraceImplementation (std::string const & name) : TraceFacilityDelegate (name) {}

		virtual void perform_log (unsigned int area, int level, std::string const & msg) = 0;
		virtual void perform_scope (bool entering, unsigned int area, char const * where) = 0;
	};




	class TraceFacility
	{
	public:
		// areas
		static unsigned int const max_nb_area		= 10000;	// zero based
		static unsigned int const first_user_area	= 1000;		// lower areas are reserved for FeedOS internal use

		// levels
		// INFO level (normal messages) is					0
		// WARNING/ERROR levels are							(1..max_nb_error_level)		+1..+15		
		// DEBUG levels are									(-max_nb_debug_level..-1)	-15..-1
		// SCOPE level (entering/leaving a function) is		-16
		static int const max_nb_level		= 32;
		static int const max_nb_error_level	= 15;
		static int const max_nb_debug_level	= max_nb_level - max_nb_error_level - 2;	// reserve 2 slots for INFO and SCOPE
		static int const info_level			= 0;						// special level
		static int const scope_level		= -max_nb_debug_level-1;	// special level
		static inline int level2index (int level) { return level+max_nb_debug_level+1; }
		static inline unsigned int level2mask (int level) { return 1<<level2index(level); }

		// setup (using delegate objects for configuration/implementation)
		static void init (TraceConfiguration & delegate_config, TraceImplementation & delegate_impl);

		// configuration
		static void reset_area_and_level_masks ();
		static void set_area_and_levels	(bool enabled, unsigned int area, int level_begin, int level_end, bool check_if_registered=true);
		static void set_area_and_level	(bool enabled, unsigned int area, int level, bool check_if_registered=true);
		static void set_area_and_scope	(bool enabled, unsigned int area, bool check_if_registered=true);
		static void register_area			(unsigned int area, std::string area_name);
		static void register_level			(int level, std::string level_name);
		static inline std::string const &		get_area_name (unsigned int area) { return s_area_names[area]; }
		static inline std::string const &		get_level_name (int level) { return s_level_names[level2index(level)]; }
		static std::set<unsigned int> const &	get_registered_areas  () { return s_registered_areas; }
		static std::set<int> const &			get_registered_levels () { return s_registered_levels; }
		static void set_file_rolling	(unsigned int log_max_file_size_mb, unsigned int log_max_nb_files);
		static unsigned int get_roll_file_size_mb() { return s_roll_file_size_mb; }
		static unsigned int get_roll_max_files() { return s_roll_max_files; }
		
		// implementation (overriding a previous implementation is supported)
		static void set_implementation (TraceImplementation & delegate_impl);

		// runtime control
		static void enable();
		static void disable();
		static void shutdown();

		// runtime queries
		static inline bool is_enabled () { return s_is_enabled; }
		static inline bool is_enabled_for_area_and_level (unsigned int area, int level) { return 0 != (s_area_and_level_masks[area] & level2mask(level)); }
		static inline bool is_enabled_for_area_and_scope (unsigned int area) { return is_enabled_for_area_and_level (area, scope_level); }

		// runtime tracing
		static inline void perform_log   (unsigned int area, int level, std::string const & msg) { s_delegate_impl_p->perform_log(area, level, msg); }
		static inline void perform_scope (bool entering, unsigned int area, char const * where) { s_delegate_impl_p->perform_scope(entering, area, where); }
		
	private:
		static void check_init_done();
		static void register_default_areas_and_levels();

		static TraceConfiguration *		s_delegate_config_p;
		static TraceImplementation *	s_delegate_impl_p;
		static TraceImplementation *	s_delegate_impl_p_save;
		static bool						s_is_enabled;
		static uint32					s_area_and_level_masks[max_nb_area];
		static std::string				s_area_names[max_nb_area];
		static std::string				s_level_names[max_nb_level];
		static std::set<unsigned int>	s_registered_areas;
		static std::set<int>			s_registered_levels;
		static unsigned int				s_roll_file_size_mb;
		static unsigned int				s_roll_max_files;
	};


	class TraceScoper
	{
	public:
		inline TraceScoper (unsigned int area, char const * where)
		{
			if (TraceFacility::is_enabled_for_area_and_scope (area)) {
				TraceFacility::perform_scope (true, m_area=area, m_where=where);
			} else {
				m_where=0;
			}
		}
		inline ~TraceScoper () { if (m_where) TraceFacility::perform_scope (false, m_area, m_where); }
	private:
		unsigned int	m_area;
		char const *	m_where;
	};


}


static unsigned int const FEEDOS_TRACE_AREA_User				= FeedOS::TraceFacility::first_user_area;
static unsigned int const FEEDOS_TRACE_AREA_Trace				= 0;
static unsigned int const FEEDOS_TRACE_AREA_Misc				= 1;
static unsigned int const FEEDOS_TRACE_AREA_Lock				= 2;
static unsigned int const FEEDOS_TRACE_AREA_Thread				= 3;
static unsigned int const FEEDOS_TRACE_AREA_Network				= 4;
static unsigned int const FEEDOS_TRACE_AREA_NetworkIncomingData	= 5;
static unsigned int const FEEDOS_TRACE_AREA_NetworkOutgoingData	= 6;
static unsigned int const FEEDOS_TRACE_AREA_Cron				= 7;
static unsigned int const FEEDOS_TRACE_AREA_Queue				= 8;
static unsigned int const FEEDOS_TRACE_AREA_Protocol			= 9;
static unsigned int const FEEDOS_TRACE_AREA_Framework			= 10;
static unsigned int const FEEDOS_TRACE_AREA_Object				= 11;
static unsigned int const FEEDOS_TRACE_AREA_API					= 12;
static unsigned int const FEEDOS_TRACE_AREA_ASSERT				= 13;
static unsigned int const FEEDOS_TRACE_AREA_ClientAPI			= 14;	// added by kannan
// add more internal areas HERE

static int const FEEDOS_TRACE_LEVEL_Scope		= FeedOS::TraceFacility::scope_level;
static int const FEEDOS_TRACE_LEVEL_Fatal		= 3;
static int const FEEDOS_TRACE_LEVEL_Critical	= 2;
static int const FEEDOS_TRACE_LEVEL_Warning		= 1;
static int const FEEDOS_TRACE_LEVEL_Info		= FeedOS::TraceFacility::info_level;
static int const FEEDOS_TRACE_LEVEL_Debug		= -1;
static int const FEEDOS_TRACE_LEVEL_MoreDebug	= -2;
static int const FEEDOS_TRACE_LEVEL_FullDebug	= -3;



#ifdef FEEDOS_DISABLE_TRACE_MACROS
#	define FEEDOS_LOG_IS_ENABLED(area,level)	;
#	define FEEDOS_DO_LOG(area,level,msg)		;
#	define FEEDOS_LOG(area,level,msg)			;
#	define FEEDOS_LOG_ONCE(area,level,msg)		;
#	define FEEDOS_SCOPER(area,where)			;
#	define FEEDOS_ASSERT(what)					;
#else
#	define FEEDOS_LOG_IS_ENABLED(area,level)	FeedOS::TraceFacility::is_enabled_for_area_and_level(FEEDOS_TRACE_AREA_##area,FEEDOS_TRACE_LEVEL_##level)
#	define FEEDOS_DO_LOG(area,level,msg)	{ std::stringstream _trace_stream_; (_trace_stream_<<msg); FeedOS::TraceFacility::perform_log (FEEDOS_TRACE_AREA_##area,FEEDOS_TRACE_LEVEL_##level,_trace_stream_.str()); }
#	define FEEDOS_LOG(area,level,msg)		if (FEEDOS_LOG_IS_ENABLED(area,level)) FEEDOS_DO_LOG(area,level,msg)
#	define FEEDOS_LOG_ONCE(area,level,msg) {static bool warn=true;if (warn){warn=false; FEEDOS_LOG(area,level,msg)}}
#	define FEEDOS_SCOPER(area,where)		FeedOS::TraceScoper feedos_trace_scoper (FEEDOS_TRACE_AREA_##area,where);
#	ifdef FEEDOS_ENABLE_PARANOID_CHECKS
#		define FEEDOS_ASSERT(what)		if (!(what)) FEEDOS_LOG(ASSERT,Fatal,"assertion failed: "#what)
#	else
#		define FEEDOS_ASSERT(what)		;
#	endif
#	define	FEEDOS_LOG_EVERY_NSEC(N,area,level,msg)	\
		if (FEEDOS_LOG_IS_ENABLED(area,level)) { \
			static FeedOS::Timestamp ___last_warn; \
			static unsigned int ___err_counter = 0; \
			FeedOS::Timestamp ___now; ___now.set_to_now_utc(); \
			if (___now.diff_seconds(___last_warn)>(N)) { \
				___last_warn=___now; \
				FEEDOS_DO_LOG(area,level,"~*"<<++___err_counter<<'~'<<msg); \
			} else { \
				FEEDOS_LOG(area,MoreDebug,"~*"<<++___err_counter<<'~'<<msg); \
			} \
		}
#endif



#endif

