/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL2Add_H
#define FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL2Add_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_ChgSubscribeInstrumentsL2Add
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (uint32 const & a, ListOfPolymorphicInstrumentCode const & b, bool c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL2Add)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL2Add, rc)
		{}
		inline Response (ListOfInstrumentStatusL2 const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL2Add, RC_OK)
		{
			Encode_ListOfInstrumentStatusL2 (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_ChgSubscribeInstrumentsL2Add
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL2Add, p)
		{
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		uint32 m_Ticket;
		ListOfPolymorphicInstrumentCode m_Codes;
		bool m_IgnoreInvalidCodes;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL2Add, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfInstrumentStatusL2 (*this, m_Snapshot);
		}
		inline ListOfInstrumentStatusL2 const & getSnapshot() const { return m_Snapshot; }
	private:
		ListOfInstrumentStatusL2 m_Snapshot;
	public:
		inline ListOfInstrumentStatusL2 & _refSnapshot() { return m_Snapshot; }
	};

}

}
#endif
