/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CONNECTION_GetMetaData_H
#define FEEDOS_generated_API_CONNECTION_GetMetaData_H

#include "gen_pdu_CONNECTION_GetMetaData.h"

#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#	include "gen_interface_CONNECTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_CONNECTION_GetMetaData (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfTagDeclaration & Tags,  FeedOS::Types::ListOfEnumTypeDeclaration & Enums,  FeedOS::Types::ListOfString & Providers, Timestamp & LastUpdate
	);

	// asynchronous version (base class to inherit from)
	class API_CONNECTION_GetMetaData_base: public AsyncRequester_base
	{
	public:

		API_CONNECTION_GetMetaData_base ();

		void send (RequestHandler & handler);

		// response callback : success + outputs
		virtual void response_CONNECTION_GetMetaData_Success (FeedOS::Types::ListOfTagDeclaration const & Tags,  FeedOS::Types::ListOfEnumTypeDeclaration const & Enums,  FeedOS::Types::ListOfString const & Providers, Timestamp const & LastUpdate) = 0;

		// response callback : some error occurred
		virtual void response_CONNECTION_GetMetaData_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
