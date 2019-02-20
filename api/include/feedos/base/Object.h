
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_OBJECT_H
#define FEEDOS_BASE_OBJECT_H

#ifndef FEEDOS_BASE_LOCK_H
#  include "lock.h"
#endif

#include <string>
#include <vector>
#include <map>

#ifdef _MSC_VER
#	pragma warning (disable:4584)	// 'MyDerivedClass' : base-class 'FeedOS::Object' is already a base-class of 'MyBaseClass'
#endif


//
// base classes for 'interesting' objects
//
namespace FeedOS {

	class NullObject;
	class OverrideObjectClass;
	void background_recycle_objects (LockedBool const & should_terminate);
	

	// base class for "interesting objects"
	// IMPORTANT: should be the first one to inherit from
	class Object
	{
		bool			m_is_dummy_derived;
		std::string		m_forced_class_name;

	private:
		friend class NullObject;
		friend class OverrideObjectClass;

		// special constructor: builds a "dummy derived" to pass as "derived_instance"
		Object (bool);
		// special constructor: builds a "dummy derived" to pass as "derived_instance"
		// + make the base object to override its real class_name
		// (useful to "hide" intermediate classes in an inheritance hierarchy)
		Object (std::string const & forced_class_name);

	protected:
		// every "interesting" class should inherit DIRECTLY from Object
		// (which MUST be the FIRST BASE CLASS)
		// - argments: class and instance names
		// - additional property: a unique (numeric) ID is computed
//		Object (std::string const & my_instance_name, std::string const & my_class_name);

		// moreover, if the derived class can be derived too, it should accept a special argument in its
		// own constructor: a reference to the derived object (which should inherit from Object directly, too)
		// AND PASS IT TO Object constructor as the "derived_instance"

		Object (Object & derived_instance, std::string const & my_class_name, std::string const & my_instance_name);

	public:

		virtual ~Object();

		// trigger a delayed-background-multiple_attempts-delete
		// the object should not be used any more
		void recycle_delete_object();

		// true if this is a terminal (inheritance-wise) object
//		inline bool is_terminal_instance () const { return m_is_terminal; }

		// unique ID
		unsigned int	get_object_id() const { return m_object_id; }

		// name of [?C++?] class
		inline std::string const &		get_object_class_name		() const { return m_class_name; }

		// name of the instance
		inline std::string const &		get_object_instance_name	() const { return m_instance_name; }

		// full instance name "[class/instance]"
		inline std::string const &		get_object_full_instance_name() const { return m_full_instance_name; }

		// override to provide "status" information
		// default is to return get_object_full_instance_name()
		virtual std::string		get_object_description () const;

		// list of sub-objects (got through inheritance)
		inline std::vector<Object *> const &	get_object_bases () const { return m_object_bases; }

	private:
		void build_full_instance_name();

		// override this to react to 'outside-triggered' delete (outside==elsewhere in inheritance graph)
		// 
		// if deletion is ok: instance should be 'stopped'/cleaned up and TRUE is returned
		// else return FALSE (a new recycling attempt will occur later unless this is the last_attempt)
		//
		// NB: If 'last_attempt' is set then object will be deleted regardless of the return value
		virtual bool	background_object_recycling_hook (bool /*last_attempt*/) { return true; }

		typedef enum {
			LivingObject,
			RecyclingScheduled,
			RecyclingRefused,
			RecyclingDone
		} RecyclingStatus;
		static char const *	get_recycling_status_str (RecyclingStatus s);
		char const *		get_recycling_status_str () const { return get_recycling_status_str(m_recycling_status); }

		// return true if the whole object hierarchy is ok for deletion
		// (should be called only on terminal instances)
		friend void background_recycle_objects (LockedBool const & should_terminate);
		bool				background_recursive_ask_for_object_recycling();
		RecyclingStatus		background_ask_for_object_recycling ();
		RecyclingStatus		m_recycling_status;
		unsigned int		m_nb_recycling_attempts;

		std::vector<Object *>	m_object_bases;

		bool			m_is_terminal;
		Object *		m_derived_instance;
		Object *		m_terminal_instance;
		unsigned int	m_object_id;
		std::string		m_class_name;
		std::string		m_instance_name;
		std::string		m_full_instance_name;
	};


	class NullObject: public Object
	{
	public:
		NullObject() : Object (false) {}
	};
	class OverrideObjectClass: public Object
	{
	public:
		OverrideObjectClass(std::string const & forced_class_name) : Object (forced_class_name) {}
	};


	// base class for Objects that can be started/stopped
	class StartableObject: public Object
	{
	protected:
		StartableObject (Object & derived_instance, std::string const & instance_name);
	public:
		~StartableObject ();

		typedef enum
		{
			Starting,
			StartError,
			Started,
			Stopping,
			StopError,
			Stopped,
			Restarting,
			Recycling,
			first_registered_state
		} State;

		char const *	get_object_state_str (State s) const;
		char const *	get_object_state_str () const { return get_object_state_str(m_state); }

		State	get_object_state () const { return m_state; }

		// return false in case of error
		bool	start_object();
		bool	stop_object();
		bool	restart_object();

	protected:

		void register_new_state (unsigned int state_num, std::string const & state_str);

		// override this
		virtual bool	impl_start_object() = 0;
		virtual bool	impl_stop_object() = 0;

		// default is to stop()/start()
		virtual bool	impl_restart_object();

		// avoid using this. 'state' is set as a side effect of impl_start_object()/impl_stop_object()
		void	force_object_state (State s);

		// what to do when recycling is triggered from 'outside': stop() if State==Started
		bool	background_object_recycling_hook (bool last_attempt);
	private:
		bool	start_object_nolock();
		bool	stop_object_nolock();
		void	set_object_state (State s);

		ExclusiveLock	m_state_lock;
		State			m_state;
		std::map<unsigned int, std::string>	m_extra_states_name;
	};


	// start/stop a list of objects in one shot
	class CollectionOfStartableObject: public StartableObject
	{
	protected:
		// constructor for subclassing
		CollectionOfStartableObject (Object & derived_instance, std::string const & instance_name);
	public:
		// constructor for instantiating objects
		CollectionOfStartableObject (std::string const & instance_name);

		void add_startable_object (StartableObject & o);

	private:
		virtual bool	impl_start_object();
		virtual bool	impl_stop_object();
		virtual bool	impl_restart_object();

		ExclusiveLock					m_list_of_startable_object_lock;
		std::vector<StartableObject *>	m_list_of_startable_object;
	};


}


#endif



