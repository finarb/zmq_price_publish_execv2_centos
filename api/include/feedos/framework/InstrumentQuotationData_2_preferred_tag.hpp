/**		**/
/**		**/
/**     **/

// syntax: Enum

//FEEDOS_DEF_PREF_TAG(0,9100,		TradingStatus			,		Types::FIXSecurityTradingStatus,	Enum)


// syntax: float64
FEEDOS_DEF_PREF_TAG	(0, 9106,		LastPrice						,		float64,		float64)
FEEDOS_DEF_PREF_TAG (1, 9107,		LastTradeQty					,		float64,		float64)
FEEDOS_DEF_PREF_TAG (2, 9134,		DailyHighPrice					,		float64,		float64)
FEEDOS_DEF_PREF_TAG (3, 9135,		DailyLowPrice					,		float64,		float64)
FEEDOS_DEF_PREF_TAG (4, 9130,		DailyTotalVolumeTraded			,		float64,		float64)
FEEDOS_DEF_PREF_TAG (5, 9136,		DailyTotalAssetTraded			,		float64,		float64) 
FEEDOS_DEF_PREF_TAG	(6, 9109,		LastTradePrice					,		float64,		float64)
FEEDOS_DEF_PREF_TAG_MAX (7, float64)

// syntax: timestamp
FEEDOS_DEF_PREF_TAG (0, 9108,		LastTradeTimestamp		,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (1, 9300,		InternalDailyOpenTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (2, 9301,		InternalDailyCloseTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (3, 9302,		InternalDailyHighTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (4, 9303,		InternalDailyLowTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (5, 9304,		InternalPriceActivityTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG (6, 9309,		PriceActivityMarketTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG_MAX (7, Timestamp)


/**
// "instant" values

FEEDOS_DEF_PREF_TAG			(0, 9106,		LastPrice				,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(1, 9107,		LastTradeQty			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(2, 9121,		SessionOpeningPrice		,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(3, 9124,		SessionHighPrice		,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(4, 9125,		SessionLowPrice			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(5, 9126,		SessionVWAPPrice		,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(6, 9120,		SessionTotalVolumeTraded,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(7, 9127,		SessionTotalAssetTraded,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(8, 9122,		PreviousSessionClosingPrice,	float64,		float64)

// "daily" values
FEEDOS_DEF_PREF_TAG			(9, 9131,		DailyOpeningPrice				,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(10, 9132,		DailyClosingPrice				,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(11, 9133,		DailySettlementPrice			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(12, 9134,		DailyHighPrice					,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(13, 9135,		DailyLowPrice					,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(14, 9130,		DailyTotalVolumeTraded			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(15, 9136,		DailyTotalAssetTraded			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(16, 9137,		PreviousDailyTotalVolumeTraded	,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(17, 9138,		PreviousDailyTotalAssetTraded	,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(18, 9142,		PreviousDailyClosingPrice		,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(19, 9145,		PreviousDailySettlementPrice	,		float64,		float64)

// "other" values
FEEDOS_DEF_PREF_TAG			(20, 9150,		OpenInterest			,		float64,		float64)
FEEDOS_DEF_PREF_TAG			(21, 9151,		PriceIncrement_dynamic	,		float64,		float64)
FEEDOS_DEF_PREF_TAG_MAX (22, float64)

//internal stuff
FEEDOS_DEF_PREF_TAG			(0, 9300,		InternalDailyOpenTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(1, 9301,		InternalDailyCloseTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(2, 9302,		InternalDailyHighTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(3, 9303,		InternalDailyLowTimestamp,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(4, 9304,		InternalPriceActivityTimestamp,	Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(5, 9108,		LastTradeTimestamp		,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(6, 9143,		PreviousBusinessDay				,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG			(7, 9144,		CurrentBusinessDay				,		Timestamp,		Timestamp)
FEEDOS_DEF_PREF_TAG_MAX (8, Timestamp)

**/
