/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayBars_H
#define FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayBars_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_DownloadHistoryIntradayBars
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, uint16 d) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayBars)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_uint16 (*this, d);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayBars)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBars, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBars, RC_OK)
		{
		}
	};

	class SubscribeNotif_IntradayBars: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayBars (ListOfQuotationIntradayBar const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayBars_IntradayBars)
		{
			Encode_ListOfQuotationIntradayBar (*this, a);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayBars, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_DownloadHistoryIntradayBars
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayBars, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_end);
			Decode_uint16 (*this, m_BarDurationSeconds);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
		inline Timestamp const & getServerUTCTimestamp_end() const { return m_ServerUTCTimestamp_end; }
		inline uint16 const & getBarDurationSeconds() const { return m_BarDurationSeconds; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		Timestamp m_ServerUTCTimestamp_begin;
		Timestamp m_ServerUTCTimestamp_end;
		uint16 m_BarDurationSeconds;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
		inline Timestamp & _refServerUTCTimestamp_end() { return m_ServerUTCTimestamp_end; }
		inline uint16 & _refBarDurationSeconds() { return m_BarDurationSeconds; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayBars, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayBars, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	class SubscribeNotif_IntradayBars: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayBars (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayBars_IntradayBars, p)
		{
			Decode_ListOfQuotationIntradayBar (*this, m_Bars);
		}
		inline ListOfQuotationIntradayBar const & getBars() const { return m_Bars; }
	private:
		ListOfQuotationIntradayBar m_Bars;
	public:
		inline ListOfQuotationIntradayBar & _refBars() { return m_Bars; }
	};

	typedef PDU_inbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayBars, p)
		{}
	};

}

}
#endif
