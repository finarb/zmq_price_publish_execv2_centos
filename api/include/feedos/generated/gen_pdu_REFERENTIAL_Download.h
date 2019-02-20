/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_Download_H
#define FEEDOS_generated_PDU_REFERENTIAL_Download_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_Download
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfMarketBranchId const & a, ListOfReferentialAttribute const & b, ListOfReferentialTagNumber const & c, Timestamp const & d, bool e, bool f, bool g) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_Download)
		{
			Encode_ListOfMarketBranchId (*this, a);
			Encode_ListOfReferentialAttribute (*this, b);
			Encode_ListOfReferentialTagNumber (*this, c);
			Encode_Timestamp (*this, d);
			Encode_bool (*this, e);
			Encode_bool (*this, f);
			Encode_bool (*this, g);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_Download)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_Download, rc)
		{}
		inline SubscribeResponse (Timestamp const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_Download, RC_OK)
		{
			Encode_Timestamp (*this, a);
		}
	};

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_BranchBegin SubscribeNotif_BranchBegin;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_Download, rc)
		{}
	};

}


namespace PDU_inbound_REFERENTIAL_Download
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_Download, p)
		{
			Decode_ListOfMarketBranchId (*this, m_TargetBranches);
			Decode_ListOfReferentialAttribute (*this, m_FilteringAttributes);
			Decode_ListOfReferentialTagNumber (*this, m_Format);
			Decode_Timestamp (*this, m_LastUpdateTimestamp);
			Decode_bool (*this, m_SendCreated);
			Decode_bool (*this, m_SendModified);
			Decode_bool (*this, m_SendDeleted);
		}
		inline ListOfMarketBranchId const & getTargetBranches() const { return m_TargetBranches; }
		inline ListOfReferentialAttribute const & getFilteringAttributes() const { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber const & getFormat() const { return m_Format; }
		inline Timestamp const & getLastUpdateTimestamp() const { return m_LastUpdateTimestamp; }
		inline bool const & getSendCreated() const { return m_SendCreated; }
		inline bool const & getSendModified() const { return m_SendModified; }
		inline bool const & getSendDeleted() const { return m_SendDeleted; }
	private:
		ListOfMarketBranchId m_TargetBranches;
		ListOfReferentialAttribute m_FilteringAttributes;
		ListOfReferentialTagNumber m_Format;
		Timestamp m_LastUpdateTimestamp;
		bool m_SendCreated;
		bool m_SendModified;
		bool m_SendDeleted;
	public:
		inline ListOfMarketBranchId & _refTargetBranches() { return m_TargetBranches; }
		inline ListOfReferentialAttribute & _refFilteringAttributes() { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber & _refFormat() { return m_Format; }
		inline Timestamp & _refLastUpdateTimestamp() { return m_LastUpdateTimestamp; }
		inline bool & _refSendCreated() { return m_SendCreated; }
		inline bool & _refSendModified() { return m_SendModified; }
		inline bool & _refSendDeleted() { return m_SendDeleted; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_Download, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_Download, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_Timestamp (*this, m_LastUpdateTimestamp);
		}
		inline Timestamp const & getLastUpdateTimestamp() const { return m_LastUpdateTimestamp; }
	private:
		Timestamp m_LastUpdateTimestamp;
	public:
		inline Timestamp & _refLastUpdateTimestamp() { return m_LastUpdateTimestamp; }
	};

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_BranchBegin SubscribeNotif_BranchBegin;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_Download, p)
		{}
	};

}

}
#endif
