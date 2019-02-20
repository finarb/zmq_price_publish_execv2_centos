
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieving referential (i.e. static) data          **/
/** STRUCTURE (list of "branches")                     **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

/** \cond refguide
 *
 * The following sample in C++ performs a download of the referential structure
 * (list of referential branches).
 *
 * It uses the FeedOS API object to perform the download:
 * \snippet perform_refstructure.cpp snippet_ref_structure_req
 *
 * \endcond
 */
void perform_refstructure (FeedOS::API::Connection & connection, int argc, char * /*argv*/[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_refstructure");	

	if (argc!=1) {
		std::cerr << "no argument expected" << std::endl;
		return;
	}

	//![snippet_ref_structure_req]
	ListOfMarketCharacteristics	markets;	// list of markets
	ListOfMarketContent			branches;	// list of branches
	Timestamp					lastUpdateTimestamp;

	ReturnCode rc = API_REFERENTIAL_DumpStructure(
			connection,
			markets,
			branches,
			lastUpdateTimestamp);

	if (rc != RC_OK)
	{
		std::cerr << "refstructure error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "refstructure ok" << std::endl;
		dump_ref_markets(markets);
		dump_ref_branches(branches);
	}
	//![snippet_ref_structure_req]
}
