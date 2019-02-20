/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_RISK_NOTIFICATIONS_H
#define FEEDOS_generated_PDU_RISK_NOTIFICATIONS_H

#ifndef FEEDOS_COMM_PDU_H
#  include "../comm/PDU.h"
#endif

#ifndef FEEDOS_generated_PDU_IDS_H
#  include "gen_pdu_ids.h"
#endif

#ifndef FEEDOS_generated_ENCODING_H
#  include "gen_encoding.h"
#endif

namespace FeedOS
{
	using namespace Types;

	namespace PDU_outbound_RISK
	{
	class SubscribeNotif_SubmittedOrder: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_SubmittedOrder (BinaryBuffer const & a, bool b) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_RISK_SubmittedOrder)
		{
			Encode_BinaryBuffer (*this, a);
			Encode_bool (*this, b);
		}
	};

	class SubscribeNotif_ExecReport: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ExecReport (Timestamp const & a, BinaryBuffer b) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_RISK_ExecReport)
		{
			Encode_Timestamp (*this, a);
			Encode_BinaryBuffer (*this, b);
		}
	};

	class SubscribeNotif_RejectedOrder: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RejectedOrder (Timestamp const & a, OrderRejectReason b, BinaryBuffer c, BinaryBuffer d, bool e) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_RISK_RejectedOrder)
		{
			Encode_Timestamp (*this, a);
			Encode_OrderRejectReason (*this, b);
			Encode_BinaryBuffer (*this, c);
			Encode_BinaryBuffer (*this, d);
			Encode_bool (*this, e);
		}
	};

	} // namespace PDU_outbound_RISK


	namespace PDU_inbound_RISK
	{
	class SubscribeNotif_SubmittedOrder: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_SubmittedOrder (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_RISK_SubmittedOrder, p)
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

	class SubscribeNotif_ExecReport: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ExecReport (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_RISK_ExecReport, p)
		{
			Decode_Timestamp (*this, m_ReceiveTimestamp);
			Decode_BinaryBuffer (*this, m_ExecReport);
		}
		inline Timestamp const & getReceiveTimestamp() const { return m_ReceiveTimestamp; }
		inline BinaryBuffer const & getExecReport() const { return m_ExecReport; }
	private:
		Timestamp m_ReceiveTimestamp;
		BinaryBuffer m_ExecReport;
	public:
		inline Timestamp & _refReceiveTimestamp() { return m_ReceiveTimestamp; }
		inline BinaryBuffer & _refExecReport() { return m_ExecReport; }
	};

	class SubscribeNotif_RejectedOrder: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RejectedOrder (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_RISK_RejectedOrder, p)
		{
			Decode_Timestamp (*this, m_RejectTimestamp);
			Decode_OrderRejectReason (*this, m_OrderRejectReason);
			Decode_BinaryBuffer (*this, m_OrderRejectReasonVerbose);
			Decode_BinaryBuffer (*this, m_Order);
			Decode_bool (*this, m_NowOrNever);
		}
		inline Timestamp const & getRejectTimestamp() const { return m_RejectTimestamp; }
		inline OrderRejectReason const & getOrderRejectReason() const { return m_OrderRejectReason; }
		inline BinaryBuffer const & getOrderRejectReasonVerbose() const { return m_OrderRejectReasonVerbose; }
		inline BinaryBuffer const & getOrder() const { return m_Order; }
		inline bool const & getNowOrNever() const { return m_NowOrNever; }
	private:
		Timestamp m_RejectTimestamp;
		OrderRejectReason m_OrderRejectReason;
		BinaryBuffer m_OrderRejectReasonVerbose;
		BinaryBuffer m_Order;
		bool m_NowOrNever;
	public:
		inline Timestamp & _refRejectTimestamp() { return m_RejectTimestamp; }
		inline OrderRejectReason & _refOrderRejectReason() { return m_OrderRejectReason; }
		inline BinaryBuffer & _refOrderRejectReasonVerbose() { return m_OrderRejectReasonVerbose; }
		inline BinaryBuffer & _refOrder() { return m_Order; }
		inline bool & _refNowOrNever() { return m_NowOrNever; }
	};

	} // namespace PDU_inbound_RISK

}
#endif
