/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_SubscribeAllReferential_H
#define FEEDOS_generated_API_REFERENTIAL_SubscribeAllReferential_H

#include "gen_pdu_REFERENTIAL_SubscribeAllReferential.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_REFERENTIAL_SubscribeAllReferential_delegate: public Subscriber_base
	{
		API_REFERENTIAL_SubscribeAllReferential_delegate (API_REFERENTIAL_SubscribeAllReferential_delegate const &);
		void operator=	(API_REFERENTIAL_SubscribeAllReferential_delegate const &);
	public:
		API_REFERENTIAL_SubscribeAllReferential_delegate (INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler);
		void		start		(RequestHandler & handler);
		
	protected:
		INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_REFERENTIAL_SubscribeAllReferential_base:
			public API_REFERENTIAL_SubscribeAllReferential_delegate,
			public virtual INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming
	{
		API_REFERENTIAL_SubscribeAllReferential_base (API_REFERENTIAL_SubscribeAllReferential_base const &);
		void operator=	(API_REFERENTIAL_SubscribeAllReferential_base const &);
	public:
		API_REFERENTIAL_SubscribeAllReferential_base ();

	};

}
#endif
