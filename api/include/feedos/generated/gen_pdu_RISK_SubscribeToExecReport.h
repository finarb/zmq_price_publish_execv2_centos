/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_RISK_SubscribeToExecReport_H
#define FEEDOS_generated_PDU_RISK_SubscribeToExecReport_H

#include "gen_pdu_RISK_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_RISK_SubscribeToExecReport
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest () :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_RISK_SubscribeToExecReport)
		{
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_RISK_SubscribeToExecReport)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_RISK_SubscribeToExecReport, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_RISK_SubscribeToExecReport, RC_OK)
		{
		}
	};

	typedef PDU_outbound_RISK::SubscribeNotif_ExecReport SubscribeNotif_ExecReport;

	typedef PDU_outbound_RISK::SubscribeNotif_RejectedOrder SubscribeNotif_RejectedOrder;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_RISK_SubscribeToExecReport, rc)
		{}
	};

}


namespace PDU_inbound_RISK_SubscribeToExecReport
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_RISK_SubscribeToExecReport, p)
		{
		}
	private:
	public:
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_RISK_SubscribeToExecReport, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_RISK_SubscribeToExecReport, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_RISK::SubscribeNotif_ExecReport SubscribeNotif_ExecReport;

	typedef PDU_inbound_RISK::SubscribeNotif_RejectedOrder SubscribeNotif_RejectedOrder;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_RISK_SubscribeToExecReport, p)
		{}
	};

}

}
#endif
