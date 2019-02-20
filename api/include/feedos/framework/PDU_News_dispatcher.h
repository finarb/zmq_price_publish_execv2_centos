
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2013      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_PDU_NEWS_DISPATCHER_H
#define FEEDOS_FRAMEWORK_PDU_NEWS_DISPATCHER_H

#include "../comm/PDU_consumer.h"
#include "../generated/gen_interface_NEWS.h"

namespace FeedOS
{
	class API_NEWS_SubscribeNews_delegate;

	class PDU_News_dispatcher: public PDU_consumer
	{
	public:
		PDU_News_dispatcher();
		PDU_News_dispatcher(INTERFACE_NEWS_SubscribeNews_streaming & consumer);
		virtual ~PDU_News_dispatcher();

		void										set_consumer(INTERFACE_NEWS_SubscribeNews_streaming & consumer);
		virtual void								consume_PDUs(std::vector<PDU>::const_iterator begin, std::vector<PDU>::const_iterator end);

		INTERFACE_NEWS_SubscribeNews_streaming *	get_consumer()
		{
			return m_Consumer;
		}

	private:
		INTERFACE_NEWS_SubscribeNews_streaming *	m_Consumer;
		API_NEWS_SubscribeNews_delegate *			m_NotifDispatcher;
	};
}

#endif // FEEDOS_FRAMEWORK_PDU_INTRADAY_BARS_DISPATCHER_H
