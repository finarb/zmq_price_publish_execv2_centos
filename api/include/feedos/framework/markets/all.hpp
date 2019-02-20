#define FEEDOS_DECLARE_FIX_TRADE_CONDITION(NAME,VALUE,DESCRIPTION)		FEEDOS_DECLARE_FIX_VALUE_STRING(TradeCondition,	NAME,	VALUE)
#include "FIX_protocol.hpp"

#define FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR(NAME,VALUE)		FEEDOS_DECLARE_MARKET_VALUE_STRING(EURONEXT,CrossOrderIndicator,	NAME,	VALUE)
#include "EURONEXT.hpp"

#define FEEDOS_DECLARE_LSE_TRADE_TYPE_INDICATOR(NAME,VALUE)				FEEDOS_DECLARE_MARKET_VALUE_STRING(LSE,TradeTypeIndicator,			NAME,	VALUE)
#define FEEDOS_DECLARE_LSE_BARGAIN_CONDITION_INDICATOR(NAME,VALUE)		FEEDOS_DECLARE_MARKET_VALUE_STRING(LSE,BargainConditionIndicator,	NAME,	VALUE)
#define FEEDOS_DECLARE_LSE_TRADE_TIME_INDICATOR(NAME,VALUE)				FEEDOS_DECLARE_MARKET_VALUE_STRING(LSE,TradeTimeIndicator,			NAME,	VALUE)
#define FEEDOS_DECLARE_LSE_CONVERTED_PRICE_INDICATOR(NAME,VALUE)		FEEDOS_DECLARE_MARKET_VALUE_STRING(LSE,ConvertedPriceIndicator,		NAME,	VALUE)
#include "LSE.hpp"

#define FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR(NAME,VALUE)				FEEDOS_DECLARE_MARKET_VALUE_STRING(CME,TradeTypeIndicator,	NAME,	VALUE)
#include "CME.hpp"

#define FEEDOS_DECLARE_LIFFE_TRADE_TYPE_INDICATOR(NAME,VALUE)			FEEDOS_DECLARE_MARKET_VALUE_STRING(LIFFE,TradeTypeIndicator,NAME,	VALUE)
#include "LIFFE.hpp"

#define FEEDOS_DECLARE_TURQUOISE_TRADE_TYPE_INDICATOR(NAME,VALUE)		FEEDOS_DECLARE_MARKET_VALUE_STRING(TURQUOISE,TradeTypeIndicator,NAME,	VALUE)
#include "TURQUOISE.hpp"

#define FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(NAME,VALUE)				FEEDOS_DECLARE_MARKET_VALUE_STRING(CEF,IndexTypeIndicator,NAME,	VALUE)
#define FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(NAME,VALUE)				FEEDOS_DECLARE_MARKET_VALUE_STRING(CEF,TradeTypeIndicator,NAME,	VALUE)
#include "CEF.hpp"
