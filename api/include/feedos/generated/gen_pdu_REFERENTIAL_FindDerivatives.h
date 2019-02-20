/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_FindDerivatives_H
#define FEEDOS_generated_PDU_REFERENTIAL_FindDerivatives_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_FindDerivatives
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (PolymorphicInstrumentCode const & a, ListOfReferentialAttribute const & b, ListOfReferentialTagNumber const & c) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_FindDerivatives)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_ListOfReferentialAttribute (*this, b);
			Encode_ListOfReferentialTagNumber (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_FindDerivatives, rc)
		{}
		inline Response (PolymorphicInstrumentCode const & a, ListOfInstrumentCharacteristics const & b) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_FindDerivatives, RC_OK)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_ListOfInstrumentCharacteristics (*this, b);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_FindDerivatives
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_FindDerivatives, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_UnderlyingInstrument);
			Decode_ListOfReferentialAttribute (*this, m_Filter);
			Decode_ListOfReferentialTagNumber (*this, m_Format);
		}
		inline PolymorphicInstrumentCode const & getUnderlyingInstrument() const { return m_UnderlyingInstrument; }
		inline ListOfReferentialAttribute const & getFilter() const { return m_Filter; }
		inline ListOfReferentialTagNumber const & getFormat() const { return m_Format; }
	private:
		PolymorphicInstrumentCode m_UnderlyingInstrument;
		ListOfReferentialAttribute m_Filter;
		ListOfReferentialTagNumber m_Format;
	public:
		inline PolymorphicInstrumentCode & _refUnderlyingInstrument() { return m_UnderlyingInstrument; }
		inline ListOfReferentialAttribute & _refFilter() { return m_Filter; }
		inline ListOfReferentialTagNumber & _refFormat() { return m_Format; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_FindDerivatives, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_PolymorphicInstrumentCode (*this, m_UnderlyingInstrument);
			Decode_ListOfInstrumentCharacteristics (*this, m_Instruments);
		}
		inline PolymorphicInstrumentCode const & getUnderlyingInstrument() const { return m_UnderlyingInstrument; }
		inline ListOfInstrumentCharacteristics const & getInstruments() const { return m_Instruments; }
	private:
		PolymorphicInstrumentCode m_UnderlyingInstrument;
		ListOfInstrumentCharacteristics m_Instruments;
	public:
		inline PolymorphicInstrumentCode & _refUnderlyingInstrument() { return m_UnderlyingInstrument; }
		inline ListOfInstrumentCharacteristics & _refInstruments() { return m_Instruments; }
	};

}

}
#endif
