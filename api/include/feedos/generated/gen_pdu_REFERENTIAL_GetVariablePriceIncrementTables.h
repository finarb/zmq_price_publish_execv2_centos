/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_GetVariablePriceIncrementTables_H
#define FEEDOS_generated_PDU_REFERENTIAL_GetVariablePriceIncrementTables_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_GetVariablePriceIncrementTables
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request () :
			PDU_outbound_Request (IDS::Request_REFERENTIAL_GetVariablePriceIncrementTables)
		{
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetVariablePriceIncrementTables, rc)
		{}
		inline Response (ListOfVariableIncrementPriceBandTable const & a) :
			PDU_outbound_Response (IDS::Response_REFERENTIAL_GetVariablePriceIncrementTables, RC_OK)
		{
			Encode_ListOfVariableIncrementPriceBandTable (*this, a);
		}
	};

}


namespace PDU_inbound_REFERENTIAL_GetVariablePriceIncrementTables
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_REFERENTIAL_GetVariablePriceIncrementTables, p)
		{
		}
	private:
	public:
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_REFERENTIAL_GetVariablePriceIncrementTables, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfVariableIncrementPriceBandTable (*this, m_Tables);
		}
		inline ListOfVariableIncrementPriceBandTable const & getTables() const { return m_Tables; }
	private:
		ListOfVariableIncrementPriceBandTable m_Tables;
	public:
		inline ListOfVariableIncrementPriceBandTable & _refTables() { return m_Tables; }
	};

}

}
#endif
