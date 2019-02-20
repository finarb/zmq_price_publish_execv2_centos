
// CME DMA via MDP API
// values sent in Context/TAG_MARKET_CME_TradeTypeIndicator

FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR (Normal			,"0")	// implicit default value (it will not be sent)
FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR (NormalForLeg	,"2")	// this will also generate FIX TradeConditions AH_COMBO
FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR (ExPit			,"3")	// this will also generate FIX TradeConditions W_EX_PIT
FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR (ExPitForLeg	,"4")	// this will also generate FIX TradeConditions AH_COMBO + W_EX_PIT

#undef FEEDOS_DECLARE_CME_TRADE_TYPE_INDICATOR
