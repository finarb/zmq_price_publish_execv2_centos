/**************************/
/** FeedOS               **/
/**                      **/
/** copyright QuantHouse **/
/**************************/

#ifndef FEEDOS_API_PRINTERS_H
#define FEEDOS_API_PRINTERS_H

#include <ostream>

#include "generated_constants.h"
#include "../comm/types.h"

#ifndef FEEDOS_COMPAT_INCLUDE
#define FEEDOS_DONT_INCLUDE_OLD_HEADERS
#include "../generated/gen_types.h"
#endif

namespace FeedOS {

	enum TagDisplayFormat
	{
		TagDisplayFormat_Unknown = 0,
		TagDisplayFormat_Raw,
		TagDisplayFormat_SourceIDSlashEnumID,
		TagDisplayFormat_ShortName,
		TagDisplayFormat_LongName,
		TagDisplayFormat_ShortAndLongName,
		TagDisplayFormat_End
	};

	char const ** get_tag_display_format_string_list ();
	TagDisplayFormat get_tag_display_format_from_string (char const * const name);
	void print_tag_display_format_help_values (char const * const spacing, std::ostream & o);
	inline TagDisplayFormat default_tag_display_format () { return TagDisplayFormat_ShortName; }

// print a value (with support for UNQUOTED)
inline void print_value (std::ostream & os, double value, bool empty_string_for_unquoted = false)
{
	if (value == Types::UNQUOTED){		if (!empty_string_for_unquoted) { os << "UNQUOTED"; }
	} else {							os << value;
	}
}

// print a "price" value (with support for UNQUOTED and ORDERBOOK_MAGIC_PRICE_*)
void print_price (std::ostream & os, double price, bool empty_string_for_unquoted = false, bool use_printff = false);

// pretty-print a tag value (without tag name)
void pretty_print_tagvalue (std::ostream & os, Types::TagNumber tag_num, Any const & tag_value	, bool show_syntax=false, TagDisplayFormat display_mode_tag=TagDisplayFormat_ShortName);

inline void pretty_print_tagvalue (std::ostream & os, Types::TagNumAndValue const & tag, bool show_syntax=false, TagDisplayFormat display_mode_tag=TagDisplayFormat_ShortName)
{
	pretty_print_tagvalue (os, tag.getNum(), tag.getValue(), show_syntax, display_mode_tag);
}

// pretty-print a tag (name and value)
void pretty_print_tag_name_and_value (std::ostream & os, Types::TagNumAndValue const & tag, bool show_syntax=false);

void pretty_print_tags(std::ostream & os, std::vector<Types::TagNumAndValue> const & tags, std::string const & indentation, bool show_syntax);

void pretty_print_news_item_value (std::ostream & os, Types::TagNumber tag_num, Any const & tag_value, bool show_syntax);
void pretty_print_news_item (std::ostream & os, Types::TagNumAndValue const & tag, bool show_syntax);
void pretty_print_event_type (std::ostream & os, Types::NewsEventType const & news_type);

// print order book quantities
inline void print_cumulated_qty (std::ostream & os, Types::FOSQty const & cumulated_qty, char const * prefix="")
{
	os << prefix << cumulated_qty.get();
}

inline void print_nb_orders (std::ostream & os, Types::FOSQty const & nb_orders, char const * prefix="")
{
	if			(nb_orders == Types::ORDERBOOK_NB_ORDERS_EMPTY)		os << prefix << "EMPTY";
	else if		(nb_orders == Types::ORDERBOOK_NB_ORDERS_UNKNOWN)	os << prefix << '?';
	else
	{
		os << prefix << nb_orders.get();
	}
}

// prints a binary string as hexadecimal
std::string pretty_print_binary_order_id_big_endian(std::string const & order_id);

inline unsigned long binary_order_id_big_endian_to_numeric(std::string const & order_id)
{
	unsigned long r = 0;
	for (unsigned int i=0; i<order_id.size(); ++i)
	{
		r <<= 8;
		r  &= static_cast<uint8>(order_id[i]);
	}
	return r;
}

// converts an order_id string into something printable
inline std::string order_id2str (std::string const & order_id)
{
	for (unsigned int i=0; i<order_id.size(); ++i)
	{
		if (!::isalnum(order_id[i]))
		{
			return pretty_print_binary_order_id_big_endian (order_id);
		}
	}
	return order_id;
}

// converts an order_id string into a numeric value (error case not checked)
inline
unsigned long order_id2numeric (std::string const & order_id)
{
	for (unsigned int i=0; i<order_id.size(); ++i)
	{
		if (!::isalnum(order_id[i]))
		{
			return binary_order_id_big_endian_to_numeric (order_id);
		}
	}
	return strtoul (order_id.c_str(), NULL, 10);
}

void print_TradingSessionId(std::ostream & os, Types::FOSTradingSessionId id);
void print_TradeImpactIndicator(std::ostream & os, Types::QuotationTradeImpactIndicatorMask const & tii);
void print_TradeCancelCorrectionContentMask(std::ostream & os, Types::TradeCancelCorrectionContentMask mask);
void print_TradeData(std::ostream & os, Types::TradeData const & td);
void print_QuotationTradeCancelCorrection(std::ostream & os, Types::QuotationTradeCancelCorrection const & tcc);
void print_SecurityStatus(std::ostream & os, uint8 security_status);
void print_OrderEntryStatus(std::ostream & os, uint8 const order_entry_status);

void print_ListOfTagNumAndValue(std::ostream & os, std::vector<Types::TagNumAndValue> const & l);
void print_ClosingPriceTypeString(std::ostream & os, Types::ClosingPriceType::Type type);

} // FeedOS namespace

std::ostream & operator << (std::ostream & os, FeedOS::Types::TagNumAndValue const & v);
std::ostream & operator << (std::ostream & os, FeedOS::Types::ClosingPriceType::Type type);

#endif /* FEEDOS_API_PRINTERS_H */
