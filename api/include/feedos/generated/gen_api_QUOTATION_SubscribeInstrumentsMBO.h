/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_QUOTATION_SubscribeInstrumentsMBO_H
#define FEEDOS_generated_API_QUOTATION_SubscribeInstrumentsMBO_H

#include "gen_pdu_QUOTATION_SubscribeInstrumentsMBO.h"

#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#	include "gen_interface_QUOTATION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_QUOTATION_SubscribeInstrumentsMBO_delegate: public Subscriber_base
	{
		API_QUOTATION_SubscribeInstrumentsMBO_delegate (API_QUOTATION_SubscribeInstrumentsMBO_delegate const &);
		void operator=	(API_QUOTATION_SubscribeInstrumentsMBO_delegate const &);
	public:
		API_QUOTATION_SubscribeInstrumentsMBO_delegate (INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = false);
		void		start		(RequestHandler & handler, ListOfPolymorphicInstrumentCode const & Codes, bool IgnoreInvalidCodes = false);
		
	protected:
		INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_QUOTATION_SubscribeInstrumentsMBO_base:
			public API_QUOTATION_SubscribeInstrumentsMBO_delegate,
			public virtual INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming
	{
		API_QUOTATION_SubscribeInstrumentsMBO_base (API_QUOTATION_SubscribeInstrumentsMBO_base const &);
		void operator=	(API_QUOTATION_SubscribeInstrumentsMBO_base const &);
	public:
		API_QUOTATION_SubscribeInstrumentsMBO_base ();

	};

}
#endif
