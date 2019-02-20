/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CORPORATE_ACTION_DeleteAdjustmentFactorEvents_H
#define FEEDOS_generated_PDU_CORPORATE_ACTION_DeleteAdjustmentFactorEvents_H

#include "gen_pdu_CORPORATE_ACTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CORPORATE_ACTION_DeleteAdjustmentFactorEvents
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfPolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, AdjustmentFactorEventTypeMask d) :
			PDU_outbound_Request (IDS::Request_CORPORATE_ACTION_DeleteAdjustmentFactorEvents)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_AdjustmentFactorEventTypeMask (*this, d);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_CORPORATE_ACTION_DeleteAdjustmentFactorEvents, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_CORPORATE_ACTION_DeleteAdjustmentFactorEvents, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_CORPORATE_ACTION_DeleteAdjustmentFactorEvents
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_CORPORATE_ACTION_DeleteAdjustmentFactorEvents, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_Timestamp (*this, m_EventDay_begin);
			Decode_Timestamp (*this, m_EventDay_end);
			Decode_AdjustmentFactorEventTypeMask (*this, m_Filter);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline Timestamp const & getEventDay_begin() const { return m_EventDay_begin; }
		inline Timestamp const & getEventDay_end() const { return m_EventDay_end; }
		inline AdjustmentFactorEventTypeMask const & getFilter() const { return m_Filter; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		Timestamp m_EventDay_begin;
		Timestamp m_EventDay_end;
		AdjustmentFactorEventTypeMask m_Filter;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline Timestamp & _refEventDay_begin() { return m_EventDay_begin; }
		inline Timestamp & _refEventDay_end() { return m_EventDay_end; }
		inline AdjustmentFactorEventTypeMask & _refFilter() { return m_Filter; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_CORPORATE_ACTION_DeleteAdjustmentFactorEvents, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
