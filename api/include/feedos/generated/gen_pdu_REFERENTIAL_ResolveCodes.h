/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_ResolveCodes_H
#define FEEDOS_generated_PDU_REFERENTIAL_ResolveCodes_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_ResolveCodes
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfPolymorphicInstrumentCode const & a, bool b) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_ResolveCodes)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_bool (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_ResolveCodes, rc)
		{}
		inline Response (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_ResolveCodes, RC_OK)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_ResolveCodes
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_ResolveCodes, p)
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

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_ResolveCodes, p)
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

}

}
#endif
