
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_MULTIPLEXED_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_MULTIPLEXED_DISPATCHER_H

#ifndef FEEDOS_COMM_PDU_L1_DISPATCHER_H
#	include "PDU_L1_dispatcher.h"
#endif

#ifndef FEEDOS_COMM_PDU_L2_DISPATCHER_H
#	include "PDU_L2_dispatcher.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_MBO_DISPATCHER_H
#	include "PDU_MBO_dispatcher.h"
#endif

#ifndef FEEDOS_FRAMEWORK_PDU_FEEDSTATUS_DISPATCHER_H
#	include "PDU_FeedStatus_dispatcher.h"
#endif

namespace FeedOS {

	class PDU_Multiplexed_dispatcher:	public PDU_L1_dispatcher,
										public PDU_L2_dispatcher,
										public PDU_MBO_dispatcher,
										public PDU_FeedStatus_dispatcher
	{
	public:

		PDU_Multiplexed_dispatcher();

		virtual ~PDU_Multiplexed_dispatcher() 
		{}

		// overrides PDU_consumer::consume_PDUs	
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end);

		INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming *	get_consumer_L1() { return PDU_L1_dispatcher::get_consumer(); }
		INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming *		get_consumer_L2() { return PDU_L2_dispatcher::get_consumer(); }
		INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming *		get_consumer_MBO() { return PDU_MBO_dispatcher::get_consumer(); }
		INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming *		get_consumer_FeedStatus() { return PDU_FeedStatus_dispatcher::get_consumer(); }
	};

}

#endif // FEEDOS_FRAMEWORK_PDU_MIXED_L1L2_DISPATCHER_H
