/*******************************/
/** FeedOS sample client code **/
/**                           **/
/** copyright QuantHouse      **/
/*******************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace FeedOS;
using namespace FeedOS::Types;

//![snippet_dl_bars_receiver]
class IntradayBarsExtPrinter :
		public INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming
//![snippet_dl_bars_receiver]
{
public:
	IntradayBarsExtPrinter(std::ostream & out)
		: m_out(out)
	{}

	virtual ~IntradayBarsExtPrinter() {}

	FEEDOS_GEN_DECL_INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming

private:
	std::ostream &	m_out;
};

//![snippet_dl_bars_started]
void IntradayBarsExtPrinter
::response_QUOTATION_DownloadHistoryIntradayBarsExt_Started()
{
	m_out << "IB\tINSTR"
//![snippet_dl_bars_started]
			<< "\tMARKET_TIMESTAMP"
			<< "\tSERVER_TIMESTAMP"
			<< "\tDURATION"
			<< "\tNB_POINTS"
			<< "\tOPEN"
			<< "\tHIGH"
			<< "\tLOW"
			<< "\tCLOSE"
			<< "\tVOLUME"
			<< "\tVALUES..."
			<< std::endl;
	m_out << "CB\tINSTR"
			<< "\tMARKET_TIMESTAMP"
			<< "\tSERVER_TIMESTAMP"
			<< "\tDURATION"
			<< "\tNB_POINTS"
			<< "\tOPEN"
			<< "\tHIGH"
			<< "\tLOW"
			<< "\tCLOSE"
			<< "\tVOLUME"
			<< "\tVALUES..."
			<< std::endl;
	m_out << "DB\tINSTR"
			<< "\tSERVER_TIMESTAMP"
			<< "\tDURATION"
			<< std::endl;
}

//![snippet_dl_bars_failed]
void IntradayBarsExtPrinter
::response_QUOTATION_DownloadHistoryIntradayBarsExt_Failed(
		ReturnCode rc)
{
	m_out << "download failed, rc=" << error_string(rc) << std::endl;
}
//![snippet_dl_bars_failed]

//![snippet_dl_bars_aborted]
void IntradayBarsExtPrinter
::aborted_QUOTATION_DownloadHistoryIntradayBarsExt(ReturnCode rc)
{
	if (rc != RC_OK)
	{
		m_out << "download aborted, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		m_out << "download done" << std::endl;
	}
}
//![snippet_dl_bars_aborted]

//![snippet_dl_bars_ibars]
void IntradayBarsExtPrinter::notif_IntradayBars(
		ListOfQuotationIntradayBar const & inBars)
{
	for (ListOfQuotationIntradayBar::const_iterator it(inBars.begin()),
			end(inBars.end()); it != end; ++it)
	{
		m_out << "IB\t";
		print_intraday_bar(m_out, *it);
	}
}
//![snippet_dl_bars_ibars]

//![snippet_dl_bars_delete]
void IntradayBarsExtPrinter::notif_DeleteBar(
		FOSInstrumentCode inInstrCode,
		uint16 inServerDuration_seconds,
		Timestamp const & inServerUTCTimestamp_begin)
{
	m_out << "DB"
			<< '\t' << inInstrCode
			<< '\t' << inServerUTCTimestamp_begin
			<< '\t' << inServerDuration_seconds
			<< std::endl;
}
//![snippet_dl_bars_delete]

//![snippet_dl_bars_corrected]
void IntradayBarsExtPrinter::notif_CorrectedBar(
		FeedOS::Types::QuotationIntradayBar const & inBar)
{
	m_out << "CB\t";
	print_intraday_bar(m_out, inBar);
}
//![snippet_dl_bars_corrected]

/** \cond refguide
 * This sample demonstrates how to use the \c DownloadHistoryIntradayBarsExt
 * subscription to download or download then subscribe to historical bars.
 * This request also lets users choose to apply corporate action adjustment
 * factors if necessary.
 *
 * <ol><li>First, implement the \c INTERFACE_QUOTATION_DownloadHistoryIntradayBarsExt_streaming
 * interface whose virtual methods are called when the events are received:</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_receiver
 *
 * <ol><li>The started callback is called when the server accepts the request.
 * </li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_started
 *
 * <ol><li>The failed callback is called if the server rejects the request. The
 * return code indicates the reason of the rejection.</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_failed
 *
 * <ol><li>The aborted callback is called when the download is completed (RC_OK)
 * or when an error occurs (the return code indicates the error).</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_aborted
 *
 * <ol><li>The \c IntradayBars callback conveys historical or real-time
 * data.</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_ibars
 *
 * <ol><li>The \c DeleteBar callback indicates that, due to a trade cancel or
 * correction, a previously sent bar has been deleted.</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_delete
 *
 * <ol><li>The \c CorrectedBar callback indicates that, due to a trade cancel or
 * correction, a previously sent bar has been modified.</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_corrected
 *
 * <ol><li>Create a delegate object giving it an instance of the receiver class.
 * Set the input parameters as needed: list of instrument codes, begin and end
 * timestamp, duration of the bars, types of adjustment factors to apply.
 * Refer to the request documentation for a comprehensive explanation of these
 * parameters.
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_request
 *
 * <ol><li>Even if we called \c sync_start, only the response (success of
 * failure) is synchronous. The other callbacks are handled asynchronously. So
 * users have to implement a mechanism to wait for the end of the download. Or,
 * if a subscription to real-time was requested, the subscription never ends
 * (except in case of errors) and users will stop the subscription themselves by
 * calling \c stop on the delegate object.</li></ol>
 * \snippet perform_download_intraday_bars_ext.cpp snippet_dl_bars_wait
 *
 * \endcond
 */
void perform_download_intraday_bars_ext(API::Connection & connection, int argc, char * argv[])
{
	FEEDOS_SCOPER(User, "perform_download_intraday_bars_ext");

	// Parse args
	if (argc < 6)
	{
		std::cerr <<"? BEGIN_TIMESTAMP END_TIMESTAMP DURATION NB_BARS_BEFORE_BEGIN INSTRUMENTS..." << std::endl;
		return;
	}

	Timestamp begin_ts;
	if (!begin_ts.set_from_string(argv[1]))
	{
		std::cerr << "syntax error for begin timestamp: " << argv[1] << std::endl;
		return;
	}

	Timestamp end_ts;
	if (!end_ts.set_from_string(argv[2]))
	{
		std::cerr << "syntax error for end timestamp: " << argv[2] << std::endl;
		return;
	}

	uint16 const bar_duration = static_cast<uint16 const>(::atoi(argv[3]));
	if (bar_duration == 0)
	{
		std::cerr << "syntax error for duration: " << argv[3] << std::endl;
		return;
	}

	uint16 nb_bars_before_begin;
	std::istringstream iss;
	iss.str(argv[4]);
	iss >> nb_bars_before_begin;
	if (!iss)
	{
		std::cerr << "syntax error for nb_bars_before_begin: " << argv[4] << std::endl;
		return;
	}

	ListOfPolymorphicInstrumentCode codes;
	for (int i = 5; i < argc; ++i)
	{
		codes.push_back(PolymorphicInstrumentCode());
		if (!codes.back().read_from_string(argv[i]))
		{
			std::cerr << "syntax error while for instrument code: " << argv[i] << std::endl;
			return;
		}
	}

	// All adj factor event types are taken into account
	AdjustmentFactorEventTypeMask const adj_factor_types = AdjustmentFactorEventTypeMask_All;

	// In this sample the receiver of the subscription is only a printer
	//![snippet_dl_bars_request]
	IntradayBarsExtPrinter printer(std::cout);
	API_QUOTATION_DownloadHistoryIntradayBarsExt_delegate req(printer);
	ReturnCode rc = req.sync_start(connection, codes, begin_ts, end_ts,
			bar_duration, adj_factor_types, nb_bars_before_begin);
	//![snippet_dl_bars_request]

	//![snippet_dl_bars_wait]
	if (rc != RC_OK)
	{
		std::cerr << "sync_start error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		while (req.subscription_is_in_progress())
		{
			API::msleep(1000);
		}
	}
	//![snippet_dl_bars_wait]
}
