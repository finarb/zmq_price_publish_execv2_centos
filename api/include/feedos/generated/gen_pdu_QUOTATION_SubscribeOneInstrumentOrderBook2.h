/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeOneInstrumentOrderBook2_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeOneInstrumentOrderBook2_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeOneInstrumentOrderBook2
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PolymorphicInstrumentCode const & a, int8 b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeOneInstrumentOrderBook2)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_int8 (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeOneInstrumentOrderBook2)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentOrderBook2, rc)
		{}
		inline SubscribeResponse (FOSInstrumentCode const & a, OrderBook const & b) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentOrderBook2, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_OrderBook (*this, b);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeOneInstrumentOrderBook2, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeOneInstrumentOrderBook2
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeOneInstrumentOrderBook2, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
			Decode_int8 (*this, m_OrderBookDepth);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
		inline int8 const & getOrderBookDepth() const { return m_OrderBookDepth; }
	private:
		PolymorphicInstrumentCode m_Code;
		int8 m_OrderBookDepth;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
		inline int8 & _refOrderBookDepth() { return m_OrderBookDepth; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeOneInstrumentOrderBook2, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentOrderBook2, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_OrderBook (*this, m_OrderBook);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline OrderBook const & getOrderBook() const { return m_OrderBook; }
	private:
		FOSInstrumentCode m_InternalCode;
		OrderBook m_OrderBook;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline OrderBook & _refOrderBook() { return m_OrderBook; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeOneInstrumentOrderBook2, p)
		{}
	};

}

}
#endif
