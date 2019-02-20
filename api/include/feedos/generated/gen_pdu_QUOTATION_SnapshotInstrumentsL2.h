/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsL2_H
#define FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsL2_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SnapshotInstrumentsL2
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfPolymorphicInstrumentCode const & a, int8 b, bool c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsL2)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_int8 (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL2, rc)
		{}
		inline Response (ListOfInstrumentStatusL2 const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL2, RC_OK)
		{
			Encode_ListOfInstrumentStatusL2 (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_SnapshotInstrumentsL2
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsL2, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_int8 (*this, m_OrderBookDepth);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline int8 const & getOrderBookDepth() const { return m_OrderBookDepth; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		int8 m_OrderBookDepth;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline int8 & _refOrderBookDepth() { return m_OrderBookDepth; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL2, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfInstrumentStatusL2 (*this, m_Result);
		}
		inline ListOfInstrumentStatusL2 const & getResult() const { return m_Result; }
	private:
		ListOfInstrumentStatusL2 m_Result;
	public:
		inline ListOfInstrumentStatusL2 & _refResult() { return m_Result; }
	};

}

}
#endif
