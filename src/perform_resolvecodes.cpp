
#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;
using namespace FeedOS::Types;

/** \cond refguide
 * This sample illustrates how to use the \c ResolveCodes request to get the
 * numerical identifiers corresponding to some polymorphic instrument codes.
 *
 * The request is done synchronously on an established connection.
 *
 * \snippet perform_resolvecodes.cpp snippet_ref_resolvecodes_req
 *
 * \endcond
 */
void perform_resolvecodes(FeedOS::API::Connection & connection, int argc, char * argv[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER(User, "perform_refstructure");

	if (argc < 2)
	{
		std::cerr << "? {CODES...}" << std::endl;
		return;
	}

	ListOfFOSInstrumentCode internal_codes;
	ListOfPolymorphicInstrumentCode polymorphic_codes;
	bool ignore_invalid_codes = true;

	// read input codes from command-line
	if (!extract_codes(polymorphic_codes, argc, argv))
	{
		std::cerr << "error parsing polymorphic codes" << std::endl;
		return;
	}

	//![snippet_ref_resolvecodes_req]
	ReturnCode rc = API_REFERENTIAL_ResolveCodes(
			connection,
			internal_codes,
			polymorphic_codes,
			ignore_invalid_codes);

	if (rc != RC_OK)
	{
		std::cerr << "error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		dump_resolved_codes(polymorphic_codes, internal_codes);
	}
	//![snippet_ref_resolvecodes_req]
}
