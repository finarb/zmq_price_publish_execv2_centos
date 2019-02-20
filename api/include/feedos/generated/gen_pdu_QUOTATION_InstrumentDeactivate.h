/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_InstrumentDeactivate_H
#define FEEDOS_generated_PDU_QUOTATION_InstrumentDeactivate_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_InstrumentDeactivate
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (String const & a, ListOfPolymorphicInstrumentCode const & b) :
			PDU_outbound_Request (IDS::Request_QUOTATION_InstrumentDeactivate)
		{
			Encode_String (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_InstrumentDeactivate, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_QUOTATION_InstrumentDeactivate, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_QUOTATION_InstrumentDeactivate
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_InstrumentDeactivate, p)
		{
			Decode_String (*this, m_OutputChannel);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
		}
		inline String const & getOutputChannel() const { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
	private:
		String m_OutputChannel;
		ListOfPolymorphicInstrumentCode m_Codes;
	public:
		inline String & _refOutputChannel() { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_InstrumentDeactivate, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
