
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_L1_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_L1_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_L1_DISPATCHER_H
#	include "../framework/PDU_L1_dispatcher.h"	
#endif

namespace FeedOS {
	
	class FeedReplay_L1: public FeedReplay_by_source_through_API
	{
	public:
		FeedReplay_L1 (INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & consumer)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_L1_dispatcher(consumer)), Multicast_definitions::QuotationDataAndStatus)
		{
		}

		virtual ~FeedReplay_L1 ()
		{
			delete m_dispatcher;
		}

		void set_filter_MessageTypes (	bool notif_TradeEvent,
										bool notif_ValuesUpdate,	
										bool notif_MarketStatus,
										bool notif_MarketNews,
										bool notif_TradeCancelCorrection
									)
		{
			m_dispatcher->set_filter_MessageTypes(notif_TradeEvent,notif_ValuesUpdate,notif_MarketStatus,notif_MarketNews, notif_TradeCancelCorrection);
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()				{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllDataAndStatus_Started(); }
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllDataAndStatus_Failed(rc); }
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ if (m_dispatcher->get_consumer()) m_dispatcher->get_consumer()->aborted_QUOTATION_SubscribeAllDataAndStatus (rc);	}

	private:
		PDU_L1_dispatcher 	* m_dispatcher;
	};
}


#endif
