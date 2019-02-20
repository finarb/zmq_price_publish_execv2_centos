/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CONNECTION_SubscribeToFeedStatus_H
#define FEEDOS_generated_PDU_CONNECTION_SubscribeToFeedStatus_H

#include "gen_pdu_CONNECTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CONNECTION_SubscribeToFeedStatus
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest () :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_CONNECTION_SubscribeToFeedStatus)
		{
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CONNECTION_SubscribeToFeedStatus)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_SubscribeToFeedStatus, rc)
		{}
		inline SubscribeResponse (ListOfFeedStatus const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_SubscribeToFeedStatus, RC_OK)
		{
			Encode_ListOfFeedStatus (*this, a);
		}
	};

	typedef PDU_outbound_CONNECTION::SubscribeNotif_FeedStatusEvent SubscribeNotif_FeedStatusEvent;

	typedef PDU_outbound_CONNECTION::SubscribeNotif_FeedStatusUpdate SubscribeNotif_FeedStatusUpdate;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CONNECTION_SubscribeToFeedStatus, rc)
		{}
	};

}


namespace PDU_inbound_CONNECTION_SubscribeToFeedStatus
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_CONNECTION_SubscribeToFeedStatus, p)
		{
		}
	private:
	public:
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CONNECTION_SubscribeToFeedStatus, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_SubscribeToFeedStatus, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfFeedStatus (*this, m_FullSnapshot);
		}
		inline ListOfFeedStatus const & getFullSnapshot() const { return m_FullSnapshot; }
	private:
		ListOfFeedStatus m_FullSnapshot;
	public:
		inline ListOfFeedStatus & _refFullSnapshot() { return m_FullSnapshot; }
	};

	typedef PDU_inbound_CONNECTION::SubscribeNotif_FeedStatusEvent SubscribeNotif_FeedStatusEvent;

	typedef PDU_inbound_CONNECTION::SubscribeNotif_FeedStatusUpdate SubscribeNotif_FeedStatusUpdate;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CONNECTION_SubscribeToFeedStatus, p)
		{}
	};

}

}
#endif
