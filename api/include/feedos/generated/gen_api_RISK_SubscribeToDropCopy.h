/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_RISK_SubscribeToDropCopy_H
#define FEEDOS_generated_API_RISK_SubscribeToDropCopy_H

#include "gen_pdu_RISK_SubscribeToDropCopy.h"

#ifndef FEEDOS_generated_INTERFACE_RISK_H
#	include "gen_interface_RISK.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_RISK_SubscribeToDropCopy_delegate: public Subscriber_base
	{
		API_RISK_SubscribeToDropCopy_delegate (API_RISK_SubscribeToDropCopy_delegate const &);
		void operator=	(API_RISK_SubscribeToDropCopy_delegate const &);
	public:
		API_RISK_SubscribeToDropCopy_delegate (INTERFACE_RISK_SubscribeToDropCopy_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler);
		void		start		(RequestHandler & handler);
		
	protected:
		INTERFACE_RISK_SubscribeToDropCopy_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_RISK_SubscribeToDropCopy_base:
			public API_RISK_SubscribeToDropCopy_delegate,
			public virtual INTERFACE_RISK_SubscribeToDropCopy_streaming
	{
		API_RISK_SubscribeToDropCopy_base (API_RISK_SubscribeToDropCopy_base const &);
		void operator=	(API_RISK_SubscribeToDropCopy_base const &);
	public:
		API_RISK_SubscribeToDropCopy_base ();

	};

}
#endif
