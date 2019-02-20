/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsMBLRemove_H
#define FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsMBLRemove_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_ChgSubscribeInstrumentsMBLRemove
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (uint32 const & a, ListOfPolymorphicInstrumentCode const & b) :
			PDU_outbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsMBLRemove)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsMBLRemove, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsMBLRemove, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_QUOTATION_ChgSubscribeInstrumentsMBLRemove
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsMBLRemove, p)
		{
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
	private:
		uint32 m_Ticket;
		ListOfPolymorphicInstrumentCode m_Codes;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsMBLRemove, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
