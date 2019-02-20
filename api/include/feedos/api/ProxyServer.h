
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2011 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_PROXY_SERVER_H
#define FEEDOS_API_PROXY_SERVER_H

#ifndef FEEDOS_API_PROXY_H
#  include "Proxy.h"
#endif

#ifndef FEEDOS_API_REQUEST_HANDLER_H
#  include "RequestHandler.h"
#endif

#ifndef FEEDOS_API_REQ_NUM_GENERATOR_H
#  include "ReqNumGenerator.h"
#endif

#include "generated_constants.h"
#include "../comm/MulticastFeedTools.h"

#include <set>
#include <deque>

namespace FeedOS {


	class ProxyServerObserver;
	class EventDispatcher_impl;
	class ProxyServer_impl_data;

	class ProxyServer:	public Proxy,
						public RequestHandler,
						protected ReqNumGenerator
	{
		friend class ProxyServer_impl_data;
		friend class EventDispatcher_impl;
	public:
		ProxyServer (std::string const & name);
		virtual ~ProxyServer ();

		typedef enum {
			NotLoggedIn,
			SendingHello,		
			LoginInProgress,	
			LoggedIn
		} LoginState;

		LoginState			get_login_state () const { return m_login_state; }
		static char const *	get_login_state_str (LoginState s);
		char const *		get_login_state_str () const { return get_login_state_str(m_login_state); }

		std::vector<std::string> get_connection_flags() const;
		bool is_connection_flag_present(std::string const & flag) const;

		bool				is_connected() const { return get_login_state() == LoggedIn; }
		ReturnCode			get_disconnection_rc() const { return m_disconnection_rc; }

		// disconnect from remote server (all pending req / ongoing subs are canceled and socket is closed)
		void disconnect ();

		// session parameters sent by server
		unsigned int		get_uid () const { return m_auth_uid; }
		unsigned int		get_gid () const { return m_auth_gid; }
		Timestamp			get_heartbeat_server_timestamp () const { return m_heartbeat_server_timestamp; }
		unsigned int		get_heartbeat_period_sec() const {  return m_heartbeat_period_sec; }

		// see comm/MulticastFeedTools.h
		typedef MsgDispatchingHooksBase MsgDispatchingHooks;

		///////////////////////////////////////////////////////////////////////////////
		// Configuring ProxyServer
		///////////////////////////////////////////////////////////////////////////////

		// provide an object to be notified when messages are begin dispatched
		void set_dispatching_hooks_obj (MsgDispatchingHooks & hook_obj);

		// observing ProxyServer (disconnection signals and more)
		void add_observer		(ProxyServerObserver &o);
		void remove_observer	(ProxyServerObserver &o);

		// enable asynchronous dispatching of incoming events. Data is enqueued.
		// A dispatching thread is created. 
		// You may use set_dispatching_hooks_obj() to catch the "warning level reached" condition.
		// enable_event_enqueueing() and disable_internal_event_dispatching() are mutually exclusive.  
		// return RC_OK in case of success
		ReturnCode enable_event_enqueueing (unsigned int queue_warning_level = 10000);

		// disable synchronous dispatching of incoming messages. Data is enqueued.
		// You have to use dispatch_pending_events() or dispatch_events_forever() in a dedicated thread.
		// You may use set_dispatching_hooks_obj() to catch the "warning level reached" condition.
		// return RC_OK in case of success
		ReturnCode	disable_internal_event_dispatching (unsigned int queue_warning_level = 10000);

		// Disable checking of incoming heartbeats 
		// (should use this when the proxy is used for massive data download).
		// It's better to call that prior 1st connection.
		void disable_heartbeat_checking ();

		///////////////////////////////////////////////////////////////////////////////
		// Internal dispatching loop
		///////////////////////////////////////////////////////////////////////////////

		// when "internal_event_dispatching" has been disabled, this should be called
		// to dispatch incoming events towards user callbacks.
		// You may provide a "warning level" (i.e. number of pending messages that will trigger a warning in the TRACE)
		// return either:
		// RC_DISCONNECTED in case of unexpected network disconnection 
		// RC_NORMAL_DISCONNECT in case the user triggered the disconnection
		// ReturnCode provided in break_dispatch_msg_forever()
		ReturnCode	dispatch_events_forever ();

		// call this to make dispatch_events_forever() return 
		void break_dispatch_msg_forever (ReturnCode	rc);

		///////////////////////////////////////////////////////////////////////////////
		// Building blocks for custom dispatching loop 
		///////////////////////////////////////////////////////////////////////////////

		// when "internal_event_dispatching" has been disabled, this can be called
		// to wait for queued events
		// return FALSE in case of error (usually a network disconnection)
		// call dispatch_pending_events() to process content
		bool wait_for_events();

		// when "internal_event_dispatching" has been disabled, this can be called
		// to dispatch pending messages towards user callbacks.
		// returns the number of messages that were processed
		unsigned int	dispatch_pending_events();

		// when "internal_event_dispatching" has been disabled, this can be called
		// to know how many events are pending in the queue
		unsigned int	nb_pending_events();

		class AdminMessage
		{
		public:
			AdminMessage ()
				:urgent		(false)
			{}

			AdminMessage (bool u, std::string const & o, std::string const & h, std::string const & c)
				:urgent		(u),origin		(o),headline	(h),content	(c)
			{}

			AdminMessage (AdminMessage const & m)
				:urgent		(m.urgent	),origin		(m.origin	),headline	(m.headline	),content	(m.content	)
			{}

			AdminMessage const & operator= (AdminMessage const & m)
			{
				urgent		=m.urgent	;	origin		=m.origin	;	headline	=m.headline	;	content		=m.content	;
				return *this;
			}

			bool		urgent;
			std::string	origin;
			std::string	headline;
			std::string	content;
		};

		// call this from FeedOS::ProxyServerObserver::proxy_admin_message_hook()
		void pop_admin_message (AdminMessage & msg);

	protected:
		void push_admin_message (AdminMessage const & msg);

		void check_nb_queued_msg(unsigned int nb_queued_msg);

		static unsigned int const login_timeout_millisec = 7500;

		// call this to initiate a Hello-Login sequence (asynchronous)
		// return false in case of error (already connected or trying to connect)
		bool initiate_log_in (	std::string const & user,
								std::string const & password,
								Types::AuthenticationMechanism auth_mechanism
								);

		// call this to perform a Hello-Login sequence (synchronously)
		// (another thread is needed to read the socket / dispatch messages)
		// Note that the legacy authentication mechanism is used only if the
		// server does not support the new one
		ReturnCode sync_log_in (std::string const & user,
								std::string const & password
								);

		// call this to perform a Hello-Login sequence (synchronously) using
		// a given authentication mechanism
		// (another thread is needed to read the socket / dispatch messages)
		ReturnCode sync_log_in (std::string const & user,
								std::string const & password,
								Types::AuthenticationMechanism auth_mechanism
								);

		// this is called by the heartbeat checking thread
		// default is to call 
		//						set_disconnected_state (RC_DISCONNECTED)
		virtual void	missing_heartbeat_condition ();

		// call this when returning to "disconnected state".
		// provide an error code in case the disconnection is unexpected
		void	set_disconnected_state (bool sync_notify_observers, ReturnCode rc/* = RC_NORMAL_DISCONNECT*/);

		// overide this to close the underlying connection (socket or whatever)
		virtual void set_disconnected_state_hook (ReturnCode /*rc*/) {}

		void		set_sync_login_in_progress();
		void		reset_sync_login_in_progress();
		ReturnCode	get_sync_login_rc() const { return m_sync_login_rc; }

		std::string	getDecoratedApplicationName() const;

		template <typename PDU>
		void handleConnectionLogin(PDU const & rsp);

		void updateConnectionFlags(Types::ListOfString const & connection_flags);

		virtual bool shouldTryToConnectWithLegacyProtocol(ReturnCode rc) const;

	private:
		ExclusiveLock				m_admin_messages_lock;
		std::deque <AdminMessage>	m_admin_messages;

		void	set_login_state (LoginState	s);
		bool	is_custom_msg_dispatching_enabled () const { return  m_custom_dispatching_enabled; }

		typedef	void (ProxyServerObserver::*ObserverCB) (ProxyServer&);
		void	notify_observers		(ObserverCB cb, char const * what);	
		void	sync_notify_observers	(ObserverCB cb, char const * what);	

		// call this after connection to the server was lost :
		// It terminates all pending-requests / ongoing-subscriptions (error_response / unsub_notif sent to Requesters)
		void cleanup_terminate_pending_requests (ReturnCode rc);
		void cleanup_terminate_ongoing_subscriptions (ReturnCode rc);
		
		void do_terminate				(ReturnCode rc);
		void cleanup_before_terminate	(ReturnCode rc);

		// from RequestHandler
		virtual void impl_process_request (RequestContext const & context, PDU const & pdu);

		// from Proxy (will either enqueue or call SYNC_ equivalent)
		virtual void receive_pdu (RequestNumber req_num, PDU const & pdu, unsigned int specific_uid, unsigned int specific_gid);
		virtual void receive_session_pdu (PDU const & pdu);

		// process incoming pdu
		void sync_receive_pdu (RequestNumber req_num, PDU const & pdu);
		void sync_receive_session_pdu (PDU const & pdu);

		// override this
		virtual void handle_session_error (ReturnCode rc) = 0;

		// call this in order to disable sending of client-side fingerprint
		static void	disable_host_fingerprint_at_login();

	public:
		typedef std::vector <RemoteMessage>::const_iterator RemoteMessageIterator;

		// called by dispatch_pending_events() or dispatch_events_forever()
		void process_queue_batch (RemoteMessageIterator begin, RemoteMessageIterator end);

	private:

		void operator=(ProxyServer const &) {}	// dummy private operator
		volatile LoginState			m_login_state;
		unsigned int				m_auth_uid;
		unsigned int				m_auth_gid;
		bool						m_custom_dispatching_enabled;
		unsigned int				m_custom_dispatching_queue_warning_level;
		bool						m_custom_dispatching_queue_warning_hook_enabled;

		MsgDispatchingHooks *		m_msg_dispatching_hooks_obj;

		Timestamp					m_heartbeat_server_timestamp;
		unsigned int				m_heartbeat_period_sec;
		bool						m_heartbeat_checking_enabled;
		static bool					s_DEFAULT_heartbeat_checking_enabled;

		ExclusiveLock					m_observers_lock;
		std::set<ProxyServerObserver*>	m_observers;

		void unblock_sync_log_in (ReturnCode rc);
		volatile bool			m_sync_login_in_progress;
		volatile ReturnCode		m_sync_login_rc;
		ConditionalVariable		m_sync_login_wait_lock;
		std::string				m_user;
		std::string				m_password;

		ExclusiveLock				m_connection_flags_lock;
		std::vector<std::string>	m_connection_flags;

		static void	compute_host_fingerprint();
		static bool				s_enable_host_fingerprint_at_login;
		static std::string		s_host_fingerprint;

		typedef std::pair<UniqueRequestId,PDU_Id> UniqueReqIdAndPDU_Id;
		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<RequestNumber,UniqueReqIdAndPDU_Id> RequestMap;                                   // local_req_num => context  (to process msg coming from network)
		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<UniqueRequestId,RequestNumber,UniqueRequestId::hasher> ReverseSubscriptionMap;    // context => local_req_num  (to process unsubreq)

		// private req_num => pending Request
		ExclusiveLock			m_pending_request_map_lock;
		RequestMap				m_pending_request_map;

		// private req_num => ongoing Subscription
		ReadWriteLock			m_ongoing_subscription_map_lock;
		RequestMap				m_ongoing_subscription_map;

		// ongoing Subscription => private req_num
		ExclusiveLock			m_reverse_subscription_map_lock;
		ReverseSubscriptionMap	m_reverse_subscription_map;

		ProxyServer_impl_data &	m_impl_data;
		EventDispatcher_impl *	m_event_dispatcher;
		
		ReturnCode				m_disconnection_rc;

	protected:
		bool					m_is_last_connection_attempt;

	public:
		static void global_init ();
		void dump_state();
	};

}

#endif

