/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CORPORATE_ACTION_PutAdjustmentFactorEvents_H
#define FEEDOS_generated_PDU_CORPORATE_ACTION_PutAdjustmentFactorEvents_H

#include "gen_pdu_CORPORATE_ACTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CORPORATE_ACTION_PutAdjustmentFactorEvents
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfAdjustmentFactorEvent const & a) :
			PDU_outbound_Request (IDS::Request_CORPORATE_ACTION_PutAdjustmentFactorEvents)
		{
			Encode_ListOfAdjustmentFactorEvent (*this, a);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_CORPORATE_ACTION_PutAdjustmentFactorEvents, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_CORPORATE_ACTION_PutAdjustmentFactorEvents, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_CORPORATE_ACTION_PutAdjustmentFactorEvents
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_CORPORATE_ACTION_PutAdjustmentFactorEvents, p)
		{
			Decode_ListOfAdjustmentFactorEvent (*this, m_Events);
		}
		inline ListOfAdjustmentFactorEvent const & getEvents() const { return m_Events; }
	private:
		ListOfAdjustmentFactorEvent m_Events;
	public:
		inline ListOfAdjustmentFactorEvent & _refEvents() { return m_Events; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_CORPORATE_ACTION_PutAdjustmentFactorEvents, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
