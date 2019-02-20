/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_NEWS_DeleteNews_H
#define FEEDOS_generated_PDU_NEWS_DeleteNews_H

#include "gen_pdu_NEWS_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_NEWS_DeleteNews
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (Timestamp const & a, Timestamp const & b) :
			PDU_outbound_Request (IDS::Request_NEWS_DeleteNews)
		{
			Encode_Timestamp (*this, a);
			Encode_Timestamp (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_NEWS_DeleteNews, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_NEWS_DeleteNews, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_NEWS_DeleteNews
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_NEWS_DeleteNews, p)
		{
			Decode_Timestamp (*this, m_ServerUTCTime_begin);
			Decode_Timestamp (*this, m_ServerUTCTime_end);
		}
		inline Timestamp const & getServerUTCTime_begin() const { return m_ServerUTCTime_begin; }
		inline Timestamp const & getServerUTCTime_end() const { return m_ServerUTCTime_end; }
	private:
		Timestamp m_ServerUTCTime_begin;
		Timestamp m_ServerUTCTime_end;
	public:
		inline Timestamp & _refServerUTCTime_begin() { return m_ServerUTCTime_begin; }
		inline Timestamp & _refServerUTCTime_end() { return m_ServerUTCTime_end; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_NEWS_DeleteNews, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
