
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** performing a snapshot of quotation data **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

#include <iomanip>
#include <limits>

using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;

/** \cond refguide
 * The following sample demonstrates how to get a L1 snapshot for some
 * instruments. It makes use of the synchronous call.
 *
 * <ol><li>Fill a \c ListOfPolymorphicInstrumentCode with the instruments you are
 * interested in. Instantiate a \c ListOfInstrumentStatusL1 object to
 * receive the snapshots.</li></ol>
 *
 * <ol><li>Then use an established connection to perform the request:</li></ol>
 * \snippet perform_snapshot.cpp snippet_snap_l1_request
 *
 * <ol><li>If the return code indicates no error, you can use the result:
 * </li></ol>
 * \snippet perform_snapshot.cpp snippet_snap_l1_result
 *
 * \endcond
 */
void perform_snapshot (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_snapshot");	

	if (argc<2) {
		cerr <<"? CODES..."<<endl;
		return;
	}

	// list of instruments we are interested into
	FeedOS::Types::ListOfPolymorphicInstrumentCode	codes;
	if (!extract_codes (codes, argc, argv))	// read them from command-line arguments
		return;

	FeedOS::Types::ListOfQuotationTagNumber requested_quotation_tags;	// empty list means 'retrieve all tags'

	// the data structure used to return the data
	FeedOS::Types::ListOfInstrumentStatusL1	result;

	// synchronous request
	//![snippet_snap_l1_request]
	ReturnCode rc = API_QUOTATION_SnapshotInstrumentsL1(
			connection,
			// outputs
			result,
			// inputs
			codes,
			requested_quotation_tags
			// use default values for remaining input params
			);
	//![snippet_snap_l1_request]

	//![snippet_snap_l1_result]
	if (rc != RC_OK) {
		cerr << "snapshot error, rc="<< error_string(rc) <<endl;
	} else {
		cerr << "snapshot ok"<<endl;
		// managing float precision
		std::cout << std::setprecision(std::numeric_limits<double>::digits10);
		// print quotation tags
		dump_instr_status(result);
	}
	//![snippet_snap_l1_result]
}
