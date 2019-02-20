/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CONNECTION_SubscribeToFeedStatus_H
#define FEEDOS_generated_API_CONNECTION_SubscribeToFeedStatus_H

#include "gen_pdu_CONNECTION_SubscribeToFeedStatus.h"

#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#	include "gen_interface_CONNECTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_CONNECTION_SubscribeToFeedStatus_delegate: public Subscriber_base
	{
		API_CONNECTION_SubscribeToFeedStatus_delegate (API_CONNECTION_SubscribeToFeedStatus_delegate const &);
		void operator=	(API_CONNECTION_SubscribeToFeedStatus_delegate const &);
	public:
		API_CONNECTION_SubscribeToFeedStatus_delegate (INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler);
		void		start		(RequestHandler & handler);
		
	protected:
		INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_CONNECTION_SubscribeToFeedStatus_base:
			public API_CONNECTION_SubscribeToFeedStatus_delegate,
			public virtual INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
	{
		API_CONNECTION_SubscribeToFeedStatus_base (API_CONNECTION_SubscribeToFeedStatus_base const &);
		void operator=	(API_CONNECTION_SubscribeToFeedStatus_base const &);
	public:
		API_CONNECTION_SubscribeToFeedStatus_base ();

	};

}
#endif
