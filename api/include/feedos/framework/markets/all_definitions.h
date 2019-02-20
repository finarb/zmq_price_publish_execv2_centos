
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2007      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_MARKETS_ALL_DEFINITIONS_H
#define FEEDOS_FRAMEWORK_MARKETS_ALL_DEFINITIONS_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	ifndef FEEDOS_API_TAGS_H
#		include "../../api/tags.h"
#	endif
#endif

namespace FeedOS { 

#define FEEDOS_DECLARE_FIX_VALUE_STRING(				KIND,NAME,VALUE)	namespace Types  { extern std::string const KIND##_##VALUE##_##NAME; }
#define FEEDOS_DECLARE_MARKET_VALUE_STRING(		MARKET,	KIND,NAME,VALUE)	namespace MARKET { extern std::string const KIND##_##NAME; }
#include "all.hpp"
#undef FEEDOS_DECLARE_FIX_VALUE_STRING
#undef FEEDOS_DECLARE_MARKET_VALUE_STRING

	// define a market value (besides the predefined ones)
	void define_market_value (Types::TagNumber tag_num, char const * value, char const * pretty_name);

	// return the "pretty name" of the given value pertaining to the given tag
	// (if unknown then return the value itself)
	char const * market_value2name (Types::TagNumber tag_num, char const * value);

	namespace Framework {

		// dump all known values related to "Trade Conditions"
		void dump_all_known_market_values (std::ostream & s);

	}

}

#endif
