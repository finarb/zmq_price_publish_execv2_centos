
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_INTRADAY_BARS_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_INTRADAY_BARS_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#	include "FeedReplay_by_source.h"
#endif

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "../generated/gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_INTRADAY_BARS_DISPATCHER_H
#	include "../framework/PDU_IntradayBars_dispatcher.h"	
#endif

namespace FeedOS {

	class FeedReplay_IntradayBars:	public FeedReplay_by_source_through_API 
	{
	public:
		FeedReplay_IntradayBars (INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming & consumer)
			: FeedReplay_by_source_through_API (*(m_dispatcher=new PDU_IntradayBars_dispatcher(consumer)), Multicast_definitions::QuotationIntradayBars)
		{
		}

		virtual ~FeedReplay_IntradayBars ()
		{
			delete m_dispatcher;
		}

	protected:

		// inherited from INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		// => call corresponding callbacks of consumer
		virtual void response_CONNECTION_MulticastDataReplayBySource_Started ()				{ m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllIntradayBars_Started(); }
		virtual void response_CONNECTION_MulticastDataReplayBySource_Failed (ReturnCode rc)	{ m_dispatcher->get_consumer()->response_QUOTATION_SubscribeAllIntradayBars_Failed(rc); }
		virtual void aborted_CONNECTION_MulticastDataReplayBySource (ReturnCode rc)			{ m_dispatcher->get_consumer()->aborted_QUOTATION_SubscribeAllIntradayBars (rc);	}

	private:
		PDU_IntradayBars_dispatcher		* m_dispatcher;
	};
}
#endif
