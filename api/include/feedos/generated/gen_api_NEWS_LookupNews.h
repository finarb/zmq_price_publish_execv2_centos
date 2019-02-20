/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_NEWS_LookupNews_H
#define FEEDOS_generated_API_NEWS_LookupNews_H

#include "gen_pdu_NEWS_LookupNews.h"

#ifndef FEEDOS_generated_INTERFACE_NEWS_H
#	include "gen_interface_NEWS.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_NEWS_LookupNews (RequestHandler & req_handler,
		// outputs
		FeedOS::Types::ListOfNewsData & Result,
		// inputs
		FeedOS::Types::ListOfNewsItem const & Filter,  FeedOS::Types::ListOfNewsItemId const & Format, uint16 MaxHits
	);

	// asynchronous version (base class to inherit from)
	class API_NEWS_LookupNews_base: public AsyncRequester_base
	{
	public:

		API_NEWS_LookupNews_base ();

		void send (RequestHandler & handler,
					//inputs
					FeedOS::Types::ListOfNewsItem const & Filter,  FeedOS::Types::ListOfNewsItemId const & Format, uint16 MaxHits);

		// response callback : success + outputs
		virtual void response_NEWS_LookupNews_Success (FeedOS::Types::ListOfNewsData const & Result) = 0;

		// response callback : some error occurred
		virtual void response_NEWS_LookupNews_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
