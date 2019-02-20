/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_Lookup_H
#define FEEDOS_generated_PDU_REFERENTIAL_Lookup_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_Lookup
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (String const & a, uint16 b, LookupMode c, ListOfReferentialAttribute const & d, ListOfReferentialTagNumber const & e) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_Lookup)
		{
			Encode_String (*this, a);
			Encode_uint16 (*this, b);
			Encode_LookupMode (*this, c);
			Encode_ListOfReferentialAttribute (*this, d);
			Encode_ListOfReferentialTagNumber (*this, e);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_Lookup, rc)
		{}
		inline Response (ListOfInstrumentCharacteristics const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_Lookup, RC_OK)
		{
			Encode_ListOfInstrumentCharacteristics (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_Lookup
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_Lookup, p)
		{
			Decode_String (*this, m_Pattern);
			Decode_uint16 (*this, m_MaxHits);
			Decode_LookupMode (*this, m_Mode);
			Decode_ListOfReferentialAttribute (*this, m_Filter);
			Decode_ListOfReferentialTagNumber (*this, m_Format);
		}
		inline String const & getPattern() const { return m_Pattern; }
		inline uint16 const & getMaxHits() const { return m_MaxHits; }
		inline LookupMode const & getMode() const { return m_Mode; }
		inline ListOfReferentialAttribute const & getFilter() const { return m_Filter; }
		inline ListOfReferentialTagNumber const & getFormat() const { return m_Format; }
	private:
		String m_Pattern;
		uint16 m_MaxHits;
		LookupMode m_Mode;
		ListOfReferentialAttribute m_Filter;
		ListOfReferentialTagNumber m_Format;
	public:
		inline String & _refPattern() { return m_Pattern; }
		inline uint16 & _refMaxHits() { return m_MaxHits; }
		inline LookupMode & _refMode() { return m_Mode; }
		inline ListOfReferentialAttribute & _refFilter() { return m_Filter; }
		inline ListOfReferentialTagNumber & _refFormat() { return m_Format; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_Lookup, p)
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
