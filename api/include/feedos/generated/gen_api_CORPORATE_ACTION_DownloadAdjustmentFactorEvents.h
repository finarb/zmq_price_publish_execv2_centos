/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_H
#define FEEDOS_generated_API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_H

#include "gen_pdu_CORPORATE_ACTION_DownloadAdjustmentFactorEvents.h"

#ifndef FEEDOS_generated_INTERFACE_CORPORATE_ACTION_H
#	include "gen_interface_CORPORATE_ACTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate: public Subscriber_base
	{
		API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate (API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate const &);
		void operator=	(API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate const &);
	public:
		API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate (INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, ListOfPolymorphicInstrumentCode const & Codes, Timestamp const & EventDay_begin, Timestamp const & EventDay_end,  AdjustmentFactorEventTypeMask Filter);
		void		start		(RequestHandler & handler, ListOfPolymorphicInstrumentCode const & Codes, Timestamp const & EventDay_begin, Timestamp const & EventDay_end,  AdjustmentFactorEventTypeMask Filter);
		
	protected:
		INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_base:
			public API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_delegate,
			public virtual INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming
	{
		API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_base (API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_base const &);
		void operator=	(API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_base const &);
	public:
		API_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_base ();

	};

}
#endif
