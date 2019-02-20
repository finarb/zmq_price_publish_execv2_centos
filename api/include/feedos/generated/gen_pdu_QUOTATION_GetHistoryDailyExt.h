/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_GetHistoryDailyExt_H
#define FEEDOS_generated_PDU_QUOTATION_GetHistoryDailyExt_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_GetHistoryDailyExt
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (PolymorphicInstrumentCode const & a, YMD_Date const & b, YMD_Date const & c, DailyExtPointType d, AdjustmentFactorEventTypeMask e) :
			PDU_outbound_Request (IDS::Request_QUOTATION_GetHistoryDailyExt)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
			Encode_YMD_Date (*this, b);
			Encode_YMD_Date (*this, c);
			Encode_DailyExtPointType (*this, d);
			Encode_AdjustmentFactorEventTypeMask (*this, e);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryDailyExt, rc)
		{}
		inline Response (FOSInstrumentCode const & a, ListOfDailyHistoryPointExt const & b) :
			PDU_outbound_Response (IDS::Response_QUOTATION_GetHistoryDailyExt, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_ListOfDailyHistoryPointExt (*this, b);
		}
	};

}


namespace PDU_inbound_QUOTATION_GetHistoryDailyExt
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_GetHistoryDailyExt, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
			Decode_YMD_Date (*this, m_BeginDate);
			Decode_YMD_Date (*this, m_EndDate);
			Decode_DailyExtPointType (*this, m_PointType);
			Decode_AdjustmentFactorEventTypeMask (*this, m_AdjustmentFactorEventTypes);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
		inline YMD_Date const & getBeginDate() const { return m_BeginDate; }
		inline YMD_Date const & getEndDate() const { return m_EndDate; }
		inline DailyExtPointType const & getPointType() const { return m_PointType; }
		inline AdjustmentFactorEventTypeMask const & getAdjustmentFactorEventTypes() const { return m_AdjustmentFactorEventTypes; }
	private:
		PolymorphicInstrumentCode m_Code;
		YMD_Date m_BeginDate;
		YMD_Date m_EndDate;
		DailyExtPointType m_PointType;
		AdjustmentFactorEventTypeMask m_AdjustmentFactorEventTypes;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
		inline YMD_Date & _refBeginDate() { return m_BeginDate; }
		inline YMD_Date & _refEndDate() { return m_EndDate; }
		inline DailyExtPointType & _refPointType() { return m_PointType; }
		inline AdjustmentFactorEventTypeMask & _refAdjustmentFactorEventTypes() { return m_AdjustmentFactorEventTypes; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_GetHistoryDailyExt, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_ListOfDailyHistoryPointExt (*this, m_Values);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline ListOfDailyHistoryPointExt const & getValues() const { return m_Values; }
	private:
		FOSInstrumentCode m_InternalCode;
		ListOfDailyHistoryPointExt m_Values;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline ListOfDailyHistoryPointExt & _refValues() { return m_Values; }
	};

}

}
#endif
