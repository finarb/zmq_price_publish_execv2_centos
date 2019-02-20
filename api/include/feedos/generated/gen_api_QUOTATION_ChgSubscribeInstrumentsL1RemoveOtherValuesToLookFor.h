/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_H
#define FEEDOS_generated_API_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_H

#include "gen_pdu_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor (RequestHandler & req_handler,
		// inputs
		uint32 Ticket,  FeedOS::Types::ListOfQuotationTagNumber const & OtherValuesToLookFor
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_base ();

		void send (RequestHandler & handler,
					//inputs
					uint32 Ticket,  FeedOS::Types::ListOfQuotationTagNumber const & OtherValuesToLookFor);

		// response callback : success
		virtual void response_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_Success () = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
