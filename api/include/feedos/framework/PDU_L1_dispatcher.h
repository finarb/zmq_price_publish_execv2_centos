
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_L1_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_L1_DISPATCHER_H

#ifndef FEEDOS_COMM_PDU_CONSUMER_H
#	include "../comm/PDU_consumer.h"
#endif

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "../generated/gen_interface_QUOTATION.h"
#endif

namespace FeedOS {

	class API_QUOTATION_SubscribeAllDataAndStatus_delegate;

	class PDU_L1_dispatcher : virtual public PDU_consumer
	{
	public:
		PDU_L1_dispatcher ();
		void set_consumer (INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & consumer);

		PDU_L1_dispatcher (INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & consumer);
		virtual ~PDU_L1_dispatcher ();

		// set filter on message types (default is to process all messages)
		void set_filter_MessageTypes (	bool notif_TradeEvent,
						bool notif_ValuesUpdate,	
						bool notif_MarketStatus,
						bool notif_MarketNews,
						bool notif_TradeCancelCorrection
						);

		// override PDU_consumer::consume_PDUs
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end);


		INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming *	get_consumer() { return m_consumer; }

	private:
		INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming *	m_consumer;
		API_QUOTATION_SubscribeAllDataAndStatus_delegate *			m_notif_dispatcher;

		bool					m_filter_process_notif_TradeEvent;
		bool					m_filter_process_notif_ValuesUpdate;
		bool					m_filter_process_notif_MarketStatus;
		bool					m_filter_process_notif_MarketNews;
		bool					m_filter_process_notif_TradeCancelCorrection;
	};
}
#endif // FEEDOS_FRAMEWORK_PDU_L1_DISPATCHER_H
