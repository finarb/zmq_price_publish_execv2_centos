
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_MBO_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_MBO_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_MBO_DISPATCHER_H
#	include "../framework/PDU_MBO_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_MBO:	public FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_MBO (INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming & consumer)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_MBO_dispatcher(consumer)), Multicast_definitions::QuotationMarketSheet)
		{
		}

		virtual ~FeedReplay_MBO ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()				{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllMarketSheet_Started();	}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllMarketSheet_Failed(rc);}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->aborted_QUOTATION_SubscribeAllMarketSheet (rc);		}

	private:
		PDU_MBO_dispatcher	* m_dispatcher;
	};

}
#endif
