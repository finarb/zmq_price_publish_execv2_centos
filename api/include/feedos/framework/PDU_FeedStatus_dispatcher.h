
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_FEEDSTATUS_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_FEEDSTATUS_DISPATCHER_H

#ifndef FEEDOS_COMM_PDU_CONSUMER_H
#	include "../comm/PDU_consumer.h"
#endif

#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#	include "../generated/gen_interface_CONNECTION.h"
#endif

namespace FeedOS {

	class API_CONNECTION_SubscribeToFeedStatus_delegate;

	class PDU_FeedStatus_dispatcher : virtual public PDU_consumer
	{
	public:
		PDU_FeedStatus_dispatcher ();
		void set_consumer (INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming & consumer);

		PDU_FeedStatus_dispatcher (INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming & consumer);
		virtual ~PDU_FeedStatus_dispatcher ();

		// overrides PDU_consumer::consume_PDUs	
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end);

		INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming *	get_consumer() { return m_consumer; }

	private:
		INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming *	m_consumer;
		API_CONNECTION_SubscribeToFeedStatus_delegate *			m_notif_dispatcher;
	};
}

#endif // FEEDOS_FRAMEWORK_PDU_MBO_DISPATCHER_H
