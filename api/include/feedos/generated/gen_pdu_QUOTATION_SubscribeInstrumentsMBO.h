/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsMBO_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeInstrumentsMBO_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeInstrumentsMBO
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, bool b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsMBO)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_bool (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsMBO)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsMBO, rc)
		{}
		inline SubscribeResponse (uint32 const & a, ListOfFOSInstrumentCode const & b) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsMBO, RC_OK)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfFOSInstrumentCode (*this, b);
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
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsMBO, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeInstrumentsMBO
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeInstrumentsMBO, p)
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
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeInstrumentsMBO, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeInstrumentsMBO, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfFOSInstrumentCode (*this, m_InternalCodes);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfFOSInstrumentCode const & getInternalCodes() const { return m_InternalCodes; }
	private:
		uint32 m_Ticket;
		ListOfFOSInstrumentCode m_InternalCodes;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfFOSInstrumentCode & _refInternalCodes() { return m_InternalCodes; }
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
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeInstrumentsMBO, p)
		{}
	};

}

}
#endif
