/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsL2_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsL2_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeInstrumentsL2
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, bool b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsL2)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_bool (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsL2)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL2, rc)
		{}
		inline SubscribeResponse (uint32 const & a, ListOfInstrumentStatusL2 const & b) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL2, RC_OK)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfInstrumentStatusL2 (*this, b);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsL2, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeInstrumentsL2
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsL2, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsL2, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsL2, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfInstrumentStatusL2 (*this, m_Snapshot);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfInstrumentStatusL2 const & getSnapshot() const { return m_Snapshot; }
	private:
		uint32 m_Ticket;
		ListOfInstrumentStatusL2 m_Snapshot;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfInstrumentStatusL2 & _refSnapshot() { return m_Snapshot; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookRefresh SubscribeNotif_OrderBookRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookDeltaRefresh SubscribeNotif_OrderBookDeltaRefresh;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_OrderBookMaxVisibleDepth SubscribeNotif_OrderBookMaxVisibleDepth;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsL2, p)
		{}
	};

}

}
#endif
