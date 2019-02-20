
#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_REF_DATA_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_REF_DATA_H

#include "FeedReplay_by_source.h"
#include "PDU_RefData_dispatcher.h"
#include "../generated/gen_interface_REFERENTIAL.h"

namespace FeedOS
{
	class FeedReplay_RefData: public FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_RefData(INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming & consumer)
		: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_RefData_dispatcher(consumer)), Multicast_definitions::ReferentialData)
		{}

		virtual ~FeedReplay_RefData ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()				{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_REFERENTIAL_SubscribeAllReferential_Started();	}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_REFERENTIAL_SubscribeAllReferential_Failed(rc);}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->aborted_REFERENTIAL_SubscribeAllReferential (rc);		}

	private:
		PDU_RefData_dispatcher * m_dispatcher;
	};
}

#endif
