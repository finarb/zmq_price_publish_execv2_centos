/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_RISK_SubmitOrder_H
#define FEEDOS_generated_PDU_RISK_SubmitOrder_H

#include "gen_pdu_RISK_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_RISK_SubmitOrder
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (BinaryBuffer const & a, bool b) :
			PDU_outbound_Request (IDS::Request_RISK_SubmitOrder)
		{
			Encode_BinaryBuffer (*this, a);
			Encode_bool (*this, b);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_RISK_SubmitOrder, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_RISK_SubmitOrder, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_RISK_SubmitOrder
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_RISK_SubmitOrder, p)
		{
			Decode_BinaryBuffer (*this, m_Order);
			Decode_bool (*this, m_NowOrNever);
		}
		inline BinaryBuffer const & getOrder() const { return m_Order; }
		inline bool const & getNowOrNever() const { return m_NowOrNever; }
	private:
		BinaryBuffer m_Order;
		bool m_NowOrNever;
	public:
		inline BinaryBuffer & _refOrder() { return m_Order; }
		inline bool & _refNowOrNever() { return m_NowOrNever; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_RISK_SubmitOrder, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
