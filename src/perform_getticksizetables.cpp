
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieve Variable Price Increment tables           **/
/** (aka "tick size tables"                            **/
/**                                                    **/
/** QuantHouse 2008                                    **/
/********************************************************/


#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

/** \cond refguide
 * The following sample in C++ retrieves the Variable Price Increment tables.
 *
 * It uses the FeedOS API object to get the tables synchronously.
 * \snippet perform_getticksizetables.cpp snippet_getvts
 *
 * \endcond
 */
void perform_getticksizetables	(FeedOS::API::Connection & connection, int argc, char * /*argv*/[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_getticksizetables");	

	if (argc!=1) {
		std::cerr << "no argument expected" << std::endl;
		return;
	}

	//![snippet_getvts]
	ListOfVariableIncrementPriceBandTable result;

	ReturnCode rc = API_REFERENTIAL_GetVariablePriceIncrementTables(
			connection,
			result);

	if (rc != RC_OK)
	{
		std::cerr << "ref_GetVariablePriceIncrementTables error, rc="
				<< error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "ref_GetVariablePriceIncrementTables ok" << std::endl;
		dump_tick_size_tables(result);
	}
	//![snippet_getvts]
}
