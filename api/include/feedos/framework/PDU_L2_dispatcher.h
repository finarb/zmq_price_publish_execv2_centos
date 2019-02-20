
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_L2_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_L2_DISPATCHER_H

#ifndef FEEDOS_COMM_PDU_CONSUMER_H
#	include "../comm/PDU_consumer.h"
#endif

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "../generated/gen_interface_QUOTATION.h"
#endif

namespace FeedOS {

	class API_QUOTATION_SubscribeAllOrderBook_delegate;

	class PDU_L2_dispatcher : virtual public PDU_consumer
	{
	public:
		PDU_L2_dispatcher ();
		void set_consumer (INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer);

		PDU_L2_dispatcher (INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer);
		virtual ~PDU_L2_dispatcher ();

		// overrides PDU_consumer::consume_PDUs	
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end);

		INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming *	get_consumer() { return m_consumer; }

	private:
		INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming *	m_consumer;
		API_QUOTATION_SubscribeAllOrderBook_delegate *			m_notif_dispatcher;
	};
}

#endif // FEEDOS_FRAMEWORK_PDU_L2_DISPATCHER_H
