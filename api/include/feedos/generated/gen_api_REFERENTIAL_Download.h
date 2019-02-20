/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_Download_H
#define FEEDOS_generated_API_REFERENTIAL_Download_H

#include "gen_pdu_REFERENTIAL_Download.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_REFERENTIAL_Download_delegate: public Subscriber_base
	{
		API_REFERENTIAL_Download_delegate (API_REFERENTIAL_Download_delegate const &);
		void operator=	(API_REFERENTIAL_Download_delegate const &);
	public:
		API_REFERENTIAL_Download_delegate (INTERFACE_REFERENTIAL_Download_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, ListOfMarketBranchId const & TargetBranches,  ListOfReferentialAttribute const & FilteringAttributes,  ListOfReferentialTagNumber const & Format, Timestamp const & LastUpdateTimestamp, bool SendCreated = true, bool SendModified = true, bool SendDeleted = true);
		void		start		(RequestHandler & handler, ListOfMarketBranchId const & TargetBranches,  ListOfReferentialAttribute const & FilteringAttributes,  ListOfReferentialTagNumber const & Format, Timestamp const & LastUpdateTimestamp, bool SendCreated = true, bool SendModified = true, bool SendDeleted = true);
		
	protected:
		INTERFACE_REFERENTIAL_Download_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_REFERENTIAL_Download_base:
			public API_REFERENTIAL_Download_delegate,
			public virtual INTERFACE_REFERENTIAL_Download_streaming
	{
		API_REFERENTIAL_Download_base (API_REFERENTIAL_Download_base const &);
		void operator=	(API_REFERENTIAL_Download_base const &);
	public:
		API_REFERENTIAL_Download_base ();

	};

}
#endif
