/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_ChgSubscribeInstrumentsL2Add_H
#define FEEDOS_generated_API_QUOTATION_ChgSubscribeInstrumentsL2Add_H

#include "gen_pdu_QUOTATION_ChgSubscribeInstrumentsL2Add.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_ChgSubscribeInstrumentsL2Add (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfInstrumentStatusL2 & Snapshot,
		// inputs
		uint32 Ticket,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = false
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_ChgSubscribeInstrumentsL2Add_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_ChgSubscribeInstrumentsL2Add_base ();

		void send (RequestHandler & handler,
					//inputs
					uint32 Ticket,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = false);

		// response callback : success + outputs
		virtual void response_QUOTATION_ChgSubscribeInstrumentsL2Add_Success (FeedOS::Types::ListOfInstrumentStatusL2 const & Snapshot) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_ChgSubscribeInstrumentsL2Add_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
