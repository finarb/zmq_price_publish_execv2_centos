/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CORPORATE_ACTION_PutAdjustmentFactorEvents_H
#define FEEDOS_generated_API_CORPORATE_ACTION_PutAdjustmentFactorEvents_H

#include "gen_pdu_CORPORATE_ACTION_PutAdjustmentFactorEvents.h"

#ifndef FEEDOS_generated_INTERFACE_CORPORATE_ACTION_H
#	include "gen_interface_CORPORATE_ACTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_CORPORATE_ACTION_PutAdjustmentFactorEvents (RequestHandler & req_handler,
		// inputs
		FeedOS::Types::ListOfAdjustmentFactorEvent const & Events
	);

	// asynchronous version (base class to inherit from)
	class API_CORPORATE_ACTION_PutAdjustmentFactorEvents_base: public AsyncRequester_base
	{
	public:

		API_CORPORATE_ACTION_PutAdjustmentFactorEvents_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfAdjustmentFactorEvent const & Events);

		// response callback : success
		virtual void response_CORPORATE_ACTION_PutAdjustmentFactorEvents_Success () = 0;

		// response callback : some error occurred
		virtual void response_CORPORATE_ACTION_PutAdjustmentFactorEvents_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
