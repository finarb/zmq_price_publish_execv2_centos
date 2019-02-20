
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2013      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_NEWS_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_NEWS_H

#include "FeedReplay_by_source.h"
#include "PDU_News_dispatcher.h"	
#include "../generated/gen_interface_NEWS.h"

namespace FeedOS
{
	class FeedReplay_News: public FeedReplay_by_source_through_API 
	{
	public:
		FeedReplay_News(INTERFACE_NEWS_SubscribeNews_streaming & consumer);
		virtual ~FeedReplay_News();

	protected:
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started()
		{
			m_dispatcher->get_consumer()->response_NEWS_SubscribeNews_Started();
		}

		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed(ReturnCode rc)
		{
			m_dispatcher->get_consumer()->response_NEWS_SubscribeNews_Failed(rc);
		}

		virtual void aborted_CONNECTION_MulticastDataReplayBySource(ReturnCode rc)
		{
			m_dispatcher->get_consumer()->aborted_NEWS_SubscribeNews(rc);
		}

	private:
		PDU_News_dispatcher		* m_dispatcher;
	};
}

#endif
