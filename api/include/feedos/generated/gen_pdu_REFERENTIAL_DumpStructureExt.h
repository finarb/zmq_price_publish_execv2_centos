/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_DumpStructureExt_H
#define FEEDOS_generated_PDU_REFERENTIAL_DumpStructureExt_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_DumpStructureExt
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request () :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_DumpStructureExt)
		{
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_DumpStructureExt, rc)
		{}
		inline Response (ListOfMarketCharacteristics const & a, ListOfEntitledMarketContent const & b, Timestamp const & c) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_DumpStructureExt, RC_OK)
		{
			Encode_ListOfMarketCharacteristics (*this, a);
			Encode_ListOfEntitledMarketContent (*this, b);
			Encode_Timestamp (*this, c);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_DumpStructureExt
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_DumpStructureExt, p)
		{
		}
	private:
	public:
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_DumpStructureExt, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfMarketCharacteristics (*this, m_Markets);
			Decode_ListOfEntitledMarketContent (*this, m_Content);
			Decode_Timestamp (*this, m_LastUpdateTimestamp);
		}
		inline ListOfMarketCharacteristics const & getMarkets() const { return m_Markets; }
		inline ListOfEntitledMarketContent const & getContent() const { return m_Content; }
		inline Timestamp const & getLastUpdateTimestamp() const { return m_LastUpdateTimestamp; }
	private:
		ListOfMarketCharacteristics m_Markets;
		ListOfEntitledMarketContent m_Content;
		Timestamp m_LastUpdateTimestamp;
	public:
		inline ListOfMarketCharacteristics & _refMarkets() { return m_Markets; }
		inline ListOfEntitledMarketContent & _refContent() { return m_Content; }
		inline Timestamp & _refLastUpdateTimestamp() { return m_LastUpdateTimestamp; }
	};

}

}
#endif
