/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SnapshotMarkets_H
#define FEEDOS_generated_PDU_QUOTATION_SnapshotMarkets_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SnapshotMarkets
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfFOSMarketId const & a) :
			PDU_outbound_Request (IDS::Request_QUOTATION_SnapshotMarkets)
		{
			Encode_ListOfFOSMarketId (*this, a);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotMarkets, rc)
		{}
		inline Response (ListOfMarketStatus const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotMarkets, RC_OK)
		{
			Encode_ListOfMarketStatus (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_SnapshotMarkets
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_SnapshotMarkets, p)
		{
			Decode_ListOfFOSMarketId (*this, m_Markets);
		}
		inline ListOfFOSMarketId const & getMarkets() const { return m_Markets; }
	private:
		ListOfFOSMarketId m_Markets;
	public:
		inline ListOfFOSMarketId & _refMarkets() { return m_Markets; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_SnapshotMarkets, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfMarketStatus (*this, m_MarketsStatus);
		}
		inline ListOfMarketStatus const & getMarketsStatus() const { return m_MarketsStatus; }
	private:
		ListOfMarketStatus m_MarketsStatus;
	public:
		inline ListOfMarketStatus & _refMarketsStatus() { return m_MarketsStatus; }
	};

}

}
#endif
