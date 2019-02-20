
// Euronext DMA via FIM API
// values sent in Context/TAG_MARKET_FIM_CrossOrderIndicator

FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR(No				,"0")	// implicit default value (it will not be sent)
FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR(Yes				,"1")	// this will also generate FIX TradeConditions X_CROSSED
FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR(YesBasket			,"3")	// this will also generate FIX TradeConditions X_CROSSED
FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR(ValuationTrade	,"4")	// ?

#undef FEEDOS_DECLARE_EURONEXT_CROSS_ORDER_INDICATOR
