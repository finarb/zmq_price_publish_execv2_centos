/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CONNECTION_LoadMetaData_H
#define FEEDOS_generated_API_CONNECTION_LoadMetaData_H

#include "gen_pdu_CONNECTION_LoadMetaData.h"

#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#	include "gen_interface_CONNECTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_CONNECTION_LoadMetaData (RequestHandler & req_handler,
		// inputs
		FeedOS::Types::ListOfTagDeclaration const & Tags,  FeedOS::Types::ListOfEnumTypeDeclaration const & Enums, String const & ProviderName, bool Merge
	);

	// asynchronous version (base class to inherit from)
	class API_CONNECTION_LoadMetaData_base: public AsyncRequester_base
	{
	public:

		API_CONNECTION_LoadMetaData_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfTagDeclaration const & Tags,  FeedOS::Types::ListOfEnumTypeDeclaration const & Enums, String const & ProviderName, bool Merge);

		// response callback : success
		virtual void response_CONNECTION_LoadMetaData_Success () = 0;

		// response callback : some error occurred
		virtual void response_CONNECTION_LoadMetaData_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
