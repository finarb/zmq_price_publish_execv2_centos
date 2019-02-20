/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeMarketsDataAndStatus_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeMarketsDataAndStatus_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeMarketsDataAndStatus
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfFOSMarketId const & a) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeMarketsDataAndStatus)
		{
			Encode_ListOfFOSMarketId (*this, a);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeMarketsDataAndStatus)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsDataAndStatus, rc)
		{}
		inline SubscribeResponse (ListOfMarketStatus const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsDataAndStatus, RC_OK)
		{
			Encode_ListOfMarketStatus (*this, a);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeEvent SubscribeNotif_TradeEvent;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ValuesUpdate SubscribeNotif_ValuesUpdate;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MarketStatus SubscribeNotif_MarketStatus;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MarketNews SubscribeNotif_MarketNews;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeMarketsDataAndStatus, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeMarketsDataAndStatus
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeMarketsDataAndStatus, p)
		{
			Decode_ListOfFOSMarketId (*this, m_Markets);
		}
		inline ListOfFOSMarketId const & getMarkets() const { return m_Markets; }
	private:
		ListOfFOSMarketId m_Markets;
	public:
		inline ListOfFOSMarketId & _refMarkets() { return m_Markets; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeMarketsDataAndStatus, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsDataAndStatus, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfMarketStatus (*this, m_MarketsStatus);
		}
		inline ListOfMarketStatus const & getMarketsStatus() const { return m_MarketsStatus; }
	private:
		ListOfMarketStatus m_MarketsStatus;
	public:
		inline ListOfMarketStatus & _refMarketsStatus() { return m_MarketsStatus; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeEvent SubscribeNotif_TradeEvent;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ValuesUpdate SubscribeNotif_ValuesUpdate;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MarketStatus SubscribeNotif_MarketStatus;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MarketNews SubscribeNotif_MarketNews;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeMarketsDataAndStatus, p)
		{}
	};

}

}
#endif
