/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_GetHistoryIntradayExtended_H
#define FEEDOS_generated_PDU_QUOTATION_GetHistoryIntradayExtended_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_GetHistoryIntradayExtended
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (PolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_GetHistoryIntradayExtended)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryIntradayExtended, rc)
		{}
		inline Response (FOSInstrumentCode const & a, ListOfIntradayHistoryPointExtended const & b) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryIntradayExtended, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_ListOfIntradayHistoryPointExtended (*this, b);
		}
	};

}


namespace PDU_inbound_QUOTATION_GetHistoryIntradayExtended
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_GetHistoryIntradayExtended, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_end);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
		inline Timestamp const & getServerUTCTimestamp_end() const { return m_ServerUTCTimestamp_end; }
	private:
		PolymorphicInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp_begin;
		Timestamp m_ServerUTCTimestamp_end;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
		inline Timestamp & _refServerUTCTimestamp_end() { return m_ServerUTCTimestamp_end; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_GetHistoryIntradayExtended, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_ListOfIntradayHistoryPointExtended (*this, m_Values);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline ListOfIntradayHistoryPointExtended const & getValues() const { return m_Values; }
	private:
		FOSInstrumentCode m_InternalCode;
		ListOfIntradayHistoryPointExtended m_Values;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline ListOfIntradayHistoryPointExtended & _refValues() { return m_Values; }
	};

}

}
#endif
