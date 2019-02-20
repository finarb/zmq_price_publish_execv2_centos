/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_GetHistoryDailyExt_H
#define FEEDOS_generated_API_QUOTATION_GetHistoryDailyExt_H

#include "gen_pdu_QUOTATION_GetHistoryDailyExt.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	// synchronous version (blocking function call)
	ReturnCode
	API_QUOTATION_GetHistoryDailyExt (RequestHandler & req_handler,
		// outputs
		FOSInstrumentCode & InternalCode,  FeedOS::Types::ListOfDailyHistoryPointExt & Values,
		// inputs
		PolymorphicInstrumentCode const & Code,  FeedOS::Types::YMD_Date const & BeginDate,  FeedOS::Types::YMD_Date const & EndDate,  FeedOS::Types::DailyExtPointType PointType,  FeedOS::Types::AdjustmentFactorEventTypeMask AdjustmentFactorEventTypes
	);

	// asynchronous version (base class to inherit from)
	class API_QUOTATION_GetHistoryDailyExt_base: public AsyncRequester_base
	{
	public:

		API_QUOTATION_GetHistoryDailyExt_base ();

		void send (RequestHandler & handler,
					//inputs
					PolymorphicInstrumentCode const & Code,  FeedOS::Types::YMD_Date const & BeginDate,  FeedOS::Types::YMD_Date const & EndDate,  FeedOS::Types::DailyExtPointType PointType,  FeedOS::Types::AdjustmentFactorEventTypeMask AdjustmentFactorEventTypes);

		// response callback : success + outputs
		virtual void response_QUOTATION_GetHistoryDailyExt_Success (FOSInstrumentCode InternalCode,  FeedOS::Types::ListOfDailyHistoryPointExt const & Values) = 0;

		// response callback : some error occurred
		virtual void response_QUOTATION_GetHistoryDailyExt_Failed (ReturnCode rc) = 0;

	private:
		virtual void handle_response (ResponseContext const & context, PDU const & pdu);
	};

}
#endif
