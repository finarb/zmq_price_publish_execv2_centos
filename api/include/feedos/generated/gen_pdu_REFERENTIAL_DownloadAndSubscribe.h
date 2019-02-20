/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_DownloadAndSubscribe_H
#define FEEDOS_generated_PDU_REFERENTIAL_DownloadAndSubscribe_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_DownloadAndSubscribe
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfMarketBranchId const & a, ListOfReferentialAttribute const & b, ListOfReferentialTagNumber const & c, Timestamp const & d, bool e, bool f, bool g, bool h) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_DownloadAndSubscribe)
		{
			Encode_ListOfMarketBranchId (*this, a);
			Encode_ListOfReferentialAttribute (*this, b);
			Encode_ListOfReferentialTagNumber (*this, c);
			Encode_Timestamp (*this, d);
			Encode_bool (*this, e);
			Encode_bool (*this, f);
			Encode_bool (*this, g);
			Encode_bool (*this, h);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_DownloadAndSubscribe)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_DownloadAndSubscribe, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_DownloadAndSubscribe, RC_OK)
		{
		}
	};

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_BranchBegin SubscribeNotif_BranchBegin;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_MarkerTimestamp SubscribeNotif_MarkerTimestamp;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_RealtimeBegin SubscribeNotif_RealtimeBegin;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_VariablePriceIncrementTables SubscribeNotif_VariablePriceIncrementTables;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_TradeConditionsDictionary SubscribeNotif_TradeConditionsDictionary;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_MetaData SubscribeNotif_MetaData;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_DownloadAndSubscribe, rc)
		{}
	};

}


namespace PDU_inbound_REFERENTIAL_DownloadAndSubscribe
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_DownloadAndSubscribe, p)
		{
			Decode_ListOfMarketBranchId (*this, m_TargetBranches);
			Decode_ListOfReferentialAttribute (*this, m_FilteringAttributes);
			Decode_ListOfReferentialTagNumber (*this, m_Format);
			Decode_Timestamp (*this, m_LastUpdateTimestamp);
			Decode_bool (*this, m_SendCreated);
			Decode_bool (*this, m_SendModified);
			Decode_bool (*this, m_SendDeleted);
			Decode_bool (*this, m_SendOtherData);
		}
		inline ListOfMarketBranchId const & getTargetBranches() const { return m_TargetBranches; }
		inline ListOfReferentialAttribute const & getFilteringAttributes() const { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber const & getFormat() const { return m_Format; }
		inline Timestamp const & getLastUpdateTimestamp() const { return m_LastUpdateTimestamp; }
		inline bool const & getSendCreated() const { return m_SendCreated; }
		inline bool const & getSendModified() const { return m_SendModified; }
		inline bool const & getSendDeleted() const { return m_SendDeleted; }
		inline bool const & getSendOtherData() const { return m_SendOtherData; }
	private:
		ListOfMarketBranchId m_TargetBranches;
		ListOfReferentialAttribute m_FilteringAttributes;
		ListOfReferentialTagNumber m_Format;
		Timestamp m_LastUpdateTimestamp;
		bool m_SendCreated;
		bool m_SendModified;
		bool m_SendDeleted;
		bool m_SendOtherData;
	public:
		inline ListOfMarketBranchId & _refTargetBranches() { return m_TargetBranches; }
		inline ListOfReferentialAttribute & _refFilteringAttributes() { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber & _refFormat() { return m_Format; }
		inline Timestamp & _refLastUpdateTimestamp() { return m_LastUpdateTimestamp; }
		inline bool & _refSendCreated() { return m_SendCreated; }
		inline bool & _refSendModified() { return m_SendModified; }
		inline bool & _refSendDeleted() { return m_SendDeleted; }
		inline bool & _refSendOtherData() { return m_SendOtherData; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_DownloadAndSubscribe, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_DownloadAndSubscribe, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_BranchBegin SubscribeNotif_BranchBegin;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_MarkerTimestamp SubscribeNotif_MarkerTimestamp;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_RealtimeBegin SubscribeNotif_RealtimeBegin;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_VariablePriceIncrementTables SubscribeNotif_VariablePriceIncrementTables;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_TradeConditionsDictionary SubscribeNotif_TradeConditionsDictionary;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_MetaData SubscribeNotif_MetaData;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_DownloadAndSubscribe, p)
		{}
	};

}

}
#endif
