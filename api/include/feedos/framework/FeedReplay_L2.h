
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_L2_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_L2_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_L2_DISPATCHER_H
#	include "../framework/PDU_L2_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_L2:	public FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_L2 (INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_L2_dispatcher(consumer)), Multicast_definitions::QuotationOrderBook)
		{
		}

		virtual ~FeedReplay_L2 ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()				{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllOrderBook_Started();	}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllOrderBook_Failed(rc);}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->aborted_QUOTATION_SubscribeAllOrderBook (rc);		}

	private:
		PDU_L2_dispatcher	* m_dispatcher;
	};

}
#endif
