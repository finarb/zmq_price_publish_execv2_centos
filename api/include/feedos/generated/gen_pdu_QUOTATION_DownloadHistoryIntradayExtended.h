/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayExtended_H
#define FEEDOS_generated_PDU_QUOTATION_DownloadHistoryIntradayExtended_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_DownloadHistoryIntradayExtended
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfPolymorphicInstrumentCode const & a, Timestamp const & b, Timestamp const & c, int32 d, bool e) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayExtended)
		{
			Encode_ListOfPolymorphicInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_int32 (*this, d);
			Encode_bool (*this, e);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayExtended)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayExtended, rc)
		{}
		inline SubscribeResponse (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayExtended, RC_OK)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

	class SubscribeNotif_IntradayExtended: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayExtended (ListOfIntradayHistoryDataExtended const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_IntradayExtended)
		{
			Encode_ListOfIntradayHistoryDataExtended (*this, a);
		}
	};

	class SubscribeNotif_Cancel: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Cancel (IntradayHistoryCancel const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_Cancel)
		{
			Encode_IntradayHistoryCancel (*this, a);
		}
	};

	class SubscribeNotif_Correction: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Correction (IntradayHistoryCorrection const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_Correction)
		{
			Encode_IntradayHistoryCorrection (*this, a);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_DownloadHistoryIntradayExtended
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadHistoryIntradayExtended, p)
		{
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_end);
			Decode_int32 (*this, m_NbPoints);
			Decode_bool (*this, m_WithTradeCancelCorrection);
		}
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
		inline Timestamp const & getServerUTCTimestamp_end() const { return m_ServerUTCTimestamp_end; }
		inline int32 const & getNbPoints() const { return m_NbPoints; }
		inline bool const & getWithTradeCancelCorrection() const { return m_WithTradeCancelCorrection; }
	private:
		ListOfPolymorphicInstrumentCode m_Codes;
		Timestamp m_ServerUTCTimestamp_begin;
		Timestamp m_ServerUTCTimestamp_end;
		int32 m_NbPoints;
		bool m_WithTradeCancelCorrection;
	public:
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
		inline Timestamp & _refServerUTCTimestamp_end() { return m_ServerUTCTimestamp_end; }
		inline int32 & _refNbPoints() { return m_NbPoints; }
		inline bool & _refWithTradeCancelCorrection() { return m_WithTradeCancelCorrection; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadHistoryIntradayExtended, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadHistoryIntradayExtended, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfFOSInstrumentCode (*this, m_Codes);
		}
		inline ListOfFOSInstrumentCode const & getCodes() const { return m_Codes; }
	private:
		ListOfFOSInstrumentCode m_Codes;
	public:
		inline ListOfFOSInstrumentCode & _refCodes() { return m_Codes; }
	};

	class SubscribeNotif_IntradayExtended: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayExtended (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_IntradayExtended, p)
		{
			Decode_ListOfIntradayHistoryDataExtended (*this, m_Trades);
		}
		inline ListOfIntradayHistoryDataExtended const & getTrades() const { return m_Trades; }
	private:
		ListOfIntradayHistoryDataExtended m_Trades;
	public:
		inline ListOfIntradayHistoryDataExtended & _refTrades() { return m_Trades; }
	};

	class SubscribeNotif_Cancel: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Cancel (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_Cancel, p)
		{
			Decode_IntradayHistoryCancel (*this, m_Cancel);
		}
		inline IntradayHistoryCancel const & getCancel() const { return m_Cancel; }
	private:
		IntradayHistoryCancel m_Cancel;
	public:
		inline IntradayHistoryCancel & _refCancel() { return m_Cancel; }
	};

	class SubscribeNotif_Correction: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Correction (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended_Correction, p)
		{
			Decode_IntradayHistoryCorrection (*this, m_Correction);
		}
		inline IntradayHistoryCorrection const & getCorrection() const { return m_Correction; }
	private:
		IntradayHistoryCorrection m_Correction;
	public:
		inline IntradayHistoryCorrection & _refCorrection() { return m_Correction; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadHistoryIntradayExtended, p)
		{}
	};

}

}
#endif
