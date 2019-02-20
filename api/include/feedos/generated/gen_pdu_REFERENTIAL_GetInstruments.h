/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_GetInstruments_H
#define FEEDOS_generated_PDU_REFERENTIAL_GetInstruments_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_GetInstruments
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfPolymorphicInstrumentCode const & a, ListOfReferentialTagNumber const & b, bool c) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_GetInstruments)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_ListOfReferentialTagNumber (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetInstruments, rc)
		{}
		inline Response (ListOfInstrumentCharacteristics const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetInstruments, RC_OK)
		{
			Encode_ListOfInstrumentCharacteristics (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_GetInstruments
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_GetInstruments, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_ListOfReferentialTagNumber (*this, m_Format);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline ListOfReferentialTagNumber const & getFormat() const { return m_Format; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		ListOfReferentialTagNumber m_Format;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline ListOfReferentialTagNumber & _refFormat() { return m_Format; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_GetInstruments, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfInstrumentCharacteristics (*this, m_Instruments);
		}
		inline ListOfInstrumentCharacteristics const & getInstruments() const { return m_Instruments; }
	private:
		ListOfInstrumentCharacteristics m_Instruments;
	public:
		inline ListOfInstrumentCharacteristics & _refInstruments() { return m_Instruments; }
	};

}

}
#endif
