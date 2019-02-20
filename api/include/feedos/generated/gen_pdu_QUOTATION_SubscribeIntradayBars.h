/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_SubscribeIntradayBars_H
#define FEEDOS_generated_PDU_QUOTATION_SubscribeIntradayBars_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_SubscribeIntradayBars
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (uint16 const & a, ListOfPolymorphicInstrumentCode const & b, bool c) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeIntradayBars)
		{
			Encode_uint16 (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
			Encode_bool (*this, c);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeIntradayBars)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeIntradayBars, rc)
		{}
		inline SubscribeResponse (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeIntradayBars, RC_OK)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

	typedef PDU_outbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_outbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeIntradayBars, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_SubscribeIntradayBars
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_SubscribeIntradayBars, p)
		{
			Decode_uint16 (*this, m_Duration);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Instruments);
			Decode_bool (*this, m_IgnoreInvalidCodes);
		}
		inline uint16 const & getDuration() const { return m_Duration; }
		inline ListOfPolymorphicInstrumentCode const & getInstruments() const { return m_Instruments; }
		inline bool const & getIgnoreInvalidCodes() const { return m_IgnoreInvalidCodes; }
	private:
		uint16 m_Duration;
		ListOfPolymorphicInstrumentCode m_Instruments;
		bool m_IgnoreInvalidCodes;
	public:
		inline uint16 & _refDuration() { return m_Duration; }
		inline ListOfPolymorphicInstrumentCode & _refInstruments() { return m_Instruments; }
		inline bool & _refIgnoreInvalidCodes() { return m_IgnoreInvalidCodes; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_SubscribeIntradayBars, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_SubscribeIntradayBars, p)
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

	typedef PDU_inbound_QUOTATION::SubscribeNotif_IntradayBars SubscribeNotif_IntradayBars;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_DeleteBar SubscribeNotif_DeleteBar;

	typedef PDU_inbound_QUOTATION::SubscribeNotif_CorrectedBar SubscribeNotif_CorrectedBar;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_SubscribeIntradayBars, p)
		{}
	};

}

}
#endif
