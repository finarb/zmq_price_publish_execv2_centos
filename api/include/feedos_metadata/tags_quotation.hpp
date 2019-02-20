
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

// FIX fields
FEEDOS_DEF_TAG			(342,		TradSesOpenTime			,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(631,		MidPrice				,		float64,		float64)
FEEDOS_DEF_TAG			(731,		SettlPriceType			,		unsigned int,	uint8)
FEEDOS_DEF_TAG			(811,		PriceDelta				,		float64,		float64)
FEEDOS_DEF_TAG			(1148,		LowLimitPrice			,		float64,		float64)
FEEDOS_DEF_TAG			(1149,		HighLimitPrice			,		float64,		float64)

// "instant" values
FEEDOS_DEF_TAG			(9100,		TradingStatus				,		Types::FIXSecurityTradingStatus,	Enum)
FEEDOS_DEF_TAG			(9102,		OrderEntryStatus			,		uint8,			uint8) // BitField indicating the order entry capabilities in the current market state. Bit '0': Order Entry Disabled, Bit '1': Order Modify Disabled, Bit '2': Order Cancel Disabled
FEEDOS_DEF_TAG			(9101,		TradingSessionId			,		Types::FOSTradingSessionId,			int8)
FEEDOS_DEF_TAG			(9106,		LastPrice					,		float64,		float64)
FEEDOS_DEF_TAG			(9107,		LastTradeQty				,		float64,		float64)
FEEDOS_DEF_TAG			(9108,		LastTradeTimestamp			,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9109,		LastTradePrice				,		float64,		float64)
FEEDOS_DEF_TAG			(9110,		LastOffBookTradePrice		,		float64,		float64)
FEEDOS_DEF_TAG			(9111,		LastOffBookTradeQty			,		float64,		float64)
FEEDOS_DEF_TAG			(9112,		LastOffBookTradeTimestamp	,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9113,		RegSHOAction				,		Types::FOSRegSHOAction,	Enum)
FEEDOS_DEF_TAG			(9140,		VarClose					,		float64,		float64)
FEEDOS_DEF_TAG			(9141,		VarClosePct					,		float64,		float64)

// "session" values
FEEDOS_DEF_TAG			(9121,		SessionOpeningPrice		,		float64,		float64)
FEEDOS_DEF_TAG			(9124,		SessionHighPrice		,		float64,		float64)
FEEDOS_DEF_TAG			(9125,		SessionLowPrice			,		float64,		float64)
FEEDOS_DEF_TAG			(9126,		SessionVWAPPrice		,		float64,		float64)
FEEDOS_DEF_TAG			(9120,		SessionTotalVolumeTraded,		float64,		float64)
FEEDOS_DEF_TAG			(9127,		SessionTotalAssetTraded,		float64,		float64)
FEEDOS_DEF_TAG			(9123,		PreviousSessionSettlementPrice,	float64,		float64) // #35767: deprecated
FEEDOS_DEF_TAG			(9122,		PreviousSessionClosingPrice,	float64,		float64)
FEEDOS_DEF_TAG			(9114,		SessionTotalOffBookAssetTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9115,		SessionTotalOffBookVolumeTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9116,		PriorSessionsTotalAssetTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9117,		PriorSessionsTotalVolumeTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9118,		PriorSessionsTotalOffBookAssetTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9119,		PriorSessionsTotalOffBookVolumeTraded,	float64,		float64)
FEEDOS_DEF_TAG			(9128,		SessionClosingPrice,	float64,		float64)

// "daily" values
FEEDOS_DEF_TAG			(9131,		DailyOpeningPrice				,		float64,		float64)
FEEDOS_DEF_TAG			(9132,		DailyClosingPrice				,		float64,		float64)
FEEDOS_DEF_TAG			(9133,		DailySettlementPrice			,		float64,		float64)
FEEDOS_DEF_TAG			(9134,		DailyHighPrice					,		float64,		float64)
FEEDOS_DEF_TAG			(9135,		DailyLowPrice					,		float64,		float64)
FEEDOS_DEF_TAG			(9130,		DailyTotalVolumeTraded			,		float64,		float64)
FEEDOS_DEF_TAG			(9136,		DailyTotalAssetTraded			,		float64,		float64)
FEEDOS_DEF_TAG			(9137,		PreviousDailyTotalVolumeTraded	,		float64,		float64)
FEEDOS_DEF_TAG			(9138,		PreviousDailyTotalAssetTraded	,		float64,		float64)
FEEDOS_DEF_TAG			(9142,		PreviousDailyClosingPrice		,		float64,		float64)
FEEDOS_DEF_TAG			(9143,		PreviousBusinessDay				,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9144,		CurrentBusinessDay				,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9145,		PreviousDailySettlementPrice	,		float64,		float64)
FEEDOS_DEF_TAG			(9148,		DailyTotalOffBookVolumeTraded 	,		float64,		float64)
FEEDOS_DEF_TAG			(9149,		DailyTotalOffBookAssetTraded	,		float64,		float64)
FEEDOS_DEF_TAG			(9154,		AverageDailyTotalVolumeTraded	,		float64,		float64)
FEEDOS_DEF_TAG			(9155,		InternalDailyClosingPriceType	,		char,			char)
FEEDOS_DEF_TAG			(9156,		PreviousInternalDailyClosingPriceType	,		char,			char)

// "other" values
FEEDOS_DEF_TAG			(9150,		OpenInterest					,		float64,		float64)
FEEDOS_DEF_TAG			(9146,		LastAuctionPrice				,		float64,		float64)
FEEDOS_DEF_TAG			(9147,		LastAuctionVolume				,		float64,		float64)
FEEDOS_DEF_TAG			(9183,		LastAuctionVolumeTraded			,		float64,		float64) // #37970: The aggregated volume of the last auction phase.
FEEDOS_DEF_TAG			(9151,		LastAuctionImbalanceSide		,		Types::ImbalanceSide,	char)
FEEDOS_DEF_TAG			(9157,		QH_LastAuctionImbalanceSide		,		Types::ImbalanceSide,	char) // #35746: Computed market side of the order imbalance
FEEDOS_DEF_TAG			(9152,		LastAuctionImbalanceVolume		,		float64,		float64)
FEEDOS_DEF_TAG			(9158,		QH_LastAuctionImbalanceVolume		,	float64,		float64) // #35746: Computed number of shares not paired at the Current Reference Price
FEEDOS_DEF_TAG			(9184,		AuctionOnDemand_Price		,			float64,		float64) // #37970: Indicative price for the matching of the Auction On Demand
FEEDOS_DEF_TAG			(9185,		AuctionOnDemand_Volume		,			float64,		float64) // #37970: Indicative volume for the matching of the Auction On Demand
FEEDOS_DEF_TAG			(9186,		AuctionOnDemand_Imbalance_Volume,		float64,		float64) // #41664: Theoretical unmatched volume after the auction on Demand fixing
FEEDOS_DEF_TAG			(9187,		AuctionOnDemand_Imbalance_Side	,		Types::ImbalanceSide,	char) // #41664: Side of the theoretical unmatched volume after the auction on Demand fixing

FEEDOS_DEF_TAG			(9153,		PriceVega						,		float64,		float64)

FEEDOS_DEF_TAG			(9160,		AveragePriceDaytoDayChange,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9161,		AveragePriceSimpleYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9162,		AveragePriceCompoundYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9163,		HighestPriceDaytoDayChange,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9164,		HighestPriceSimpleYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9165,		HighestPriceCompoundYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9166,		LowestPriceDaytoDayChange,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9167,		LowestPriceSimpleYield,						FOSPrice,		float64)
FEEDOS_DEF_TAG			(9168,		LowestPriceCompoundYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9169,		MedianPrice,								FOSPrice,		float64)
FEEDOS_DEF_TAG			(9170,		MedianPriceDaytoDayChange,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9171,		MedianPriceSimpleYield,						FOSPrice,		float64)
FEEDOS_DEF_TAG			(9172,		MedianPriceCompoundYield,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9173,		NumberOfReportingCompanies,					int,			int32)

FEEDOS_DEF_TAG			(9174,		DailyHighBidPrice,							float64,		float64)
FEEDOS_DEF_TAG			(9175,		DailyLowBidPrice,							float64,		float64)
FEEDOS_DEF_TAG			(9176,		DailyHighAskPrice,							float64,		float64)
FEEDOS_DEF_TAG			(9177,		DailyLowAskPrice,							float64,		float64)
FEEDOS_DEF_TAG			(9178,		DailyHighMidPrice,							float64,		float64)
FEEDOS_DEF_TAG			(9179,		DailyLowMidPrice,							float64,		float64)

FEEDOS_DEF_TAG			(9180,		DailyNumberOfBlockTrades,					unsigned int,	uint32)
FEEDOS_DEF_TAG			(9181,		DailyTotalBlockVolumeTraded,				float64,		float64)
FEEDOS_DEF_TAG			(9182,		MarketTradingStatusCode,		Types::FOSDictionaryEntryId,uint32)

// internal stuff
FEEDOS_DEF_TAG			(9300,		InternalDailyOpenTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9301,		InternalDailyCloseTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9302,		InternalDailyHighTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9303,		InternalDailyLowTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9304,		InternalPriceActivityTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9305,		InternalLastAuctionTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9310,		InternalDailyBusinessDayTimestamp,	Timestamp,	Timestamp)

FEEDOS_DEF_TAG			(9306,		InternalCrossIndicator,				bool,			bool)

FEEDOS_DEF_TAG			(9307,		InternalBestBidNbOrders,			int,			int32)
FEEDOS_DEF_TAG			(9308,		InternalBestAskNbOrders,			int,			int32)

FEEDOS_DEF_TAG			(9309,		PriceActivityMarketTimestamp,		Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9200,		52WeekHighPrice,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9201,		52WeekHighPriceTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9202,		52WeekLowPrice,						FOSPrice,		float64)
FEEDOS_DEF_TAG			(9203,		52WeekLowPriceTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9204,		YearToDateHighPrice,				FOSPrice,		float64)
FEEDOS_DEF_TAG			(9205,		YearToDateHighPriceTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9206,		YearToDateLowPrice,					FOSPrice,		float64)
FEEDOS_DEF_TAG			(9207,		YearToDateLowPriceTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9208,		DailyNumberOfTrades,				FOSInteger,		uint32)
FEEDOS_DEF_TAG			(9209,		PreviousDailyHighPrice,				FOSPrice,		float64)
FEEDOS_DEF_TAG			(9210,		PreviousDailyLowPrice,				FOSPrice,		float64)

FEEDOS_DEF_TAG			(9211,		PreviousValidBidPrice,				FOSPrice,		float64)
FEEDOS_DEF_TAG			(9212,		PreviousValidBidTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9213,		PreviousValidAskPrice,				FOSPrice,		float64)
FEEDOS_DEF_TAG			(9214,		PreviousValidAskTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9215,		DailyClosingBidPrice,				FOSPrice,		float64)
FEEDOS_DEF_TAG			(9216,		DailyClosingAskPrice,				FOSPrice,		float64)

FEEDOS_DEF_TAG			(9220,		ReportingType,					std::string,	String)
FEEDOS_DEF_TAG			(9221,		NetAssetValuePrice,				float64,		float64)
FEEDOS_DEF_TAG			(9222,		TotalNetAssets,					float64,		float64)
FEEDOS_DEF_TAG			(9223,		WrapPrice,						float64,		float64)
FEEDOS_DEF_TAG			(9224,		EstimatedLongTimeReturn,		float64,		float64)
FEEDOS_DEF_TAG			(9225,		DailyDividend,					float64,		float64)
FEEDOS_DEF_TAG			(9226,		DailyDividendIndicator,			char,			char)
FEEDOS_DEF_TAG			(9227,		Footnotes,						std::string,	String)
FEEDOS_DEF_TAG			(9228,		AccruedInterest,				float64,		float64)
FEEDOS_DEF_TAG			(9229,		EntryTimestamp,					Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9230,		AvgMaturityDays,				uint16,			uint16) // in days
FEEDOS_DEF_TAG			(9231,		AvgLifeDays,					uint16,			uint16) // in days

FEEDOS_DEF_TAG			(9232,		YieldSevenDayGross,				float64,		float64)
FEEDOS_DEF_TAG			(9233,		YieldSevenDaySubsidized,		float64,		float64)
FEEDOS_DEF_TAG			(9234,		YieldSevenDayAnnualized,		float64,		float64)
FEEDOS_DEF_TAG			(9235,		YieldThirtyDay,					float64,		float64)
FEEDOS_DEF_TAG			(9236,		YieldThirtyDayTimestamp,		Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9237,		CorporateActionType,			char,			char)
FEEDOS_DEF_TAG			(9238,		ShortTermGain,					float64,		float64)
FEEDOS_DEF_TAG			(9239,		LongTermGain,					float64,		float64)
FEEDOS_DEF_TAG			(9240,		UnallocatedDistribution,		float64,		float64)
FEEDOS_DEF_TAG			(9241,		ReturnOnCapital,				float64,		float64)
FEEDOS_DEF_TAG			(9242,		ExDistributionTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9243,		RecordTimestamp,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9244,		PaymentTimestamp,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9245,		ReinvestTimestamp,				Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9246,		DistributionType,				char,			char)
FEEDOS_DEF_TAG			(9247,		TotalCashDistribution,			float64,		float64)
FEEDOS_DEF_TAG			(9248,		NonQualifiedCashDistribution,	float64,		float64)
FEEDOS_DEF_TAG			(9249,		QualifiedCashDistribution,		float64,		float64)
FEEDOS_DEF_TAG			(9250,		TaxFreeCashDistribution,		float64,		float64)
FEEDOS_DEF_TAG			(9252,		OrdinaryForeignTaxCredit,		float64,		float64)
FEEDOS_DEF_TAG			(9253,		QualifiedForeignTaxCredit,		float64,		float64)
FEEDOS_DEF_TAG			(9254,		LastYield,						float64,		float64)

FEEDOS_DEF_TAG			(9255,		LimitUpLimitDownIndicator,		char,			char)
FEEDOS_DEF_TAG			(9256,		MinimumNumberOfReportingCompaniesFlag,	bool,	bool)
FEEDOS_DEF_TAG			(9257,		StockDividend,					float64,		float64)

FEEDOS_DEF_TAG			(9258,		CancelledOrModifiedTradePrice,					float64,		float64)
FEEDOS_DEF_TAG			(9259,		CancelledOrModifiedTradeQuantity,				float64,		float64)

FEEDOS_DEF_TAG			(9364,		RetailPriceImprovement,						char,			char)
FEEDOS_DEF_TAG			(9366,		DailyClosingBidTimestamp,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9367,		DailyClosingAskTimestamp,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9368,		AdjustedDailyClosingPrice,		float64,		float64)
FEEDOS_DEF_TAG			(9369,		PreviousAdjustedDailyClosingPrice,	float64,	float64)

FEEDOS_DEF_TAG			(9370,		TradingReferencePrice,			float64,		float64)
FEEDOS_DEF_TAG			(9371,		ExchangeLastComputedPrice,		float64,		float64)
FEEDOS_DEF_TAG			(9267,		ExchangeIndicativeBuyPrice,		float64,		float64) // #37970: Computed and Indicative price provided by exchange for Buy Side of an instrument for Mifid II pre-trade transparency
FEEDOS_DEF_TAG			(9268,		ExchangeIndicativeSellPrice,		float64,		float64) // #37970: Computed and Indicative price provided by exchange for Sell Side of an instrument for Mifid II pre-trade transparency
FEEDOS_DEF_TAG			(9270,		ExchangeIndicativeBuyVolume,		float64,		float64) // #39432: Volume linked to ExchangeIndicativeBuyPrice provided by exchange for Buy Side of an instrument for Mifid II pre-trade transparency
FEEDOS_DEF_TAG			(9271,		ExchangeIndicativeSellVolume,		float64,		float64) // #39432: Volume linked to ExchangeIndicativeBuyPrice provided by exchange for Buy Side of an instrument for Mifid II pre-trade transparency

FEEDOS_DEF_TAG			(9373,		UnadjustedDailyClosingPrice,		float64,		float64)
FEEDOS_DEF_TAG			(9374,		PreviousUnadjustedDailyClosingPrice,	float64,	float64)

FEEDOS_DEF_TAG			(9377,		EstimatedCashPerUnitCreation,		float64,		float64) // This field represents the estimated amount of cash needed to create a fund unit
FEEDOS_DEF_TAG			(9378,		TotalCashPerUnitCreation,			float64,		float64) // This field represents the total amount of cash needed to create a fund unit
FEEDOS_DEF_TAG			(9379,		ImpliedVolatility,					float64,		float64)

FEEDOS_DEF_TAG			(9380,		SettlementPriceDate,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9381,		PreviousSettlementPriceDate,		Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9382,		OpenInterestDate,					Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9383,		SettlementPriceType,				char,			char)
FEEDOS_DEF_TAG			(9384,		PreviousSettlementPriceType,		char,			char)

FEEDOS_DEF_TAG			(9385,		LastEligibleTradePrice,				float64,		float64)
FEEDOS_DEF_TAG			(9386,		LastEligibleTradeQty,				float64,		float64)
FEEDOS_DEF_TAG			(9387,		LastEligibleTradeTimestamp,			Timestamp,		Timestamp)

FEEDOS_DEF_TAG			(9388,		DailyOpeningPriceTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9389,		DailyClosingPriceTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9390,		DailyHighPriceTimestamp,			Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9391,		DailyLowPriceTimestamp,				Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9392,		PreviousDailyClosingPriceTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9393,		InternalDailyVWAP,					float64,		float64)

FEEDOS_DEF_TAG			(9394,		MARKET_TradingStatus,				Types::FOSDictionaryEntryId,	uint32) // Generic Tag to provide the raw Market Trading Status information at the instrument level
FEEDOS_DEF_TAG			(9395,		MARKET_HaltReason,					unsigned int,	uint32) // Halt reason for the instrument. This tag contains the market value without interpretation
FEEDOS_DEF_TAG			(9396,		StaticTradingReferencePrice,		FOSPrice,		float64) // During the opening auction, the static reference price is the last traded price (usually the previous day’s closing price, adjusted if necessary to account for coupon payment) or the last indicative price disseminated.
FEEDOS_DEF_TAG			(9260,		MARKET_GroupTradingStatus,			Types::FOSDictionaryEntryId,	uint32) // Generic Tag to provide the raw Market TradingStatus information at the group, segment or market level
FEEDOS_DEF_TAG			(9269,		MarketCondition,				 uint8,			uint8) // 39320: Normalized tag defining the market condition declared by a trading venue, according to MiFID II / RTS 8 requirement.

FEEDOS_DEF_TAG			(9262,		PreviousOpenInterest,				float64,		float64) // Previous trading day's Open Interest. Persisting previous day's Open Interest allows us to catch data corrections published by the exchange after the start of a new session.
FEEDOS_DEF_TAG			(9263,		PreviousOpenInterestDate,			Timestamp,		Timestamp) // The date PreviousOpenInterest is effective for.

FEEDOS_DEF_TAG			(9264,		SessionNumberOfTrades,				FOSInteger,		uint32) // Number of on-book transactions on an instrument.
FEEDOS_DEF_TAG			(9265,		HasContinuationFlag,				bool,			bool) // Set by InstrumentMBLData to TRUE when processing a DeltaRefresh with ContinuationFlag set.
FEEDOS_DEF_TAG			(9266,		NationalConsolidatedVolume,			float64,		float64)

FEEDOS_DEF_TAG			(9397,		Consolidation_LastEvent,			uint8,			uint8)
FEEDOS_DEF_TAG			(9398,		Consolidation_LastEventTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_TAG			(9399,		Consolidation_LastEventLeg,			FOSLowLevelInstrumentCode,	uint32)
FEEDOS_DEF_TAG_LIST		(10000,		LegConsolidationStatus,				uint8,			uint8,	100)

////////////////////////////
// USER-specific fields (59000..59999)
////////////////////////////
FEEDOS_DEF_TAG_LIST		(59000,	QUOT_USER,							float64,		float64,	1000)



////////////////////////////
// MARKET-specific fields
////////////////////////////


// SWX
FEEDOS_DEF_TAG			(14452,		MARKET_SWX_BookCondition,					int,			int32)
FEEDOS_DEF_TAG			(14453,		MARKET_SWX_SecurityTradingStatus,			int,			int32)
FEEDOS_DEF_TAG			(14454,		MARKET_SWX_TradingSessionSubID,				std::string,	String)

// BOVESPA
FEEDOS_DEF_TAG			(14470,		MARKET_BOVESPA_SecurityTradingStatus,		std::string,	String)

// XETRA ULTRA PLUS
FEEDOS_DEF_TAG			(14480,		MARKET_XETRA_ULTRA_PLUS_InstrumentStatus,	float64,		float64)

// ICE
FEEDOS_DEF_TAG			(14500,		MARKET_ICE_BlockVolume,						float64,		float64)
FEEDOS_DEF_TAG			(14501,		MARKET_ICE_EFSVolume,						float64,		float64)
FEEDOS_DEF_TAG			(14502,		MARKET_ICE_EFPVolume,						float64,		float64)
FEEDOS_DEF_TAG			(14503,		MARKET_ICE_IntervalPriceLimitsOnHold,		bool,			bool)

// Euronext UTP
FEEDOS_DEF_TAG			(14550,		MARKET_EURONEXT_HaltReason,					std::string,	String)
FEEDOS_DEF_TAG			(14551,		MARKET_EURONEXT_ClassState,					std::string,	String)
FEEDOS_DEF_TAG			(14552,		MARKET_EURONEXT_OrderEntryRejection,		char,			char) // Indicates whether order entry is allowed or forbidden. Valid values are:'N' : Order entry allowed, 'Y' : Order entry forbidden
FEEDOS_DEF_TAG			(14553,		MARKET_EURONEXT_InstrumentState,			char,			char) // Indicates the state of the instrument. Valid values are: '0' - Not applicable , 'A' - Auction , 'H' - Halted , Null (or space) - Inherited (following the state of the class the instrument belongs to)
FEEDOS_DEF_TAG			(14554,		MARKET_EURONEXT_PhaseQualifier,				int,			int32) // Indicates the trading mode. Valid values are: '0' - Call BBO Only, '1' - Trading At Last, '2' - Random uncrossing, '3' - Suspended, '4' - Wholesale allowed
FEEDOS_DEF_TAG			(14555,		MARKET_EURONEXT_OrderPriority,				int64,			int64) // #35836: Rank giving the priority of the order. The order with the lowest value of Order Priority has the highest priority. /!\ This is encoded as int64 whereas the market is using uint64. As this is epoch in nanosecond, this is sufficient for thenext 300+ years, but usage may change in the future.
FEEDOS_DEF_TAG			(14556,		MARKET_EURONEXT_TradingPeriod,				uint8,			uint8) // #37076: Provides the current trading period. Possible values: 1 = Opening (Cash and Derivatives) / 2 = Standard (Cash and Derivatives) / 3 = Closing (Cash and Derivatives)
FEEDOS_DEF_TAG			(14557,		MARKET_EURONEXT_StatusReason,				uint8,			uint8) // #41453: Provides the reason for Instrument State changes on Euronext

// OMX SAXESS
FEEDOS_DEF_TAG			(14590,		MARKET_OMX_SAXESS_OrderbookState,			std::string,	String)
FEEDOS_DEF_TAG			(14591,		MARKET_OMX_SAXESS_OrderbookStopCode,		std::string,	String)
FEEDOS_DEF_TAG			(14592,		MARKET_OMX_SAXESS_InstrumentStopCode,		std::string,	String)
FEEDOS_DEF_TAG			(14593,		MARKET_OMX_SAXESS_SubmarketStopCode,		std::string,	String)

// OMX NORDIC
FEEDOS_DEF_TAG			(14594,		MARKET_OMX_NORDIC_MarketSegmentState,		std::string,	String)
FEEDOS_DEF_TAG			(14595,		MARKET_OMX_NORDIC_OrderBookTradingState,	std::string,	String)
FEEDOS_DEF_TAG			(14596,		MARKET_OMX_NORDIC_OrderBookHaltReason,		std::string,	String)
FEEDOS_DEF_TAG			(14597,		MARKET_OMX_NORDIC_NoteCodes1,				int,			int32) // this tag contains a concatenation of the 4 market bitfields (4 bitfields with values from 0 to 128 for each bitfield). Bitfields 1 to 4
FEEDOS_DEF_TAG			(14598,		MARKET_OMX_NORDIC_NoteCodes2,				int,			int32) // this tag contains a concatenation of the 4 market bitfields (4 bitfields with values from 0 to 128 for each bitfield). Bitfields 5 to 8

// LSE
FEEDOS_DEF_TAG			(14600,		MARKET_LSE_PeriodName,						std::string,	String) // #37701: deprecated
FEEDOS_DEF_TAG			(14601,		MARKET_LSE_PeriodStatus,					std::string,	String) // #37701: deprecated
FEEDOS_DEF_TAG			(14602,		MARKET_LSE_SuspendedIndicator,				std::string,	String) // #37701: deprecated
FEEDOS_DEF_TAG			(14603,		MARKET_LSE_HaltReason,						std::string,	String) // #37701: deprecated
FEEDOS_DEF_TAG			(14604,		MARKET_LSE_OffBookReportingTradingStatus,	std::string,	String) // #37701: deprecated

// LIFFE
FEEDOS_DEF_TAG			(14650,		MARKET_LIFFE_MarketMode,					std::string,	String)
FEEDOS_DEF_TAG			(14651,		MARKET_LIFFE_MarketStatuses,				unsigned int,	uint32)

// ADH
FEEDOS_DEF_TAG			(14700,		MARKET_ADH_OrderbookStateCode,				std::string,	String)

// TURQUOISE MIT
FEEDOS_DEF_TAG			(14720,		MARKET_TURQUOISE_HaltReason,					std::string,	String)
FEEDOS_DEF_TAG			(14721,		MARKET_TURQUOISE_DarkBookTradingStatus,			Types::FIXSecurityTradingStatus,	Enum)
FEEDOS_DEF_TAG			(14722,		MARKET_TURQUOISE_OffBookReportingTradingStatus,	Types::FIXSecurityTradingStatus,	Enum)

// CME
FEEDOS_DEF_TAG			(14740,		MARKET_CME_PreliminarySettlementPrice,			float64,		float64) // #35767: deprecated

// LSE_MIT
FEEDOS_DEF_TAG			(14750, MARKET_LSE_MIT_TradingStatusDetails,		std::string, String) // #37701: deprecated
FEEDOS_DEF_TAG			(14752, MARKET_LSE_MIT_HaltReason,					std::string, String) // #37701: deprecated
#if 0
	(14753, MARKET_LSE_MIT_OffBookReportingHaltReason,			std::string, String)
	(14751, MARKET_LSE_MIT_OffBookReportingTradingStatus,		Types::FIXSecurityTradingStatus, Enum)
	(14754, MARKET_LSE_MIT_OffBookReportingTradingStatusDetails, std::string, String)
#endif
FEEDOS_DEF_TAG			(14756, 	MARKET_LSE_MIT_TotalAuctionVolume,					float64, float64)

//OSE_OMX
FEEDOS_DEF_TAG			(14755, MARKET_OSE_TradingStateName,	std::string,    String)

// NASDAQ
FEEDOS_DEF_TAG			(14770,		MARKET_NASDAQ_TradingActionReason,		std::string,	String)
FEEDOS_DEF_TAG			(14771,		MARKET_NASDAQ_FarPrice,					float64,		float64)
FEEDOS_DEF_TAG			(14772,		MARKET_NASDAQ_NearPrice,				float64,		float64)

// NYSE
FEEDOS_DEF_TAG			(14790,		MARKET_NYSE_TradeCond,								std::string,	String)
FEEDOS_DEF_TAG			(14791,		MARKET_NYSE_SecurityStatus,						char,					char)
FEEDOS_DEF_TAG			(14792,		MARKET_NYSE_HaltCondition,						char,					char)

// OMNET_OMX
FEEDOS_DEF_TAG			(14800,		MARKET_OMNET_OMX_TradingStateName,				std::string,			String)

// BATS
FEEDOS_DEF_TAG			(14850,		MARKET_BATS_AuctionType,						char,					char)

// BPOD
FEEDOS_DEF_TAG			(14870,		MARKET_BPOD_SubscriptionErrorCode,				uint8,			uint8)

// CEF
FEEDOS_DEF_TAG			(14900,		MARKET_CEF_LastTradeTradingPhase,				char,					char)

// BME
FEEDOS_DEF_TAG			(14920, 	MARKET_BME_DynamicVariationRange,			float64,		float64)
FEEDOS_DEF_TAG			(14921, 	MARKET_BME_StaticVariationRange,			float64,		float64)
FEEDOS_DEF_TAG			(14922,		MARKET_BME_HaltReason,						uint8,			uint8)

// Affari MIT
FEEDOS_DEF_TAG			(14950,		MARKET_MILAN_MIT_TradingStatusDetails,			char,					char)

// PINKSHEET
// the following two tags should be context tags but are defined here since it is a low liquidity market
FEEDOS_DEF_TAG			(14960,		MARKET_PINKSHEET_QuoteFlags,					uint16,					uint16)
FEEDOS_DEF_TAG			(14961,		MARKET_PINKSHEET_QuoteCondition,				char,					char)

// JSE MIT
FEEDOS_DEF_TAG			(14970,		MARKET_JSE_MIT_TradingStatusDetails,			char,					char)

// BPIPE
FEEDOS_DEF_TAG			(14980,		MARKET_BPIPE_PreviousBidPrice,				FOSPrice,			float64)
FEEDOS_DEF_TAG			(14981,		MARKET_BPIPE_PreviousAskPrice,				FOSPrice,			float64)

// MFDS
FEEDOS_DEF_TAG			(14990,		MARKET_MFDS_Flags,							uint16,				uint16)
FEEDOS_DEF_TAG			(14991,		MARKET_MFDS_CapitalDistributionFlags,		uint16,				uint16)
FEEDOS_DEF_TAG			(14992,		MARKET_MFDS_DividendInterestFlags,			uint16,				uint16)

// HK
FEEDOS_DEF_TAG			(15010,		MARKET_HK_TradingState,						std::string,		String) // #37959: deprecated
FEEDOS_DEF_TAG			(15011,		MARKET_HK_ShortSellSharesTraded,			float64,			float64)
FEEDOS_DEF_TAG			(15012,		MARKET_HK_ShortSellTurnover,				float64,			float64)
FEEDOS_DEF_TAG			(15013,		MARKET_HK_CoolingOffStartTime,				Timestamp,			Timestamp) // Time when the cooling off period starts
FEEDOS_DEF_TAG			(15014,		MARKET_HK_CoolingOffEndTime,				Timestamp,			Timestamp) // Time when the cooling off period ends
FEEDOS_DEF_TAG			(15015,		MARKET_HK_DailyQuotaBalance,				float64,			float64)
FEEDOS_DEF_TAG			(15016,		MARKET_HK_BuyTurnover,						float64,			float64)
FEEDOS_DEF_TAG			(15017,		MARKET_HK_SellTurnover,						float64,			float64)
FEEDOS_DEF_TAG			(15018,		MARKET_HK_BuySellTurnover,					float64,			float64)
FEEDOS_DEF_TAG			(15019,		MARKET_HK_NominalPrice,					float64,			float64) // #37459: Reference price used to define the limitations and characteristics of the trading.

// QUANTUM
FEEDOS_DEF_TAG			(15020,		MARKET_QUANTUM_StockState,					std::string,		String) // #37641: deprecated
FEEDOS_DEF_TAG			(15021,		MARKET_QUANTUM_GroupStatus,					char,				char) // #37641: deprecated

// JSDA
FEEDOS_DEF_TAG			(15030,		MARKET_JSDA_PrefixSequenceNumber,			std::string,		String)
FEEDOS_DEF_TAG			(15031,		MARKET_JSDA_DataType,						std::string,		String)

// NGM
FEEDOS_DEF_TAG			(15040,		MARKET_NGM_KnockOutBuyback,					char,				char) // #32841: deprecated
FEEDOS_DEF_TAG			(15041,		MARKET_NGM_FinancialStatus,					std::string,		String)

// TSE
FEEDOS_DEF_TAG			(15060,		MARKET_TSE_BidMarketOrderVolume,			float64,			float64) // total volume of bid market orders
FEEDOS_DEF_TAG			(15061,		MARKET_TSE_AskMarketOrderVolume,			float64,			float64) // total volume of bid market orders
FEEDOS_DEF_TAG			(15062,		MARKET_TSE_BidSpecialQuotePrice,			float64,			float64)
FEEDOS_DEF_TAG			(15063,		MARKET_TSE_AskSpecialQuotePrice,			float64,			float64)

// MICEX
FEEDOS_DEF_TAG			(15070,		MARKET_MICEX_SecurityTradingStatus,			uint16,				uint16) // TradingStatus as it comes from the exchange.

// ULTRAFEED
FEEDOS_DEF_TAG			(15080,		MARKET_ULTRAFEED_CorporateActionReportType,	uint8,				uint8)

// Korean Equities
FEEDOS_DEF_TAG			(15090,		MARKET_KOR_LiquidityProviderHoldedQuantity,	float64,			float64) // #37772: Volume of accounts held by the liquidity provider
