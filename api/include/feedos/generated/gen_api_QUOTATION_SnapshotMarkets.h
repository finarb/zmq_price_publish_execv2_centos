/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_SnapshotMarkets_H
#define FEEDOS_generated_API_QUOTATION_SnapshotMarkets_H

#include "gen_pdu_QUOTATION_SnapshotMarkets.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_SnapshotMarkets (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfMarketStatus & MarketsStatus,
		// inputs
		FeedOS::Types::ListOfFOSMarketId const & Markets
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_SnapshotMarkets_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_SnapshotMarkets_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfFOSMarketId const & Markets);

		// response callback : success + outputs
		virtual void response_QUOTATION_SnapshotMarkets_Success (FeedOS::Types::ListOfMarketStatus const & MarketsStatus) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_SnapshotMarkets_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
