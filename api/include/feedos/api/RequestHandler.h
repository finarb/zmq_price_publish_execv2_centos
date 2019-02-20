
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_REQUEST_HANDLER_H
#define FEEDOS_API_REQUEST_HANDLER_H

#include "Message.h"

namespace FeedOS {


	class RequestHandler
	{
	public:
		// initially available
		RequestHandler (std::string const & name);
		virtual ~RequestHandler () {}

		inline std::string const & get_request_handler_name () const { return m_name; }
		inline bool is_available () const { return m_is_available; }
		void set_availability (bool v);
		void set_not_available (ReturnCode error_rc);	// default "error_rc" is RC_NOT_AVAILABLE

		inline void process_request (RequestContext const & context, PDU const & pdu)
		{
			if (is_available()) {
				impl_process_request (context, pdu);
			} else {
				send_error_response (context, pdu.get_id(), m_not_available_rc);
			}
		}
		inline void process_request (Request const & req) { process_request (req.get_context(), req.get_pdu()); }

		// reply to a req/subreq with given RC
		void send_error_response (UniqueRequestId const & context, PDU_Id pdu_id, ReturnCode rc);

	protected:

		// abort a subscription with given RC
		void send_unsub_notif (UniqueRequestId const & context, PDU_Id pdu_id, ReturnCode rc);

		// to be defined by derived classes
		virtual void	impl_process_request (RequestContext const & context, PDU const & pdu) = 0;

	private:
		void operator=(RequestHandler const &) {}	// dummy private operator
		std::string		m_name;
		bool			m_is_available;
		ReturnCode		m_not_available_rc;
	};


}


#endif
