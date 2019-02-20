/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_NEWS_SubscribeNews_H
#define FEEDOS_generated_PDU_NEWS_SubscribeNews_H

#include "gen_pdu_NEWS_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_NEWS_SubscribeNews
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfNewsItem const & a, ListOfNewsItemId const & b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_NEWS_SubscribeNews)
		{
			Encode_ListOfNewsItem (*this, a);
			Encode_ListOfNewsItemId (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_NEWS_SubscribeNews)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_SubscribeNews, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_SubscribeNews, RC_OK)
		{
		}
	};

	typedef PDU_outbound_NEWS::SubscribeNotif_NewsData SubscribeNotif_NewsData;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_NEWS_SubscribeNews, rc)
		{}
	};

}


namespace PDU_inbound_NEWS_SubscribeNews
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_NEWS_SubscribeNews, p)
		{
			Decode_ListOfNewsItem (*this, m_Filter);
			Decode_ListOfNewsItemId (*this, m_Format);
		}
		inline ListOfNewsItem const & getFilter() const { return m_Filter; }
		inline ListOfNewsItemId const & getFormat() const { return m_Format; }
	private:
		ListOfNewsItem m_Filter;
		ListOfNewsItemId m_Format;
	public:
		inline ListOfNewsItem & _refFilter() { return m_Filter; }
		inline ListOfNewsItemId & _refFormat() { return m_Format; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_NEWS_SubscribeNews, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_SubscribeNews, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_NEWS::SubscribeNotif_NewsData SubscribeNotif_NewsData;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_NEWS_SubscribeNews, p)
		{}
	};

}

}
#endif
