
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2008 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FRAMEWORK_TOOLS_H
#define FEEDOS_FRAMEWORK_FRAMEWORK_TOOLS_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#include <fstream>

namespace FeedOS {

	bool read_instrument_code_from_string		(Types::ListOfPolymorphicInstrumentCode & instr_codes, std::string const & s);
	bool read_instrument_codes_from_file		(Types::ListOfPolymorphicInstrumentCode & instr_codes, std::istream & i);
	bool read_instrument_codes_from_arguments	(Types::ListOfPolymorphicInstrumentCode & instr_codes, int & argc, char ** & argv);

	bool read_MIC_from_string		(Types::ListOfFOSMarketId & mics, std::string const & s);
	bool read_MICs_from_file		(Types::ListOfFOSMarketId & mics, std::istream & i);
	bool read_MICs_from_arguments	(Types::ListOfFOSMarketId & mics, int & argc, char ** & argv);

} // namespace FeedOS

#endif
