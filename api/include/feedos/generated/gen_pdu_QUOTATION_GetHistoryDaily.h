/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_GetHistoryDaily_H
#define FEEDOS_generated_PDU_QUOTATION_GetHistoryDaily_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_GetHistoryDaily
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (PolymorphicInstrumentCode const & a, YMD_Date const & b, YMD_Date const & c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_GetHistoryDaily)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_YMD_Date (*this, b);
			Encode_YMD_Date (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryDaily, rc)
		{}
		inline Response (FOSInstrumentCode const & a, ListOfDailyHistoryPoint const & b) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryDaily, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_ListOfDailyHistoryPoint (*this, b);
		}
	};

}


namespace PDU_inbound_QUOTATION_GetHistoryDaily
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_GetHistoryDaily, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
			Decode_YMD_Date (*this, m_MarketLocalDate_begin);
			Decode_YMD_Date (*this, m_MarketLocalDate_end);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
		inline YMD_Date const & getMarketLocalDate_begin() const { return m_MarketLocalDate_begin; }
		inline YMD_Date const & getMarketLocalDate_end() const { return m_MarketLocalDate_end; }
	private:
		PolymorphicInstrumentCode m_Code;
		YMD_Date m_MarketLocalDate_begin;
		YMD_Date m_MarketLocalDate_end;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
		inline YMD_Date & _refMarketLocalDate_begin() { return m_MarketLocalDate_begin; }
		inline YMD_Date & _refMarketLocalDate_end() { return m_MarketLocalDate_end; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_GetHistoryDaily, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_ListOfDailyHistoryPoint (*this, m_Values);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline ListOfDailyHistoryPoint const & getValues() const { return m_Values; }
	private:
		FOSInstrumentCode m_InternalCode;
		ListOfDailyHistoryPoint m_Values;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline ListOfDailyHistoryPoint & _refValues() { return m_Values; }
	};

}

}
#endif
