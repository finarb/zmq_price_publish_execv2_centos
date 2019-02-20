/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsL1_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsL1_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeInstrumentsL1
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, ListOfQuotationTagNumber const & b, QuotationContentMask c, bool d) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsL1)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_ListOfQuotationTagNumber (*this, b);
			Encode_QuotationContentMask (*this, c);
			Encode_bool (*this, d);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsL1)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL1, rc)
		{}
		inline SubscribeResponse (uint32 const & a, ListOfInstrumentStatusL1 const & b) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL1, RC_OK)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfInstrumentStatusL1 (*this, b);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsL1, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeInstrumentsL1
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsL1, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_ListOfQuotationTagNumber (*this, m_OtherValuesToLookFor);
			Decode_QuotationContentMask (*this, m_ContentMask);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline ListOfQuotationTagNumber const & getOtherValuesToLookFor() const { return m_OtherValuesToLookFor; }
		inline QuotationContentMask const & getContentMask() const { return m_ContentMask; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		ListOfQuotationTagNumber m_OtherValuesToLookFor;
		QuotationContentMask m_ContentMask;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline ListOfQuotationTagNumber & _refOtherValuesToLookFor() { return m_OtherValuesToLookFor; }
		inline QuotationContentMask & _refContentMask() { return m_ContentMask; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsL1, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL1, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfInstrumentStatusL1 (*this, m_Snapshot);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfInstrumentStatusL1 const & getSnapshot() const { return m_Snapshot; }
	private:
		uint32 m_Ticket;
		ListOfInstrumentStatusL1 m_Snapshot;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfInstrumentStatusL1 & _refSnapshot() { return m_Snapshot; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeEventExt SubscribeNotif_TradeEventExt;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_TradeCancelCorrection SubscribeNotif_TradeCancelCorrection;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsL1, p)
		{}
	};

}

}
#endif
