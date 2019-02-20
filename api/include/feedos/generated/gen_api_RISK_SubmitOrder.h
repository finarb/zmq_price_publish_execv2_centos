/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_RISK_SubmitOrder_H
#define FEEDOS_generated_API_RISK_SubmitOrder_H

#include "gen_pdu_RISK_SubmitOrder.h"

#ifndef FEEDOS_generated_INTERFACE_RISK_H
#	include "gen_interface_RISK.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_RISK_SubmitOrder (RequestHandler & req_handler,
		// inputs
		BinaryBuffer Order, bool NowOrNever = false
	);

	// asynchronous version (base class to inherit from)
	class API_RISK_SubmitOrder_base: public AsyncRequester_base
	{
	public:

		API_RISK_SubmitOrder_base ();

		void send (RequestHandler & handler,
					//inputs
					BinaryBuffer Order, bool NowOrNever = false);

		// response callback : success
		virtual void response_RISK_SubmitOrder_Success () = 0;

		// response callback : some error occurred
		virtual void response_RISK_SubmitOrder_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
