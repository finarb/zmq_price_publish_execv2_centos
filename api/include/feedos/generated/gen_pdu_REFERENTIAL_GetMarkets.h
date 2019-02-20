/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_GetMarkets_H
#define FEEDOS_generated_PDU_REFERENTIAL_GetMarkets_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_GetMarkets
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfFOSMarketId const & a) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_GetMarkets)
		{
			Encode_ListOfFOSMarketId (*this, a);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetMarkets, rc)
		{}
		inline Response (ListOfMarketCharacteristics const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetMarkets, RC_OK)
		{
			Encode_ListOfMarketCharacteristics (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_GetMarkets
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_GetMarkets, p)
		{
			Decode_ListOfFOSMarketId (*this, m_MarketIds);
		}
		inline ListOfFOSMarketId const & getMarketIds() const { return m_MarketIds; }
	private:
		ListOfFOSMarketId m_MarketIds;
	public:
		inline ListOfFOSMarketId & _refMarketIds() { return m_MarketIds; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_GetMarkets, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfMarketCharacteristics (*this, m_Markets);
		}
		inline ListOfMarketCharacteristics const & getMarkets() const { return m_Markets; }
	private:
		ListOfMarketCharacteristics m_Markets;
	public:
		inline ListOfMarketCharacteristics & _refMarkets() { return m_Markets; }
	};

}

}
#endif
