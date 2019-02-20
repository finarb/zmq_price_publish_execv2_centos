/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor_H
#define FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (uint32 const & a, ListOfQuotationTagNumber const & b) :
			PDU_outbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor)
		{
			Encode_uint32 (*this, a);
			Encode_ListOfQuotationTagNumber (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor, rc)
		{}
		inline Response (ListOfInstrumentStatusL1 const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor, RC_OK)
		{
			Encode_ListOfInstrumentStatusL1 (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor, p)
		{
			Decode_uint32 (*this, m_Ticket);
			Decode_ListOfQuotationTagNumber (*this, m_OtherValuesToLookFor);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline ListOfQuotationTagNumber const & getOtherValuesToLookFor() const { return m_OtherValuesToLookFor; }
	private:
		uint32 m_Ticket;
		ListOfQuotationTagNumber m_OtherValuesToLookFor;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline ListOfQuotationTagNumber & _refOtherValuesToLookFor() { return m_OtherValuesToLookFor; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfInstrumentStatusL1 (*this, m_Snapshot);
		}
		inline ListOfInstrumentStatusL1 const & getSnapshot() const { return m_Snapshot; }
	private:
		ListOfInstrumentStatusL1 m_Snapshot;
	public:
		inline ListOfInstrumentStatusL1 & _refSnapshot() { return m_Snapshot; }
	};

}

}
#endif
