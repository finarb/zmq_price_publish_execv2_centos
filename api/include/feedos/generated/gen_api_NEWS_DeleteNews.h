/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_NEWS_DeleteNews_H
#define FEEDOS_generated_API_NEWS_DeleteNews_H

#include "gen_pdu_NEWS_DeleteNews.h"

#ifndef FEEDOS_generated_INTERFACE_NEWS_H
#	include "gen_interface_NEWS.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_NEWS_DeleteNews (RequestHandler & req_handler,
		// inputs
		Timestamp const & ServerUTCTime_begin, Timestamp const & ServerUTCTime_end
	);

	// asynchronous version (base class to inherit from)
	class API_NEWS_DeleteNews_base: public AsyncRequester_base
	{
	public:

		API_NEWS_DeleteNews_base ();

		void send (RequestHandler & handler,
					//inputs
					Timestamp const & ServerUTCTime_begin, Timestamp const & ServerUTCTime_end);

		// response callback : success
		virtual void response_NEWS_DeleteNews_Success () = 0;

		// response callback : some error occurred
		virtual void response_NEWS_DeleteNews_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
