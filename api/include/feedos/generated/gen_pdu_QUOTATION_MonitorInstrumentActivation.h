/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_MonitorInstrumentActivation_H
#define FEEDOS_generated_PDU_QUOTATION_MonitorInstrumentActivation_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_MonitorInstrumentActivation
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfString const & a, bool b, bool c, bool d, bool e) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MonitorInstrumentActivation)
		{
			Encode_ListOfString (*this, a);
			Encode_bool (*this, b);
			Encode_bool (*this, c);
			Encode_bool (*this, d);
			Encode_bool (*this, e);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MonitorInstrumentActivation)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MonitorInstrumentActivation, rc)
		{}
		inline SubscribeResponse (uint32 const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MonitorInstrumentActivation, RC_OK)
		{
			Encode_uint32 (*this, a);
		}
	};

	class SubscribeNotif_InstrumentActivationSuccess: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentActivationSuccess (String const & a, ListOfPolymorphicInstrumentCode const & b) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentActivationSuccess)
		{
			Encode_String (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
		}
	};

	class SubscribeNotif_InstrumentActivationFailure: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentActivationFailure (String const & a, ListOfPolymorphicInstrumentCode const & b, ReturnCode c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentActivationFailure)
		{
			Encode_String (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
			Encode_ReturnCode (*this, c);
		}
	};

	class SubscribeNotif_InstrumentDeactivationWarning: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentDeactivationWarning (String const & a, ListOfPolymorphicInstrumentCode const & b, uint32 c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentDeactivationWarning)
		{
			Encode_String (*this, a);
			Encode_ListOfPolymorphicInstrumentCode (*this, b);
			Encode_uint32 (*this, c);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MonitorInstrumentActivation, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_MonitorInstrumentActivation
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_MonitorInstrumentActivation, p)
		{
			Decode_ListOfString (*this, m_MonitoredOutputChannels);
			Decode_bool (*this, m_SendCurrentActivationList);
			Decode_bool (*this, m_SendActivationSuccess);
			Decode_bool (*this, m_SendActivationFailure);
			Decode_bool (*this, m_SendDeactivationWarning);
		}
		inline ListOfString const & getMonitoredOutputChannels() const { return m_MonitoredOutputChannels; }
		inline bool const & getSendCurrentActivationList() const { return m_SendCurrentActivationList; }
		inline bool const & getSendActivationSuccess() const { return m_SendActivationSuccess; }
		inline bool const & getSendActivationFailure() const { return m_SendActivationFailure; }
		inline bool const & getSendDeactivationWarning() const { return m_SendDeactivationWarning; }
	private:
		ListOfString m_MonitoredOutputChannels;
		bool m_SendCurrentActivationList;
		bool m_SendActivationSuccess;
		bool m_SendActivationFailure;
		bool m_SendDeactivationWarning;
	public:
		inline ListOfString & _refMonitoredOutputChannels() { return m_MonitoredOutputChannels; }
		inline bool & _refSendCurrentActivationList() { return m_SendCurrentActivationList; }
		inline bool & _refSendActivationSuccess() { return m_SendActivationSuccess; }
		inline bool & _refSendActivationFailure() { return m_SendActivationFailure; }
		inline bool & _refSendDeactivationWarning() { return m_SendDeactivationWarning; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_MonitorInstrumentActivation, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_MonitorInstrumentActivation, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_uint32 (*this, m_NbFollowingActivationList);
		}
		inline uint32 const & getNbFollowingActivationList() const { return m_NbFollowingActivationList; }
	private:
		uint32 m_NbFollowingActivationList;
	public:
		inline uint32 & _refNbFollowingActivationList() { return m_NbFollowingActivationList; }
	};

	class SubscribeNotif_InstrumentActivationSuccess: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentActivationSuccess (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentActivationSuccess, p)
		{
			Decode_String (*this, m_OutputChannel);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
		}
		inline String const & getOutputChannel() const { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
	private:
		String m_OutputChannel;
		ListOfPolymorphicInstrumentCode m_Codes;
	public:
		inline String & _refOutputChannel() { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
	};

	class SubscribeNotif_InstrumentActivationFailure: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentActivationFailure (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentActivationFailure, p)
		{
			Decode_String (*this, m_OutputChannel);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_ReturnCode (*this, m_ErrorCode);
		}
		inline String const & getOutputChannel() const { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline ReturnCode const & getErrorCode() const { return m_ErrorCode; }
	private:
		String m_OutputChannel;
		ListOfPolymorphicInstrumentCode m_Codes;
		ReturnCode m_ErrorCode;
	public:
		inline String & _refOutputChannel() { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline ReturnCode & _refErrorCode() { return m_ErrorCode; }
	};

	class SubscribeNotif_InstrumentDeactivationWarning: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentDeactivationWarning (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MonitorInstrumentActivation_InstrumentDeactivationWarning, p)
		{
			Decode_String (*this, m_OutputChannel);
			Decode_ListOfPolymorphicInstrumentCode (*this, m_Codes);
			Decode_uint32 (*this, m_CountdownSeconds);
		}
		inline String const & getOutputChannel() const { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode const & getCodes() const { return m_Codes; }
		inline uint32 const & getCountdownSeconds() const { return m_CountdownSeconds; }
	private:
		String m_OutputChannel;
		ListOfPolymorphicInstrumentCode m_Codes;
		uint32 m_CountdownSeconds;
	public:
		inline String & _refOutputChannel() { return m_OutputChannel; }
		inline ListOfPolymorphicInstrumentCode & _refCodes() { return m_Codes; }
		inline uint32 & _refCountdownSeconds() { return m_CountdownSeconds; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_MonitorInstrumentActivation, p)
		{}
	};

}

}
#endif
