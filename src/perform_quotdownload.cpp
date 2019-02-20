
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieving instrument data (referential+quotation) **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

//![snippet_quot_download_receiver]
class QuotDownloadPrinter:
		public virtual INTERFACE_QUOTATION_DownloadInstruments_streaming
//![snippet_quot_download_receiver]
{
	std::ostream &	m_out;
	bool			m_opt_verbose;
	bool			m_opt_show_progress;
	bool			m_opt_print_syntax;
	bool			m_is_running;

	void show_progress ();

//	void dump_instr_data_one_line_PRETTY	(InstrumentData const & instr_data);
	void dump_instr_data_one_line_RAW		(InstrumentData const & instr_data);
	void dump_instr_data_one_line			(InstrumentData const & instr_data)
	{
		dump_instr_data_one_line_RAW	(instr_data);
	}

	unsigned int	m_counter_nb_instrument;

	FOSMarketId		m_current_branch_MIC;
	std::string		m_current_branch_CFICODE;
	std::string		m_current_branch_SECTYPE;

public:
	QuotDownloadPrinter (	std::ostream & out,
							bool opt_verbose, 
							bool opt_show_progress,
							bool opt_print_syntax
						)
		:m_out					(out)
		,m_opt_verbose			(opt_verbose)
		,m_opt_show_progress	(opt_show_progress)
		,m_opt_print_syntax		(opt_print_syntax)
		,m_is_running			(false)
	{}

	bool is_running() const { return m_is_running; }

	FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadInstruments_streaming
};

//![snippet_quot_download_started]
void QuotDownloadPrinter::response_QUOTATION_DownloadInstruments_Started(
		Timestamp const & inLastActivityTimestamp)
{
	if (m_opt_verbose) {
		std::cerr << "started..." << std::endl;
	}

	// download is starting ...
	// hint: store the "inLastUpdateTimestamp" and use this with -since next
	// time to query only new/modified instruments
	std::cout << "activity timestamp: " << inLastActivityTimestamp << std::endl;

	m_counter_nb_instrument = 0;
	m_is_running = true;
}
//![snippet_quot_download_started]

//![snippet_quot_download_failed]
void QuotDownloadPrinter::response_QUOTATION_DownloadInstruments_Failed(
		ReturnCode rc)
{
	std::cerr << "Download_Failed, rc=" << error_string(rc) << std::endl;
	m_is_running = false;
}
//![snippet_quot_download_failed]

//![snippet_quot_download_aborted]
void QuotDownloadPrinter::aborted_QUOTATION_DownloadInstruments(
		ReturnCode rc)
{
	if (RC_OK != rc) {
		std::cerr << "\naborted, rc=" << error_string(rc) << std::endl;
	} else {
		if (m_opt_verbose) {
			std::cerr << "\nfinished" << std::endl;
		}
	}
	m_is_running=false;
}
//![snippet_quot_download_aborted]

//![snippet_quot_download_branchbegin]
void QuotDownloadPrinter::notif_BranchBegin(
		MarketBranchId const & inBranch,
		uint32 inCurrentQuantity,
		uint32 inSelectedQuantity)
{
	if (m_opt_verbose) {
		FOSMarketId market_id	= inBranch.getMarketId();
		std::string cficode		= inBranch.getCFICode();
		std::string sectype		= inBranch.getSecurityType();
		std::cerr <<
			"*** BranchBegin:"
			" MIC=" << market_id.to_str() <<
			" CFICode=" << cficode <<
			" SecurityType=" << sectype <<
			'\t' << inSelectedQuantity <<
			'/' << inCurrentQuantity // number of instruments in this branch
			<< std::endl;
	}

	m_current_branch_MIC		= inBranch.getMarketId();
	m_current_branch_CFICODE	= inBranch.getCFICode();
	m_current_branch_SECTYPE	= inBranch.getSecurityType();
}
//![snippet_quot_download_branchbegin]

//![snippet_quot_download_instruments]
void QuotDownloadPrinter::notif_Instruments(
		ListOfInstrumentData const & inInstruments)
{
	m_counter_nb_instrument += (unsigned int)inInstruments.size();
	show_progress();
	for (ListOfInstrumentData::const_iterator it = inInstruments.begin();
			it != inInstruments.end(); ++it)
	{
		InstrumentData const & instr_data = *it;
		dump_instr_data_one_line(instr_data);
	}
}
//![snippet_quot_download_instruments]

void QuotDownloadPrinter::dump_instr_data_one_line_RAW (InstrumentData const & instr_data)
{
	FOSInstrumentCode internal_instr_code = instr_data.getCode();

	m_out
		<< internal_instr_code
		<< "\tFOSMarketId=" << market_id_internal2iso (m_current_branch_MIC)
		<< "\tCFICode=" << m_current_branch_CFICODE
		<< "\tSecurityType=" << m_current_branch_SECTYPE
		;

	// referential data 
	{
		ListOfReferentialAttribute const & attributes = instr_data.getAttributes();
		for (ListOfReferentialAttribute::const_iterator it = attributes.begin(); it != attributes.end(); ++it) {
			ReferentialAttribute const & attrib = *it;
			TagNumber tag_num = attrib.getNum();
			Any const & tag_value = attrib.getValue();

			m_out << '\t';	
			tag_num2str (tag_num, m_out);
			m_out << '=';
			if (m_opt_print_syntax) {
				tag_value.dump (m_out, m_opt_print_syntax);
			} else {
				pretty_print_tagvalue (m_out, tag_num, tag_value);
			}
		}
	}

	// quotation data
	{
		ListOfQuotationVariable const & variables = instr_data.getValues();
		for (ListOfQuotationVariable::const_iterator it = variables.begin(); it != variables.end(); ++it) {
			ReferentialAttribute const & attrib = *it;
			TagNumber tag_num = attrib.getNum();
			Any const & tag_value = attrib.getValue();

			m_out << '\t';	
			tag_num2str (tag_num, m_out);
			m_out << '=';	
			tag_value.dump (m_out, m_opt_print_syntax);
		}
	}

	// TODO ?
	// OrderBook const & order_book = instr_data.getOrderBook();

	m_out << '\n';
}


void QuotDownloadPrinter::show_progress ()
{
	if (m_opt_show_progress) {
		std::cerr << "TOTAL: "<<m_counter_nb_instrument<<" \r"<<std::flush;
	}
}

/** \cond refguide
 * This sample illustrates how to implement the quotation download request to
 * retrieve referential data (optionally) and quotation data using branches
 * specification.
 *
 * <ol><li>Implement the \c INTERFACE_QUOTATION_DownloadInstruments_streaming
 * interface whose virtual methods are called when the events are received:
 * </li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_receiver
 *
 * <ol><li>The started callback is called when the server has accepted the
 * request. The given timestamp can be used to retrieve only new or modified
 * instruments on a subsequent request:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_started
 *
 * <ol><li>The failed callback is called if the server rejects the request. The
 * given return code indicates the rejection reason:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_failed
 *
 * <ol><li>The aborted callback is called when the download is over (\c RC_OK),
 * or when an error occurs:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_aborted
 *
 * <ol><li>The \c BranchBegin callback marks the beginning of a new instrument
 * branch; until the next \c BranchBegin notification, all following
 * \c Instruments notifications will refer to instruments belonging to this
 * branch:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_branchbegin
 *
 * <ol><li>The \c Instruments callback conveys the requested data:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_instruments
 *
 * <ol><li>Now that the receiver is implemented, set the input parameters
 * according to your needs. First set the branches you are interested in:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_branches
 *
 * <ol><li>Referential tags can be set to get referential data along with the
 * quotation data:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_ref_attr
 *
 * <ol><li>Set the quotation tags you are interested in. Only these tags will
 * be retrieved:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_quot_attr
 *
 * <ol><li>Instantiate the delegate that will handle the request, giving it
 * an instance of your callbacks handler:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_delegate
 *
 * <ol><li>Start the request:</li></ol>
 * \snippet perform_quotdownload.cpp snippet_quot_download_request
 *
 * As processing is asynchronous, implement a mechanism that will wait for
 * the subscription to terminate (aborted callback). Note that, even if we
 * called \c sync_start, the callbacks are handled asynchronously; the
 * \c sync_start method only waits for the server response (whether the request
 * is accepted or not and why).
 * \endcond
 */
void perform_quotdownload (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	FEEDOS_SCOPER (User, "perform_quotdownload");	

	ListOfMarketBranchId		param_TargetBranches;			// if empty then all branches are retrieved
	ListOfReferentialAttribute	param_FilteringAttributes;		// if empty then no filtering is done
	ListOfReferentialTagNumber	param_RefTags;					// if empty then all attributes are sent
	ListOfQuotationTagNumber	param_QuotTags;					// if empty then all variables are sent
	Timestamp					param_LastActivityTimestamp;	// reserved for future use
	int8						param_OrderBookDepth = 0;		// reserved for future use

	//
	// [optional] list of branches to download. Some basic wildcarding is supported.
	//
	//![snippet_quot_download_branches]
	param_TargetBranches.push_back(MarketBranchId(MARKET_ID_unknown, "",
			"MRI")); // download all indices
	param_TargetBranches.push_back(MarketBranchId(MARKET_ID_unknown, "",
			"E")); // download all equities
	param_TargetBranches.push_back(MarketBranchId(MARKET_ID_unknown, "",
			"F")); // download all futures (including MLEG-Fxxxxx)
	//![snippet_quot_download_branches]


	//
	// [optional] list of attributes to retrieve
	//
	//![snippet_quot_download_ref_attr]
	param_RefTags.push_back(TAG_LocalCodeStr);
	param_RefTags.push_back(TAG_Symbol);
	param_RefTags.push_back(TAG_ISIN);
	//![snippet_quot_download_ref_attr]

	//
	// [optional] list of variables to retrieve
	//
	//![snippet_quot_download_quot_attr]
	param_QuotTags.push_back(TAG_LastTradeTimestamp);
	param_QuotTags.push_back(TAG_LastPrice);
	param_QuotTags.push_back(TAG_DailyTotalVolumeTraded);
	//![snippet_quot_download_quot_attr]

	bool opt_verbose = false;
	if ( (argc > 1) && !strcmp(argv[1],"-v") ) {
		opt_verbose=true;
		++argv;
		--argc;
	}

	/*
	if ( (argc > 2) && !strcmp(argv[1],"-since") ) {
		if (!param_LastUpdateTimestamp.set_from_string (argv[2])) {
			std::cerr << "invalid date"<<std::endl;
			return;
		}
		argv+=2;
		argc-=2;
	}
	*/

	if (argc>1) {
		std::cerr <<"usage: [-v]"
//			" [-since DATE]"
			<<std::endl;
		return;
	}

	QuotDownloadPrinter	printer (	std::cout,			// output stream
									opt_verbose,	// "VERBOSE"
									opt_verbose,	// "SHOW PROGRESS"
									opt_verbose		// "PRINT SYNTAX"
								);

	//![snippet_quot_download_delegate]
	API_QUOTATION_DownloadInstruments_delegate req(printer);
	//![snippet_quot_download_delegate]

	// start the subscription (synchronous version)
	//![snippet_quot_download_request]
	ReturnCode rc = req.sync_start(
			connection,
			param_TargetBranches,
			param_FilteringAttributes,
			param_RefTags,
			param_QuotTags,
			param_LastActivityTimestamp,
			param_OrderBookDepth);
	//![snippet_quot_download_request]

	if (rc != RC_OK) {
		std::cerr << "sync_start error, rc=" << error_string(rc) << std::endl;
	} else {
		while (req.subscription_is_in_progress()) {
			API::msleep (1000);
		}
	}
}
