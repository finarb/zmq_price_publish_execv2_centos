/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_generated_API_CONNECTION_MulticastDataReplayBySource_H
#define FEEDOS_generated_API_CONNECTION_MulticastDataReplayBySource_H

#include "gen_pdu_CONNECTION_MulticastDataReplayBySource.h"

#ifndef FEEDOS_generated_INTERFACE_CONNECTION_H
#	include "gen_interface_CONNECTION.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

namespace FeedOS {

	class API_CONNECTION_MulticastDataReplayBySource_delegate: public Subscriber_base
	{
		API_CONNECTION_MulticastDataReplayBySource_delegate (API_CONNECTION_MulticastDataReplayBySource_delegate const &);
		void operator=	(API_CONNECTION_MulticastDataReplayBySource_delegate const &);
	public:
		API_CONNECTION_MulticastDataReplayBySource_delegate (INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming & delegate);

		ReturnCode	sync_start	(RequestHandler & handler, uint16 InternalSourceId, String const & Channel, Timestamp const & RangeBeginServerDate, Timestamp const & RangeEndServerDate, float64 AccelerationFactor);
		void		start		(RequestHandler & handler, uint16 InternalSourceId, String const & Channel, Timestamp const & RangeBeginServerDate, Timestamp const & RangeEndServerDate, float64 AccelerationFactor);
		
	protected:
		INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming &	m_delegate;
		virtual void receive_subrsp			(PDU_inbound_SubscribeResponse const & pdu);
		virtual void receive_notif			(PDU_inbound_SubscribeNotif const & pdu);
		virtual void receive_unsub_notif	(PDU_inbound_UnsubscribeNotif const & pdu);
	};

	class API_CONNECTION_MulticastDataReplayBySource_base:
			public API_CONNECTION_MulticastDataReplayBySource_delegate,
			public virtual INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
	{
		API_CONNECTION_MulticastDataReplayBySource_base (API_CONNECTION_MulticastDataReplayBySource_base const &);
		void operator=	(API_CONNECTION_MulticastDataReplayBySource_base const &);
	public:
		API_CONNECTION_MulticastDataReplayBySource_base ();

	};

}
#endif
