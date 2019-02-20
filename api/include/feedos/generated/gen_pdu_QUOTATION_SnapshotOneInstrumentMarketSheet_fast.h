/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SnapshotOneInstrumentMarketSheet_fast_H
#define FEEDOS_generated_PDU_QUOTATION_SnapshotOneInstrumentMarketSheet_fast_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SnapshotOneInstrumentMarketSheet_fast
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (FOSInstrumentCode const & a) :
			PDU_outbound_Request (IDS::Request_QUOTATION_SnapshotOneInstrumentMarketSheet_fast)
		{
			Encode_FOSInstrumentCode (*this, a);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotOneInstrumentMarketSheet_fast, rc)
		{}
		inline Response (InstrumentStatusMarketSheet const & a) :
			PDU_outbound_Response (IDS::Response_QUOTATION_SnapshotOneInstrumentMarketSheet_fast, RC_OK)
		{
			Encode_InstrumentStatusMarketSheet (*this, a);
		}
	};

}


namespace PDU_inbound_QUOTATION_SnapshotOneInstrumentMarketSheet_fast
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_QUOTATION_SnapshotOneInstrumentMarketSheet_fast, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
	private:
		FOSInstrumentCode m_Code;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_QUOTATION_SnapshotOneInstrumentMarketSheet_fast, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_InstrumentStatusMarketSheet (*this, m_Result);
		}
		inline InstrumentStatusMarketSheet const & getResult() const { return m_Result; }
	private:
		InstrumentStatusMarketSheet m_Result;
	public:
		inline InstrumentStatusMarketSheet & _refResult() { return m_Result; }
	};

}

}
#endif
