
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_GENERATED_CONSTANTS_H
#define FEEDOS_API_GENERATED_CONSTANTS_H

#include <iostream>

#ifndef FEEDOS_COMM_TYPES_H
#	include "../comm/types.h"
#endif

#include <ctype.h>

#ifndef FEEDOS_COMPAT_INCLUDE
#ifndef FEEDOS_GEN_PDU_TYPES_H
#	define FEEDOS_DONT_INCLUDE_OLD_HEADERS
#	include "../generated/gen_types.h"
#endif
#endif

namespace FeedOS {
namespace Types {

#include "special_values.hpp"

#undef FEEDOS_DEF_LAYER_ID
#define FEEDOS_DEF_LAYER_ID(NUM,NAME,USAGE) static OrderBookLayerId const ORDERBOOK_LAYER_##NAME = NUM;
#include "ids_mbl_layer.h"
#undef FEEDOS_DEF_LAYER_ID

	int64 const ORDERBOOK_UNLIMITED_DEPTH	= FEEDOS_MAKE_INT64(-1);

	char const FIXSide_Buy	= '1';
	char const FIXSide_Sell	= '2';
	char const FIXSide_BuyAndSell	= '3';	// non-standard value

	char const FIXScope_LocalMarket = '1';
	char const FIXScope_National = '2';
	char const FIXScope_Global = '3';

	char const ImbalanceSide_BuyImbalance = 'B';
	char const ImbalanceSide_SellImbalance = 'S';
	char const ImbalanceSide_NoImbalance = 'N';
	char const ImbalanceSide_InsufficientOrdersToCalculate = 'O';

	char const OptionExerciseStyle_American = 'A';
	char const OptionExerciseStyle_European = 'E';

	unsigned int const 	PriceType_Percentage	=  1; // (e.g. percent of par) (often called "dollar price" for fixed income)
	unsigned int const	PriceType_PerUnit		=  2; //(i.e. per share or contract)
	unsigned int const	PriceType_FixedAmount	=  3; //(absolute value)
	unsigned int const	PriceType_Discount		=  4; //percentage points below par
	unsigned int const	PriceType_Premium		=  5; //percentage points over par
	unsigned int const	PriceType_Spread		=  6;
	unsigned int const	PriceType_TEDprice		=  7;
	unsigned int const	PriceType_TEDyield 		=  8;
	unsigned int const	PriceType_Yield			=  9;
	unsigned int const	PriceType_FixedCabinet	=  10; // trade price (primarily for listed futures and options)
	unsigned int const	PriceType_VariableCabinet=  11; // trade price (primarily for listed futures and options)

#define FEEDOS_DEF_FIX_SECTYPE(VALUE,DESCR)	extern std::string const FIXSecurityType_##VALUE;
#include "FIX_SecurityType.hpp"
#undef FEEDOS_DEF_FIX_SECTYPE

	uint32 const QuotationContentMask_EVERYTHING				=	(uint32)-1;

	uint32 const QuotationContentBit_TradingStatus				=	1<<QuotationUpdateContent_TradingStatus;
	uint32 const QuotationContentBit_Bid						=	1<<QuotationUpdateContent_Bid;
	uint32 const QuotationContentBit_Ask						=	1<<QuotationUpdateContent_Ask;
	uint32 const QuotationContentBit_LastPrice					=	1<<QuotationUpdateContent_LastPrice;
	uint32 const QuotationContentBit_LastTradeQty				=	1<<QuotationUpdateContent_LastTradeQty;
	uint32 const QuotationContentBit_Open						=	1<<QuotationUpdateContent_Open;
	uint32 const QuotationContentBit_Close						=	1<<QuotationUpdateContent_Close;
	uint32 const QuotationContentBit_High						=	1<<QuotationUpdateContent_High;
	uint32 const QuotationContentBit_Low						=	1<<QuotationUpdateContent_Low;
	uint32 const QuotationContentBit_OCHL_daily					=	1<<QuotationUpdateContent_OCHL_daily;
	uint32 const QuotationContentBit_OtherValues				=	1<<QuotationUpdateContent_OtherValues;
	uint32 const QuotationContentBit_OpeningNextCalendarDay		=	1<<QuotationUpdateContent_OpeningNextCalendarDay;
	uint32 const QuotationContentBit_Context					=	1<<QuotationUpdateContent_Context;
	uint32 const QuotationContentBit_OffBookTrade				=	1<<QuotationUpdateContent_OffBookTrade;
	uint32 const QuotationContentBit_ChangeBusinessDay		=	1<<QuotationUpdateContent_ChangeBusinessDay;
	uint32 const QuotationContentBit_Session					=	1<<QuotationUpdateContent_Session;

	uint32 const QuotationContentBit_BidOrAsk					=	QuotationContentBit_Bid | QuotationContentBit_Ask;

	static std::string const s_METADATA_ENUM_TYPE_DECLARATION_MIC_NAME = "iso_10383";
	static std::string const s_METADATA_ENUM_TYPE_DECLARATION_EID_NAME = "entitlements";
	static std::string const s_METADATA_ENUM_TYPE_DECLARATION_DICT_PREFIX = "dictionary_";

	// Closing price types
	namespace ClosingPriceType
	{
		enum Type
		{
			Undefined = '0',
			OfficialClose = 'a',
			OfficialIndicative = 'b',
			OfficialCarryOver = 'c',
			LastPrice = 'd',
			LastEligiblePrice = 'e',
			Manual = 'z'
		};
	}

	// Settlement price types
	namespace SettlementPriceType
	{
		enum Type
		{
			Official = 'a',
			Preliminary = 'b',
			Manual = 'z',
			Undefined = '0'
		};
	}

	uint32 const TradeImpactIndicatorBit_HasOpen			= 1 << QuotationTradeImpactIndicator_HasOpen;
	uint32 const TradeImpactIndicatorBit_HasHighLow			= 1 << QuotationTradeImpactIndicator_HasHighLow;
	uint32 const TradeImpactIndicatorBit_HasLast			= 1 << QuotationTradeImpactIndicator_HasLast;
	uint32 const TradeImpactIndicatorBit_HasVolume			= 1 << QuotationTradeImpactIndicator_HasVolume;
	uint32 const TradeImpactIndicatorBit_HasOffBookVolume	= 1 << QuotationTradeImpactIndicator_HasOffBookVolume;
	uint32 const TradeImpactIndicatorBit_HasVWAP			= 1 << QuotationTradeImpactIndicator_HasVWAP;
	uint32 const TradeImpactIndicatorBit_Open				= 1 << QuotationTradeImpactIndicator_Open;
	uint32 const TradeImpactIndicatorBit_HighLow			= 1 << QuotationTradeImpactIndicator_HighLow;
	uint32 const TradeImpactIndicatorBit_Last				= 1 << QuotationTradeImpactIndicator_Last;
	uint32 const TradeImpactIndicatorBit_Volume				= 1 << QuotationTradeImpactIndicator_Volume;
	uint32 const TradeImpactIndicatorBit_OffBookVolume		= 1 << QuotationTradeImpactIndicator_OffBookVolume;
	uint32 const TradeImpactIndicatorBit_VWAP				= 1 << QuotationTradeImpactIndicator_VWAP;

	uint8 const TradeCancelCorrectionContentBit_IsCorrection	= 1 << TradeCancelCorrectionContent_IsCorrection;
	uint8 const TradeCancelCorrectionContentBit_IsFromVenue		= 1 << TradeCancelCorrectionContent_IsFromVenue;
	uint8 const TradeCancelCorrectionContentBit_CorrectedValues	= 1 << TradeCancelCorrectionContent_CorrectedValues;
	uint8 const TradeCancelCorrectionContentBit_OffBookTrade	= 1 << TradeCancelCorrectionContent_OffBookTrade;
	uint8 const TradeCancelCorrectionContentBit_CurrentSession	= 1 << TradeCancelCorrectionContent_CurrentSession;

	// Adjustment Factor Event Types
	uint32 const AdjustmentFactorEventTypeMask_NoAdjustment					= 0;
	uint32 const AdjustmentFactorEventTypeMask_All							= static_cast<uint32>(-1);

	uint32 const AdjustmentFactorEventTypeBit_RightsSameClass				= 1 << AdjustmentFactorEventType_RightsSameClass;
	uint32 const AdjustmentFactorEventTypeBit_RightsDifferentClass			= 1 << AdjustmentFactorEventType_RightsDifferentClass;
	uint32 const AdjustmentFactorEventTypeBit_EntitlementSameClass			= 1 << AdjustmentFactorEventType_EntitlementSameClass;
	uint32 const AdjustmentFactorEventTypeBit_EntitlementDifferentClass		= 1 << AdjustmentFactorEventType_EntitlementDifferentClass;
	uint32 const AdjustmentFactorEventTypeBit_Subdivision					= 1 << AdjustmentFactorEventType_Subdivision;
	uint32 const AdjustmentFactorEventTypeBit_Consolidation					= 1 << AdjustmentFactorEventType_Consolidation;
	uint32 const AdjustmentFactorEventTypeBit_Demerger						= 1 << AdjustmentFactorEventType_Demerger;
	uint32 const AdjustmentFactorEventTypeBit_CapitalReturn					= 1 << AdjustmentFactorEventType_CapitalReturn;
	uint32 const AdjustmentFactorEventTypeBit_Distribution					= 1 << AdjustmentFactorEventType_Distribution;
	uint32 const AdjustmentFactorEventTypeBit_BonusSameClass				= 1 << AdjustmentFactorEventType_BonusSameClass;
	uint32 const AdjustmentFactorEventTypeBit_BonusDifferentClass			= 1 << AdjustmentFactorEventType_BonusDifferentClass;
	uint32 const AdjustmentFactorEventTypeBit_CapitalReduction				= 1 << AdjustmentFactorEventType_CapitalReduction;
	uint32 const AdjustmentFactorEventTypeBit_CashDividend					= 1 << AdjustmentFactorEventType_CashDividend;
	uint32 const AdjustmentFactorEventTypeBit_ScriptDividendSameClass		= 1 << AdjustmentFactorEventType_ScriptDividendSameClass;
	uint32 const AdjustmentFactorEventTypeBit_ScriptDividendDifferentClass	= 1 << AdjustmentFactorEventType_ScriptDividendDifferentClass;
	uint32 const AdjustmentFactorEventTypeBit_CapitalCall					= 1 << AdjustmentFactorEventType_CapitalCall;

	FOSTradingSessionId const InvalidSessionId = 0;
	FOSTradingSessionId const CoreSessionId = 127;

	enum AuthenticationMechanism
	{
		AuthenticationMechanism_Legacy	= 0,
		AuthenticationMechanism_SHA_512	= 1
	};

	// Possible values for QuotationVariable_Consolidation_LastEvent
	uint8 const ConsolidationEvent_None = 0;
	uint8 const ConsolidationEvent_SourceDisabled = 1; // "manually"
	uint8 const ConsolidationEvent_LegDisabled = 2; // "manually"
	uint8 const ConsolidationEvent_MICDisabled = 3; // "manually"
	uint8 const ConsolidationEvent_SourceEnabled = 4;
	uint8 const ConsolidationEvent_LegEnabled = 5;
	uint8 const ConsolidationEvent_MICEnabled = 6;
	uint8 const ConsolidationEvent_SourceExcluded = 7; // because of feed status
	uint8 const ConsolidationEvent_SourceIncluded = 8;
	uint8 const ConsolidationEvent_LegExcluded = 9; // because of trading status
	uint8 const ConsolidationEvent_LegIncluded = 10;
	uint8 const ConsolidationEvent_LegCrossed = 11; // because of BBO cross
	uint8 const ConsolidationEvent_LegUncrossed = 12;

	// Possible values for ReferentialVariable_SecurityStatus
	uint8 const SecurityStatus_Active = 1;
	uint8 const SecurityStatus_Inactive = 2;
	uint8 const SecurityStatus_Suspended = 3;
	uint8 const SecurityStatus_PendingActivation = 4;

	// Possible values for QuotationVariable_OrderEntryStatus -- Note: This is a bitfield
	uint8 const OrderEntryStatus_OrderEntryDisabled = 0;
	uint8 const OrderEntryStatus_OrderModifyDisabled = 1;
	uint8 const OrderEntryStatus_OrderCancelDisabled = 2;
	uint8 const OrderEntryStatusBit_OrderEntryDisabled = 1 << OrderEntryStatus_OrderEntryDisabled;
	uint8 const OrderEntryStatusBit_OrderModifyDisabled = 1 << OrderEntryStatus_OrderModifyDisabled;
	uint8 const OrderEntryStatusBit_OrderCancelDisabled = 1 << OrderEntryStatus_OrderCancelDisabled;

	// Possible values for QuotationVariable_MarketCondition
	uint8 const MarketCondition_NormalMarket = 0;
	uint8 const MarketCondition_StressedMarket = 1;
	uint8 const MarketCondition_ExceptionalMarket = 2;

} // Types namespace
} // FeedOS namespace

#endif
