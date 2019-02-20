
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** QuantHouse 2005                **/
/************************************/

#ifndef FEEDOS_SAMPLE_CLI_TOOLS_H
#define FEEDOS_SAMPLE_CLI_TOOLS_H

#include <feedos/api/api.h>
#include <feedos/base/date.h>
#include <cstring>
#include <stdio.h>

// dump a price on STDOUT (with support for special values)
void print_price_83f		(double price);
void print_qty				(FeedOS::FOSLowLevelInteger qty);
void print_nb_orders		(FeedOS::FOSLowLevelInteger nb_orders);

void dump_tick_size_tables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & tables);

void dump_ref_markets		(FeedOS::Types::ListOfMarketCharacteristics const & markets);
void dump_ref_branches		(FeedOS::Types::ListOfMarketContent const & branches);

void dump_quot_variables	(std::ostream & os, FeedOS::Types::ListOfQuotationVariable const & list, bool compact=false);
inline
void dump_quot_variables	(FeedOS::Types::ListOfQuotationVariable const & list)
{
	dump_quot_variables	(std::cout, list);
}
void dump_quot_context		(FeedOS::Types::ListOfQuotationContextFlag const & list);


void dump_instr_charac		(FeedOS::Types::ListOfInstrumentCharacteristics const & list);

void dump_one_side_limit	(FeedOS::Types::OrderBookEntryExt const & entry, char const * side_str);
void dump_halfbook			(FeedOS::Types::ListOfOrderBookEntry const & list, char const * side_str);

void dump_best_limits		(FeedOS::Types::OrderBookBestLimitsExt const & best_limits);

void dump_instr_status		(FeedOS::Types::ListOfInstrumentStatusL1 const & list);

void dump_histo_intraday	(FeedOS::Types::ListOfIntradayHistoryPoint const & list);
void dump_histo_intraday2 (FeedOS::Types::ListOfIntradayHistoryPoint2 const & list,
						   std::map<unsigned int,FeedOS::ListOfQuotationContextFlag> const & dictionary,
						   bool raw_mode);
void dump_histo_intraday_extended(FeedOS::Types::ListOfIntradayHistoryPointExtended const & list, std::map<unsigned int, FeedOS::ListOfQuotationContextFlag> const & dictionary);

void dump_histo_daily_ext	(FeedOS::Types::ListOfDailyHistoryPointExt const & list);

bool extract_codes			(FeedOS::Types::ListOfPolymorphicInstrumentCode & codes, int & argc, char ** & argv);
bool extract_MICs			(FeedOS::Types::ListOfFOSMarketId & market_ids, int & argc, char ** & argv);

void dump_metadata			(FeedOS::Types::ListOfTagDeclaration const & inTags, FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums, FeedOS::Types::ListOfString const & inProviders);
void dump_trade_conditions	(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const &values);

void dump_news_field		(std::ostream & os, FeedOS::Types::ListOfNewsItem const & list, FeedOS::Timestamp & actual_origin_utc_time);
void print_news_id			(std::ostream & os, FeedOS::Types::NewsUuid const & news_id);
void print_news				(std::ostream & os, FeedOS::Types::NewsData const & news, FeedOS::Timestamp & actual_origin_utc_time , bool with_type = false);
void print_news				(std::ostream & os, FeedOS::Types::ListOfNewsData const & news, FeedOS::Timestamp & actual_origin_utc_time, bool with_type = false);

void print_intraday_bar		(std::ostream & os, FeedOS::Types::QuotationIntradayBar const & bar);

void dump_resolved_codes	(FeedOS::Types::ListOfPolymorphicInstrumentCode const & polymorphic_codes,
		FeedOS::Types::ListOfFOSInstrumentCode const & internal_codes);


#endif
