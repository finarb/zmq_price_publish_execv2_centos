/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeMarketsOrderBook_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeMarketsOrderBook_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeMarketsOrderBook
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfFOSMarketId const & a) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeMarketsOrderBook)
		{
			Encode_ListOfFOSMarketId (*this, a);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeMarketsOrderBook)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsOrderBook, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsOrderBook, RC_OK)
		{
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MBLFullRefresh SubscribeNotif_MBLFullRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MBLOverlapRefresh SubscribeNotif_MBLOverlapRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MBLDeltaRefresh SubscribeNotif_MBLDeltaRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MBLMaxVisibleDepth SubscribeNotif_MBLMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeMarketsOrderBook, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeMarketsOrderBook
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeMarketsOrderBook, p)
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
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeMarketsOrderBook, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeMarketsOrderBook, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MBLFullRefresh SubscribeNotif_MBLFullRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MBLOverlapRefresh SubscribeNotif_MBLOverlapRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MBLDeltaRefresh SubscribeNotif_MBLDeltaRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MBLMaxVisibleDepth SubscribeNotif_MBLMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeMarketsOrderBook, p)
		{}
	};

}

}
#endif
