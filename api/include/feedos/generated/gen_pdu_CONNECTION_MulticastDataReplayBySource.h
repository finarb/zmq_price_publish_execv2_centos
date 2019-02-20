/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CONNECTION_MulticastDataReplayBySource_H
#define FEEDOS_generated_PDU_CONNECTION_MulticastDataReplayBySource_H

#include "gen_pdu_CONNECTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CONNECTION_MulticastDataReplayBySource
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (uint16 const & a, String const & b, Timestamp const & c, Timestamp const & d, float64 e) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_CONNECTION_MulticastDataReplayBySource)
		{
			Encode_uint16 (*this, a);
			Encode_String (*this, b);
			Encode_Timestamp (*this, c);
			Encode_Timestamp (*this, d);
			Encode_float64 (*this, e);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CONNECTION_MulticastDataReplayBySource)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_MulticastDataReplayBySource, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_MulticastDataReplayBySource, RC_OK)
		{
		}
	};

	class SubscribeNotif_ReplayData: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ReplayData (ListOfBinaryBuffer const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_MulticastDataReplayBySource_ReplayData)
		{
			Encode_ListOfBinaryBuffer (*this, a);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CONNECTION_MulticastDataReplayBySource, rc)
		{}
	};

}


namespace PDU_inbound_CONNECTION_MulticastDataReplayBySource
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_CONNECTION_MulticastDataReplayBySource, p)
		{
			Decode_uint16 (*this, m_InternalSourceId);
			Decode_String (*this, m_Channel);
			Decode_Timestamp (*this, m_RangeBeginServerDate);
			Decode_Timestamp (*this, m_RangeEndServerDate);
			Decode_float64 (*this, m_AccelerationFactor);
		}
		inline uint16 const & getInternalSourceId() const { return m_InternalSourceId; }
		inline String const & getChannel() const { return m_Channel; }
		inline Timestamp const & getRangeBeginServerDate() const { return m_RangeBeginServerDate; }
		inline Timestamp const & getRangeEndServerDate() const { return m_RangeEndServerDate; }
		inline float64 const & getAccelerationFactor() const { return m_AccelerationFactor; }
	private:
		uint16 m_InternalSourceId;
		String m_Channel;
		Timestamp m_RangeBeginServerDate;
		Timestamp m_RangeEndServerDate;
		float64 m_AccelerationFactor;
	public:
		inline uint16 & _refInternalSourceId() { return m_InternalSourceId; }
		inline String & _refChannel() { return m_Channel; }
		inline Timestamp & _refRangeBeginServerDate() { return m_RangeBeginServerDate; }
		inline Timestamp & _refRangeEndServerDate() { return m_RangeEndServerDate; }
		inline float64 & _refAccelerationFactor() { return m_AccelerationFactor; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_CONNECTION_MulticastDataReplayBySource, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_CONNECTION_MulticastDataReplayBySource, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	class SubscribeNotif_ReplayData: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ReplayData (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_MulticastDataReplayBySource_ReplayData, p)
		{
			Decode_ListOfBinaryBuffer (*this, m_Frames);
		}
		inline ListOfBinaryBuffer const & getFrames() const { return m_Frames; }
	private:
		ListOfBinaryBuffer m_Frames;
	public:
		inline ListOfBinaryBuffer & _refFrames() { return m_Frames; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_CONNECTION_MulticastDataReplayBySource, p)
		{}
	};

}

}
#endif
