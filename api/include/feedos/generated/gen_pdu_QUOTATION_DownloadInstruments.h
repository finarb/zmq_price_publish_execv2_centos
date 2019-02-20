/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_DownloadInstruments_H
#define FEEDOS_generated_PDU_QUOTATION_DownloadInstruments_H

#include "gen_pdu_QUOTATION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_QUOTATION_DownloadInstruments
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (ListOfMarketBranchId const & a, ListOfReferentialAttribute const & b, ListOfReferentialTagNumber const & c, ListOfQuotationTagNumber const & d, Timestamp const & e, int8 f) :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadInstruments)
		{
			Encode_ListOfMarketBranchId (*this, a);
			Encode_ListOfReferentialAttribute (*this, b);
			Encode_ListOfReferentialTagNumber (*this, c);
			Encode_ListOfQuotationTagNumber (*this, d);
			Encode_Timestamp (*this, e);
			Encode_int8 (*this, f);
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadInstruments)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadInstruments, rc)
		{}
		inline SubscribeResponse (Timestamp const & a) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadInstruments, RC_OK)
		{
			Encode_Timestamp (*this, a);
		}
	};

	class SubscribeNotif_BranchBegin: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_BranchBegin (MarketBranchId const & a, uint32 b, uint32 c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadInstruments_BranchBegin)
		{
			Encode_MarketBranchId (*this, a);
			Encode_uint32 (*this, b);
			Encode_uint32 (*this, c);
		}
	};

	class SubscribeNotif_Instruments: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Instruments (ListOfInstrumentData const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadInstruments_Instruments)
		{
			Encode_ListOfInstrumentData (*this, a);
		}
	};

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadInstruments, rc)
		{}
	};

}


namespace PDU_inbound_QUOTATION_DownloadInstruments
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_QUOTATION_DownloadInstruments, p)
		{
			Decode_ListOfMarketBranchId (*this, m_TargetBranches);
			Decode_ListOfReferentialAttribute (*this, m_FilteringAttributes);
			Decode_ListOfReferentialTagNumber (*this, m_ReferentialTags);
			Decode_ListOfQuotationTagNumber (*this, m_QuotationTags);
			Decode_Timestamp (*this, m_LastActivityTimestamp);
			Decode_int8 (*this, m_OrderBookDepth);
		}
		inline ListOfMarketBranchId const & getTargetBranches() const { return m_TargetBranches; }
		inline ListOfReferentialAttribute const & getFilteringAttributes() const { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber const & getReferentialTags() const { return m_ReferentialTags; }
		inline ListOfQuotationTagNumber const & getQuotationTags() const { return m_QuotationTags; }
		inline Timestamp const & getLastActivityTimestamp() const { return m_LastActivityTimestamp; }
		inline int8 const & getOrderBookDepth() const { return m_OrderBookDepth; }
	private:
		ListOfMarketBranchId m_TargetBranches;
		ListOfReferentialAttribute m_FilteringAttributes;
		ListOfReferentialTagNumber m_ReferentialTags;
		ListOfQuotationTagNumber m_QuotationTags;
		Timestamp m_LastActivityTimestamp;
		int8 m_OrderBookDepth;
	public:
		inline ListOfMarketBranchId & _refTargetBranches() { return m_TargetBranches; }
		inline ListOfReferentialAttribute & _refFilteringAttributes() { return m_FilteringAttributes; }
		inline ListOfReferentialTagNumber & _refReferentialTags() { return m_ReferentialTags; }
		inline ListOfQuotationTagNumber & _refQuotationTags() { return m_QuotationTags; }
		inline Timestamp & _refLastActivityTimestamp() { return m_LastActivityTimestamp; }
		inline int8 & _refOrderBookDepth() { return m_OrderBookDepth; }
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_QUOTATION_DownloadInstruments, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_QUOTATION_DownloadInstruments, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_Timestamp (*this, m_LastActivityTimestamp);
		}
		inline Timestamp const & getLastActivityTimestamp() const { return m_LastActivityTimestamp; }
	private:
		Timestamp m_LastActivityTimestamp;
	public:
		inline Timestamp & _refLastActivityTimestamp() { return m_LastActivityTimestamp; }
	};

	class SubscribeNotif_BranchBegin: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_BranchBegin (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadInstruments_BranchBegin, p)
		{
			Decode_MarketBranchId (*this, m_Branch);
			Decode_uint32 (*this, m_CurrentQuantity);
			Decode_uint32 (*this, m_SelectedQuantity);
		}
		inline MarketBranchId const & getBranch() const { return m_Branch; }
		inline uint32 const & getCurrentQuantity() const { return m_CurrentQuantity; }
		inline uint32 const & getSelectedQuantity() const { return m_SelectedQuantity; }
	private:
		MarketBranchId m_Branch;
		uint32 m_CurrentQuantity;
		uint32 m_SelectedQuantity;
	public:
		inline MarketBranchId & _refBranch() { return m_Branch; }
		inline uint32 & _refCurrentQuantity() { return m_CurrentQuantity; }
		inline uint32 & _refSelectedQuantity() { return m_SelectedQuantity; }
	};

	class SubscribeNotif_Instruments: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Instruments (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DownloadInstruments_Instruments, p)
		{
			Decode_ListOfInstrumentData (*this, m_Instruments);
		}
		inline ListOfInstrumentData const & getInstruments() const { return m_Instruments; }
	private:
		ListOfInstrumentData m_Instruments;
	public:
		inline ListOfInstrumentData & _refInstruments() { return m_Instruments; }
	};

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_QUOTATION_DownloadInstruments, p)
		{}
	};

}

}
#endif
