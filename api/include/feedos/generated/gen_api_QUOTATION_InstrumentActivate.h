/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_InstrumentActivate_H
#define FEEDOS_generated_API_QUOTATION_InstrumentActivate_H

#include "gen_pdu_QUOTATION_InstrumentActivate.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_InstrumentActivate (RequestHandler & req_handler,
		// inputs
		String const & OutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = true
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_InstrumentActivate_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_InstrumentActivate_base ();

		void send (RequestHandler & handler,
					//inputs
					String const & OutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = true);

		// response callback : success
		virtual void response_QUOTATION_InstrumentActivate_Success () = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_InstrumentActivate_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
