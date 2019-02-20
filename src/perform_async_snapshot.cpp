
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** performing a snapshot of quotation data **/
/** on several instruments at once          **/
/**                                         **/
/** (asynchronous version)                  **/
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


class MySnapshotHandler: public API_QUOTATION_SnapshotInstrumentsL1_base
{
public:
	// response callback : success + outputs
	virtual void response_QUOTATION_SnapshotInstrumentsL1_Success (FeedOS::Types::ListOfInstrumentStatusL1 const & result)
	{
		cerr << "snapshot ok"<<endl;
		// managing float precision
		std::cout << std::setprecision(std::numeric_limits<double>::digits10);
		// print quotation tags
		dump_instr_status (result);
	}

	// response callback : some error occurred
	virtual void response_QUOTATION_SnapshotInstrumentsL1_Failed (ReturnCode rc)
	{
		cerr << "snapshot error, rc="<< error_string(rc) <<endl;
	}
};



void perform_async_snapshot (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_async_snapshot");	

	if (argc<2) {
		cerr <<"? CODES..."<<endl;
		return;
	}

	// list of instruments we are interested into
	FeedOS::Types::ListOfPolymorphicInstrumentCode	codes;
	if (!extract_codes (codes, argc, argv))	// read them from command-line arguments
		return;

	// list of "other values" we are interested in (none at this time)
	FeedOS::Types::ListOfQuotationTagNumber otherValues;		

	// the data structure used to return the data
	FeedOS::Types::ListOfInstrumentStatusL1	result;

	// instantiate "receiver" object
	MySnapshotHandler req;

	// send asynchronous request
	req.send (connection, 
					// inputs
					codes, 
					otherValues
					// use default values for remaining input params
				);

	// wait (reponse callbacks within receiver object will be triggered by another thread)
	getchar();
}
