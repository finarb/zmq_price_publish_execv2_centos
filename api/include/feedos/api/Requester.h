
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_REQUESTER_H
#define FEEDOS_API_REQUESTER_H

#ifndef FEEDOS_API_MESSAGE_H
#  include "Message.h"
#endif

#ifndef FEEDOS_API_REQ_NUM_GENERATOR_H
#  include "ReqNumGenerator.h"
#endif

namespace FeedOS {


	class ResponseHandler_interface
	{
	public:
		virtual ~ResponseHandler_interface() {}

		// overide this
		virtual void handle_response (ResponseContext const & /*context*/, PDU const & /*pdu*/) {}	// NOT pure virtual, on purpose
		inline void  handle_response (Response const & rsp) { handle_response (rsp.get_context(), rsp.get_pdu()); }

	};


	class Requester:	virtual protected ResponseHandler_interface,
						protected ReqNumGenerator
						
	{
	public:
		static void dispatch_response (ResponseContext const & context, PDU const & pdu);
		static inline void dispatch_response (Response const & rsp) { dispatch_response (rsp.get_context(), rsp.get_pdu()); }

		// build/register a new "client" instance
		Requester (std::string const & name);

		virtual ~Requester();

		inline std::string const &	get_name () const { return m_name; }
		RequesterId					get_id () const { return m_id; }

		AuthInfo const &	get_auth () const { return m_auth; }
		void				set_auth (AuthInfo const & a) { m_auth=a; }

		// call this to initiate a new request/subscription
		RequestContext new_context_for_request ()		{ return RequestContext (m_id, new_req_num_for_request(), m_auth); }
		RequestContext new_context_for_subscription ()	{ return RequestContext (m_id, new_req_num_for_subscription(), m_auth); }

	protected:
		void	unregister_instance ();

	private:
		void operator=(Requester const &) {}	// dummy private operator

		void			register_instance ();

		bool			m_is_registered;
		std::string		m_name;
		RequesterId		m_id;
		AuthInfo		m_auth;
	};





	class SyncRequester: protected Requester
	{
	public:
		SyncRequester (std::string const & name
						/* DEPRECATED , int timeout_ms=-1*/);
		~SyncRequester ();

		PDU sync_send (RequestHandler & handler, PDU const & pdu, int timeout_ms=-1);

		/* DEPRECATED
		// -1 means "infinite" (this is the default)
		void set_timeout_for_sync_operations (int timeout_ms);
		*/

	private:
		void wakeup_sync_send (PDU const & pdu);
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);

		ConditionalVariable		m_cond_lock;
		PDU						m_rsp_pdu;
		volatile bool			m_req_in_progress;
	};



	class AsyncRequester_base: protected Requester
	{
	public:
		AsyncRequester_base (std::string const & name
						/* DEPRECATED , int timeout_ms=-1*/);
		~AsyncRequester_base ();

		void send (RequestHandler & handler, PDU const & pdu, int timeout_ms=-1);

		/* DEPRECATED
		// -1 means "infinite" (this is the default)
		void set_timeout_for_async_operations (int timeout_ms);
		*/

	private:
		ExclusiveLock			m_lock;
	};




	class Subscriber_base: protected Requester
	{
		Subscriber_base (Subscriber_base const &);
		void operator=	(Subscriber_base const &);
	public:
		Subscriber_base (std::string const & name
						/* DEPRECATED , int timeout_ms=-1*/);
		~Subscriber_base ();

		// optional argument: timeout in milliseconds (default is -1 : "infinite")
		ReturnCode sync_start (RequestHandler & handler, PDU const & subreq_pdu, int timeout_ms=-1);

		// return false in case of failure (i.e. "already started")
		bool start (RequestHandler & handler, PDU const & subreq_pdu);

		// stop the subscription
		void stop ();

		// stop the subscription and wait for user callbacks to complete
		void sync_stop ();

		/* DEPRECATED, use last parameter in sync_start()
		void set_timeout_for_sync_operations (int timeout_ms);
		*/

		typedef enum
		{
			Stopped,				// [sync_]start() never called OR stop() by user
			SyncWaitingForResponse,	// sync_start() in progress, waiting for SubRsp
			WaitingForResponse,		//      start() called, waiting for SubRsp
			InProgress,				// [sync_]start() called, subscription accepted 
			Failed,					// [sync_]start() called, subscription refused by server
			Aborted,				// [sync_]start() called, subscription accepted THEN aborted by the server
			TimedOut				// [sync_]start() called, subscription not accepted in a timely manner
		} SubscriptionState;

		SubscriptionState		get_state () const { return m_state; }
		char const *			get_state_str () const { return state2str(m_state); }
		static char const *		state2str (SubscriptionState s);

		bool subscription_is_started() const 
		{
			switch (get_state()) {
			case SyncWaitingForResponse:
			case WaitingForResponse:
			case InProgress:
				return true;
			default:
				return false;
			}
		}
		bool subscription_is_waiting_for_response() const 
		{
			switch (get_state()) {
			case SyncWaitingForResponse:
			case WaitingForResponse:
				return true;
			default:
				return false;
			}
		}
		bool subscription_is_in_progress() const { return get_state () == InProgress; }

		// retrieve the last return code (set when SubscribeResponse and UnsubNotif are received)
		ReturnCode		get_last_rc() const { return m_subrsp_rc; }

		// low-level message dispatcher
		inline void		internal_dispatch_incoming_pdu_nolock (PDU const & pdu)
		{
			switch (pdu.get_id().get_type()) {
			case PDU_Type_SubscribeNotif:		dispatch_incoming_NOTIF_nolock			(pdu); break;
			case PDU_Type_SubscribeResponse:	dispatch_incoming_SUBRSP_nolock			(pdu); break;
			case PDU_Type_UnsubscribeNotif:		dispatch_incoming_UNSUB_NOTIF_nolock	(pdu); break;
			default:
				log_internal_dispatch_incoming_pdu_UNEXPECTED (pdu);
			}
		}

	protected:
		// called by receive_rsp() to dispatch incoming PDUs
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & /*pdu*/) {}
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & /*pdu*/) {}

	public:
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & /*pdu*/) {}

	private:

		void dispatch_incoming_NOTIF_nolock			(PDU const & pdu);
		void dispatch_incoming_SUBRSP_nolock		(PDU const & pdu);
		void dispatch_incoming_UNSUB_NOTIF_nolock	(PDU const & pdu);

		void log_internal_dispatch_incoming_pdu_UNEXPECTED (PDU const & pdu);

		void set_state_nolock (SubscriptionState s);
		void send_subreq_nolock (RequestHandler & handler, PDU const & subreq_pdu);
		void send_unsubreq_nolock ();

		void wakeup_sync_start ();
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);

		RequestHandler *			m_handler;
		RequestContext				m_context;
		PDU_Id						m_subreq_pdu_id;
		ExclusiveLock				m_lock;
		ConditionalVariable			m_sync_start_cond_lock;
		volatile ReturnCode			m_subrsp_rc;
		volatile SubscriptionState	m_state;
	};


}


#endif
