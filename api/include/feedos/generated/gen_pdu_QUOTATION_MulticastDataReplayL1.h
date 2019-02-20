/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_MulticastDataReplayL1_H
#define FEEDOS_generated_PDU_QUOTATION_MulticastDataReplayL1_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_MulticastDataReplayL1
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (QuotationReplaySubject const & a, QuotationReplayL1Filter const & b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MulticastDataReplayL1)
		{
			Encode_QuotationReplaySubject (*this, a);
			Encode_QuotationReplayL1Filter (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MulticastDataReplayL1)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL1, rc)
		{}
		inline SubscribeResponse (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL1, RC_OK)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MulticastDataReplayHeader SubscribeNotif_MulticastDataReplayHeader;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeEvent SubscribeNotif_TradeEvent;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ValuesUpdate SubscribeNotif_ValuesUpdate;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MarketStatus SubscribeNotif_MarketStatus;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MarketNews SubscribeNotif_MarketNews;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MulticastDataReplayL1, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_MulticastDataReplayL1
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MulticastDataReplayL1, p)
		{
			Decode_QuotationReplaySubject (*this, m_Subject);
			Decode_QuotationReplayL1Filter (*this, m_ContentFilter);
		}
		inline QuotationReplaySubject const & getSubject() const { return m_Subject; }
		inline QuotationReplayL1Filter const & getContentFilter() const { return m_ContentFilter; }
	private:
		QuotationReplaySubject m_Subject;
		QuotationReplayL1Filter m_ContentFilter;
	public:
		inline QuotationReplaySubject & _refSubject() { return m_Subject; }
		inline QuotationReplayL1Filter & _refContentFilter() { return m_ContentFilter; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MulticastDataReplayL1, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL1, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfFOSInstrumentCode (*this, m_InternalCodes);
		}
		inline ListOfFOSInstrumentCode const & getInternalCodes() const { return m_InternalCodes; }
	private:
		ListOfFOSInstrumentCode m_InternalCodes;
	public:
		inline ListOfFOSInstrumentCode & _refInternalCodes() { return m_InternalCodes; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MulticastDataReplayHeader SubscribeNotif_MulticastDataReplayHeader;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeEvent SubscribeNotif_TradeEvent;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ValuesUpdate SubscribeNotif_ValuesUpdate;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MarketStatus SubscribeNotif_MarketStatus;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_MarketNews SubscribeNotif_MarketNews;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MulticastDataReplayL1, p)
		{}
	};

}

}
#endif
