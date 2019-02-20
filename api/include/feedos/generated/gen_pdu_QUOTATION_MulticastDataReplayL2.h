/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_MulticastDataReplayL2_H
#define FEEDOS_generated_PDU_QUOTATION_MulticastDataReplayL2_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_MulticastDataReplayL2
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (QuotationReplaySubject const & a, QuotationReplayL2Filter const & b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MulticastDataReplayL2)
		{
			Encode_QuotationReplaySubject (*this, a);
			Encode_QuotationReplayL2Filter (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MulticastDataReplayL2)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL2, rc)
		{}
		inline SubscribeResponse (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL2, RC_OK)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_MulticastDataReplayHeader SubscribeNotif_MulticastDataReplayHeader;

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
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MulticastDataReplayL2, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_MulticastDataReplayL2
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MulticastDataReplayL2, p)
		{
			Decode_QuotationReplaySubject (*this, m_Subject);
			Decode_QuotationReplayL2Filter (*this, m_ContentFilter);
		}
		inline QuotationReplaySubject const & getSubject() const { return m_Subject; }
		inline QuotationReplayL2Filter const & getContentFilter() const { return m_ContentFilter; }
	private:
		QuotationReplaySubject m_Subject;
		QuotationReplayL2Filter m_ContentFilter;
	public:
		inline QuotationReplaySubject & _refSubject() { return m_Subject; }
		inline QuotationReplayL2Filter & _refContentFilter() { return m_ContentFilter; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MulticastDataReplayL2, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MulticastDataReplayL2, p)
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
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MulticastDataReplayL2, p)
		{}
	};

}

}
#endif
