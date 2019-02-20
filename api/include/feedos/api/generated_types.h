
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_GENERATED_TYPES_H
#define FEEDOS_API_GENERATED_TYPES_H

#ifndef FEEDOS_API_GENERATED_CONSTANTS_H
#	include "generated_constants.h"
#endif

#include "Printers.h"

#ifndef FEEDOS_COMM_TYPES_H
#	include "../comm/types.h"
#endif

#ifndef FEEDOS_COMPAT_INCLUDE
#ifndef FEEDOS_GEN_PDU_TYPES_H
#	define FEEDOS_DONT_INCLUDE_OLD_HEADERS
#	include "../generated/gen_types.h"
#endif
#endif

namespace FeedOS {
	namespace Types {

	inline void split_OrderBookChangeIndicator (int source_Indicator, bool & is_complete, unsigned int & start_level)
	{
		if (source_Indicator < 0) {
			is_complete=true;
			start_level=-source_Indicator-1;
		} else {
			is_complete=false;
			start_level=source_Indicator;
		}
	}

	inline int build_OrderBookChangeIndicator (bool is_complete, unsigned int start_level)
	{
		if (is_complete)
			return -((int)start_level+1);
		else
			return start_level;
	}

#define FEEDOS_QUOT_UPD_CONTENT_HAS(CONTENT_MASK,WHAT)	((CONTENT_MASK & (1<<FeedOS::Types::QuotationUpdateContent_##WHAT))?true:false)

	void do_check_syntax_consistancy (TagNumAndValue const & v);

#if FEEDOS_ENABLE_PARANOID_CHECKS
	inline void check_syntax_consistancy (TagNumAndValue const & v) { do_check_syntax_consistancy(v); }
#else
	inline void check_syntax_consistancy (TagNumAndValue const &) {}
#endif


	inline OrderBookEntry convert_ext2basic (OrderBookEntryExt const & source)
	{
		if (source.getNbOrders() == ORDERBOOK_NB_ORDERS_EMPTY) {
			return OrderBookEntry (source.getPrice(), 0);
		} else {
			return OrderBookEntry (source.getPrice(), source.getQty());
		}
	}

	inline OrderBookEntryExt convert_basic2ext (OrderBookEntry const & source)
	{
		if (source.getQty() == 0) {
			return OrderBookEntryExt (source.getPrice(), source.getQty(), ORDERBOOK_NB_ORDERS_EMPTY);
		} else {
			return OrderBookEntryExt (source.getPrice(), source.getQty(), ORDERBOOK_NB_ORDERS_UNKNOWN);
		}
	}

	inline OrderBookEntryExt convert_MBL2legacy (MBLOrderBookEntry const & source)
	{
		return OrderBookEntryExt (source.getPrice(), static_cast<double>(source.getQty().getCumulatedUnits()), static_cast<int32>(source.getQty().getNbOrders()));
	}

	} // namespace Types
} // namespace FeedOS

#endif
