/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeAllIntradayBars_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeAllIntradayBars_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeAllIntradayBars
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest () :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeAllIntradayBars)
		{
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeAllIntradayBars)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllIntradayBars, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllIntradayBars, RC_OK)
		{
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeAllIntradayBars, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeAllIntradayBars
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeAllIntradayBars, p)
		{
		}
	private:
	public:
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeAllIntradayBars, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllIntradayBars, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeAllIntradayBars, p)
		{}
	};

}

}
#endif
