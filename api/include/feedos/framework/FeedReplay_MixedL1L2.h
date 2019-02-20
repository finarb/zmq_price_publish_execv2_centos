
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_MIXED_L1L2_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_MIXED_L1L2_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_MIXED_L1L2_DISPATCHER_H
#	include "PDU_MixedL1L2_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_MixedL1L2:	public	FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_MixedL1L2 (	INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming	& consumer_L1,
								INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming		& consumer_L2)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_MixedL1L2_dispatcher(consumer_L1,consumer_L2)), Multicast_definitions::QuotationMixedL1L2)
		{
		}

		virtual ~FeedReplay_MixedL1L2 ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()
		{
			if (m_dispatcher->get_consumer_L1())	m_dispatcher->get_consumer_L1()->response_QUOTATION_SubscribeAllDataAndStatus_Started();
			if (m_dispatcher->get_consumer_L2())	m_dispatcher->get_consumer_L2()->response_QUOTATION_SubscribeAllOrderBook_Started();
		}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)
		{
			if (m_dispatcher->get_consumer_L1())	m_dispatcher->get_consumer_L1()->response_QUOTATION_SubscribeAllDataAndStatus_Failed(rc);	
			if (m_dispatcher->get_consumer_L2())	m_dispatcher->get_consumer_L2()->response_QUOTATION_SubscribeAllOrderBook_Failed(rc);	
		}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)	
		{ 
			if (m_dispatcher->get_consumer_L1())	m_dispatcher->get_consumer_L1()->aborted_QUOTATION_SubscribeAllDataAndStatus (rc);			
			if (m_dispatcher->get_consumer_L2())	m_dispatcher->get_consumer_L2()->aborted_QUOTATION_SubscribeAllOrderBook (rc);			
		}

	private:
		PDU_MixedL1L2_dispatcher		* m_dispatcher;

	};
}
#endif
