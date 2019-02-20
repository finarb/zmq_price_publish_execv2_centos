
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** subscribing to "market by limit"    **/
/**                                **/
/** QuantHouse 2006                **/
/************************************/
#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

// FeedOS API printer
#include <feedos/framework/FeedPrinter_L2.h>

// TODO: then use reverse map to translate internal codes
// (see perform_subscribe)

//
//
//    MAIN function (start the subscription and wait for ENTER key to be pressed)
//
//
void perform_subscribe_MBL (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_MBL");	

	if (argc < 2) 
	{
		std::cerr <<"? CODE"<<std::endl;
		return;
	}

	// list of instruments we are interested into
	FeedOS::Types::ListOfPolymorphicInstrumentCode	input_codes;
	if (!extract_codes (input_codes, argc, argv))	// read them from command-line arguments
	{
		std::cerr << "Could not read instrument codes from command line" << std::endl;
		return;
	}

	FeedOS::FeedPrinter_L2_instruments printer(std::cout);
	printer.set_output_format(	FeedOS::FeedPrinter_L2_base::DEFAULT_output_format_recv_timestamp_mode,	
								FeedOS::FeedPrinter_L2_base::DEFAULT_output_format_opt_f,				
								true,																	
								FeedOS::FeedPrinter_L2_base::DEFAULT_output_format_opt_cache_book,		
								FeedOS::FeedPrinter_L2_base::DEFAULT_output_format_opt_order_book_depth,
								FeedOS::FeedPrinter_L2_base::DEFAULT_output_format_opt_split_into_delta,
								FeedOS::FeedPrinter_L2_base::DEFAULT_output_print_numeric);				

	FeedOS::API_QUOTATION_SubscribeInstrumentsMBL_delegate req (printer);

	// Display field roles
	printer.init();

	// start the subscription (synchronous version)
	FeedOS::ListOfOrderBookLayerId requested_layers; // Empty list means we want ALL layers
	FeedOS::ReturnCode rc = req.sync_start (connection, input_codes,requested_layers);

	if ( FeedOS::RC_OK != rc ) {
		std::cerr << "sync_start error, rc="<< FeedOS::error_string(rc) <<std::endl;
	} else {
		getchar(); // wait for user input
	}
	req.stop (); // stop subscription
}
