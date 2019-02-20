/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_GetTradeConditionsDictionary_H
#define FEEDOS_generated_PDU_REFERENTIAL_GetTradeConditionsDictionary_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_GetTradeConditionsDictionary
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request () :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_GetTradeConditionsDictionary)
		{
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetTradeConditionsDictionary, rc)
		{}
		inline Response (ListOfTradeConditionsDictionaryEntry const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetTradeConditionsDictionary, RC_OK)
		{
			Encode_ListOfTradeConditionsDictionaryEntry (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_GetTradeConditionsDictionary
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_GetTradeConditionsDictionary, p)
		{
		}
	private:
	public:
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_GetTradeConditionsDictionary, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfTradeConditionsDictionaryEntry (*this, m_Entries);
		}
		inline ListOfTradeConditionsDictionaryEntry const & getEntries() const { return m_Entries; }
	private:
		ListOfTradeConditionsDictionaryEntry m_Entries;
	public:
		inline ListOfTradeConditionsDictionaryEntry & _refEntries() { return m_Entries; }
	};

}

}
#endif
