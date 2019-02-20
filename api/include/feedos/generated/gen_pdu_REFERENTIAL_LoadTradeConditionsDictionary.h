/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_LoadTradeConditionsDictionary_H
#define FEEDOS_generated_PDU_REFERENTIAL_LoadTradeConditionsDictionary_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_LoadTradeConditionsDictionary
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfTradeConditionsDictionaryEntry const & a, bool b) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_LoadTradeConditionsDictionary)
		{
			Encode_ListOfTradeConditionsDictionaryEntry (*this, a);
			Encode_bool (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_LoadTradeConditionsDictionary, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_LoadTradeConditionsDictionary, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_REFERENTIAL_LoadTradeConditionsDictionary
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_LoadTradeConditionsDictionary, p)
		{
			Decode_ListOfTradeConditionsDictionaryEntry (*this, m_Entries);
			Decode_bool (*this, m_Merge);
		}
		inline ListOfTradeConditionsDictionaryEntry const & getEntries() const { return m_Entries; }
		inline bool const & getMerge() const { return m_Merge; }
	private:
		ListOfTradeConditionsDictionaryEntry m_Entries;
		bool m_Merge;
	public:
		inline ListOfTradeConditionsDictionaryEntry & _refEntries() { return m_Entries; }
		inline bool & _refMerge() { return m_Merge; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_LoadTradeConditionsDictionary, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
