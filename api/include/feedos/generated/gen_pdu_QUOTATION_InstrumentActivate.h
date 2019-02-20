/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_InstrumentActivate_H
#define FEEDOS_generated_PDU_QUOTATION_InstrumentActivate_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_InstrumentActivate
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (String const & a, ListOfPolymorphicInstrumentCode const & b, bool c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_InstrumentActivate)
		{
			Encode_String (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_InstrumentActivate, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_QUOTATION_InstrumentActivate, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_QUOTATION_InstrumentActivate
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_InstrumentActivate, p)
		{
			Decode_String (*this, m_OutputChannel);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline String const & getOutputChannel() const { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		String m_OutputChannel;
		ListOfPolymorphicInstrumentCode m_Codes;
		bool m_IgnoreInvalidCodes;
	public:
		inline String & _refOutputChannel() { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_InstrumentActivate, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
