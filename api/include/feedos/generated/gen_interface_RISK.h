/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_RISK_H
#define FEEDOS_generated_INTERFACE_RISK_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_RISK_SubscribeToSubmittedOrder_streaming \
		virtual void response_RISK_SubscribeToSubmittedOrder_Started (); \
		virtual void response_RISK_SubscribeToSubmittedOrder_Failed (ReturnCode rc); \
		virtual void aborted_RISK_SubscribeToSubmittedOrder (ReturnCode rc); \
		virtual void notif_SubmittedOrder	(BinaryBuffer inOrder, bool inNowOrNever); \


	class INTERFACE_RISK_SubscribeToSubmittedOrder_streaming
	{
	public:
		virtual ~INTERFACE_RISK_SubscribeToSubmittedOrder_streaming() {}

		virtual void response_RISK_SubscribeToSubmittedOrder_Started () = 0;
		virtual void response_RISK_SubscribeToSubmittedOrder_Failed (ReturnCode rc) = 0;
		virtual void aborted_RISK_SubscribeToSubmittedOrder (ReturnCode rc) = 0;
		virtual void notif_SubmittedOrder	(BinaryBuffer inOrder, bool inNowOrNever) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_RISK_SubscribeToExecReport_streaming \
		virtual void response_RISK_SubscribeToExecReport_Started (); \
		virtual void response_RISK_SubscribeToExecReport_Failed (ReturnCode rc); \
		virtual void aborted_RISK_SubscribeToExecReport (ReturnCode rc); \
		virtual void notif_ExecReport	(Timestamp const & inReceiveTimestamp, BinaryBuffer inExecReport); \
		virtual void notif_RejectedOrder	(Timestamp const & inRejectTimestamp,  FeedOS::Types::OrderRejectReason inOrderRejectReason, BinaryBuffer inOrderRejectReasonVerbose, BinaryBuffer inOrder, bool inNowOrNever); \


	class INTERFACE_RISK_SubscribeToExecReport_streaming
	{
	public:
		virtual ~INTERFACE_RISK_SubscribeToExecReport_streaming() {}

		virtual void response_RISK_SubscribeToExecReport_Started () = 0;
		virtual void response_RISK_SubscribeToExecReport_Failed (ReturnCode rc) = 0;
		virtual void aborted_RISK_SubscribeToExecReport (ReturnCode rc) = 0;
		virtual void notif_ExecReport	(Timestamp const & inReceiveTimestamp, BinaryBuffer inExecReport) = 0;
		virtual void notif_RejectedOrder	(Timestamp const & inRejectTimestamp,  FeedOS::Types::OrderRejectReason inOrderRejectReason, BinaryBuffer inOrderRejectReasonVerbose, BinaryBuffer inOrder, bool inNowOrNever) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_RISK_SubscribeToDropCopy_streaming \
		virtual void response_RISK_SubscribeToDropCopy_Started (); \
		virtual void response_RISK_SubscribeToDropCopy_Failed (ReturnCode rc); \
		virtual void aborted_RISK_SubscribeToDropCopy (ReturnCode rc); \
		virtual void notif_SubmittedOrder	(BinaryBuffer inOrder, bool inNowOrNever); \
		virtual void notif_ExecReport	(Timestamp const & inReceiveTimestamp, BinaryBuffer inExecReport); \
		virtual void notif_RejectedOrder	(Timestamp const & inRejectTimestamp,  FeedOS::Types::OrderRejectReason inOrderRejectReason, BinaryBuffer inOrderRejectReasonVerbose, BinaryBuffer inOrder, bool inNowOrNever); \


	class INTERFACE_RISK_SubscribeToDropCopy_streaming
	{
	public:
		virtual ~INTERFACE_RISK_SubscribeToDropCopy_streaming() {}

		virtual void response_RISK_SubscribeToDropCopy_Started () = 0;
		virtual void response_RISK_SubscribeToDropCopy_Failed (ReturnCode rc) = 0;
		virtual void aborted_RISK_SubscribeToDropCopy (ReturnCode rc) = 0;
		virtual void notif_SubmittedOrder	(BinaryBuffer inOrder, bool inNowOrNever) = 0;
		virtual void notif_ExecReport	(Timestamp const & inReceiveTimestamp, BinaryBuffer inExecReport) = 0;
		virtual void notif_RejectedOrder	(Timestamp const & inRejectTimestamp,  FeedOS::Types::OrderRejectReason inOrderRejectReason, BinaryBuffer inOrderRejectReasonVerbose, BinaryBuffer inOrder, bool inNowOrNever) = 0;

	};
}
#endif
