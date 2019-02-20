
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieving referential (i.e. static) data          **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

using namespace FeedOS;	
using namespace FeedOS::Types;

namespace RefDownloadSample
{

//![snippet_ref_download_subclass]
class RefDownloadPrinter:
		public virtual INTERFACE_REFERENTIAL_Download_streaming
//![snippet_ref_download_subclass]
{
	std::ostream &	m_out;
	bool			m_opt_verbose;
	bool			m_opt_show_progress;
	bool			m_opt_raw_mode;
	bool			m_is_running;

	void show_progress ();

	void dump_instr_data_one_line_PRETTY	(InstrumentCharacteristics const & instr_data);
	void dump_instr_data_one_line_RAW		(InstrumentCharacteristics const & instr_data);
	void dump_instr_data_one_line			(InstrumentCharacteristics const & instr_data)
	{
		if (m_opt_raw_mode)	dump_instr_data_one_line_RAW	(instr_data);
		else				dump_instr_data_one_line_PRETTY	(instr_data);
	}

	unsigned int	m_counter_nb_deleted;
	unsigned int	m_counter_nb_created;
	unsigned int	m_counter_nb_modified;

public:
	RefDownloadPrinter (std::ostream & out, bool opt_verbose, bool opt_show_progress, bool opt_raw_mode)
		:m_out					(out)
		,m_opt_verbose			(opt_verbose)
		,m_opt_show_progress	(opt_show_progress)
		,m_opt_raw_mode			(opt_raw_mode)
		,m_is_running			(false)
	{}

	bool is_running() const { return m_is_running; }

	FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_Download_streaming
};


//![snippet_ref_download_started]
void RefDownloadPrinter::response_REFERENTIAL_Download_Started(
		Timestamp const & inLastUpdateTimestamp)
{
	if (m_opt_verbose)
	{
		std::cerr << "started..." << std::endl;
	}

	// download is starting...
	// hint: store the "inLastUpdateTimestamp" and use this with -since next
	// time to query only new/modified instruments
	std::cerr << "timestamp of remote referential data: "
			<< inLastUpdateTimestamp << std::endl;

	m_counter_nb_deleted	=0;
	m_counter_nb_created	=0;
	m_counter_nb_modified	=0;
	m_is_running=true;
}
//![snippet_ref_download_started]

//![snippet_ref_download_failed]
void RefDownloadPrinter::response_REFERENTIAL_Download_Failed(ReturnCode rc)
{
	std::cerr << "Download_Failed, rc=" << error_string(rc) << std::endl;
	m_is_running=false;
}
//![snippet_ref_download_failed]

//![snippet_ref_download_aborted]
void RefDownloadPrinter::aborted_REFERENTIAL_Download(ReturnCode rc)
{
	if (RC_OK != rc)
	{
		std::cerr << "\naborted, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		if (m_opt_verbose)
		{
			std::cerr << "\nfinished" << std::endl;
		}
	}
	m_is_running=false;
}
//![snippet_ref_download_aborted]

//![snippet_ref_download_branchbegin]
void RefDownloadPrinter::notif_BranchBegin(
		MarketBranchId const & inBranch,
		uint32 inCurrentQuantity,
		uint32 inDeletedQuantity,
		uint32 inCreatedQuantity,
		uint32 inModifiedQuantity)
{
	if (m_opt_verbose)
	{
		FOSMarketId market_id	= inBranch.getMarketId();
		std::string cficode		= inBranch.getCFICode();
		std::string sectype		= inBranch.getSecurityType();
		std::cerr << 
			"*** BranchBegin:"
			" MIC="<<market_id.to_str()<<
			" CFICode="<<cficode<<
			" SecurityType="<<sectype<<
			// how many "deleted" instruments you will receive
			'\t' << inDeletedQuantity <<
			// how many "created" instruments you will receive
			'+' << inCreatedQuantity <<
			// how many "modified" instruments you will receive
			'+' << inModifiedQuantity <<
			// the total number of instruments in this branch
			'/' << inCurrentQuantity
			<< std::endl;
	}
}
//![snippet_ref_download_branchbegin]

//![snippet_ref_download_deleted]
void RefDownloadPrinter::notif_InstrumentsDeleted(
		ListOfFOSInstrumentCode const & inInternalCodes)
{
	m_counter_nb_deleted += (unsigned int)inInternalCodes.size();
	show_progress();
	for (ListOfFOSInstrumentCode::const_iterator it =
			inInternalCodes.begin(); it != inInternalCodes.end(); ++it)
	{
		FOSInstrumentCode const & internal_instr_code = *it;
		m_out << "DELETED\t" << internal_instr_code << '\n';
	}
}
//![snippet_ref_download_deleted]

//![snippet_ref_download_created]
void RefDownloadPrinter::notif_InstrumentsCreated(
		ListOfInstrumentCharacteristics const & inInstruments)
{
	m_counter_nb_created += (unsigned int)inInstruments.size();
	show_progress();
	for (ListOfInstrumentCharacteristics::const_iterator it =
			inInstruments.begin(); it != inInstruments.end(); ++it)
	{
		InstrumentCharacteristics const & instr_data = *it;
		m_out << "CREATED\t";
		dump_instr_data_one_line(instr_data);
		m_out << '\n';
	}
}
//![snippet_ref_download_created]

//![snippet_ref_download_modified]
void RefDownloadPrinter::notif_InstrumentsModified(
		ListOfInstrumentCharacteristics const & inInstruments)
{
	m_counter_nb_modified += (unsigned int)inInstruments.size();
	show_progress();
	for (ListOfInstrumentCharacteristics::const_iterator it =
			inInstruments.begin(); it != inInstruments.end(); ++it)
	{
		InstrumentCharacteristics const & instr_data = *it;
		m_out << "MODIFIED\t";
		dump_instr_data_one_line(instr_data);
		m_out << '\n';
	}
}
//![snippet_ref_download_modified]


void RefDownloadPrinter::dump_instr_data_one_line_RAW (InstrumentCharacteristics const & instr_data)
{
	FOSInstrumentCode internal_instr_code = instr_data.getCode();
	ListOfReferentialAttribute const & attributes = instr_data.getAttributes();

	m_out << internal_instr_code;

	for (ListOfReferentialAttribute::const_iterator it = attributes.begin();
		 it != attributes.end(); ++it)
	{
		ReferentialAttribute const & attrib = *it;
		TagNumber tag_num = attrib.getNum();
		Any const & tag_value = attrib.getValue();

		m_out << '\t';	
		if (tag_num == TAG_FOSMarketId) {
			// pretty print the market_id (string flavour rather than the internal numeric value)
			FOSMarketId market_id (tag_value.get_uint16());
			market_id.dump (m_out);
		} else {
			tag_value.dump (m_out, false);
		}
	}
}


void RefDownloadPrinter::dump_instr_data_one_line_PRETTY (InstrumentCharacteristics const & instr_data)
{
	FOSInstrumentCode internal_instr_code = instr_data.getCode();
	ListOfReferentialAttribute const & attributes = instr_data.getAttributes();

	m_out << internal_instr_code;

	int maturity_year	= 0;
	int maturity_month	= 0;
	int maturity_day	= 0;

	for (ListOfReferentialAttribute::const_iterator it = attributes.begin();
		 it != attributes.end(); ++it)
	{
		ReferentialAttribute const & attrib = *it;
		TagNumber tag_num = attrib.getNum();
		Any const & tag_value = attrib.getValue();

		// special processing for "maturity"
		if			(tag_num == TAG_MaturityYear)	{ maturity_year		= tag_value.get_uint16();
		} else if	(tag_num == TAG_MaturityMonth)	{ maturity_month	= tag_value.get_uint8();
		} else if	(tag_num == TAG_MaturityDay)	{ maturity_day		= tag_value.get_uint8();
		} else {
			// all other tags
			m_out << '\t';	
			tag_num2str (tag_num, m_out);
			m_out << "=(";	
			pretty_print_tagvalue (m_out, tag_num, tag_value);
			m_out << ')';
		}
	}

	// post-processing: print maturity in a compact way
	char maturity_str[32];
	if (0!=maturity_year) {
		if (0!=maturity_month) {
			if (0!=maturity_day) {
				sprintf (maturity_str, "%04i-%02i-%02i", (int)maturity_year,
						 (int)maturity_month, (int)maturity_day);
			} else {
				sprintf (maturity_str, "%04i-%02i", (int)maturity_year,
						 (int)maturity_month);
			}
		} else {
			sprintf (maturity_str, "%04i", (int)maturity_year);
		}
		m_out << "\tMaturity=("<<maturity_str<<')';
	}

}

void RefDownloadPrinter::show_progress ()
{
	if (m_opt_show_progress) {
		std::cerr << "TOTAL: deleted=" << m_counter_nb_deleted
				  << " created=" << m_counter_nb_created
				  << " modified=" << m_counter_nb_modified << " \r" << std::flush;
	}
}

} // namespace RefDownloadSample


/** \cond refguide
 * To perform a referential download in FeedOS API C++, you need to implement an
 * interface and several callbacks that handle the request and response, then adjust
 * the returned data's attributes and filter the result, as described in the
 * procedure below.
 *
 * This sample prints the instruments belonging to the referential database along with
 * their tags on the standard output.
 *
 * <ol><li>Implement the \c FeedOS::INTERFACE_REFERENTIAL_Download_streaming interface
 * whose virtual methods are called when the download is performed.</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_subclass
 * 
 * <ol><li>Implement the started callback that is called when the server acknowledges the query,
 * as shown below:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_started
 *
 * <ol><li>Implement the failed callback to be called if there is an error during the query:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_failed
 *
 * <ol><li>Implement the aborted callback to be called when the referential download completes
 * (return code is \c RC_OK) or if an error occurs during the download:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_aborted
 *
 * <ol><li>Implement the branch begin callback to be called for each requested branch
 * with details about the referential download:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_branchbegin
 *
 * <ol><li>Implement the created instruments' callback to be called for each created instrument:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_created
 *
 * <ol><li>Implement the modified instruments' callback to be called for each modified
 * instrument:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_modified
 *
 * <ol><li>Implement the deleted instruments' callback to be called for each deleted instrument,
 * as shown below:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_deleted
 *
 * <ol><li>Customize the instruments to be retrieved, by adjusting the available parameters:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_params
 *
 * <ol><li>Limit the data to be downloaded, by choosing the markets, as shown in the example below.
 * Please notice that the object \c MarketBranchId can appear in two types of reference – requests/subscriptions
 * and callbacks. Depending on the reference type, you can use this object as a branch filter
 * or branch identifier. In the following sample, MarketBranchId acts as a filter and it is used
 * to distinguish among the branches to be downloaded (such as XPAR, FUT, CB or MRI).
 * However, in the callback previously described, \c MarketBranchId behaves as a
 * referential branch identifier (based on the MIC, CFICode and SecurityType)</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_custom
 *
 * <ol><li>Customize the attributes to be downloaded:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_attr
 *
 * <ol><li>Filter the attributes to be downloaded:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_attr_filter
 *
 * <ol><li>Register the object whose callbacks will be called, as shown below:</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_reg
 *
 * <ol><li>Perform the request. The request is synchronous: the process waits for the server to reply
 * and blocks the calling thread until the query completes.</li></ol>
 * \snippet perform_refdownload.cpp snippet_ref_download_req
 *
 * \endcond
 */
void perform_refdownload (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	FEEDOS_SCOPER (User, "perform_refdownload");	

	//![snippet_ref_download_params]
	// if empty, then all the branches are retrieved
	ListOfMarketBranchId		param_TargetBranches;
	// if empty, then no filtering is applied
	ListOfReferentialAttribute	param_FilteringAttributes;
	// if empty, then all the attributes are sent
	ListOfReferentialTagNumber	param_Format;
	// if null, then all the instruments are sent, regardless of their
	// modification date
	Timestamp					param_LastUpdateTimestamp;
	bool						param_SendCreated	= true;
	bool						param_SendModified	= true;
	bool						param_SendDeleted	= true;
	//![snippet_ref_download_params]


#if 0
	//![snippet_ref_download_custom]
	//
	// [optional] list of branches to download. Some basic wildcarding is supported.
	//
	{
		// download French equities
		param_TargetBranches.push_back(MarketBranchId(
				market_id_iso2internal ("XPAR"), "", "E"));
		// download Eurex Futures
		param_TargetBranches.push_back(MarketBranchId(
				MARKET_ID_XEUR, "FUT", ""));
		// download all the convertible bonds
		param_TargetBranches.push_back(MarketBranchId(
				MARKET_ID_unknown, "CB", ""));
		// download all the indices
		param_TargetBranches.push_back(MarketBranchId(
				MARKET_ID_unknown, "", "MRI"));
	}
	//![snippet_ref_download_custom]
#endif

#if 0
	//![snippet_ref_download_attr_filter]
	//
	// [optional] list of attributes to filters
	//
	param_FilteringAttributes.push_back(ReferentialAttribute_SecurityType(
			"FUT")); // Type=Future
	param_FilteringAttributes.push_back(ReferentialAttribute_MaturityYear(
			2008));	// AND expiry in 2008
	//![snippet_ref_download_attr_filter]
#endif

	//![snippet_ref_download_attr]
	//
	// [optional] list of attributes to retrieve
	//
	{
		// can be induced from "notif_BranchBegin" (or simply retrieved from the
		// FOSInstrumentCode)
		param_Format.push_back(TAG_FOSMarketId);
		// can be induced from "notif_BranchBegin"
		param_Format.push_back(TAG_CFICode);
		// can be induced from "notif_BranchBegin"
		param_Format.push_back(TAG_SecurityType);

		// this is used (along with FOSMarketId) to build a
		// LocalInstrumentCode/PolymorphicInstrumentCode
		param_Format.push_back(TAG_LocalCodeStr);
		// exchange symbol
		param_Format.push_back(TAG_Symbol);
		// verbose description
		param_Format.push_back(TAG_Description);
		// ISIN
		param_Format.push_back(TAG_ISIN);

		// for derivatives
		param_Format.push_back(TAG_MaturityYear);
		param_Format.push_back(TAG_MaturityMonth);
		param_Format.push_back(TAG_MaturityDay);
		param_Format.push_back(TAG_StrikePrice);
	}
	//![snippet_ref_download_attr]


	bool opt_verbose = false;
	if ( (argc > 1) && !strcmp(argv[1],"-v") ) {
		opt_verbose=true;
		++argv;
		--argc;
	}

	if ( (argc > 2) && !strcmp(argv[1],"-since") ) {
		if (!param_LastUpdateTimestamp.set_from_string (argv[2])) {
			std::cerr << "invalid date" << std::endl;
			return;
		}
		argv+=2;
		argc-=2;
	}

	bool opt_raw = false;
	if ( (argc > 1) && !strcmp(argv[1],"-raw") ) {
		opt_raw=true;
		++argv;
		--argc;
	}

	if (argc>1) {
		std::cerr <<"usage: [-v] [-raw] [-since DATE]"<< std::endl;
		return;
	}

	//![snippet_ref_download_reg]
	RefDownloadSample::RefDownloadPrinter printer(
			std::cout, // output stream
			opt_verbose, // "VERBOSE"
			opt_verbose, // "SHOW PROGRESS"
			opt_raw); // "RAW MODE"

	API_REFERENTIAL_Download_delegate req(printer);
	//![snippet_ref_download_reg]

	//![snippet_ref_download_req]
	// start the subscription (synchronous version)
	ReturnCode rc = req.sync_start(
			connection,
			param_TargetBranches,
			param_FilteringAttributes,
			param_Format,
			param_LastUpdateTimestamp,
			param_SendCreated,
			param_SendModified,
			param_SendDeleted);

	if (rc != RC_OK)
	{
		std::cerr << "sync_start error, rc=" << error_string(rc)
				<< std::endl;
	}
	else
	{
		while (req.subscription_is_in_progress())
		{
			API::msleep(1000);
		}
	}
	//![snippet_ref_download_req]

}
