
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
 * The following sample in C++ retrieves the Trade Conditions Dictionary tables.
 *
 * It uses the FeedOS API object to get the dictionary synchronously.
 * \snippet perform_gettradeconditions.cpp snippet_gettc
 *
 * \endcond
 */
void perform_gettradeconditions	(FeedOS::API::Connection & connection, int argc, char * /*argv*/[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_gettradeconditions");	

	if (argc!=1) {
		std::cerr << "no argument expected" << std::endl;
		return;
	}

	//![snippet_gettc]
	FeedOS::Types::ListOfTradeConditionsDictionaryEntry result;

	ReturnCode rc = API_REFERENTIAL_GetTradeConditionsDictionary(
			connection,
			result);

	if (rc != RC_OK)
	{
		std::cerr << "ref_GetTradeConditionsDictionary error, rc="
				  << error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "ref_GetTradeConditionsDictionary ok" << std::endl;
		dump_trade_conditions(result);
	}
	//![snippet_gettc]
}
