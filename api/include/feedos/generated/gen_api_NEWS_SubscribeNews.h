/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_NEWS_SubscribeNews_H
#define FEEDOS_generated_API_NEWS_SubscribeNews_H

#include "gen_pdu_NEWS_SubscribeNews.h"

#ifndef FEEDOS_generated_INTERFACE_NEWS_H
#	include "gen_interface_NEWS.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_NEWS_SubscribeNews_delegate: public Subscriber_base
	{
		API_NEWS_SubscribeNews_delegate (API_NEWS_SubscribeNews_delegate const &);
		void operator=	(API_NEWS_SubscribeNews_delegate const &);
	public:
		API_NEWS_SubscribeNews_delegate (INTERFACE_NEWS_SubscribeNews_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, ListOfNewsItem const & Filter,  ListOfNewsItemId const & Format);
		void		start		(RequestHandler & handler, ListOfNewsItem const & Filter,  ListOfNewsItemId const & Format);
		
	protected:
		INTERFACE_NEWS_SubscribeNews_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_NEWS_SubscribeNews_base:
			public API_NEWS_SubscribeNews_delegate,
			public virtual INTERFACE_NEWS_SubscribeNews_streaming
	{
		API_NEWS_SubscribeNews_base (API_NEWS_SubscribeNews_base const &);
		void operator=	(API_NEWS_SubscribeNews_base const &);
	public:
		API_NEWS_SubscribeNews_base ();

	};

}
#endif
