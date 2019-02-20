
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_MULTIPLEXED_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_MULTIPLEXED_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_MULTIPLEXED_DISPATCHER_H
#	include "PDU_Multiplexed_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_Multiplexed:	public	FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_Multiplexed ()
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_Multiplexed_dispatcher), Multicast_definitions::Multiplexed)
		{
		}

		virtual ~FeedReplay_Multiplexed ()
		{
			delete m_dispatcher;
		}

		void set_consumer_L1		(INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming& c) { m_dispatcher->PDU_L1_dispatcher::set_consumer (c); }
		void set_consumer_L2		(INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming	& c) { m_dispatcher->PDU_L2_dispatcher::set_consumer (c); }
		void set_consumer_MBO		(INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming	& c) { m_dispatcher->PDU_MBO_dispatcher::set_consumer (c); }
		void set_consumer_FeedStatus(INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming	& c) { m_dispatcher->PDU_FeedStatus_dispatcher::set_consumer (c); }

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()
		{
			if (m_dispatcher->get_consumer_L1())			m_dispatcher->get_consumer_L1()			->response_QUOTATION_SubscribeAllDataAndStatus_Started();
			if (m_dispatcher->get_consumer_L2())			m_dispatcher->get_consumer_L2()			->response_QUOTATION_SubscribeAllOrderBook_Started();
			if (m_dispatcher->get_consumer_MBO())		m_dispatcher->get_consumer_MBO()			->response_QUOTATION_SubscribeAllMarketSheet_Started();
			if (m_dispatcher->get_consumer_FeedStatus())	
			{
				static FeedOS::Types::ListOfFeedStatus const empty_FullSnapshot;
				m_dispatcher->get_consumer_FeedStatus()	->response_CONNECTION_SubscribeToFeedStatus_Started(empty_FullSnapshot);
			}
		}
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)
		{
			if (m_dispatcher->get_consumer_L1())			m_dispatcher->get_consumer_L1()			->response_QUOTATION_SubscribeAllDataAndStatus_Failed(rc);	
			if (m_dispatcher->get_consumer_L2())			m_dispatcher->get_consumer_L2()			->response_QUOTATION_SubscribeAllOrderBook_Failed(rc);	
			if (m_dispatcher->get_consumer_MBO())		m_dispatcher->get_consumer_MBO()			->response_QUOTATION_SubscribeAllMarketSheet_Failed(rc);
			if (m_dispatcher->get_consumer_FeedStatus())	m_dispatcher->get_consumer_FeedStatus()	->response_CONNECTION_SubscribeToFeedStatus_Failed(rc);
		}
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)	
		{ 
			if (m_dispatcher->get_consumer_L1())			m_dispatcher->get_consumer_L1()			->aborted_QUOTATION_SubscribeAllDataAndStatus (rc);			
			if (m_dispatcher->get_consumer_L2())			m_dispatcher->get_consumer_L2()			->aborted_QUOTATION_SubscribeAllOrderBook (rc);			
			if (m_dispatcher->get_consumer_MBO())		m_dispatcher->get_consumer_MBO()			->aborted_QUOTATION_SubscribeAllMarketSheet(rc);
			if (m_dispatcher->get_consumer_FeedStatus())	m_dispatcher->get_consumer_FeedStatus()	->aborted_CONNECTION_SubscribeToFeedStatus(rc);
		}

	private:
		PDU_Multiplexed_dispatcher		* m_dispatcher;

	};
}
#endif
