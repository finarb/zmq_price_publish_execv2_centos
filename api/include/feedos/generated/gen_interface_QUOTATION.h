/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_QUOTATION_H
#define FEEDOS_generated_INTERFACE_QUOTATION_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming \
		virtual void response_QUOTATION_SubscribeAllDataAndStatus_Started (); \
		virtual void response_QUOTATION_SubscribeAllDataAndStatus_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllDataAndStatus (ReturnCode rc); \
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData); \
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData); \
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData); \
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData); \
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus); \
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews); \


	class INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming() {}

		virtual void response_QUOTATION_SubscribeAllDataAndStatus_Started () = 0;
		virtual void response_QUOTATION_SubscribeAllDataAndStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeAllDataAndStatus (ReturnCode rc) = 0;
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData) = 0;
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData) = 0;
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData) = 0;
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData) = 0;
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus) = 0;
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming \
		virtual void response_QUOTATION_SubscribeAllOrderBook_Started (); \
		virtual void response_QUOTATION_SubscribeAllOrderBook_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllOrderBook (ReturnCode rc); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth); \
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData); \
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData); \
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData); \
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData); \


	class INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming() {}

		virtual void response_QUOTATION_SubscribeAllOrderBook_Started () = 0;
		virtual void response_QUOTATION_SubscribeAllOrderBook_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeAllOrderBook (ReturnCode rc) = 0;
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits) = 0;
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta) = 0;
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth) = 0;
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData) = 0;
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData) = 0;
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData) = 0;
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllStatus_streaming \
		virtual void response_QUOTATION_SubscribeAllStatus_Started (); \
		virtual void response_QUOTATION_SubscribeAllStatus_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllStatus (ReturnCode rc); \
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus); \
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews); \


	class INTERFACE_QUOTATION_SubscribeAllStatus_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeAllStatus_streaming() {}

		virtual void response_QUOTATION_SubscribeAllStatus_Started () = 0;
		virtual void response_QUOTATION_SubscribeAllStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeAllStatus (ReturnCode rc) = 0;
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus) = 0;
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeMarketsStatus_streaming \
		virtual void response_QUOTATION_SubscribeMarketsStatus_Started (FeedOS::Types::ListOfMarketStatus const & inMarketsStatus); \
		virtual void response_QUOTATION_SubscribeMarketsStatus_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeMarketsStatus (ReturnCode rc); \
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus); \
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews); \


	class INTERFACE_QUOTATION_SubscribeMarketsStatus_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeMarketsStatus_streaming() {}

		virtual void response_QUOTATION_SubscribeMarketsStatus_Started (FeedOS::Types::ListOfMarketStatus const & inMarketsStatus) = 0;
		virtual void response_QUOTATION_SubscribeMarketsStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeMarketsStatus (ReturnCode rc) = 0;
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus) = 0;
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming \
		virtual void response_QUOTATION_SubscribeInstrumentsL1_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatusL1 const & inSnapshot); \
		virtual void response_QUOTATION_SubscribeInstrumentsL1_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeInstrumentsL1 (ReturnCode rc); \
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData); \
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData); \


	class INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming() {}

		virtual void response_QUOTATION_SubscribeInstrumentsL1_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatusL1 const & inSnapshot) = 0;
		virtual void response_QUOTATION_SubscribeInstrumentsL1_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeInstrumentsL1 (ReturnCode rc) = 0;
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData) = 0;
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstruments_OBSOLETE_streaming \
		virtual void response_QUOTATION_SubscribeInstruments_OBSOLETE_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatus const & inSnapshot); \
		virtual void response_QUOTATION_SubscribeInstruments_OBSOLETE_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeInstruments_OBSOLETE (ReturnCode rc); \
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData); \
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData); \


	class INTERFACE_QUOTATION_SubscribeInstruments_OBSOLETE_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeInstruments_OBSOLETE_streaming() {}

		virtual void response_QUOTATION_SubscribeInstruments_OBSOLETE_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatus const & inSnapshot) = 0;
		virtual void response_QUOTATION_SubscribeInstruments_OBSOLETE_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeInstruments_OBSOLETE (ReturnCode rc) = 0;
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData) = 0;
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook2_streaming \
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Started (FOSInstrumentCode inInternalCode,  FeedOS::Types::OrderBook const & inOrderBook); \
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeOneInstrumentOrderBook2 (ReturnCode rc); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth); \


	class INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook2_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook2_streaming() {}

		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Started (FOSInstrumentCode inInternalCode,  FeedOS::Types::OrderBook const & inOrderBook) = 0;
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeOneInstrumentOrderBook2 (ReturnCode rc) = 0;
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits) = 0;
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta) = 0;
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming \
		virtual void response_QUOTATION_SubscribeInstrumentsL2_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatusL2 const & inSnapshot); \
		virtual void response_QUOTATION_SubscribeInstrumentsL2_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeInstrumentsL2 (ReturnCode rc); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth); \


	class INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming() {}

		virtual void response_QUOTATION_SubscribeInstrumentsL2_Started (uint32 inTicket,  FeedOS::Types::ListOfInstrumentStatusL2 const & inSnapshot) = 0;
		virtual void response_QUOTATION_SubscribeInstrumentsL2_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeInstrumentsL2 (ReturnCode rc) = 0;
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits) = 0;
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta) = 0;
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming \
		virtual void response_QUOTATION_SubscribeInstrumentsMBL_Started (uint32 inTicket,  FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void response_QUOTATION_SubscribeInstrumentsMBL_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeInstrumentsMBL (ReturnCode rc); \
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData); \
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData); \
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData); \
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData); \


	class INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming() {}

		virtual void response_QUOTATION_SubscribeInstrumentsMBL_Started (uint32 inTicket,  FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void response_QUOTATION_SubscribeInstrumentsMBL_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeInstrumentsMBL (ReturnCode rc) = 0;
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData) = 0;
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData) = 0;
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData) = 0;
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming \
		virtual void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started (FOSInstrumentCode inInternalCode, Timestamp const & inLastUpdateServerUTCTimestamp, Timestamp const & inLastUpdateMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot); \
		virtual void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeOneInstrumentMarketSheet (ReturnCode rc); \
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel); \
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide); \
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot); \
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues); \


	class INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming() {}

		virtual void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started (FOSInstrumentCode inInternalCode, Timestamp const & inLastUpdateServerUTCTimestamp, Timestamp const & inLastUpdateMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot) = 0;
		virtual void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeOneInstrumentMarketSheet (ReturnCode rc) = 0;
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel) = 0;
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide) = 0;
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot) = 0;
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming \
		virtual void response_QUOTATION_SubscribeInstrumentsMBO_Started (uint32 inTicket,  FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void response_QUOTATION_SubscribeInstrumentsMBO_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeInstrumentsMBO (ReturnCode rc); \
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel); \
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide); \
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot); \
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues); \


	class INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeInstrumentsMBO_streaming() {}

		virtual void response_QUOTATION_SubscribeInstrumentsMBO_Started (uint32 inTicket,  FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void response_QUOTATION_SubscribeInstrumentsMBO_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeInstrumentsMBO (ReturnCode rc) = 0;
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel) = 0;
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide) = 0;
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot) = 0;
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming \
		virtual void response_QUOTATION_SubscribeAllMarketSheet_Started (); \
		virtual void response_QUOTATION_SubscribeAllMarketSheet_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllMarketSheet (ReturnCode rc); \
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel); \
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel); \
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide); \
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot); \
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues); \


	class INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming() {}

		virtual void response_QUOTATION_SubscribeAllMarketSheet_Started () = 0;
		virtual void response_QUOTATION_SubscribeAllMarketSheet_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeAllMarketSheet (ReturnCode rc) = 0;
		virtual void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide,  FeedOS::Types::MarketSheetEntry const & inEntry,  FeedOS::Types::MarketSheetLevel inOldLevel,  FeedOS::Types::MarketSheetLevel inNewLevel) = 0;
		virtual void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide, String const & inOrderID,  FeedOS::Types::MarketSheetLevel inLevel) = 0;
		virtual void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationContextFlag const & inContext,  FeedOS::Types::FIXSide inSide) = 0;
		virtual void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::MarketSheet const & inSnapshot) = 0;
		virtual void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_MulticastDataReplayL1_streaming \
		virtual void response_QUOTATION_MulticastDataReplayL1_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void response_QUOTATION_MulticastDataReplayL1_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_MulticastDataReplayL1 (ReturnCode rc); \
		virtual void notif_MulticastDataReplayHeader	(FeedOS::Types::MulticastFrameHeaderStruct const & inHeader); \
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData); \
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData); \
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData); \
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData); \
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus); \
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews); \


	class INTERFACE_QUOTATION_MulticastDataReplayL1_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_MulticastDataReplayL1_streaming() {}

		virtual void response_QUOTATION_MulticastDataReplayL1_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void response_QUOTATION_MulticastDataReplayL1_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_MulticastDataReplayL1 (ReturnCode rc) = 0;
		virtual void notif_MulticastDataReplayHeader	(FeedOS::Types::MulticastFrameHeaderStruct const & inHeader) = 0;
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData) = 0;
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData) = 0;
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData) = 0;
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData) = 0;
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus) = 0;
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_MulticastDataReplayL2_streaming \
		virtual void response_QUOTATION_MulticastDataReplayL2_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void response_QUOTATION_MulticastDataReplayL2_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_MulticastDataReplayL2 (ReturnCode rc); \
		virtual void notif_MulticastDataReplayHeader	(FeedOS::Types::MulticastFrameHeaderStruct const & inHeader); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth); \
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData); \
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData); \
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData); \
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData); \


	class INTERFACE_QUOTATION_MulticastDataReplayL2_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_MulticastDataReplayL2_streaming() {}

		virtual void response_QUOTATION_MulticastDataReplayL2_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void response_QUOTATION_MulticastDataReplayL2_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_MulticastDataReplayL2 (ReturnCode rc) = 0;
		virtual void notif_MulticastDataReplayHeader	(FeedOS::Types::MulticastFrameHeaderStruct const & inHeader) = 0;
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits) = 0;
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta) = 0;
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth) = 0;
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData) = 0;
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData) = 0;
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData) = 0;
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadInstruments_streaming \
		virtual void response_QUOTATION_DownloadInstruments_Started (Timestamp const & inLastActivityTimestamp); \
		virtual void response_QUOTATION_DownloadInstruments_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_DownloadInstruments (ReturnCode rc); \
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inSelectedQuantity); \
		virtual void notif_Instruments	(FeedOS::Types::ListOfInstrumentData const & inInstruments); \


	class INTERFACE_QUOTATION_DownloadInstruments_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_DownloadInstruments_streaming() {}

		virtual void response_QUOTATION_DownloadInstruments_Started (Timestamp const & inLastActivityTimestamp) = 0;
		virtual void response_QUOTATION_DownloadInstruments_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_DownloadInstruments (ReturnCode rc) = 0;
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inSelectedQuantity) = 0;
		virtual void notif_Instruments	(FeedOS::Types::ListOfInstrumentData const & inInstruments) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming \
		virtual void response_QUOTATION_SubscribeAllIntradayBars_Started (); \
		virtual void response_QUOTATION_SubscribeAllIntradayBars_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllIntradayBars (ReturnCode rc); \
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList); \
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin); \
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar); \


	class INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeAllIntradayBars_streaming() {}

		virtual void response_QUOTATION_SubscribeAllIntradayBars_Started () = 0;
		virtual void response_QUOTATION_SubscribeAllIntradayBars_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeAllIntradayBars (ReturnCode rc) = 0;
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList) = 0;
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin) = 0;
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming \
		virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Started (FeedOS::Types::ListOfMarketStatus const & inMarketsStatus); \
		virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeMarketsDataAndStatus (ReturnCode rc); \
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData); \
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData); \
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData); \
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData); \
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus); \
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews); \


	class INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming() {}

		virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Started (FeedOS::Types::ListOfMarketStatus const & inMarketsStatus) = 0;
		virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeMarketsDataAndStatus (ReturnCode rc) = 0;
		virtual void notif_TradeEventExt	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEventExt const & inData) = 0;
		virtual void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData) = 0;
		virtual void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData) = 0;
		virtual void notif_TradeCancelCorrection	(FOSInstrumentCode inCode, Timestamp const & inServerTimestamp,  FeedOS::Types::QuotationTradeCancelCorrection const & inData) = 0;
		virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus) = 0;
		virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming \
		virtual void response_QUOTATION_SubscribeMarketsOrderBook_Started (); \
		virtual void response_QUOTATION_SubscribeMarketsOrderBook_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeMarketsOrderBook (ReturnCode rc); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth); \
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData); \
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData); \
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData); \
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData); \


	class INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming() {}

		virtual void response_QUOTATION_SubscribeMarketsOrderBook_Started () = 0;
		virtual void response_QUOTATION_SubscribeMarketsOrderBook_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeMarketsOrderBook (ReturnCode rc) = 0;
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits) = 0;
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta) = 0;
		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth) = 0;
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData) = 0;
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData) = 0;
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData) = 0;
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadHistoryIntradayBars_streaming \
		virtual void response_QUOTATION_DownloadHistoryIntradayBars_Started (); \
		virtual void response_QUOTATION_DownloadHistoryIntradayBars_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_DownloadHistoryIntradayBars (ReturnCode rc); \
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inBars); \
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin); \
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar); \


	class INTERFACE_QUOTATION_DownloadHistoryIntradayBars_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_DownloadHistoryIntradayBars_streaming() {}

		virtual void response_QUOTATION_DownloadHistoryIntradayBars_Started () = 0;
		virtual void response_QUOTATION_DownloadHistoryIntradayBars_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_DownloadHistoryIntradayBars (ReturnCode rc) = 0;
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inBars) = 0;
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin) = 0;
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming \
		virtual void response_QUOTATION_DownloadHistoryIntradayBarsExt_Started (); \
		virtual void response_QUOTATION_DownloadHistoryIntradayBarsExt_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_DownloadHistoryIntradayBarsExt (ReturnCode rc); \
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList); \
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin); \
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar); \


	class INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming() {}

		virtual void response_QUOTATION_DownloadHistoryIntradayBarsExt_Started () = 0;
		virtual void response_QUOTATION_DownloadHistoryIntradayBarsExt_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_DownloadHistoryIntradayBarsExt (ReturnCode rc) = 0;
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList) = 0;
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin) = 0;
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming \
		virtual void response_QUOTATION_DownloadHistoryIntradayExtended_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inCodes); \
		virtual void response_QUOTATION_DownloadHistoryIntradayExtended_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_DownloadHistoryIntradayExtended (ReturnCode rc); \
		virtual void notif_IntradayExtended	(FeedOS::Types::ListOfIntradayHistoryDataExtended const & inTrades); \
		virtual void notif_Cancel	(FeedOS::Types::IntradayHistoryCancel const & inCancel); \
		virtual void notif_Correction	(FeedOS::Types::IntradayHistoryCorrection const & inCorrection); \


	class INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_DownloadHistoryIntradayExtended_streaming() {}

		virtual void response_QUOTATION_DownloadHistoryIntradayExtended_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inCodes) = 0;
		virtual void response_QUOTATION_DownloadHistoryIntradayExtended_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_DownloadHistoryIntradayExtended (ReturnCode rc) = 0;
		virtual void notif_IntradayExtended	(FeedOS::Types::ListOfIntradayHistoryDataExtended const & inTrades) = 0;
		virtual void notif_Cancel	(FeedOS::Types::IntradayHistoryCancel const & inCancel) = 0;
		virtual void notif_Correction	(FeedOS::Types::IntradayHistoryCorrection const & inCorrection) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_MonitorInstrumentActivation_streaming \
		virtual void response_QUOTATION_MonitorInstrumentActivation_Started (uint32 inNbFollowingActivationList); \
		virtual void response_QUOTATION_MonitorInstrumentActivation_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_MonitorInstrumentActivation (ReturnCode rc); \
		virtual void notif_InstrumentActivationSuccess	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes); \
		virtual void notif_InstrumentActivationFailure	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes, ReturnCode inErrorCode); \
		virtual void notif_InstrumentDeactivationWarning	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes, uint32 inCountdownSeconds); \


	class INTERFACE_QUOTATION_MonitorInstrumentActivation_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_MonitorInstrumentActivation_streaming() {}

		virtual void response_QUOTATION_MonitorInstrumentActivation_Started (uint32 inNbFollowingActivationList) = 0;
		virtual void response_QUOTATION_MonitorInstrumentActivation_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_MonitorInstrumentActivation (ReturnCode rc) = 0;
		virtual void notif_InstrumentActivationSuccess	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes) = 0;
		virtual void notif_InstrumentActivationFailure	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes, ReturnCode inErrorCode) = 0;
		virtual void notif_InstrumentDeactivationWarning	(String const & inOutputChannel,  FeedOS::Types::ListOfPolymorphicInstrumentCode const & inCodes, uint32 inCountdownSeconds) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeIntradayBars_streaming \
		virtual void response_QUOTATION_SubscribeIntradayBars_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inCodes); \
		virtual void response_QUOTATION_SubscribeIntradayBars_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeIntradayBars (ReturnCode rc); \
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList); \
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin); \
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar); \


	class INTERFACE_QUOTATION_SubscribeIntradayBars_streaming
	{
	public:
		virtual ~INTERFACE_QUOTATION_SubscribeIntradayBars_streaming() {}

		virtual void response_QUOTATION_SubscribeIntradayBars_Started (FeedOS::Types::ListOfFOSInstrumentCode const & inCodes) = 0;
		virtual void response_QUOTATION_SubscribeIntradayBars_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeIntradayBars (ReturnCode rc) = 0;
		virtual void notif_IntradayBars	(FeedOS::Types::ListOfQuotationIntradayBar const & inList) = 0;
		virtual void notif_DeleteBar	(FOSInstrumentCode inInstrCode, uint16 inServerDuration_seconds, Timestamp const & inServerUTCTimestamp_begin) = 0;
		virtual void notif_CorrectedBar	(FeedOS::Types::QuotationIntradayBar const & inBar) = 0;

	};
}
#endif
