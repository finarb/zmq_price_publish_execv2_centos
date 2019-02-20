/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_GetHistoryDaily_H
#define FEEDOS_generated_API_QUOTATION_GetHistoryDaily_H

#include "gen_pdu_QUOTATION_GetHistoryDaily.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_GetHistoryDaily (RequestHandler & req_handler,
		// outputs
		FOSInstrumentCode & InternalCode,  FeedOS::Types::ListOfDailyHistoryPoint & Values,
		// inputs
		PolymorphicInstrumentCode const & Code,  FeedOS::Types::YMD_Date const & MarketLocalDate_begin,  FeedOS::Types::YMD_Date const & MarketLocalDate_end
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_GetHistoryDaily_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_GetHistoryDaily_base ();

		void send (RequestHandler & handler,
					//inputs
					PolymorphicInstrumentCode const & Code,  FeedOS::Types::YMD_Date const & MarketLocalDate_begin,  FeedOS::Types::YMD_Date const & MarketLocalDate_end);

		// response callback : success + outputs
		virtual void response_QUOTATION_GetHistoryDaily_Success (FOSInstrumentCode InternalCode,  FeedOS::Types::ListOfDailyHistoryPoint const & Values) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_GetHistoryDaily_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
