
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

// QUOTATION "CONTEXT" TAGS -- not persistent.
// Used to provide details on realtime events. See notif_TradeEventExt()


////////////////////////////
// FIX fields 
////////////////////////////
FEEDOS_DEF_TAG	(58,		Text,				std::string,		String)
FEEDOS_DEF_TAG	(277,		TradeCondition,		std::string,		String)
FEEDOS_DEF_TAG	(288,		Buyer,				std::string,		String)
FEEDOS_DEF_TAG	(289,		Seller,				std::string,		String)
FEEDOS_DEF_TAG	(546,		Scope,				Types::FIXScope,	char)
FEEDOS_DEF_TAG	(1003,		TradeID,			std::string,		String)


////////////////////////////
// non-standard tags
////////////////////////////
FEEDOS_DEF_TAG (9350,		OriginFOSMarketIdOf_LastPrice,	FOSLowLevelMarketId,			uint16)
FEEDOS_DEF_TAG (9351,		OriginOf_LastPrice,				std::string,					String)

FEEDOS_DEF_TAG (9352,		OriginFOSMarketIdOf_BestBid,	FOSLowLevelMarketId,			uint16)
FEEDOS_DEF_TAG (9353,		OriginOf_BestBid,				std::string,					String)

FEEDOS_DEF_TAG (9354,		OriginFOSMarketIdOf_BestAsk,	FOSLowLevelMarketId,			uint16)
FEEDOS_DEF_TAG (9355,		OriginOf_BestAsk,				std::string,					String)

FEEDOS_DEF_TAG (9906,		OriginOf_Quote,					std::string,					String) // 38145: origin of a Quote into a SI Quotes MBL multi layer or into an AOD MBL (Segment MIC)

FEEDOS_DEF_TAG (9356,		AggressorSide,					Types::FIXSide,					char)
FEEDOS_DEF_TAG (9357,		OrderModificationReason,		Types::OrderModificationReason,	Enum)
FEEDOS_DEF_TAG (9358,		TradeConditionsDictionaryKey,	uint32,		uint32)
FEEDOS_DEF_TAG (9359,		NbOfBuyOrdersTraded,			int32,		int32)
FEEDOS_DEF_TAG (9360,		NbOfSellOrdersTraded,			int32,		int32)
FEEDOS_DEF_TAG (9361,		PegOrderLimitPrice,				float64,	float64)
FEEDOS_DEF_TAG (9362,		HiddenLiquidityFlag,			bool,		bool)
FEEDOS_DEF_TAG (9363,		TargetMBLLayerId,				Types::OrderBookLayerId,		uint32)
FEEDOS_DEF_TAG (9365,		RawSequenceNumber,				uint32,							uint32)
FEEDOS_DEF_TAG (9901,		MMTFlagsV2,						std::string,					String) // generic trade condition as it comes from the exchange
FEEDOS_DEF_TAG (9904,		MMTFlagsV3,						std::string,					String) // generic trade condition as it comes from the exchange
FEEDOS_DEF_TAG (9907,		MiFID_TradePrice,				std::string,					String) // 38145: Price for trade Mifid II on CLOB instrument (second trade message)
FEEDOS_DEF_TAG (9908,		MiFID_TradeQty,					std::string,					String) // 38145: Quantity for trade Mifid II on CLOB instrument (second trade message)
FEEDOS_DEF_TAG (9913,		LastTradePriceCurrency,					std::string,					String) // 39432: Currency of the current trade. Disseminate only if the currency is different from PriceCurrency (tag Id:15)

FEEDOS_DEF_TAG (9902,		TradeImpactIndicator,			uint32,		uint32)
FEEDOS_DEF_TAG (9903,		TradingVenue,					FOSLowLevelMarketId,	uint16) // Trade condition, containing the market identification code from which a trade is reported.
FEEDOS_DEF_TAG (9909,		TradeExecutionVenue,			std::string,			String) // 38145: Most of the Time this is the MIC of the Execution Venue
FEEDOS_DEF_TAG (9910,		TradePublicationVenue,			std::string,			String) // 38145: Most of the Time this is the MIC of the Publication Venue
FEEDOS_DEF_TAG (9905,		TradeExecutionTimestamp,		Timestamp,				Timestamp) // 38145: Date and time when the transaction was executed.

FEEDOS_DEF_TAG (9375,		ActualTradingSessionId,					int8,							int8)
FEEDOS_DEF_TAG (9376,		CancelledOrModifiedTradingSessionId,	int8,							int8)
FEEDOS_DEF_TAG (9261,		MARKET_TradeType,		Types::FOSDictionaryEntryId,	uint32) // Generic Tag to provide the raw Market Trade Type or Trade Indicator or Trade Flag information

FEEDOS_DEF_TAG (9911,		AuctionOnDemand_TradingStatus,	Types::FIXSecurityTradingStatus,	Enum) // 38145: Specific Trading Status for AOD
FEEDOS_DEF_TAG (9912,		AuctionOnDemand_Start,			bool,								bool) // 38145: Set to True when the AOD starts / to False when the AOD is ended


////////////////////////////
// COMSTOCK-specific fields (30000 + CTF token number)
////////////////////////////
FEEDOS_DEF_TAG	(30000,		COMSTOCK_TOKENS_FIRST,				std::string,		String)
FEEDOS_DEF_TAG	(30003,		COMSTOCK_ENUM_SRC_ID,				std::string,		String)
FEEDOS_DEF_TAG	(32000,		COMSTOCK_QUOTE_COND_1,				std::string,		String)
FEEDOS_DEF_TAG	(32500,		COMSTOCK_f79,						std::string,		String)
FEEDOS_DEF_TAG	(33137,		COMSTOCK_FUND_INDEX_MEMBERSHIP,		std::string,		String)	// this is a referential tag !
FEEDOS_DEF_TAG	(39999,		COMSTOCK_TOKENS_LAST,				std::string,		String)


////////////////////////////
// MARKET-specific fields
////////////////////////////

// LSE
FEEDOS_DEF_TAG	(15000,		MARKET_LSE_TradeTypeIndicator,				std::string,		String)  // #37701: deprecated
FEEDOS_DEF_TAG	(15001,		MARKET_LSE_UncrossingVolume,				float64,			float64) // #37701: deprecated
FEEDOS_DEF_TAG	(15002,		MARKET_LSE_BargainConditionIndicator,		std::string,		String) // #37701: deprecated
FEEDOS_DEF_TAG	(15003,		MARKET_LSE_TradeTimeIndicator,				std::string,		String) // #37701: deprecated
FEEDOS_DEF_TAG	(15004,		MARKET_LSE_ConvertedPriceIndicator,			std::string,		String) // #37701: deprecated

// Euronext via FIM/UTP protocol
FEEDOS_DEF_TAG	(15050,		MARKET_EURONEXT_CrossOrderIndicator,		std::string,		String)
FEEDOS_DEF_TAG	(15051,		MARKET_EURONEXT_TheoreticalOpeningVolume,	float64,			float64)
FEEDOS_DEF_TAG	(15052,		MARKET_EURONEXT_OrderPriorityTimestamp,		Timestamp,			Timestamp)
FEEDOS_DEF_TAG	(15053,		MARKET_EURONEXT_TradeOffExchangeFlag,		std::string,		String)
FEEDOS_DEF_TAG	(15054,		MARKET_EURONEXT_TradingVenue,				std::string,		String)
FEEDOS_DEF_TAG	(15055,		MARKET_EURONEXT_OpeningTradeIndicator,		std::string,		String)
FEEDOS_DEF_TAG	(15056,		MARKET_EURONEXT_TradeTypeOfOperation,		std::string,		String)
FEEDOS_DEF_TAG	(15057,		MARKET_EURONEXT_MarketMechanism,			uint32,				uint32)

// CME
FEEDOS_DEF_TAG	(15100,		MARKET_CME_TradeTypeIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(15101,		MARKET_CME_MatchEventIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(15102,		MARKET_CME_MsgSeqNum,						uint32,				uint32)

// LIFFE
FEEDOS_DEF_TAG	(15200,		MARKET_LIFFE_TradeTypeIndicator,			std::string,		String)
FEEDOS_DEF_TAG  (15201,     MARKET_LIFFE_XDP_TradeTypeIndicator,		std::string,		String)

// B-PIPE
FEEDOS_DEF_TAG	(15250,		BPIPE_TradeAction,							std::string,		String)
FEEDOS_DEF_TAG	(15251,		BPIPE_TradeCondition,						std::string,		String)
FEEDOS_DEF_TAG	(15252,		BPIPE_TradeTypeIndicator,					std::string,		String)
FEEDOS_DEF_TAG	(15253,		BPIPE_QuoteConditionBid,					std::string,		String)
FEEDOS_DEF_TAG	(15254,		BPIPE_QuoteConditionAsk,					std::string,		String)
FEEDOS_DEF_TAG	(15255,		BPIPE_QuoteCondition,						std::string,		String)

// TURQUOISE
FEEDOS_DEF_TAG	(15300,		MARKET_TURQUOISE_TradeTypeIndicator,		std::string,		String) // #38896: deprecated
FEEDOS_DEF_TAG	(15301,		MARKET_TURQUOISE_LastAuctionQty,			float64,			float64)
FEEDOS_DEF_TAG	(15302,		MARKET_TURQUOISE_EndOfAuctionTime,			Timestamp,			Timestamp)
// obsolete: don't reuse:
// FEEDOS_DEF_TAG	(15303,		MARKET_TURQUOISE_TradeId,					std::string,		String)
// obsolete: don't reuse:
// FEEDOS_DEF_TAG	(15304,		MARKET_TURQUOISE_DealId,					std::string,		String)

// CEF
FEEDOS_DEF_TAG	(15150,		MARKET_CEF_IndexTypeIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(15151,		MARKET_CEF_LastAuctionQty,					float64,			float64)
FEEDOS_DEF_TAG	(15400,		MARKET_CEF_TradeTypeIndicator,				std::string,		String)

// SWX
FEEDOS_DEF_TAG	(15450,		MARKET_SWX_TradeTypeIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(15451,		MARKET_SWX_LastAuctionQty,					float64,			float64)
FEEDOS_DEF_TAG	(15452,		MARKET_SWX_TradeOffExchangeFlag,			std::string,		String)
FEEDOS_DEF_TAG	(15453,		MARKET_SWX_TradingPhase,					std::string,		String)

// ICE
FEEDOS_DEF_TAG	(15501,		MARKET_ICE_BlockTradeType,					std::string,		String)
FEEDOS_DEF_TAG	(15502,		MARKET_ICE_SystemPricedLegType,				std::string,		String)
FEEDOS_DEF_TAG	(15503,		MARKET_ICE_SequenceWithinMillis,			int32,				int32) // Can be used in conjunction with TransactDateTime field for sequence of deals within same milliseconds time.
FEEDOS_DEF_TAG	(15504,		MARKET_ICE_IsImplied,						bool,				bool) // Indicate the deal resulted from implied order if set to 1. It does not affect how market stats are calculated.

// BOVESPA
FEEDOS_DEF_TAG	(15550,		MARKET_BOVESPA_OrderPriorityTimestamp,		Timestamp,			Timestamp)
FEEDOS_DEF_TAG	(15551,		MARKET_BOVESPA_OriginOfTrade,				std::string,		String)

// BME
FEEDOS_DEF_TAG	(15600,		MARKET_BME_IndexTypeIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(15602,		MARKET_BME_TradeTypeIndicator,				std::string,		String)

// NASDAQ UTP
FEEDOS_DEF_TAG	(15650,     MARKET_NASDAQ_UTP_SaleCondition,            std::string,        String)
FEEDOS_DEF_TAG  (15651,     MARKET_NASDAQ_UTP_QuoteCondition,           char,               char)
FEEDOS_DEF_TAG  (15652,     MARKET_NASDAQ_UTP_SubMarketCenterId,        char,               char)

// CTA
FEEDOS_DEF_TAG  (15700,     MARKET_CTA_SaleCondition,                   std::string,        String)
FEEDOS_DEF_TAG  (15701,     MARKET_CTA_QuoteCondition,                  char,               char)

// BURGUNDY
FEEDOS_DEF_TAG	(15750,		MARKET_BURGUNDY_SubTypeOfTrade,				std::string,		String)

// EUREX ULTRA PLUS
FEEDOS_DEF_TAG	(15800,		MARKET_EUREX_ULTRA_PLUS_TradeType,			std::string,		String)
FEEDOS_DEF_TAG	(15801,		MARKET_EUREX_ULTRA_PLUS_TradeIndicator,		std::string,		String)
FEEDOS_DEF_TAG	(15802,		MARKET_EUREX_ULTRA_PLUS_StrategyTradeIndicator,std::string,		String)

// NASDAQ OMX EUROPE
FEEDOS_DEF_TAG	(15850,		MARKET_NASDAQ_OMX_EU_TradeType,				std::string,		String)

// XETRA ULTRA PLUS
FEEDOS_DEF_TAG	(15900,		MARKET_XETRA_ULTRA_PLUS_TradeType,			std::string,		String)
FEEDOS_DEF_TAG	(15901,		MARKET_XETRA_ULTRA_PLUS_TradeTypeIndicator,	char,				char)

// LSE_MIT
FEEDOS_DEF_TAG	(15950,		MARKET_LSE_MIT_OffBookReportingTradeTypeIndicator,	std::string,		String)
FEEDOS_DEF_TAG	(15951,		MARKET_LSE_MIT_AuctionTypeIndicator,		std::string,		String)
FEEDOS_DEF_TAG	(15952,		MARKET_LSE_MIT_FirmQuote,							bool,				bool) // #37701: deprecated
FEEDOS_DEF_TAG	(15953,		MARKET_LSE_MIT_CrossType,					char,				char) // #37701: deprecated

//BVMF
FEEDOS_DEF_TAG	(16000,		MARKET_BVMF_TradeTypeIndicator,				std::string,		String)
FEEDOS_DEF_TAG	(16001,		MARKET_BVMF_MsgSeqNum,						uint32,				uint32)

//OSE_OMX
FEEDOS_DEF_TAG	(16050,		MARKET_OSAKA_TradeCondition,                std::string,        String)
FEEDOS_DEF_TAG	(16051,		MARKET_OSAKA_TradeSource,                   std::string,        String)
FEEDOS_DEF_TAG	(16052,		MARKET_OSAKA_JNetTradingType,               std::string,        String)

// OMX
FEEDOS_DEF_TAG	(16100,		MARKET_OMX_NORDIC_OrderReferenceNumber,	    uint32,		        uint32)
FEEDOS_DEF_TAG	(16101,		MARKET_OMX_NORDIC_TradeType,		        char,		        char)
FEEDOS_DEF_TAG	(16102,		MARKET_OMX_NORDIC_NumberOfTrades,		    uint32,		        uint32)
FEEDOS_DEF_TAG	(16103,		MARKET_OMX_NORDIC_CrossType,		        char,		        char)
FEEDOS_DEF_TAG	(16104, 	MARKET_OMX_NORDIC_ReportedTradeType,		char,				char) // #37946: deprecated

// BATS
FEEDOS_DEF_TAG	(16150,		MARKET_BATS_ExecutionType,	                std::string,		String)
FEEDOS_DEF_TAG	(16151,		MARKET_BATS_TradeReportFlags,				unsigned int,		uint16) // specific trade condition as it comes from the exchange [2 chars encoded in an uint 16]

// TMX
FEEDOS_DEF_TAG	(16170,		MARKET_TMX_CrossType,		                char,				char) // #37641: deprecated
FEEDOS_DEF_TAG	(16171,		MARKET_TMX_StockState,		                std::string,		String)
FEEDOS_DEF_TAG	(16172,		MARKET_TMX_SettlementTerms,					char,				char)
FEEDOS_DEF_TAG	(16173,		MARKET_TMX_GroupStatus,		                std::string,		String)

// ADH
FEEDOS_DEF_TAG	(16200,		MARKET_ADH_TradeType,		   	   	        std::string,	    String)

// DIRECTEDGE
FEEDOS_DEF_TAG	(16220,		MARKET_DIRECTEDGE_HiddenLiquidityFlag,		bool,				bool)

// HOTSPOT
FEEDOS_DEF_TAG	(16250,		MARKET_HOTSPOT_MinQty,						float64,			float64)
FEEDOS_DEF_TAG	(16251,		MARKET_HOTSPOT_LotSize,						float64,			float64)

// RTS
FEEDOS_DEF_TAG	(16270,		MARKET_RTS_TradeStatusSellSide,				uint32,				uint32)
FEEDOS_DEF_TAG	(16271,		MARKET_RTS_TradeStatusBuySide,				uint32,				uint32)

// CHIX
FEEDOS_DEF_TAG	(16300,		MARKET_CHIX_ExecutionType,	                std::string,		String)

// JSE MIT
FEEDOS_DEF_TAG	(16320,		MARKET_JSE_MIT_AuctionTypeIndicator,		char,		char)

// MILAN MIT
FEEDOS_DEF_TAG	(16350,		MARKET_MILAN_MIT_AuctionTypeIndicator,		char,		char)

// BPOD
FEEDOS_DEF_TAG	(16370,		MARKET_BPOD_PreviousBidPrice,				FOSPrice,			float64) // deprecated
FEEDOS_DEF_TAG	(16371,		MARKET_BPOD_PreviousAskPrice,				FOSPrice,			float64) // deprecated

// OPRA
FEEDOS_DEF_TAG	(16380,		MARKET_OPRA_QuodCondition,					char,				char)
FEEDOS_DEF_TAG	(16381,		MARKET_OPRA_TradeCondition,					char,				char)

// CMA
FEEDOS_DEF_TAG	(16280,		MARKET_CMA_QuoteType,						uint16,				uint16)
FEEDOS_DEF_TAG	(16281,		MARKET_CMA_QuoteStatus,						uint16,				uint16)

// MONTREAL
FEEDOS_DEF_TAG	(16290,		MARKET_MONTREAL_TradeCondition,				char,				char)

// TSE
FEEDOS_DEF_TAG	(16390,		MARKET_TSE_BidQuoteCondition,				char,				char)
FEEDOS_DEF_TAG	(16391,		MARKET_TSE_AskQuoteCondition,				char,				char)
FEEDOS_DEF_TAG	(16392,		MARKET_TSE_TostnetPriceCode,				uint8,				uint8)
FEEDOS_DEF_TAG	(16393,		MARKET_TSE_TostnetTransactionFlag,			char,				char)

// TOCOM
FEEDOS_DEF_TAG	(16400,		MARKET_TOCOM_TradeCondition,				uint16,				uint16) // Trade condition as it comes from the exchange
FEEDOS_DEF_TAG	(16401,		MARKET_TOCOM_TradeSource,					uint16,				uint16) // Deal source as it comes from the exchange

// ULTRAFEED
FEEDOS_DEF_TAG	(16410,		MARKET_ULTRAFEED_QuoteCondition,			uint8,				uint8)

// OMX
FEEDOS_DEF_TAG	(16420,		MARKET_OMX_TradeCondition,					uint8,				uint8) // trade condition as it comes from the exchange. List of values are integer [0-99]
FEEDOS_DEF_TAG	(16421,		MARKET_OMX_TradeSource,						uint16,				uint16) // deal source as it comes from the exchange. List of values are integers [1-999]

// SET
FEEDOS_DEF_TAG	(16422,		MARKET_SET_MatchType,						std::string,		String) // deal source as it comes from the exchange. Should be a string as several values are a string of 2 chars. (example AQ, S1, M6, ...)
