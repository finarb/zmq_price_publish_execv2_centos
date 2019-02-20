
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** using "lookup" request to locate instruments       **/
/** (with optional filtering/formatting)               **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/


#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

/** \cond refguide
 * To perform a Referential Lookup request in FeedOS API C++, you need to provide a string that
 * acts as a filter when querying the referential server.
 *
 * If an instrument matches the query, it is returned along with the requested attributes,
 * as described in the sample below:
 *
 * <ol><li>Add optional filters to narrow the search:</li></ol>
 * \snippet perform_reflookup.cpp snippet_ref_structure_filter
 *
 * <ol><li>List the attributes to retrieve:</li></ol>
 * \snippet perform_reflookup.cpp snippet_ref_structure_attr
 *
 * <ol><li>Specify the type of search:</li></ol>
 * \snippet perform_reflookup.cpp snippet_ref_structure_type
 *
 * <ol><li>Use the FeedOS API object to perform the lookup:</li></ol>
 * \snippet perform_reflookup.cpp snippet_ref_structure_req
 *
 * \endcond
 */
void perform_reflookup (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_reflookup");	

	if (argc!=2) {
		std::cerr << "? PATTERN" << std::endl;
		return;
	}

	std::string pattern=argv[1]; ++argv; --argc;	// string to look for

	//![snippet_ref_structure_type]
	// precise search (try Wide)
	LookupMode mode = LookupMode_Narrow;
	//![snippet_ref_structure_type]
	uint16 maxHits = 10;

#if 1
	FeedOS::Types::ListOfReferentialAttribute filter;
#else	// this is an example of filtering. It is disabled in this sample.
	//![snippet_ref_structure_filter]
	ListOfReferentialAttribute filter;

	// Type=Option
	filter.push_back(ReferentialAttribute_SecurityType("OPT"));
	// OR Type=Future
	filter.push_back(ReferentialAttribute_SecurityType("FUT"));
	// AND expires in 2006
	filter.push_back(ReferentialAttribute_MaturityYear(2006));
	//![snippet_ref_structure_filter]
#endif

	// the list of attributes we are interested in
	//![snippet_ref_structure_attr]
	FeedOS::Types::ListOfReferentialTagNumber format;
	// IMPORTANT: part of the "local code"
	format.push_back (FeedOS::TAG_FOSMarketId);
	// IMPORTANT: part of the "local code"
	format.push_back (FeedOS::TAG_LocalCodeStr);
	format.push_back (FeedOS::TAG_Symbol);
	format.push_back (FeedOS::TAG_Description);
	format.push_back (FeedOS::TAG_CFICode);
	format.push_back (FeedOS::TAG_SecurityType);
	//![snippet_ref_structure_attr]

	//![snippet_ref_structure_req]
	ListOfInstrumentCharacteristics result_hits;

	ReturnCode rc = API_REFERENTIAL_Lookup(
			connection,
			result_hits,
			pattern,
			maxHits,
			mode,
			filter,
			format);

	if (rc != RC_OK)
	{
		std::cerr << "lookup error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "lookup ok, nb_hits=" << (unsigned int)result_hits.size()
				<< std::endl;
		dump_instr_charac(result_hits);
	}
	//![snippet_ref_structure_req]
}
