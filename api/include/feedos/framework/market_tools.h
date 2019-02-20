
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_MARKET_TOOLS_H
#define FEEDOS_FRAMEWORK_MARKET_TOOLS_H

//#ifndef FEEDOS_API_API_H
//#  include "../api/api.h"
//#endif

#include <string>

namespace FeedOS {


	/**
	 *
	 * Convert a decimal price into its representation in fractional using the fractional specification provided in the
	 * referential.
	 *
	 * Please refer to documentation:
	 *   http://www.cmegroup.com/resources-for/files/cbotclientimpact.pdf
	 *   Section 3 (page 20) + Appendix J (page 75)
	 *
	 * Note: this feature is specific to the CME DMA market.
	 *
	 * @param displayPricePrimaryDenominator	tdftpd - the input tick Display Format Type for the Primary Denominator
	 * @param displayPriceSecondaryDenominator	tdftsd - the input tick Display Format Type for the Secondary Denominator
	 * @param displayPriceNbOfDecimal			nddp - the input number of decimal in display price
	 * @param decimal_price						the input decimal price
	 * @param fractional_display_price			the output display price in fractional
	 * @return true if convertion suceeded, false in case of error
	 *
	 */
	bool convert_CME_decimal_to_fractional_display_price (
		unsigned int displayPricePrimaryDenominator,
		unsigned int displayPriceSecondaryDenominator,
		unsigned int displayPriceNbOfDecimal,
		double decimal_price,
		std::string & fractional_display_price
		);

} // namespace FeedOS

#endif
