

/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieving referential (i.e. static) data          **/
/** on several instruments at once                     **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/



#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

/** \cond refguide
 * To perform a referential Get Instruments request in FeedOS API C++, you need to provide
 * a list of attributes to retrieve, which acts as a filter when querying the
 * referential server, as shown below:
 * \snippet perform_refget.cpp snippet_ref_get_attr
 *
 * Use the FeedOS API object to get the instruments' attributes:
 * \snippet perform_refget.cpp snippet_ref_get_req
 *
 * \endcond
 */
void perform_refget (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_refget");	

	if (argc<2) {
		std::cerr << "? CODES..." << std::endl;
		return;
	}

	//![snippet_ref_get_attr]
	// list of the requested attributes (empty => everything)
	ListOfReferentialTagNumber format;
	//![snippet_ref_get_attr]

	//![snippet_ref_get_req]
	// list of the instruments you want to retrieve
	ListOfPolymorphicInstrumentCode	codes;
	 // read them from command-line arguments
	if (!extract_codes (codes, argc, argv))
	{
		return;
	}

	FeedOS::Types::ListOfInstrumentCharacteristics result;

	ReturnCode rc = API_REFERENTIAL_GetInstruments(
			connection,
			result,
			codes,
			format);

	if (rc != RC_OK)
	{
		std::cerr << "refget error, rc="<< error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "refget ok" << std::endl;
		dump_instr_charac(result);
	}
	//![snippet_ref_get_req]
}
