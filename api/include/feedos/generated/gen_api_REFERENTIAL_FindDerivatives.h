/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_FindDerivatives_H
#define FEEDOS_generated_API_REFERENTIAL_FindDerivatives_H

#include "gen_pdu_REFERENTIAL_FindDerivatives.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_REFERENTIAL_FindDerivatives (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfInstrumentCharacteristics & Instruments,
		// inputs
		PolymorphicInstrumentCode const & UnderlyingInstrument,  FeedOS::Types::ListOfReferentialAttribute const & Filter,  FeedOS::Types::ListOfReferentialTagNumber const & Format
	);

	// asynchronous version (base class to inherit from)
	class API_REFERENTIAL_FindDerivatives_base: public AsyncRequester_base
	{
	public:

		API_REFERENTIAL_FindDerivatives_base ();

		void send (RequestHandler & handler,
					//inputs
					PolymorphicInstrumentCode const & UnderlyingInstrument,  FeedOS::Types::ListOfReferentialAttribute const & Filter,  FeedOS::Types::ListOfReferentialTagNumber const & Format);

		// response callback : success + outputs
		virtual void response_REFERENTIAL_FindDerivatives_Success (PolymorphicInstrumentCode const & UnderlyingInstrument,  FeedOS::Types::ListOfInstrumentCharacteristics const & Instruments) = 0;

		// response callback : some error occurred
		virtual void response_REFERENTIAL_FindDerivatives_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
