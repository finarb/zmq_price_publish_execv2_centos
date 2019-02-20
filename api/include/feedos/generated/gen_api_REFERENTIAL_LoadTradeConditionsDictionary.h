/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_LoadTradeConditionsDictionary_H
#define FEEDOS_generated_API_REFERENTIAL_LoadTradeConditionsDictionary_H

#include "gen_pdu_REFERENTIAL_LoadTradeConditionsDictionary.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_REFERENTIAL_LoadTradeConditionsDictionary (RequestHandler & req_handler,
		// inputs
		FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & Entries, bool Merge
	);

	// asynchronous version (base class to inherit from)
	class API_REFERENTIAL_LoadTradeConditionsDictionary_base: public AsyncRequester_base
	{
	public:

		API_REFERENTIAL_LoadTradeConditionsDictionary_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & Entries, bool Merge);

		// response callback : success
		virtual void response_REFERENTIAL_LoadTradeConditionsDictionary_Success () = 0;

		// response callback : some error occurred
		virtual void response_REFERENTIAL_LoadTradeConditionsDictionary_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
