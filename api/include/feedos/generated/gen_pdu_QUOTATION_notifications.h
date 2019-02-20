/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_QUOTATION_NOTIFICATIONS_H
#define FEEDOS_generated_PDU_QUOTATION_NOTIFICATIONS_H

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

	namespace PDU_outbound_QUOTATION
	{
	class SubscribeNotif_TradeEvent: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeEvent (FOSInstrumentCode const & a, Timestamp const & b, QuotationTradeEvent const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeEvent)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_QuotationTradeEvent (*this, c);
		}
	};

	class SubscribeNotif_ValuesUpdate: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ValuesUpdate (FOSInstrumentCode const & a, Timestamp const & b, QuotationValuesUpdate const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ValuesUpdate)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_QuotationValuesUpdate (*this, c);
		}
	};

	class SubscribeNotif_TradeEventExt: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeEventExt (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, QuotationTradeEventExt const & d) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeEventExt)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_QuotationTradeEventExt (*this, d);
		}
	};

	class SubscribeNotif_ValuesUpdateOneInstrument: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ValuesUpdateOneInstrument (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationVariable const & d) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ValuesUpdateOneInstrument)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationVariable (*this, d);
		}
	};

	class SubscribeNotif_TradeCancelCorrection: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeCancelCorrection (FOSInstrumentCode const & a, Timestamp const & b, QuotationTradeCancelCorrection const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeCancelCorrection)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_QuotationTradeCancelCorrection (*this, c);
		}
	};

	class SubscribeNotif_IntradayBars: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayBars (ListOfQuotationIntradayBar const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_IntradayBars)
		{
			Encode_ListOfQuotationIntradayBar (*this, a);
		}
	};

	class SubscribeNotif_DeleteBar: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_DeleteBar (FOSInstrumentCode const & a, uint16 b, Timestamp const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DeleteBar)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_uint16 (*this, b);
			Encode_Timestamp (*this, c);
		}
	};

	class SubscribeNotif_CorrectedBar: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_CorrectedBar (QuotationIntradayBar const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_CorrectedBar)
		{
			Encode_QuotationIntradayBar (*this, a);
		}
	};

	class SubscribeNotif_OrderBookRefresh: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookRefresh (FOSInstrumentCode const & a, Timestamp const & b, int8 c, int8 d, ListOfOrderBookEntry const & e, ListOfOrderBookEntry const & f) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookRefresh)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_int8 (*this, c);
			Encode_int8 (*this, d);
			Encode_ListOfOrderBookEntry (*this, e);
			Encode_ListOfOrderBookEntry (*this, f);
		}
	};

	class SubscribeNotif_OrderBookDeltaRefresh: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookDeltaRefresh (FOSInstrumentCode const & a, Timestamp const & b, OrderBookDeltaRefresh const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookDeltaRefresh)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_OrderBookDeltaRefresh (*this, c);
		}
	};

	class SubscribeNotif_OrderBookMaxVisibleDepth: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookMaxVisibleDepth (FOSInstrumentCode const & a, int8 b) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookMaxVisibleDepth)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_int8 (*this, b);
		}
	};

	class SubscribeNotif_MBLFullRefresh: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLFullRefresh (ListOfMBLSnapshot const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLFullRefresh)
		{
			Encode_ListOfMBLSnapshot (*this, a);
		}
	};

	class SubscribeNotif_MBLOverlapRefresh: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLOverlapRefresh (MBLOverlapRefresh const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLOverlapRefresh)
		{
			Encode_MBLOverlapRefresh (*this, a);
		}
	};

	class SubscribeNotif_MBLDeltaRefresh: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLDeltaRefresh (MBLDeltaRefresh const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLDeltaRefresh)
		{
			Encode_MBLDeltaRefresh (*this, a);
		}
	};

	class SubscribeNotif_MBLMaxVisibleDepth: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLMaxVisibleDepth (MBLMaxVisibleDepth const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLMaxVisibleDepth)
		{
			Encode_MBLMaxVisibleDepth (*this, a);
		}
	};

	class SubscribeNotif_MarketNews: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarketNews (MarketNews const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MarketNews)
		{
			Encode_MarketNews (*this, a);
		}
	};

	class SubscribeNotif_MarketStatus: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarketStatus (MarketStatus const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MarketStatus)
		{
			Encode_MarketStatus (*this, a);
		}
	};

	class SubscribeNotif_MulticastDataReplayHeader: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MulticastDataReplayHeader (MulticastFrameHeaderStruct const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MulticastDataReplayHeader)
		{
			Encode_MulticastFrameHeaderStruct (*this, a);
		}
	};

	class SubscribeNotif_NewOrder: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_NewOrder (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationContextFlag const & d, FIXSide e, MarketSheetEntry const & f, MarketSheetLevel g) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_NewOrder)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationContextFlag (*this, d);
			Encode_FIXSide (*this, e);
			Encode_MarketSheetEntry (*this, f);
			Encode_MarketSheetLevel (*this, g);
		}
	};

	class SubscribeNotif_ModifyOrder: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ModifyOrder (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationContextFlag const & d, FIXSide e, MarketSheetEntry const & f, MarketSheetLevel g, MarketSheetLevel h) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ModifyOrder)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationContextFlag (*this, d);
			Encode_FIXSide (*this, e);
			Encode_MarketSheetEntry (*this, f);
			Encode_MarketSheetLevel (*this, g);
			Encode_MarketSheetLevel (*this, h);
		}
	};

	class SubscribeNotif_RemoveOneOrder: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveOneOrder (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationContextFlag const & d, FIXSide e, String const & f, MarketSheetLevel g) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveOneOrder)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationContextFlag (*this, d);
			Encode_FIXSide (*this, e);
			Encode_String (*this, f);
			Encode_MarketSheetLevel (*this, g);
		}
	};

	class SubscribeNotif_RemoveAllPreviousOrders: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveAllPreviousOrders (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationContextFlag const & d, FIXSide e, String const & f, MarketSheetLevel g) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveAllPreviousOrders)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationContextFlag (*this, d);
			Encode_FIXSide (*this, e);
			Encode_String (*this, f);
			Encode_MarketSheetLevel (*this, g);
		}
	};

	class SubscribeNotif_RemoveAllOrders: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveAllOrders (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, ListOfQuotationContextFlag const & d, FIXSide e) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveAllOrders)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_ListOfQuotationContextFlag (*this, d);
			Encode_FIXSide (*this, e);
		}
	};

	class SubscribeNotif_Retransmission: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Retransmission (FOSInstrumentCode const & a, Timestamp const & b, Timestamp const & c, MarketSheet const & d) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_Retransmission)
		{
			Encode_FOSInstrumentCode (*this, a);
			Encode_Timestamp (*this, b);
			Encode_Timestamp (*this, c);
			Encode_MarketSheet (*this, d);
		}
	};

	} // namespace PDU_outbound_QUOTATION


	namespace PDU_inbound_QUOTATION
	{
	class SubscribeNotif_TradeEvent: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeEvent (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeEvent, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_QuotationTradeEvent (*this, m_Data);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline QuotationTradeEvent const & getData() const { return m_Data; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_MarketUTCTimestamp;
		QuotationTradeEvent m_Data;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline QuotationTradeEvent & _refData() { return m_Data; }
	};

	class SubscribeNotif_ValuesUpdate: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ValuesUpdate (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ValuesUpdate, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_QuotationValuesUpdate (*this, m_Data);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline QuotationValuesUpdate const & getData() const { return m_Data; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_MarketUTCTimestamp;
		QuotationValuesUpdate m_Data;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline QuotationValuesUpdate & _refData() { return m_Data; }
	};

	class SubscribeNotif_TradeEventExt: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeEventExt (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeEventExt, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_QuotationTradeEventExt (*this, m_Data);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline QuotationTradeEventExt const & getData() const { return m_Data; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		QuotationTradeEventExt m_Data;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline QuotationTradeEventExt & _refData() { return m_Data; }
	};

	class SubscribeNotif_ValuesUpdateOneInstrument: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ValuesUpdateOneInstrument (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ValuesUpdateOneInstrument, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationVariable (*this, m_Values);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationVariable const & getValues() const { return m_Values; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationVariable m_Values;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationVariable & _refValues() { return m_Values; }
	};

	class SubscribeNotif_TradeCancelCorrection: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeCancelCorrection (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_TradeCancelCorrection, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerTimestamp);
			Decode_QuotationTradeCancelCorrection (*this, m_Data);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerTimestamp() const { return m_ServerTimestamp; }
		inline QuotationTradeCancelCorrection const & getData() const { return m_Data; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerTimestamp;
		QuotationTradeCancelCorrection m_Data;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerTimestamp() { return m_ServerTimestamp; }
		inline QuotationTradeCancelCorrection & _refData() { return m_Data; }
	};

	class SubscribeNotif_IntradayBars: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_IntradayBars (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_IntradayBars, p)
		{
			Decode_ListOfQuotationIntradayBar (*this, m_List);
		}
		inline ListOfQuotationIntradayBar const & getList() const { return m_List; }
	private:
		ListOfQuotationIntradayBar m_List;
	public:
		inline ListOfQuotationIntradayBar & _refList() { return m_List; }
	};

	class SubscribeNotif_DeleteBar: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_DeleteBar (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_DeleteBar, p)
		{
			Decode_FOSInstrumentCode (*this, m_InstrCode);
			Decode_uint16 (*this, m_ServerDuration_seconds);
			Decode_Timestamp (*this, m_ServerUTCTimestamp_begin);
		}
		inline FOSInstrumentCode const & getInstrCode() const { return m_InstrCode; }
		inline uint16 const & getServerDuration_seconds() const { return m_ServerDuration_seconds; }
		inline Timestamp const & getServerUTCTimestamp_begin() const { return m_ServerUTCTimestamp_begin; }
	private:
		FOSInstrumentCode m_InstrCode;
		uint16 m_ServerDuration_seconds;
		Timestamp m_ServerUTCTimestamp_begin;
	public:
		inline FOSInstrumentCode & _refInstrCode() { return m_InstrCode; }
		inline uint16 & _refServerDuration_seconds() { return m_ServerDuration_seconds; }
		inline Timestamp & _refServerUTCTimestamp_begin() { return m_ServerUTCTimestamp_begin; }
	};

	class SubscribeNotif_CorrectedBar: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_CorrectedBar (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_CorrectedBar, p)
		{
			Decode_QuotationIntradayBar (*this, m_Bar);
		}
		inline QuotationIntradayBar const & getBar() const { return m_Bar; }
	private:
		QuotationIntradayBar m_Bar;
	public:
		inline QuotationIntradayBar & _refBar() { return m_Bar; }
	};

	class SubscribeNotif_OrderBookRefresh: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookRefresh (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookRefresh, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_int8 (*this, m_BidChangeIndicator);
			Decode_int8 (*this, m_AskChangeIndicator);
			Decode_ListOfOrderBookEntry (*this, m_BidLimits);
			Decode_ListOfOrderBookEntry (*this, m_AskLimits);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline int8 const & getBidChangeIndicator() const { return m_BidChangeIndicator; }
		inline int8 const & getAskChangeIndicator() const { return m_AskChangeIndicator; }
		inline ListOfOrderBookEntry const & getBidLimits() const { return m_BidLimits; }
		inline ListOfOrderBookEntry const & getAskLimits() const { return m_AskLimits; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		int8 m_BidChangeIndicator;
		int8 m_AskChangeIndicator;
		ListOfOrderBookEntry m_BidLimits;
		ListOfOrderBookEntry m_AskLimits;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline int8 & _refBidChangeIndicator() { return m_BidChangeIndicator; }
		inline int8 & _refAskChangeIndicator() { return m_AskChangeIndicator; }
		inline ListOfOrderBookEntry & _refBidLimits() { return m_BidLimits; }
		inline ListOfOrderBookEntry & _refAskLimits() { return m_AskLimits; }
	};

	class SubscribeNotif_OrderBookDeltaRefresh: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookDeltaRefresh (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookDeltaRefresh, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_OrderBookDeltaRefresh (*this, m_Delta);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline OrderBookDeltaRefresh const & getDelta() const { return m_Delta; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		OrderBookDeltaRefresh m_Delta;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline OrderBookDeltaRefresh & _refDelta() { return m_Delta; }
	};

	class SubscribeNotif_OrderBookMaxVisibleDepth: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_OrderBookMaxVisibleDepth (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_OrderBookMaxVisibleDepth, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_int8 (*this, m_MaxVisibleDepth);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline int8 const & getMaxVisibleDepth() const { return m_MaxVisibleDepth; }
	private:
		FOSInstrumentCode m_Code;
		int8 m_MaxVisibleDepth;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline int8 & _refMaxVisibleDepth() { return m_MaxVisibleDepth; }
	};

	class SubscribeNotif_MBLFullRefresh: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLFullRefresh (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLFullRefresh, p)
		{
			Decode_ListOfMBLSnapshot (*this, m_Data);
		}
		inline ListOfMBLSnapshot const & getData() const { return m_Data; }
	private:
		ListOfMBLSnapshot m_Data;
	public:
		inline ListOfMBLSnapshot & _refData() { return m_Data; }
	};

	class SubscribeNotif_MBLOverlapRefresh: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLOverlapRefresh (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLOverlapRefresh, p)
		{
			Decode_MBLOverlapRefresh (*this, m_Data);
		}
		inline MBLOverlapRefresh const & getData() const { return m_Data; }
	private:
		MBLOverlapRefresh m_Data;
	public:
		inline MBLOverlapRefresh & _refData() { return m_Data; }
	};

	class SubscribeNotif_MBLDeltaRefresh: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLDeltaRefresh (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLDeltaRefresh, p)
		{
			Decode_MBLDeltaRefresh (*this, m_Data);
		}
		inline MBLDeltaRefresh const & getData() const { return m_Data; }
	private:
		MBLDeltaRefresh m_Data;
	public:
		inline MBLDeltaRefresh & _refData() { return m_Data; }
	};

	class SubscribeNotif_MBLMaxVisibleDepth: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MBLMaxVisibleDepth (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MBLMaxVisibleDepth, p)
		{
			Decode_MBLMaxVisibleDepth (*this, m_Data);
		}
		inline MBLMaxVisibleDepth const & getData() const { return m_Data; }
	private:
		MBLMaxVisibleDepth m_Data;
	public:
		inline MBLMaxVisibleDepth & _refData() { return m_Data; }
	};

	class SubscribeNotif_MarketNews: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarketNews (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MarketNews, p)
		{
			Decode_MarketNews (*this, m_News);
		}
		inline MarketNews const & getNews() const { return m_News; }
	private:
		MarketNews m_News;
	public:
		inline MarketNews & _refNews() { return m_News; }
	};

	class SubscribeNotif_MarketStatus: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarketStatus (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MarketStatus, p)
		{
			Decode_MarketStatus (*this, m_Status);
		}
		inline MarketStatus const & getStatus() const { return m_Status; }
	private:
		MarketStatus m_Status;
	public:
		inline MarketStatus & _refStatus() { return m_Status; }
	};

	class SubscribeNotif_MulticastDataReplayHeader: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MulticastDataReplayHeader (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_MulticastDataReplayHeader, p)
		{
			Decode_MulticastFrameHeaderStruct (*this, m_Header);
		}
		inline MulticastFrameHeaderStruct const & getHeader() const { return m_Header; }
	private:
		MulticastFrameHeaderStruct m_Header;
	public:
		inline MulticastFrameHeaderStruct & _refHeader() { return m_Header; }
	};

	class SubscribeNotif_NewOrder: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_NewOrder (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_NewOrder, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationContextFlag (*this, m_Context);
			Decode_FIXSide (*this, m_Side);
			Decode_MarketSheetEntry (*this, m_Entry);
			Decode_MarketSheetLevel (*this, m_Level);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag const & getContext() const { return m_Context; }
		inline FIXSide const & getSide() const { return m_Side; }
		inline MarketSheetEntry const & getEntry() const { return m_Entry; }
		inline MarketSheetLevel const & getLevel() const { return m_Level; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationContextFlag m_Context;
		FIXSide m_Side;
		MarketSheetEntry m_Entry;
		MarketSheetLevel m_Level;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag & _refContext() { return m_Context; }
		inline FIXSide & _refSide() { return m_Side; }
		inline MarketSheetEntry & _refEntry() { return m_Entry; }
		inline MarketSheetLevel & _refLevel() { return m_Level; }
	};

	class SubscribeNotif_ModifyOrder: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_ModifyOrder (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_ModifyOrder, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationContextFlag (*this, m_Context);
			Decode_FIXSide (*this, m_Side);
			Decode_MarketSheetEntry (*this, m_Entry);
			Decode_MarketSheetLevel (*this, m_OldLevel);
			Decode_MarketSheetLevel (*this, m_NewLevel);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag const & getContext() const { return m_Context; }
		inline FIXSide const & getSide() const { return m_Side; }
		inline MarketSheetEntry const & getEntry() const { return m_Entry; }
		inline MarketSheetLevel const & getOldLevel() const { return m_OldLevel; }
		inline MarketSheetLevel const & getNewLevel() const { return m_NewLevel; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationContextFlag m_Context;
		FIXSide m_Side;
		MarketSheetEntry m_Entry;
		MarketSheetLevel m_OldLevel;
		MarketSheetLevel m_NewLevel;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag & _refContext() { return m_Context; }
		inline FIXSide & _refSide() { return m_Side; }
		inline MarketSheetEntry & _refEntry() { return m_Entry; }
		inline MarketSheetLevel & _refOldLevel() { return m_OldLevel; }
		inline MarketSheetLevel & _refNewLevel() { return m_NewLevel; }
	};

	class SubscribeNotif_RemoveOneOrder: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveOneOrder (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveOneOrder, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationContextFlag (*this, m_Context);
			Decode_FIXSide (*this, m_Side);
			Decode_String (*this, m_OrderID);
			Decode_MarketSheetLevel (*this, m_Level);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag const & getContext() const { return m_Context; }
		inline FIXSide const & getSide() const { return m_Side; }
		inline String const & getOrderID() const { return m_OrderID; }
		inline MarketSheetLevel const & getLevel() const { return m_Level; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationContextFlag m_Context;
		FIXSide m_Side;
		String m_OrderID;
		MarketSheetLevel m_Level;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag & _refContext() { return m_Context; }
		inline FIXSide & _refSide() { return m_Side; }
		inline String & _refOrderID() { return m_OrderID; }
		inline MarketSheetLevel & _refLevel() { return m_Level; }
	};

	class SubscribeNotif_RemoveAllPreviousOrders: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveAllPreviousOrders (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveAllPreviousOrders, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationContextFlag (*this, m_Context);
			Decode_FIXSide (*this, m_Side);
			Decode_String (*this, m_OrderID);
			Decode_MarketSheetLevel (*this, m_Level);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag const & getContext() const { return m_Context; }
		inline FIXSide const & getSide() const { return m_Side; }
		inline String const & getOrderID() const { return m_OrderID; }
		inline MarketSheetLevel const & getLevel() const { return m_Level; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationContextFlag m_Context;
		FIXSide m_Side;
		String m_OrderID;
		MarketSheetLevel m_Level;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag & _refContext() { return m_Context; }
		inline FIXSide & _refSide() { return m_Side; }
		inline String & _refOrderID() { return m_OrderID; }
		inline MarketSheetLevel & _refLevel() { return m_Level; }
	};

	class SubscribeNotif_RemoveAllOrders: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RemoveAllOrders (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_RemoveAllOrders, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_ListOfQuotationContextFlag (*this, m_Context);
			Decode_FIXSide (*this, m_Side);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag const & getContext() const { return m_Context; }
		inline FIXSide const & getSide() const { return m_Side; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		ListOfQuotationContextFlag m_Context;
		FIXSide m_Side;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline ListOfQuotationContextFlag & _refContext() { return m_Context; }
		inline FIXSide & _refSide() { return m_Side; }
	};

	class SubscribeNotif_Retransmission: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_Retransmission (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_QUOTATION_Retransmission, p)
		{
			Decode_FOSInstrumentCode (*this, m_Code);
			Decode_Timestamp (*this, m_ServerUTCTimestamp);
			Decode_Timestamp (*this, m_MarketUTCTimestamp);
			Decode_MarketSheet (*this, m_Snapshot);
		}
		inline FOSInstrumentCode const & getCode() const { return m_Code; }
		inline Timestamp const & getServerUTCTimestamp() const { return m_ServerUTCTimestamp; }
		inline Timestamp const & getMarketUTCTimestamp() const { return m_MarketUTCTimestamp; }
		inline MarketSheet const & getSnapshot() const { return m_Snapshot; }
	private:
		FOSInstrumentCode m_Code;
		Timestamp m_ServerUTCTimestamp;
		Timestamp m_MarketUTCTimestamp;
		MarketSheet m_Snapshot;
	public:
		inline FOSInstrumentCode & _refCode() { return m_Code; }
		inline Timestamp & _refServerUTCTimestamp() { return m_ServerUTCTimestamp; }
		inline Timestamp & _refMarketUTCTimestamp() { return m_MarketUTCTimestamp; }
		inline MarketSheet & _refSnapshot() { return m_Snapshot; }
	};

	} // namespace PDU_inbound_QUOTATION

}
#endif
