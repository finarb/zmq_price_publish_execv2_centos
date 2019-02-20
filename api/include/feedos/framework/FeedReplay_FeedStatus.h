
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_FEEDSTATUS_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_FEEDSTATUS_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_FEEDSTATUS_DISPATCHER_H
#	include "../framework/PDU_FeedStatus_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_FeedStatus:	public FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_FeedStatus (INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming & consumer)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_FeedStatus_dispatcher(consumer)), Multicast_definitions::ConnectionFeedStatus)
		{
		}

		virtual ~FeedReplay_FeedStatus ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()
		{
			if (m_dispatcher->get_consumer())
			{
				static FeedOS::Types::ListOfFeedStatus const empty_FullSnapshot;
				m_dispatcher->get_consumer()->response_CONNECTION_SubscribeToFeedStatus_Started(empty_FullSnapshot);
			}
		}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_CONNECTION_SubscribeToFeedStatus_Failed(rc);}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->aborted_CONNECTION_SubscribeToFeedStatus (rc);		}

	private:
		PDU_FeedStatus_dispatcher	* m_dispatcher;
	};

}
#endif
