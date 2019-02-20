/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_SnapshotInstrumentsMBL_H
#define FEEDOS_generated_API_QUOTATION_SnapshotInstrumentsMBL_H

#include "gen_pdu_QUOTATION_SnapshotInstrumentsMBL.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_SnapshotInstrumentsMBL (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfMBLSnapshot & Result,
		// inputs
		FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes,  FeedOS::Types::ListOfOrderBookLayerId const & LayerIds = ListOfOrderBookLayerId(), FOSInteger const & OrderBookDepth = -1, bool IgnoreInvalidCodes = false
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_SnapshotInstrumentsMBL_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_SnapshotInstrumentsMBL_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes,  FeedOS::Types::ListOfOrderBookLayerId const & LayerIds = ListOfOrderBookLayerId(), FOSInteger const & OrderBookDepth = -1, bool IgnoreInvalidCodes = false);

		// response callback : success + outputs
		virtual void response_QUOTATION_SnapshotInstrumentsMBL_Success (FeedOS::Types::ListOfMBLSnapshot const & Result) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_SnapshotInstrumentsMBL_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
