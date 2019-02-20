/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_REFERENTIAL_DownloadAndSubscribe_H
#define FEEDOS_generated_API_REFERENTIAL_DownloadAndSubscribe_H

#include "gen_pdu_REFERENTIAL_DownloadAndSubscribe.h"

#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#	include "gen_interface_REFERENTIAL.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_REFERENTIAL_DownloadAndSubscribe_delegate: public Subscriber_base
	{
		API_REFERENTIAL_DownloadAndSubscribe_delegate (API_REFERENTIAL_DownloadAndSubscribe_delegate const &);
		void operator=	(API_REFERENTIAL_DownloadAndSubscribe_delegate const &);
	public:
		API_REFERENTIAL_DownloadAndSubscribe_delegate (INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, ListOfMarketBranchId const & TargetBranches,  ListOfReferentialAttribute const & FilteringAttributes,  ListOfReferentialTagNumber const & Format, Timestamp const & LastUpdateTimestamp, bool SendCreated = true, bool SendModified = true, bool SendDeleted = true, bool SendOtherData = true);
		void		start		(RequestHandler & handler, ListOfMarketBranchId const & TargetBranches,  ListOfReferentialAttribute const & FilteringAttributes,  ListOfReferentialTagNumber const & Format, Timestamp const & LastUpdateTimestamp, bool SendCreated = true, bool SendModified = true, bool SendDeleted = true, bool SendOtherData = true);
		
	protected:
		INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_REFERENTIAL_DownloadAndSubscribe_base:
			public API_REFERENTIAL_DownloadAndSubscribe_delegate,
			public virtual INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming
	{
		API_REFERENTIAL_DownloadAndSubscribe_base (API_REFERENTIAL_DownloadAndSubscribe_base const &);
		void operator=	(API_REFERENTIAL_DownloadAndSubscribe_base const &);
	public:
		API_REFERENTIAL_DownloadAndSubscribe_base ();

	};

}
#endif
