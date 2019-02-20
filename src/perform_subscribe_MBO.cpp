
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to quotation events         **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/

#include <feedos/zmqpp/MarketSheetClient_text.h>
#include <stdio.h>
#include <cstring>

// uncomment the following "using" statements to simplify code
//using namespace std;
//using namespace FeedOS;
//using namespace FeedOS::Types;

static void usage()
{
	std::cerr << "usage: [-depth N] [-counters] [-descr] [-sheet] [-book]\n";
}


/** \cond refguide
 * To perform an MBO instrument subscription in FeedOS API C++, you need to implement an
 * interface and several callbacks that handle the request and responses, as described in the
 * procedure below:
 *
 * <ol><li>Implement the \c FeedOS::API_QUOTATION_SubscribeOneInstrumentMarketSheet_base interface
 * whose virtual methods are called when the events are received.</li></ol>
 * \snippet MarketSheetClient_base.h snippet_sub_MBO_subclass
 *
 * <ol><li>Implement the started callback to be called when the server acknowledges the query,
 * as shown below:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_started
 *
 * <ol><li>Implement the failed callback to be called if there is an error during the query:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_failed
 *
 * <ol><li>Implement the aborted callback to be called when the subscription completes
 * (return code is \c RC_OK) or if an error occurs:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_aborted
 *
 * <ol><li>Implement the real-time callback \c NewOrder to be called when an order is added
 * to the market sheet:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_neworder
 *
 * <ol><li>Implement the real-time callback \c ModifyOrder to be called when an order is modified
 * in the market sheet:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_modifyorder
 *
 * <ol><li>Implement the real-time callback \c RemoveOneOrder to be called when an order is removed
 * from the market sheet:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_remove1order
 *
 * <ol><li>Implement the real-time callback \c RemoveAllPreviousOrders to be called when the beginning
 * of the market sheet is cleared:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_removeallpreviousorders
 *
 * <ol><li>Implement the real-time callback \c RemoveAllOrders to be called when the market sheet
 * is cleared:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_removeallorders
 *
 * <ol><li>Implement the real-time callback \c Retransmission to be called when the market sheet is
 * retransmitted:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_retransmit
 *
 * <ol><li>Implement the real-time callback \c ValuesUpdateOneInstrument to be called when
 * the quotation variables are updated:</li></ol>
 * \snippet MarketSheetClient_base.cpp snippet_sub_MBO_vu
 *
 * <ol><li>Customize the MBO subscription instruments:</li></ol>
 * \snippet perform_subscribe_MBO.cpp snippet_sub_MBO_custom
 *
 * <ol><li>Perform the request (synchronous):</li></ol>
 * \snippet perform_subscribe_MBO.cpp snippet_sub_MBO_req
 *
 * \endcond
 */
void perform_subscribe_MBO (FeedOS::API::Connection & connection, int argc, char * argv[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_MBO");

	int opt_depth=-1;	// print full depth
	if ( (argc > 1) && !strcmp(argv[1],"-depth") )	{
		opt_depth = atoi(argv[2]);
		argv +=2; argc -=2;
	}

	bool opt_print_counters= false;
	if ( (argc > 1) && !strcmp(argv[1],"-counters") ) {
		opt_print_counters =true;
		++argv;
		--argc;
	}

	bool opt_print_updates_description = false;
	if ( (argc > 1) && !strcmp(argv[1],"-descr") ) {
		opt_print_updates_description =true;
		++argv;
		--argc;
	}

	bool opt_reprint_sheet_after_every_update = false;
	if ( (argc > 1) && !strcmp(argv[1],"-sheet") ) {
		opt_reprint_sheet_after_every_update =true;
		++argv;
		--argc;
	}

	bool opt_reprint_book_after_every_update = false;
	if ( (argc > 1) && !strcmp(argv[1],"-book") ) {
		opt_reprint_book_after_every_update =true;
		++argv;
		--argc;
	}

	if (!opt_print_updates_description &&
		!opt_reprint_book_after_every_update &&
		!opt_reprint_sheet_after_every_update &&
		!opt_print_counters)
	{
		std::cerr << "default behaviour is: -counters"<<std::endl;
		opt_print_counters = true;
	}

	if (argc!=2) {
		usage();
		return;
	}

	//![snippet_sub_MBO_custom]
	char const * instr_code_str = argv[1];

	FeedOS::PolymorphicInstrumentCode instr_code;
	if (!instr_code.read_from_string (instr_code_str))
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCode: "
				<< instr_code_str << std::endl;
		return;
	}
	//![snippet_sub_MBO_custom]

	//![snippet_sub_MBO_req]
	Sample::MarketSheetClient_text req(
			std::cout,
			opt_print_counters,
			opt_print_updates_description,
			opt_reprint_book_after_every_update,
			opt_reprint_sheet_after_every_update,
			opt_depth);

	// Start the subscription (synchronous version).
	FeedOS::ReturnCode rc = req.sync_start (connection, instr_code);

	if (rc != FeedOS::RC_OK)
	{
		std::cerr << "sync_start error, rc=" << FeedOS::error_string(rc)
				<< std::endl;
	}
	else
	{
		getchar();
	}
	req.stop ();
	//![snippet_sub_MBO_req]
}
