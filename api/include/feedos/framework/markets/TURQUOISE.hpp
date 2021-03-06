// TURQUOISE DMA
// values sent in Context/MARKET_TURQUOISE_TradeTypeIndicator

FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(TRANSPARENT_TO_TRANSPARENT,			"5")	// implicit default value (it will not be sent)
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_DARK,							"3")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_TRANSPARENT,					"4")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(TRADE_REPORT,							"9")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(MANUAL_LAST_TRADE_PRICE,				"10")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(MANUAL_LAST_AUCTION_PRICE,			"11")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(UPDATED_REFERENCE_PRICE,				"12")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(TRADE_REPORT_AUCTION,					"102")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_DARK_AUCTION,					"103")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_TRANSPARENT_AUCTION,			"104")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(TRANSPARENT_TO_TRANSPARENT_AUCTION,	"105")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(AUCTION,								"2")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_DARK_OWN_MATCH,				"6")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(DARK_TO_TRANSPARENT_OWN_MATCH,		"7")
FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(TRANSPARENT_TO_TRANSPARENT_OWN_MATCH,	"8")

#undef FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR
