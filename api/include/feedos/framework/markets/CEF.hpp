// CEF
// values sent in Context/TAG_MARKET_CEF_TradeTypeIndicator

FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(BestValuationPriceWithoutTurnover		,"B")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(MarketTradeCrossing						,"M")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(ExchangeTrade							,"X") // implicit default value (it will not be sent)
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(LastMidpointOrderPrice					,"P")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(XetraBestTrade							,"S")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(BlockCrossingTrade						,"L")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(Opening									,"2")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(Variable								,"3")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(Fixing									,"5")
FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR(Closing									,"9")

#undef FEEDOS_DECLARE_CEF_TRADE_TYPE_INDICATOR

// values sent in Context/TAG_MARKET_CEF_IndexTypeIndicator

FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(Indicative								,"I")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(Representative							,"R")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(Official								,"A") // implicit default value (it will not be sent)
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(NotVerified								,"U")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(FixingIndex								,"K")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(FuturesSettlementIndex					,"F")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(OptionsSettlementIndex					,"O")
FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR(PreliminarySettlement					,"V")

#undef FEEDOS_DECLARE_CEF_INDEX_TYPE_INDICATOR
