/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_NEWS_DownloadHistoryNews_H
#define FEEDOS_generated_PDU_NEWS_DownloadHistoryNews_H

#include "gen_pdu_NEWS_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_NEWS_DownloadHistoryNews
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (Timestamp const & a, Timestamp const & b) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_NEWS_DownloadHistoryNews)
		{
			Encode_Timestamp (*this, a);
			Encode_Timestamp (*this, b);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_NEWS_DownloadHistoryNews)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_DownloadHistoryNews, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_DownloadHistoryNews, RC_OK)
		{
		}
	};

	class SubscribeNotif_HistoricalNews: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_HistoricalNews (ListOfNewsData const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_NEWS_DownloadHistoryNews_HistoricalNews)
		{
			Encode_ListOfNewsData (*this, a);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_NEWS_DownloadHistoryNews, rc)
		{}
	};

}


namespace PDU_inbound_NEWS_DownloadHistoryNews
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_NEWS_DownloadHistoryNews, p)
		{
			Decode_Timestamp (*this, m_OrigUTCTime_begin);
			Decode_Timestamp (*this, m_OrigUTCTime_end);
		}
		inline Timestamp const & getOrigUTCTime_begin() const { return m_OrigUTCTime_begin; }
		inline Timestamp const & getOrigUTCTime_end() const { return m_OrigUTCTime_end; }
	private:
		Timestamp m_OrigUTCTime_begin;
		Timestamp m_OrigUTCTime_end;
	public:
		inline Timestamp & _refOrigUTCTime_begin() { return m_OrigUTCTime_begin; }
		inline Timestamp & _refOrigUTCTime_end() { return m_OrigUTCTime_end; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_NEWS_DownloadHistoryNews, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_NEWS_DownloadHistoryNews, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	class SubscribeNotif_HistoricalNews: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_HistoricalNews (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_NEWS_DownloadHistoryNews_HistoricalNews, p)
		{
			Decode_ListOfNewsData (*this, m_News);
		}
		inline ListOfNewsData const & getNews() const { return m_News; }
	private:
		ListOfNewsData m_News;
	public:
		inline ListOfNewsData & _refNews() { return m_News; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_NEWS_DownloadHistoryNews, p)
		{}
	};

}

}
#endif
