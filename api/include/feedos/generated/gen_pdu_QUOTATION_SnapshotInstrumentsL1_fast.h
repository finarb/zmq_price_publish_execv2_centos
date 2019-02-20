/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsL1_fast_H
#define FEEDOS_generated_PDU_QUOTATION_SnapshotInstrumentsL1_fast_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SnapshotInstrumentsL1_fast
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfFOSInstrumentCode const & a, ListOfQuotationTagNumber const & b, bool c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsL1_fast)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
			Encode_ListOfQuotationTagNumber (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL1_fast, rc)
		{}
		inline Response (ListOfInstrumentStatusL1 const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL1_fast, RC_OK)
		{
			Encode_ListOfInstrumentStatusL1 (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_SnapshotInstrumentsL1_fast
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_SnapshotInstrumentsL1_fast, p)
		{
			Decode_ListOfFOSInstrumentCode (*this, m_Codes);
			Decode_ListOfQuotationTagNumber (*this, m_Values);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline ListOfFOSInstrumentCode const & getCodes() const { return m_Codes; }
		inline ListOfQuotationTagNumber const & getValues() const { return m_Values; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		ListOfFOSInstrumentCode m_Codes;
		ListOfQuotationTagNumber m_Values;
		bool m_IgnoreInvalidCodes;
	public:
		inline ListOfFOSInstrumentCode & _refCodes() { return m_Codes; }
		inline ListOfQuotationTagNumber & _refValues() { return m_Values; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_SnapshotInstrumentsL1_fast, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfInstrumentStatusL1 (*this, m_Result);
		}
		inline ListOfInstrumentStatusL1 const & getResult() const { return m_Result; }
	private:
		ListOfInstrumentStatusL1 m_Result;
	public:
		inline ListOfInstrumentStatusL1 & _refResult() { return m_Result; }
	};

}

}
#endif
