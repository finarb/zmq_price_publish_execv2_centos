/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CONNECTION_NOTIFICATIONS_H
#define FEEDOS_generated_PDU_CONNECTION_NOTIFICATIONS_H

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

	namespace PDU_outbound_CONNECTION
	{
	class SubscribeNotif_FeedStatusUpdate: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_FeedStatusUpdate (String const & a, Timestamp const & b, FeedStatus const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_FeedStatusUpdate)
		{
			Encode_String (*this, a);
			Encode_Timestamp (*this, b);
			Encode_FeedStatus (*this, c);
		}
	};

	class SubscribeNotif_FeedStatusEvent: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_FeedStatusEvent (String const & a, Timestamp const & b, FeedStatusEvent const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_FeedStatusEvent)
		{
			Encode_String (*this, a);
			Encode_Timestamp (*this, b);
			Encode_FeedStatusEvent (*this, c);
		}
	};

	} // namespace PDU_outbound_CONNECTION


	namespace PDU_inbound_CONNECTION
	{
	class SubscribeNotif_FeedStatusUpdate: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_FeedStatusUpdate (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_FeedStatusUpdate, p)
		{
			Decode_String (*this, m_Sender);
			Decode_Timestamp (*this, m_SenderUTCTimestamp);
			Decode_FeedStatus (*this, m_Status);
		}
		inline String const & getSender() const { return m_Sender; }
		inline Timestamp const & getSenderUTCTimestamp() const { return m_SenderUTCTimestamp; }
		inline FeedStatus const & getStatus() const { return m_Status; }
	private:
		String m_Sender;
		Timestamp m_SenderUTCTimestamp;
		FeedStatus m_Status;
	public:
		inline String & _refSender() { return m_Sender; }
		inline Timestamp & _refSenderUTCTimestamp() { return m_SenderUTCTimestamp; }
		inline FeedStatus & _refStatus() { return m_Status; }
	};

	class SubscribeNotif_FeedStatusEvent: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_FeedStatusEvent (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_CONNECTION_FeedStatusEvent, p)
		{
			Decode_String (*this, m_Sender);
			Decode_Timestamp (*this, m_SenderUTCTimestamp);
			Decode_FeedStatusEvent (*this, m_Event);
		}
		inline String const & getSender() const { return m_Sender; }
		inline Timestamp const & getSenderUTCTimestamp() const { return m_SenderUTCTimestamp; }
		inline FeedStatusEvent const & getEvent() const { return m_Event; }
	private:
		String m_Sender;
		Timestamp m_SenderUTCTimestamp;
		FeedStatusEvent m_Event;
	public:
		inline String & _refSender() { return m_Sender; }
		inline Timestamp & _refSenderUTCTimestamp() { return m_SenderUTCTimestamp; }
		inline FeedStatusEvent & _refEvent() { return m_Event; }
	};

	} // namespace PDU_inbound_CONNECTION

}
#endif
