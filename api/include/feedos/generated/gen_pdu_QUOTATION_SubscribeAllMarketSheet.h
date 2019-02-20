/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeAllMarketSheet_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeAllMarketSheet_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeAllMarketSheet
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest () :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeAllMarketSheet)
		{
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeAllMarketSheet)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllMarketSheet, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllMarketSheet, RC_OK)
		{
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_NewOrder SubscribeNotif_NewOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ModifyOrder SubscribeNotif_ModifyOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveOneOrder SubscribeNotif_RemoveOneOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveAllPreviousOrders SubscribeNotif_RemoveAllPreviousOrders;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveAllOrders SubscribeNotif_RemoveAllOrders;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_Retransmission SubscribeNotif_Retransmission;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ValuesUpdateOneInstrument SubscribeNotif_ValuesUpdateOneInstrument;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeAllMarketSheet, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeAllMarketSheet
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeAllMarketSheet, p)
		{
		}
	private:
	public:
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeAllMarketSheet, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeAllMarketSheet, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_NewOrder SubscribeNotif_NewOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ModifyOrder SubscribeNotif_ModifyOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveOneOrder SubscribeNotif_RemoveOneOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveAllPreviousOrders SubscribeNotif_RemoveAllPreviousOrders;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveAllOrders SubscribeNotif_RemoveAllOrders;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_Retransmission SubscribeNotif_Retransmission;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ValuesUpdateOneInstrument SubscribeNotif_ValuesUpdateOneInstrument;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeAllMarketSheet, p)
		{}
	};

}

}
#endif
