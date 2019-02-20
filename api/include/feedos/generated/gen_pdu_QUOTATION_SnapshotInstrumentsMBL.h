/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsMBL_H
#define FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsMBL_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SnapshotInstrumentsMBL
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfPolymorphicInstrumentCode const & a, ListOfOrderBookLayerId const & b, FOSInteger const & c, bool d) :
			PDU_outbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsMBL)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_ListOfOrderBookLayerId (*this, b);
			Encode_FOSInteger (*this, c);
			Encode_bool (*this, d);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsMBL, rc)
		{}
		inline Response (ListOfMBLSnapshot const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsMBL, RC_OK)
		{
			Encode_ListOfMBLSnapshot (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_SnapshotInstrumentsMBL
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsMBL, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_ListOfOrderBookLayerId (*this, m_LayerIds);
			Decode_FOSInteger (*this, m_OrderBookDepth);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline ListOfOrderBookLayerId const & getLayerIds() const { return m_LayerIds; }
		inline FOSInteger const & getOrderBookDepth() const { return m_OrderBookDepth; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		ListOfOrderBookLayerId m_LayerIds;
		FOSInteger m_OrderBookDepth;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline ListOfOrderBookLayerId & _refLayerIds() { return m_LayerIds; }
		inline FOSInteger & _refOrderBookDepth() { return m_OrderBookDepth; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsMBL, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfMBLSnapshot (*this, m_Result);
		}
		inline ListOfMBLSnapshot const & getResult() const { return m_Result; }
	private:
		ListOfMBLSnapshot m_Result;
	public:
		inline ListOfMBLSnapshot & _refResult() { return m_Result; }
	};

}

}
#endif
