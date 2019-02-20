
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_QUOTATION_H
#define FEEDOS_API_QUOTATION_H

#ifndef FEEDOS_API_API_H
#  include "api.h"
#endif

#include "../deprecated/deprecated_api_QUOTATION.h"


/////////////////////////
// instruments - L1
#include "../generated/gen_api_QUOTATION_SnapshotInstrumentsL1.h"
#include "../generated/gen_api_QUOTATION_SubscribeInstrumentsL1.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL1Add.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL1Remove.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL1NewContentMask.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL1AddOtherValuesToLookFor.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL1RemoveOtherValuesToLookFor.h"
#include "../generated/gen_api_QUOTATION_DownloadHistoryIntradayExtended.h"


/////////////////////////
// instruments - L2 MBL
#include "../generated/gen_api_QUOTATION_SubscribeInstrumentsL2.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL2Add.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsL2Remove.h"
#include "../generated/gen_api_QUOTATION_SubscribeInstrumentsMBL.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsMBLAdd.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsMBLRemove.h"


/////////////////////////
// instruments - L2 MBO
#include "../generated/gen_api_QUOTATION_SubscribeOneInstrumentMarketSheet.h"
#include "../generated/gen_api_QUOTATION_SubscribeInstrumentsMBO.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsMBOAdd.h"
#include "../generated/gen_api_QUOTATION_ChgSubscribeInstrumentsMBORemove.h"


/////////////////////////
// subscribe by MIC
#include "../generated/gen_api_QUOTATION_SubscribeMarketsDataAndStatus.h"
#include "../generated/gen_api_QUOTATION_SubscribeMarketsOrderBook.h"


/////////////////////////
// instruments - histo
#include "../generated/gen_api_QUOTATION_GetHistoryDaily.h"
#include "../generated/gen_api_QUOTATION_GetHistoryDailyExt.h"
#include "../generated/gen_api_QUOTATION_GetHistoryIntraday.h"
#include "../generated/gen_api_QUOTATION_GetHistoryIntraday2.h"
#include "../generated/gen_api_QUOTATION_GetHistoryIntradayExtended.h"
#include "../generated/gen_api_QUOTATION_GetHistoryIntradayExtendedNTicks.h"
#include "../generated/gen_api_QUOTATION_GetHistoryDailyExt.h"

/////////////////////////
// instruments - mass download
#include "../generated/gen_api_QUOTATION_DownloadInstruments.h"
#include "../generated/gen_api_QUOTATION_DownloadHistoryIntradayBarsExt.h"

/////////////////////////
// market news
#include "../generated/gen_api_QUOTATION_SubscribeMarketsStatus.h"
#include "../generated/gen_api_QUOTATION_SubscribeAllStatus.h"


#endif
