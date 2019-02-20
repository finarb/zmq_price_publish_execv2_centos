
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** (c) QuantHouse 2007            **/
/************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/framework/framework_tools.h>
#include <feedos/framework/ReferentialPriceIncrementTable.h>
#include <feedos/comm/FOSEntitlementId.h>
#include <feedos/comm/FOSDictionaryEntryId.h>
#include <fstream>
#include <iomanip>  

using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;


void print_price_83f (double price)
{
	cout << flush;
	char const * special_price_str;
	if		(price == FeedOS::Types::UNQUOTED)							special_price_str = "UNQUOTED";
	else if	(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_BEST)		special_price_str = "AT_BEST";
	else if	(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_OPEN)		special_price_str = "AT_OPEN";
	else if	(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_CLOSE)	special_price_str = "AT_CLOSE";
	else if	(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_PEG)			special_price_str = "PEG";
	else {
		printf ("%8.3f", price);
		fflush(stdout);
		return;
	}

	printf ("%8s", (char const*) special_price_str);
	fflush(stdout);
}

void print_qty(FeedOS::FOSLowLevelInteger qty)
{
	std::ostringstream os;
	os << std::setw(6) << qty;
	printf (" x%s", os.str().c_str());
	fflush(stdout);
}

void print_nb_orders(FeedOS::FOSLowLevelInteger nb_orders)
{
	char const * special_nb_orders_str;
	if			(nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_EMPTY)		special_nb_orders_str = "EMPTY"; 
	else if		(nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_UNKNOWN)	special_nb_orders_str = "?"; 
	else
	{
		printf (" @%6i", static_cast<unsigned int>(nb_orders));
		fflush(stdout);
		return;
	}
	printf (" @%6s", (char const*) special_nb_orders_str);
	fflush(stdout);
}

/*
bool extract_codes (FeedOS::Types::ListOfPolymorphicInstrumentCode & codes, int & argc, char ** & argv)
{
	while (argc>1) {
		FeedOS::PolymorphicInstrumentCode instr_code;

		// use built-in parsing function.
		// example of valid values: 
		//		XEUR@FDAX1205
		//		XEUR@ODAX1205P5000
		//		XBRU@FR0000120404
		if (!instr_code.read_from_string (argv[1])) {
			std::cerr << "syntax error while reading PolymorphicInstrumentCode: "<<argv[1]<<'\n';
			return false;
		}
		codes.push_back (instr_code);	++argv; --argc;
	}
	return true;
}
*/


bool extract_codes (FeedOS::Types::ListOfPolymorphicInstrumentCode & instr_codes, int & argc, char ** & argv)
{
	return read_instrument_codes_from_arguments (instr_codes, argc, argv);
}

bool extract_MICs (FeedOS::Types::ListOfFOSMarketId & market_ids, int & argc, char ** & argv)
{
	while (argc>1) {
		FOSMarketId mic;

		if (!mic.read_from_string (argv[1])) {
			std::cerr << "syntax error while reading FOSMarketId: "<<argv[1]<<'\n';
			return false;
		}
		market_ids.push_back (mic);	++argv; --argc;
	}
	return true;
}

void dump_news_field	(std::ostream & os, FeedOS::Types::ListOfNewsItem const & news_items, FeedOS::Timestamp & actual_origin_utc_time)
{
	for (size_t i = 0; i < news_items.size(); ++i) 
	{
		pretty_print_news_item(os, news_items[i], true);
		if (TAG_OrigUTCTime == news_items[i].getNum())
		{
			actual_origin_utc_time = news_items[i].getValue().get_Timestamp();
		}
		os << std::endl;
	}
}

void print_news_id			(std::ostream & os, FeedOS::Types::NewsUuid const & news_id)
{
	os		<< std::setfill('0') << std::setw(8) << std::hex << news_id.getWordA() 
	<< '-'	<< std::setfill('0') << std::setw(8) << std::hex << news_id.getWordB() 
	<< '-'	<< std::setfill('0') << std::setw(8) << std::hex << news_id.getWordC() 
	<< '-'	<< std::setfill('0') << std::setw(8) << std::hex << news_id.getWordD()
	<< std::dec;
}

void print_news(std::ostream & os, FeedOS::Types::ListOfNewsData const & news, FeedOS::Timestamp & actual_origin_utc_time, bool with_type)
{
	for (FeedOS::Types::ListOfNewsData::const_iterator news_it = news.begin();
		news.end() != news_it;
		++news_it)
	{
		print_news(os, *news_it, actual_origin_utc_time, with_type);
	}
}

void print_news(std::ostream & os, FeedOS::Types::NewsData const & news, FeedOS::Timestamp & actual_origin_utc_time, bool with_type)
{
	os << "NE "	<< " id=";
	print_news_id(os, news.getId());
	if (with_type)
	{
		pretty_print_event_type(os, news.getType());
	}
	os << " serv=" << news.getServerUTCTime();
	os << std::endl;
	dump_news_field(os, news.getItems(), actual_origin_utc_time);
}

void dump_instr_charac (FeedOS::Types::ListOfInstrumentCharacteristics const & list)
{
	for (unsigned int i=0; i<list.size(); ++i) 
	{
		cout << "code = "<<list[i].getCode()<<'\n';
		pretty_print_tags(cout, list[i].getAttributes(), "    ", false);
	}
}

void dump_quot_variables (std::ostream & os, FeedOS::Types::ListOfQuotationVariable const & list, bool compact)
{
	if (compact)
	{
		for (unsigned int i = 0; i < list.size(); ++i)
		{
			if (i)
			{
				os << ", ";
			}
			pretty_print_tag_name_and_value(os, list[i], false);
		}
		os << std::endl;
	}
	else
	{
		pretty_print_tags(os, list, "    ", false);
	}
}


void dump_halfbook (FeedOS::Types::ListOfOrderBookEntry const & list, char const * side_str)
{
	for (unsigned int i=0; i<list.size(); ++i) 
	{
		OrderBookEntry const & entry = list[i];
		cout << "\t"<< side_str <<" # "<<i<<" price=";
		print_price_83f (entry.getPrice());
		cout <<"\tqty="<<entry.getQty()<<'\n';
	}
}


void dump_one_side_limit (FeedOS::Types::OrderBookEntryExt const & entry, char const * side_str)
{
	cout << side_str <<':';
	cout << "\tprice=";	print_price_83f (entry.getPrice());
	cout << "\tqty="<<entry.getQty();
	switch (entry.getNbOrders()) {
	case FeedOS::Types::ORDERBOOK_NB_ORDERS_UNKNOWN:
		cout << "\tnb_orders=?";
		break;
	case FeedOS::Types::ORDERBOOK_NB_ORDERS_EMPTY:
		// number of orders at this price: NONE (the price/qty are the latest valid values)
		cout << "\t(NO ORDER)";
		break;
	default:
		cout << "\tnb_orders="<<entry.getNbOrders();
	}
	cout<<'\n';
}


void dump_best_limits (FeedOS::Types::OrderBookBestLimitsExt const & best_limits)
{
	dump_one_side_limit (best_limits.getBestBid(), "    BID");
	dump_one_side_limit (best_limits.getBestAsk(), "    ASK");
}


void dump_instr_status (FeedOS::Types::ListOfInstrumentStatusL1	const & list)
{
	for (unsigned int i=0; i<list.size(); ++i) 
	{
		InstrumentStatusL1 const & instr = list[i];

		cout <<"code = "<<instr.getCode()<<'\n';

		dump_quot_variables (instr.getValues());

		dump_best_limits (instr.getBestLimits());
	}
}


void dump_histo_intraday (FeedOS::Types::ListOfIntradayHistoryPoint const & list)
{
	for (unsigned int i=0; i<list.size(); ++i) 
	{
		IntradayHistoryPoint const & point = list[i];
		TransactionOrPrice const & trade = point.getTrade();

		cout	//<< point.getSessionId() << '\t'
				<<trade.getMarketUTCTimestamp().str_full() << '\t';
		print_price (cout, trade.getPrice());	cout << '\t';
		print_value (cout, trade.getQty());		cout << '\n';
	}
}

void dump_content_mask(unsigned int content_mask, bool raw_mode)
{
	if (!raw_mode)
	{
		std::string content_mask_str;
		bool const event_daily = (content_mask & QuotationContentBit_OCHL_daily) != 0;

		if (content_mask & QuotationContentBit_Open)	{ event_daily ? content_mask_str.push_back('O') : content_mask_str.push_back('o'); }
		if (content_mask & QuotationContentBit_Close)	{ event_daily ? content_mask_str.push_back('C') : content_mask_str.push_back('c'); }
		if (content_mask & QuotationContentBit_High)	{ event_daily ? content_mask_str.push_back('H') : content_mask_str.push_back('h'); }
		if (content_mask & QuotationContentBit_Low)		{ event_daily ? content_mask_str.push_back('L') : content_mask_str.push_back('l'); }
		if (content_mask & QuotationContentBit_TradingStatus)			{ content_mask_str.push_back('s'); }
		if (content_mask & QuotationContentBit_Bid)						{ content_mask_str.push_back('b'); }
		if (content_mask & QuotationContentBit_Ask)						{ content_mask_str.push_back('a'); }
		if (content_mask & QuotationContentBit_LastPrice)				{ content_mask_str.push_back('p'); }
		if (content_mask & QuotationContentBit_LastTradeQty)			{ content_mask_str.push_back('q'); }
		if (content_mask & QuotationContentBit_OCHL_daily)				{ content_mask_str.push_back('d'); }
		if (content_mask & QuotationContentBit_OtherValues)				{ content_mask_str.push_back('v'); }
		if (content_mask & QuotationContentBit_OpeningNextCalendarDay)	{ content_mask_str.push_back('n'); }
		if (content_mask & QuotationContentBit_Context)					{ content_mask_str.push_back('x'); }
		if (content_mask & QuotationContentBit_OffBookTrade)			{ content_mask_str.push_back('f'); }
		if (content_mask & QuotationContentBit_ChangeBusinessDay)		{ content_mask_str.push_back('y'); }
		if (content_mask & QuotationContentBit_Session)					{ content_mask_str.push_back('e'); }

		// TODO: manage OffBook flag 
		cout << content_mask_str;		
	}
	else
	{
		cout << content_mask;
	}	
}

void dump_trade_conditions_value(unsigned int const index,
								 std::map<unsigned int,ListOfQuotationContextFlag> const & dictionary,
								 bool raw_mode)
{
	if (0 != index)
	{
		if (!raw_mode)
		{
			std::map<unsigned int,ListOfQuotationContextFlag>::const_iterator tradecondition_entry = dictionary.find(index);
			if (dictionary.end() != tradecondition_entry)
			{
				ListOfQuotationContextFlag const & tradeconditions = tradecondition_entry -> second;
				ListOfQuotationContextFlag::const_iterator cur = tradeconditions.begin(); 
				ListOfQuotationContextFlag::const_iterator end = tradeconditions.end();
				for (;end != cur; ++cur) 
				{
					cout << tag_num2str(cur -> getNum());
					cout << "=" << cur -> getValue().to_str(false);
					if (end != cur+1) cout << ",";
				}
			}
			else
			{
				cout << "UNKNOWN_INDEX";
			}
		}
		else
		{
			cout << index;
		}
	}
}

void dump_histo_intraday2 (FeedOS::Types::ListOfIntradayHistoryPoint2 const & list,
						   std::map<unsigned int,FeedOS::ListOfQuotationContextFlag> const & dictionary,
						   bool raw_mode)
{
	for (unsigned int i=0; i<list.size(); ++i) 
	{
		IntradayHistoryPoint2 const & point = list[i];

		cout << point.getServerUTCTime().str_full() << '\t'
			 << point.getMarketUTCTime().str_full() << '\t';
		print_price (cout, point.getPrice());	cout << '\t';
		print_value (cout, point.getLastTradeQty()); cout << '\t';
		dump_content_mask(point.getContentMask(),raw_mode); cout << '\t';
		dump_trade_conditions_value(point.getTradeConditionIndex(),dictionary,raw_mode); cout << '\n';
	}
}

void dump_histo_intraday_extended(FeedOS::Types::ListOfIntradayHistoryPointExtended const & list, std::map<unsigned int, FeedOS::ListOfQuotationContextFlag> const & dictionary)
{
	static bool const raw_mode = false;
	static bool const compact = true;

	for (FeedOS::Types::ListOfIntradayHistoryPointExtended::const_iterator it(list.begin()), end(list.end()); end != it; ++it)
	{
		IntradayHistoryPointExtended const & point = *it;

		std::cout 	<< point.getServerUTCTimestamp().str_full() << '\t'
					<< point.getMarketUTCTimestamp().str_full() << '\t';
		print_price(std::cout, point.getPrice()); std::cout << '\t';
		print_value(std::cout, point.getLastTradeQty()); std::cout << '\t';
		dump_content_mask(point.getContentMask(),raw_mode); std::cout << '\t';
		dump_trade_conditions_value(point.getTradeConditionIndex(), dictionary, raw_mode); std::cout << '\t';
		dump_quot_variables(std::cout, point.getProperties(), compact);
		std::cout << '\n';
	}
}

void dump_histo_daily_ext(FeedOS::Types::ListOfDailyHistoryPointExt const & list)
{
	static bool const compact = true;

	for (FeedOS::Types::ListOfDailyHistoryPointExt::const_iterator it(list.begin()); it != list.end(); ++it)
	{
		DailyHistoryPointExt const & point = *it;
		Timestamp date;
		date.set_timet(86400*point.getDate().getDaysSinceEpoch());

		std::cout << date << '\t';
		if (point.getTradingSessionId() == CoreSessionId)
		{
			std::cout << "Core";
		}
		else
		{
			std::cout << static_cast<int32>(point.getTradingSessionId());
		}
		std::cout << '\t';
		print_value(std::cout, point.getOpen());			std::cout << '\t';
		print_value(std::cout, point.getHigh());			std::cout << '\t';
		print_value(std::cout, point.getLow());				std::cout << '\t';
		print_value(std::cout, point.getClose());			std::cout << '\t';
		print_value(std::cout, point.getVolumeTraded());	std::cout << '\t';
		print_value(std::cout, point.getAssetTraded());		std::cout << '\t';
		dump_quot_variables(std::cout, point.getOtherValues(), compact);
		std::cout << std::endl;
	}
}

void dump_ref_markets (FeedOS::Types::ListOfMarketCharacteristics const & markets)
{
	for (FeedOS::Types::ListOfMarketCharacteristics::const_iterator market_it = markets.begin(); market_it!=markets.end(); ++market_it) {
		MarketCharacteristics const & market = *market_it;

		FOSMarketId mic = market.getMarketId();
		string market_description = mic.get_description ();

		cout <<
			"\nMIC      = " << market_id_internal2iso(mic) << 
			"\nDescr.   = " << market_description <<
			"\nTimeZone = " << market.getTimeZone() <<
			"\nCountry  = " << market.getCountry() << 
			'\n';
	}
}


void dump_ref_branches (FeedOS::Types::ListOfMarketContent const & branches)
{
	for (FeedOS::Types::ListOfMarketContent::const_iterator market_it = branches.begin(); market_it!=branches.end(); ++market_it) {
		FeedOS::FOSMarketId market_id = market_it->getMarketId();

		string market_name = market_id.to_str();

		cout << "\nMarket:\t"<<market_name<< '\n';

		for (ListOfMarketBranchContent::const_iterator branch_it = market_it->getContent().begin(); branch_it!=market_it->getContent().end(); ++branch_it) 
		{
			MarketBranchId const & branch_ID = branch_it->getBranchId();
			string security_type			= branch_ID.getSecurityType();
			string cfi_code					= branch_ID.getCFICode();
			unsigned int branch_quantity	= branch_it->getQuantity();

			cout << "\t"<<market_name<<'\t'<<security_type << '\t' <<cfi_code << " (" << branch_quantity << " instruments)" << '\n';
		}
	}
}


void dump_tick_size_tables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & tables)
{
	// use framework/ReferentialPriceIncrementTables to handle VarTickSize data
	ReferentialPriceIncrementTables t (tables);
	t.print_content(cout);
}

void dump_trade_conditions(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const &values)
{
	for (size_t i = 0; i < values.size(); ++i)
	{
		ListOfQuotationContextFlag::const_iterator cur = values[i].getValue().begin(); 
		ListOfQuotationContextFlag::const_iterator const end = values[i].getValue().end();
		for (;end != cur; ++cur)
		{
			cout << tag_num2str(cur -> getNum());
			cout << "=" << cur -> getValue().to_str(false);
			if (end != cur+1)
			{
				cout << ",";
			}
			else
			{
				cout << '\n';
			}
		}
	}
}

void dump_metadata(FeedOS::Types::ListOfTagDeclaration const & inTags, FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums, FeedOS::Types::ListOfString const & inProviders)
{
	for (FeedOS::Types::ListOfTagDeclaration::const_iterator it = inTags.begin(); inTags.end() != it; ++it)
	{
		cout
			<< "METADATA_TAG"
			<< "\t" << it->getTagUsage()
			<< "\t" << syntax2string( static_cast<AnySyntax>(static_cast<unsigned int>(it->getTagSyntax())))
			<< "\t" << it->getTagNumericId()
			<< "\t" << it->getTagName()
			<< "\t" << it->getTagDescription()
			<< endl;
	}
	for (FeedOS::Types::ListOfEnumTypeDeclaration::const_iterator it_enum = inEnums.begin(); inEnums.end() != it_enum; ++it_enum)
	{
		for (FeedOS::Types::ListOfTagNumber::const_iterator it_tag = it_enum->getRelatedTags().begin(); it_enum->getRelatedTags().end() != it_tag; ++it_tag)
		{
			cout
				<< "METADATA_ENUM_TAG"
				<< "\t" << it_enum->getEnumName()
				<< "\t" << it_enum->getEnumDescription()
				<< "\t" << *it_tag
				<< endl;
		}
		for (FeedOS::Types::ListOfEnumValueDeclaration::const_iterator it_val = it_enum->getEnumValues().begin(); it_enum->getEnumValues().end() != it_val; ++it_val)
		{
			cout
				<< "METADATA_ENUM_VALUE"
				<< "\t" << it_enum->getEnumName()
				<< "\t" << it_enum->getEnumDescription()
				<< "\t" << it_val->getValue()
				<< "\t" << it_val->getValueName()
				<< "\t" << it_val->getValueDescription()
				<< endl;
		}
	}
	for (FeedOS::Types::ListOfString::const_iterator it = inProviders.begin(); inProviders.end() != it; ++it)
	{
		cout
			<< "METADATA_PROVIDER"
			<< "\t" << *it
			<< endl;
	}
}


void print_intraday_bar(std::ostream & os, FeedOS::Types::QuotationIntradayBar const & bar)
{
	os << bar.getInstrCode();
	os << '\t' << bar.getMarketUTCTimestamp_begin();
	os << '\t' << bar.getServerUTCTimestamp_begin();
	os << '\t' << bar.getServerDuration_seconds();
	os << '\t' << bar.getNbPoints();
	os << '\t' << bar.getOpen();
	os << '\t' << bar.getHigh();
	os << '\t' << bar.getLow();
	os << '\t' << bar.getClose();
	os << '\t' << bar.getVolumeTraded();
	os << '\t';
	static bool const compact = true; // on one line
	dump_quot_variables(os, bar.getOtherValues(), compact);
	os << std::endl;
}

void dump_resolved_codes(
		ListOfPolymorphicInstrumentCode const & polymorphic_codes,
		ListOfFOSInstrumentCode const & internal_codes
		)
{
	ListOfPolymorphicInstrumentCode::const_iterator p(polymorphic_codes.begin()),
			p_end(polymorphic_codes.end());
	ListOfFOSInstrumentCode::const_iterator i(internal_codes.begin()),
			i_end(internal_codes.end());

	for (; (i != i_end) && (p != p_end); ++i, ++p)
	{
		std::cout << *p << " => ";
		if (*i == INVALID_INSTRUMENT_CODE)
		{
			std::cout << "invalid";
		}
		else
		{
			std::cout << *i;
		}
		std::cout << std::endl;
	}

	if (i != i_end)
	{
		std::cerr << "more internal codes than polymorphic codes" << std::endl;
	}
	if (p != p_end)
	{
		std::cerr << "more polymorphic codes than internal codes" << std::endl;
	}
}
