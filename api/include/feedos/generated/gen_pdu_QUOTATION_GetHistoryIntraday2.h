/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_GetHistoryIntraday2_H
#define FEEDOS_generated_PDU_QUOTATION_GetHistoryIntraday2_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_GetHistoryIntraday2
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (PolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, int32 d) :
			PDU_outbound_Request (IDS::Request_QUOTATION_GetHistoryIntraday2)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_int32 (*this, d);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryIntraday2, rc)
		{}
		inline Response (FOSInstrumentCode const & a, ListOfIntradayHistoryPoint2 const & b) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryIntraday2, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_ListOfIntradayHistoryPoint2 (*this, b);
		}
	};

}


namespace PDU_inbound_QUOTATION_GetHistoryIntraday2
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_GetHistoryIntraday2, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_end);
			Decode_int32 (*this, m_NbPoints);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
		inline Timestamp const & getServerUTCTimestamp_end() const { return m_ServerUTCTimestamp_end; }
		inline int32 const & getNbPoints() const { return m_NbPoints; }
	private:
		PolymorphicInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp_begin;
		Timestamp m_ServerUTCTimestamp_end;
		int32 m_NbPoints;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
		inline Timestamp & _refServerUTCTimestamp_end() { return m_ServerUTCTimestamp_end; }
		inline int32 & _refNbPoints() { return m_NbPoints; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_GetHistoryIntraday2, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_ListOfIntradayHistoryPoint2 (*this, m_Values);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline ListOfIntradayHistoryPoint2 const & getValues() const { return m_Values; }
	private:
		FOSInstrumentCode m_InternalCode;
		ListOfIntradayHistoryPoint2 m_Values;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline ListOfIntradayHistoryPoint2 & _refValues() { return m_Values; }
	};

}

}
#endif
