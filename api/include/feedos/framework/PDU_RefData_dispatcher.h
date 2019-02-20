
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_REF_DATA_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_REF_DATA_DISPATCHER_H

#include "../comm/PDU_consumer.h"
#include "../generated/gen_interface_REFERENTIAL.h"

namespace FeedOS {

	class API_REFERENTIAL_SubscribeAllReferential_delegate;

	class PDU_RefData_dispatcher : virtual public PDU_consumer
	{
	public:
		PDU_RefData_dispatcher ();
		void set_consumer (INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming & consumer);

		PDU_RefData_dispatcher (INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming & consumer);
		virtual ~PDU_RefData_dispatcher ();

		// override PDU_consumer::consume_PDUs
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end);

		INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming *	get_consumer() { return m_consumer; }

	private:
		INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming *	m_consumer;
		API_REFERENTIAL_SubscribeAllReferential_delegate *			m_notif_dispatcher;
	};
}
#endif // FEEDOS_FRAMEWORK_PDU_REF_DATA_DISPATCHER_H
