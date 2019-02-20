/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_LoadVariablePriceIncrementTables_H
#define FEEDOS_generated_PDU_REFERENTIAL_LoadVariablePriceIncrementTables_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_LoadVariablePriceIncrementTables
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfVariableIncrementPriceBandTable const & a, bool b) :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_LoadVariablePriceIncrementTables)
		{
			Encode_ListOfVariableIncrementPriceBandTable (*this, a);
			Encode_bool (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_LoadVariablePriceIncrementTables, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_LoadVariablePriceIncrementTables, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_REFERENTIAL_LoadVariablePriceIncrementTables
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_LoadVariablePriceIncrementTables, p)
		{
			Decode_ListOfVariableIncrementPriceBandTable (*this, m_Tables);
			Decode_bool (*this, m_Merge);
		}
		inline ListOfVariableIncrementPriceBandTable const & getTables() const { return m_Tables; }
		inline bool const & getMerge() const { return m_Merge; }
	private:
		ListOfVariableIncrementPriceBandTable m_Tables;
		bool m_Merge;
	public:
		inline ListOfVariableIncrementPriceBandTable & _refTables() { return m_Tables; }
		inline bool & _refMerge() { return m_Merge; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_LoadVariablePriceIncrementTables, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
