/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayBarsExt_H
#define FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayBarsExt_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_DownloadHistoryIntradayBarsExt
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, uint16 d, AdjustmentFactorEventTypeMask e, uint16 f) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayBarsExt)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_uint16 (*this, d);
			Encode_AdjustmentFactorEventTypeMask (*this, e);
			Encode_uint16 (*this, f);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayBarsExt)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBarsExt, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBarsExt, RC_OK)
		{
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayBarsExt, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_DownloadHistoryIntradayBarsExt
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayBarsExt, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_end);
			Decode_uint16 (*this, m_BarDurationSeconds);
			Decode_AdjustmentFactorEventTypeMask (*this, m_AdjustmentFactorEventTypes);
			Decode_uint16 (*this, m_NbBarsBeforeBegin);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
		inline Timestamp const & getServerUTCTimestamp_end() const { return m_ServerUTCTimestamp_end; }
		inline uint16 const & getBarDurationSeconds() const { return m_BarDurationSeconds; }
		inline AdjustmentFactorEventTypeMask const & getAdjustmentFactorEventTypes() const { return m_AdjustmentFactorEventTypes; }
		inline uint16 const & getNbBarsBeforeBegin() const { return m_NbBarsBeforeBegin; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		Timestamp m_ServerUTCTimestamp_begin;
		Timestamp m_ServerUTCTimestamp_end;
		uint16 m_BarDurationSeconds;
		AdjustmentFactorEventTypeMask m_AdjustmentFactorEventTypes;
		uint16 m_NbBarsBeforeBegin;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
		inline Timestamp & _refServerUTCTimestamp_end() { return m_ServerUTCTimestamp_end; }
		inline uint16 & _refBarDurationSeconds() { return m_BarDurationSeconds; }
		inline AdjustmentFactorEventTypeMask & _refAdjustmentFactorEventTypes() { return m_AdjustmentFactorEventTypes; }
		inline uint16 & _refNbBarsBeforeBegin() { return m_NbBarsBeforeBegin; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayBarsExt, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBarsExt, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayBarsExt, p)
		{}
	};

}

}
#endif
