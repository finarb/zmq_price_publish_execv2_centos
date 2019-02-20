
/*******************************************/
/** FeedOS sample client code             **/
/**                                       **/
/** (c) QuantHouse 2012                   **/
/**                                       **/
/** a simple Command Line Interface tool  **/
/** that performs various requests        **/
/**                                       **/
/**  basic usage of ProxyServerObserver   **/
/**  is demonstrated                      **/
/**                                       **/
/*******************************************/

#include <feedos/api/api.h>
#include <exception>
#include <iostream>
using namespace std;

#include <feedos/zmqpp/simple_observer.h>

void perform_refstructure						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_reflookup							(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_refget								(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_resolvecodes						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_snapshot							(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe							(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_L1_tags					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_oneMBL					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_oneMBL_and_mergeLayers	(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_async_snapshot						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_market_status						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_histo_intraday_extended			(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_histo_intraday_extended_N_ticks	(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_refdownload						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_refdownload_and_subscribe			(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_quotdownload						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_MBL						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_MBO						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_instruments_MBO			(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_getticksizetables					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_gettradeconditions					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_feed_status				(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_L1_by_MIC				(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_L2_by_MIC				(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_price_instruments					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_subscribe_NEWS						(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_newslookup							(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_histo_newsdownload					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_download_intraday_bars_ext			(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_dl_and_sub_histo_intraday_extended	(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_histo_daily_ext					(FeedOS::API::Connection & connection, int argc, char * argv[]);
void perform_get_generic_tag_by_source_id		(FeedOS::API::Connection & connection, int argc, char const * const argv[]);

static void usage(std::string const & err)
{
	std::cerr << "error: "<<err<<
"\n"
"\narguments: [OPTIONS] server port user pass REQUEST [params]"
"\n"
"\n  OPTIONS:"
"\n        -v                              # verbose mode"
"\n        -l                              # enable log file"
"\n        -d                              # debug mode (implies -l)"
"\n"
"\n  SUPPORTED REQUESTS:"
"\n"
"\n    refstructure                        => dump the structure of instruments referential"
"\n    refdownload                         => dump whole or part of instruments referential"
"\n    refdownload_and_subscribe           => subscribe to whole or part of referential data"
"\n    reflookup                           => look for instruments using a pattern string"
"\n    refget                              => retrieve instruments characteristics"
"\n    resolvecodes                        => get internal codes from local codes"
"\n    getticksizetables                   => retrieve variable tick size tables"
"\n    gettradeconditions                  => retrieve trade conditions"
"\n    snapshot                            => retrieve instruments quotation data"
"\n    subscribe                           => subscribe to real-time quotation events"
"\n    subscribe_L1_tags                   => subscribe to real-time quotation events, demonstrates tag processing using API cache management"
"\n    subscribe_oneMBL                    => subscribe to real-time mbl events for one instrument"
"\n    subscribe_oneMBL_and_mergeLayers    => subscribe to real-time mbl events for one instrument and merge layers into a new one"
"\n    subscribe_MBL                       => subscribe to real-time mbl events"
"\n    subscribe_MBO                       => subscribe to real-time market sheet events"
"\n    subscribe_instruments_MBO           => subscribe to real-time market sheet events for many instruments"
"\n    subscribe_NEWS                      => subscribe to real-time news events"
"\n    newslookup                          => look for news using some criteria"
"\n    async_snapshot                      => same as 'snapshot', but asynchronous version"
"\n    market_status                       => subscribe to market status & news"
"\n    histo_intraday_extended             => get trades (with properties) for an instrument"
"\n    histo_intraday_extended_N_ticks     => get N trades (with properties) from/to a timestamp for an instrument"
"\n    dl_and_sub_histo_intraday_extended  => multi-instrument download (and subscribe to) historical trades and trade cancels/corrections"
"\n    histo_news                          => download historical news that occurred between two dates"
"\n    quotdownload                        => dump instrument data (referential and quotation)"
"\n    feed_status                         => subscribe to events related to feed health"
"\n    subscribe_L1_by_MIC                 => subscribe to L1 for a whole MIC (no initial snapshot)"
"\n    subscribe_L2_by_MIC                 => subscribe to L2 for a whole MIC (no initial snapshot)"
"\n    price_instruments                   => compute monetary value of given instruments"
"\n    bars                                => get intraday bars"
"\n    histo_daily_ext                     => get daily and session values for an instrument"
"\n    get_generic_tag_by_source_id        => get generic tag by source id"
"\n"
	;
}

static void init_feedos_trace_facility(char const * program_name, bool /*opt_verbose*/, bool opt_debug)
{
	// init trace facility only if verbose mode is ON
	FeedOS::API::init_trace_all_areas(std::string(program_name)+".log", 
						false,			// append_mode		
						opt_debug,		// flush_every_line		
						true,			// enable_error_levels	
						true,			// enable_warning_level	
						true,			// enable_info_level	
						opt_debug,		// enable_debug_levels	
						false			// enable_scope_level
					);
	FeedOS::API::init_trace_user_area (); // enable all trace levels for area "User"
}

int main (int argc, char * argv[]) 
{
	char const program_name [] = "sample_cli";

	bool opt_verbose = false;
	bool opt_log_file = false;
	bool opt_debug = false;
	if ( (argc > 1) && !strcmp(argv[1],"-v") ) { opt_verbose=true; ++argv; --argc; }
	if ( (argc > 1) && !strcmp(argv[1],"-l") ) { opt_log_file=true; ++argv; --argc; }
	if ( (argc > 1) && !strcmp(argv[1],"-d") ) { opt_debug=opt_log_file=true; ++argv;--argc; }

	try {

		// init trace stuff (optional)
		if (opt_log_file)
		{
			init_feedos_trace_facility(program_name, opt_verbose, opt_debug);
		}

		// initialise the API
		FeedOS::ReturnCode rc = FeedOS::API::init(program_name);
		if (rc != FeedOS::RC_OK){
			cerr << "FeedOS::API::init() failed, rc="<<rc<<endl;
			return 1;
		}

		FEEDOS_LOG (User, Info, "starting");

		// dump various information in the log file
		{
			std::stringstream info;
			info << "\n\tapi_version="<<FEEDOS_API_VERSION_STRING;
//			info << "\n\tlist of supported tags:\n";		FeedOS::dump_supported_tags (info);
			FEEDOS_LOG (User, Info, "info: "<<info.str());
		}


		// read arguments from command line 
		if (argc<6) {
			usage("not enough arguments");
			exit (1);
		}
		std::string const server	=argv[1];	++argv; --argc;
		int const port				=atoi(argv[1]);++argv; --argc;
		std::string const user		=argv[1];	++argv; --argc;
		std::string const pass		=argv[1];	++argv; --argc;
		std::string const request	=argv[1];	++argv; --argc;

		//
		// connect to feedos server
		//
		FeedOS::API::Connection connection;
#if 0	// uncomment this to enable "monitoring" of the Connection object
		SimpleObserver	conn_observer;
		connection.add_observer (conn_observer);
#endif

		rc = connection.sync_connect (server, port, user, pass);
		if (rc!=FeedOS::RC_OK) {
			FEEDOS_LOG (User, Warning, "cannot connect to "<<server<<':'<<port<<" rc="<<FeedOS::error_string(rc));
			cerr << "cannot connect, rc="<<FeedOS::error_string(rc)<<endl;
			exit (1);
		}

		// load extra tags, MICs, etc
		FeedOS::API::sync_download_metadata (connection);


		//
		// execute the given request
		//
		FEEDOS_LOG (User, Debug , "main() trying to execute: "<<request);

		if		(request=="refstructure")						perform_refstructure					(connection, argc, argv);
		else if	(request=="refdownload")						perform_refdownload						(connection, argc, argv);
		else if	(request=="refdownload_and_subscribe")			perform_refdownload_and_subscribe		(connection, argc, argv);
		else if	(request=="reflookup")							perform_reflookup						(connection, argc, argv);
		else if (request=="refget")								perform_refget							(connection, argc, argv);
		else if (request=="resolvecodes")						perform_resolvecodes					(connection, argc, argv);
		else if (request=="gettradeconditions")					perform_gettradeconditions				(connection, argc, argv);
		else if (request=="snapshot")							perform_snapshot						(connection, argc, argv);
		else if (request=="subscribe")							perform_subscribe						(connection, argc, argv);
		else if (request=="subscribe_L1_tags")					perform_subscribe_L1_tags				(connection, argc, argv);
		else if (request=="subscribe_oneMBL")					perform_subscribe_oneMBL				(connection, argc, argv);
		else if (request=="subscribe_oneMBL_and_mergeLayers")	perform_subscribe_oneMBL_and_mergeLayers(connection, argc, argv);
		else if (request=="subscribe_MBL")						perform_subscribe_MBL					(connection, argc, argv);
		else if (request=="async_snapshot")						perform_async_snapshot					(connection, argc, argv);
		else if (request=="market_status")						perform_market_status					(connection, argc, argv);
		else if (request=="histo_intraday_extended")			perform_histo_intraday_extended			(connection, argc, argv);
		else if (request=="histo_intraday_extended_N_ticks")	perform_histo_intraday_extended_N_ticks	(connection, argc, argv);
		else if (request=="quotdownload")						perform_quotdownload					(connection, argc, argv);
		else if (request=="subscribe_MBO")						perform_subscribe_MBO					(connection, argc, argv);
		else if (request=="subscribe_instruments_MBO")			perform_subscribe_instruments_MBO		(connection, argc, argv);
		else if (request=="getticksizetables")					perform_getticksizetables				(connection, argc, argv);
		else if (request=="feed_status")						perform_subscribe_feed_status			(connection, argc, argv);
		else if (request=="subscribe_L1_by_MIC")				perform_subscribe_L1_by_MIC				(connection, argc, argv);
		else if (request=="subscribe_L2_by_MIC")				perform_subscribe_L2_by_MIC				(connection, argc, argv);
		else if (request=="price_instruments")					perform_price_instruments				(connection, argc, argv);
		else if (request=="subscribe_NEWS")						perform_subscribe_NEWS					(connection, argc, argv);
		else if (request=="newslookup")							perform_newslookup						(connection, argc, argv);
		else if (request=="histo_news")							perform_histo_newsdownload				(connection, argc, argv);
		else if (request=="bars")								perform_download_intraday_bars_ext		(connection, argc, argv);
		else if (request=="dl_and_sub_histo_intraday_extended")	perform_dl_and_sub_histo_intraday_extended(connection, argc, argv);
		else if (request=="histo_daily_ext")					perform_histo_daily_ext					(connection, argc, argv);
		else if (request=="get_generic_tag_by_source_id")		perform_get_generic_tag_by_source_id	(connection, argc, argv);
		else {
			usage("unknown request: "+request);
		}

		//
		// stop the network connection and shutdown the API
		//
		FEEDOS_LOG (User, Info, "stopping");
		connection.disconnect();
		FeedOS::API::shutdown();

	} catch (std::exception & e) {
		cerr << e.what()<< endl;
	}

	return 0;
}
