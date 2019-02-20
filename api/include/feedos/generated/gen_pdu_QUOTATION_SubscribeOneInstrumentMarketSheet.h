/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeOneInstrumentMarketSheet_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeOneInstrumentMarketSheet_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeOneInstrumentMarketSheet
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PolymorphicInstrumentCode const & a) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeOneInstrumentMarketSheet)
		{
			Encode_PolymorphicInstrumentCode (*this, a);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeOneInstrumentMarketSheet)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentMarketSheet, rc)
		{}
		inline SubscribeResponse (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, MarketSheet const & d) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentMarketSheet, RC_OK)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_MarketSheet (*this, d);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_NewOrder SubscribeNotif_NewOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ModifyOrder SubscribeNotif_ModifyOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveOneOrder SubscribeNotif_RemoveOneOrder;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveAllPreviousOrders SubscribeNotif_RemoveAllPreviousOrders;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_RemoveAllOrders SubscribeNotif_RemoveAllOrders;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_Retransmission SubscribeNotif_Retransmission;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_ValuesUpdateOneInstrument SubscribeNotif_ValuesUpdateOneInstrument;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeOneInstrumentMarketSheet, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeOneInstrumentMarketSheet
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeOneInstrumentMarketSheet, p)
		{
			Decode_PolymorphicInstrumentCode (*this, m_Code);
		}
		inline PolymorphicInstrumentCode const & getCode() const { return m_Code; }
	private:
		PolymorphicInstrumentCode m_Code;
	public:
		inline PolymorphicInstrumentCode & _refCode() { return m_Code; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeOneInstrumentMarketSheet, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeOneInstrumentMarketSheet, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_FOSInstrumentCode (*this, m_InternalCode);
			Decode_Timestamp (*this, m_LastUpdateServerUTCTimestamp);
			Decode_Timestamp (*this, m_LastUpdateMarketUTCTimestamp);
			Decode_MarketSheet (*this, m_Snapshot);
		}
		inline FOSInstrumentCode const & getInternalCode() const { return m_InternalCode; }
		inline Timestamp const & getLastUpdateServerUTCTimestamp() const { return m_LastUpdateServerUTCTimestamp; }
		inline Timestamp const & getLastUpdateMarketUTCTimestamp() const { return m_LastUpdateMarketUTCTimestamp; }
		inline MarketSheet const & getSnapshot() const { return m_Snapshot; }
	private:
		FOSInstrumentCode m_InternalCode;
		Timestamp m_LastUpdateServerUTCTimestamp;
		Timestamp m_LastUpdateMarketUTCTimestamp;
		MarketSheet m_Snapshot;
	public:
		inline FOSInstrumentCode & _refInternalCode() { return m_InternalCode; }
		inline Timestamp & _refLastUpdateServerUTCTimestamp() { return m_LastUpdateServerUTCTimestamp; }
		inline Timestamp & _refLastUpdateMarketUTCTimestamp() { return m_LastUpdateMarketUTCTimestamp; }
		inline MarketSheet & _refSnapshot() { return m_Snapshot; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_NewOrder SubscribeNotif_NewOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ModifyOrder SubscribeNotif_ModifyOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveOneOrder SubscribeNotif_RemoveOneOrder;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveAllPreviousOrders SubscribeNotif_RemoveAllPreviousOrders;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_RemoveAllOrders SubscribeNotif_RemoveAllOrders;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_Retransmission SubscribeNotif_Retransmission;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_ValuesUpdateOneInstrument SubscribeNotif_ValuesUpdateOneInstrument;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeOneInstrumentMarketSheet, p)
		{}
	};

}

}
#endif
