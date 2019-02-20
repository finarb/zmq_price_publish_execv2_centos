/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_H
#define FEEDOS_generated_PDU_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_H

#include "gen_pdu_CORPORATE_ACTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CORPORATE_ACTION_DownloadAdjustmentFactorEvents
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, AdjustmentFactorEventTypeMask d) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_CORPORATE_ACTION_DownloadAdjustmentFactorEvents)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_AdjustmentFactorEventTypeMask (*this, d);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CORPORATE_ACTION_DownloadAdjustmentFactorEvents)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, RC_OK)
		{
		}
	};

	class SubscribeNotif_AdjustmentFactorEvents: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_AdjustmentFactorEvents (ListOfAdjustmentFactorEvent const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_AdjustmentFactorEvents)
		{
			Encode_ListOfAdjustmentFactorEvent (*this, a);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, rc)
		{}
	};

}


namespace PDU_inbound_CORPORATE_ACTION_DownloadAdjustmentFactorEvents
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, p)
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

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	class SubscribeNotif_AdjustmentFactorEvents: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_AdjustmentFactorEvents (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_AdjustmentFactorEvents, p)
		{
			Decode_ListOfAdjustmentFactorEvent (*this, m_Events);
		}
		inline ListOfAdjustmentFactorEvent const & getEvents() const { return m_Events; }
	private:
		ListOfAdjustmentFactorEvent m_Events;
	public:
		inline ListOfAdjustmentFactorEvent & _refEvents() { return m_Events; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CORPORATE_ACTION_DownloadAdjustmentFactorEvents, p)
		{}
	};

}

}
#endif
