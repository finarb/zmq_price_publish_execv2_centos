/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#define FEEDOS_generated_INTERFACE_CONNECTION_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_Login_streaming \
		virtual void response_CONNECTION_Login_Started (FeedOS::Types::UserId inUID,  FeedOS::Types::UserGroupId inGID, uint16 inHeartbeatPeriod_seconds, Timestamp const & inServerDate); \
		virtual void response_CONNECTION_Login_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_Login (ReturnCode rc); \
		virtual void notif_Heartbeat	(Timestamp const & inServerDate); \
		virtual void notif_AdminMessage	(bool inUrgent, String const & inOrigin, String const & inHeadline, String const & inContent); \


	class INTERFACE_CONNECTION_Login_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_Login_streaming() {}

		virtual void response_CONNECTION_Login_Started (FeedOS::Types::UserId inUID,  FeedOS::Types::UserGroupId inGID, uint16 inHeartbeatPeriod_seconds, Timestamp const & inServerDate) = 0;
		virtual void response_CONNECTION_Login_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_Login (ReturnCode rc) = 0;
		virtual void notif_Heartbeat	(Timestamp const & inServerDate) = 0;
		virtual void notif_AdminMessage	(bool inUrgent, String const & inOrigin, String const & inHeadline, String const & inContent) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_LoginExt_streaming \
		virtual void response_CONNECTION_LoginExt_Started (FeedOS::Types::UserId inUID,  FeedOS::Types::UserGroupId inGID, uint16 inHeartbeatPeriod_seconds, Timestamp const & inServerDate); \
		virtual void response_CONNECTION_LoginExt_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_LoginExt (ReturnCode rc); \
		virtual void notif_DummyNotif	(uint32 inDummyField); \


	class INTERFACE_CONNECTION_LoginExt_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_LoginExt_streaming() {}

		virtual void response_CONNECTION_LoginExt_Started (FeedOS::Types::UserId inUID,  FeedOS::Types::UserGroupId inGID, uint16 inHeartbeatPeriod_seconds, Timestamp const & inServerDate) = 0;
		virtual void response_CONNECTION_LoginExt_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_LoginExt (ReturnCode rc) = 0;
		virtual void notif_DummyNotif	(uint32 inDummyField) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_MulticastDataRecovery_streaming \
		virtual void response_CONNECTION_MulticastDataRecovery_Started (uint32 inRangeBegin, uint32 inRangeEnd,  FeedOS::Types::ListOfBinaryBuffer const & inFrames); \
		virtual void response_CONNECTION_MulticastDataRecovery_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_MulticastDataRecovery (ReturnCode rc); \
		virtual void notif_RecoveredData	(uint32 inRangeBegin, uint32 inRangeEnd,  FeedOS::Types::ListOfBinaryBuffer const & inFrames); \


	class INTERFACE_CONNECTION_MulticastDataRecovery_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_MulticastDataRecovery_streaming() {}

		virtual void response_CONNECTION_MulticastDataRecovery_Started (uint32 inRangeBegin, uint32 inRangeEnd,  FeedOS::Types::ListOfBinaryBuffer const & inFrames) = 0;
		virtual void response_CONNECTION_MulticastDataRecovery_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_MulticastDataRecovery (ReturnCode rc) = 0;
		virtual void notif_RecoveredData	(uint32 inRangeBegin, uint32 inRangeEnd,  FeedOS::Types::ListOfBinaryBuffer const & inFrames) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming \
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started (); \
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc); \
		virtual void notif_ReplayData	(FeedOS::Types::ListOfBinaryBuffer const & inFrames); \


	class INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming() {}

		virtual void response_CONNECTION_MulticastDataReplayBySource_Started () = 0;
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc) = 0;
		virtual void notif_ReplayData	(FeedOS::Types::ListOfBinaryBuffer const & inFrames) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming \
		virtual void response_CONNECTION_SubscribeToFeedStatus_Started (FeedOS::Types::ListOfFeedStatus const & inFullSnapshot); \
		virtual void response_CONNECTION_SubscribeToFeedStatus_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_SubscribeToFeedStatus (ReturnCode rc); \
		virtual void notif_FeedStatusEvent	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatusEvent const & inEvent); \
		virtual void notif_FeedStatusUpdate	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatus const & inStatus); \


	class INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming() {}

		virtual void response_CONNECTION_SubscribeToFeedStatus_Started (FeedOS::Types::ListOfFeedStatus const & inFullSnapshot) = 0;
		virtual void response_CONNECTION_SubscribeToFeedStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_SubscribeToFeedStatus (ReturnCode rc) = 0;
		virtual void notif_FeedStatusEvent	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatusEvent const & inEvent) = 0;
		virtual void notif_FeedStatusUpdate	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatus const & inStatus) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_CONNECTION_SubscribeToFeedHandlerStatus_streaming \
		virtual void response_CONNECTION_SubscribeToFeedHandlerStatus_Started (FeedOS::Types::FeedHandlerConfiguration const & inConfiguration,  FeedOS::Types::FeedHandlerState const & inCurrentFeedHandlerState); \
		virtual void response_CONNECTION_SubscribeToFeedHandlerStatus_Failed (ReturnCode rc); \
		virtual void aborted_CONNECTION_SubscribeToFeedHandlerStatus (ReturnCode rc); \
		virtual void notif_FeedStatusEvent	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatusEvent const & inEvent); \
		virtual void notif_FeedHandlerStatusUpdate	(FeedOS::Types::FeedHandlerState const & inFeedHandlerState); \


	class INTERFACE_CONNECTION_SubscribeToFeedHandlerStatus_streaming
	{
	public:
		virtual ~INTERFACE_CONNECTION_SubscribeToFeedHandlerStatus_streaming() {}

		virtual void response_CONNECTION_SubscribeToFeedHandlerStatus_Started (FeedOS::Types::FeedHandlerConfiguration const & inConfiguration,  FeedOS::Types::FeedHandlerState const & inCurrentFeedHandlerState) = 0;
		virtual void response_CONNECTION_SubscribeToFeedHandlerStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_CONNECTION_SubscribeToFeedHandlerStatus (ReturnCode rc) = 0;
		virtual void notif_FeedStatusEvent	(String const & inSender, Timestamp const & inSenderUTCTimestamp,  FeedOS::Types::FeedStatusEvent const & inEvent) = 0;
		virtual void notif_FeedHandlerStatusUpdate	(FeedOS::Types::FeedHandlerState const & inFeedHandlerState) = 0;

	};
}
#endif
