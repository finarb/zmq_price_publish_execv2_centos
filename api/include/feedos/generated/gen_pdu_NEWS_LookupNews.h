/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_NEWS_LookupNews_H
#define FEEDOS_generated_PDU_NEWS_LookupNews_H

#include "gen_pdu_NEWS_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_NEWS_LookupNews
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfNewsItem const & a, ListOfNewsItemId const & b, uint16 c) :
			PDU_outbound_Request (IDS::Request_NEWS_LookupNews)
		{
			Encode_ListOfNewsItem (*this, a);
			Encode_ListOfNewsItemId (*this, b);
			Encode_uint16 (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_NEWS_LookupNews, rc)
		{}
		inline Response (ListOfNewsData const & a) :
			PDU_outbound_Response (IDS::Response_NEWS_LookupNews, RC_OK)
		{
			Encode_ListOfNewsData (*this, a);
		}
	};

}


namespace PDU_inbound_NEWS_LookupNews
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_NEWS_LookupNews, p)
		{
			Decode_ListOfNewsItem (*this, m_Filter);
			Decode_ListOfNewsItemId (*this, m_Format);
			Decode_uint16 (*this, m_MaxHits);
		}
		inline ListOfNewsItem const & getFilter() const { return m_Filter; }
		inline ListOfNewsItemId const & getFormat() const { return m_Format; }
		inline uint16 const & getMaxHits() const { return m_MaxHits; }
	private:
		ListOfNewsItem m_Filter;
		ListOfNewsItemId m_Format;
		uint16 m_MaxHits;
	public:
		inline ListOfNewsItem & _refFilter() { return m_Filter; }
		inline ListOfNewsItemId & _refFormat() { return m_Format; }
		inline uint16 & _refMaxHits() { return m_MaxHits; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_NEWS_LookupNews, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfNewsData (*this, m_Result);
		}
		inline ListOfNewsData const & getResult() const { return m_Result; }
	private:
		ListOfNewsData m_Result;
	public:
		inline ListOfNewsData & _refResult() { return m_Result; }
	};

}

}
#endif
