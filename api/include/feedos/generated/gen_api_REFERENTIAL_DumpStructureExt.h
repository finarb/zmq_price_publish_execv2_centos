/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_DumpStructureExt_H
#define FEEDOS_generated_API_REFERENTIAL_DumpStructureExt_H

#include "gen_pdu_REFERENTIAL_DumpStructureExt.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_REFERENTIAL_DumpStructureExt (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfMarketCharacteristics & Markets,  FeedOS::Types::ListOfEntitledMarketContent & Content, Timestamp & LastUpdateTimestamp
	);

	// asynchronous version (base class to inherit from)
	class API_REFERENTIAL_DumpStructureExt_base: public AsyncRequester_base
	{
	public:

		API_REFERENTIAL_DumpStructureExt_base ();

		void send (RequestHandler & handler);

		// response callback : success + outputs
		virtual void response_REFERENTIAL_DumpStructureExt_Success (FeedOS::Types::ListOfMarketCharacteristics const & Markets,  FeedOS::Types::ListOfEntitledMarketContent const & Content, Timestamp const & LastUpdateTimestamp) = 0;

		// response callback : some error occurred
		virtual void response_REFERENTIAL_DumpStructureExt_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
