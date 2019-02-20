/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask_H
#define FEEDOS_generated_PDU_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (uint32 const & a, QuotationContentMask b, bool c) :
			PDU_outbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask)
		{
			Encode_uint32 (*this, a);
			Encode_QuotationContentMask (*this, b);
			Encode_bool (*this, c);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask, rc)
		{}
		inline Response (ListOfInstrumentStatusL1 const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask, RC_OK)
		{
			Encode_ListOfInstrumentStatusL1 (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask, p)
		{
			Decode_uint32 (*this, m_Ticket);
			Decode_QuotationContentMask (*this, m_ContentMask);
			Decode_bool (*this, m_ResendSnapshot);
		}
		inline uint32 const & getTicket() const { return m_Ticket; }
		inline QuotationContentMask const & getContentMask() const { return m_ContentMask; }
		inline bool const & getResendSnapshot() const { return m_ResendSnapshot; }
	private:
		uint32 m_Ticket;
		QuotationContentMask m_ContentMask;
		bool m_ResendSnapshot;
	public:
		inline uint32 & _refTicket() { return m_Ticket; }
		inline QuotationContentMask & _refContentMask() { return m_ContentMask; }
		inline bool & _refResendSnapshot() { return m_ResendSnapshot; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask, p)
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
