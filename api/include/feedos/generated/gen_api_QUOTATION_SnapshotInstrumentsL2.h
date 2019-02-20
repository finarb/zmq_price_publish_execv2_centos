/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_SnapshotInstrumentsL2_H
#define FEEDOS_generated_API_QUOTATION_SnapshotInstrumentsL2_H

#include "gen_pdu_QUOTATION_SnapshotInstrumentsL2.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_SnapshotInstrumentsL2 (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfInstrumentStatusL2 & Result,
		// inputs
		FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, int8 OrderBookDepth = -1, bool IgnoreInvalidCodes = false
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_SnapshotInstrumentsL2_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_SnapshotInstrumentsL2_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes, int8 OrderBookDepth = -1, bool IgnoreInvalidCodes = false);

		// response callback : success + outputs
		virtual void response_QUOTATION_SnapshotInstrumentsL2_Success (FeedOS::Types::ListOfInstrumentStatusL2 const & Result) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_SnapshotInstrumentsL2_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
