
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** retrieving instrument data (referential+quotation) **/
/**                                                    **/
/** QuantHouse 2006                                    **/
/********************************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>

using namespace std;
using namespace FeedOS;	
using namespace FeedOS::Types;


class NewsDownloadPrinter: public virtual FeedOS::INTERFACE_NEWS_DownloadHistoryNews_streaming
{
	std::ostream &	m_out;
	bool			m_opt_verbose;
	bool			m_opt_show_progress;
	bool			m_is_running;

	size_t			m_nb_news_downloaded;
	Timestamp		m_OriginUTCTime_current;

	void show_progress ();

public:
	NewsDownloadPrinter (	std::ostream & out,
							bool opt_verbose, 
							bool opt_show_progress
						)
		:m_out					(out)
		,m_opt_verbose			(opt_verbose)
		,m_opt_show_progress	(opt_show_progress)
		,m_is_running			(false)
		,m_nb_news_downloaded	(0)
	{}

	bool is_running() const { return m_is_running; }

	FEEDOS_GEN_DECL_INTERFACE_NEWS_DownloadHistoryNews_streaming
};


void NewsDownloadPrinter::response_NEWS_DownloadHistoryNews_Started ()
{
	if (m_opt_verbose) 
	{
		std::cerr << "started..."<<endl;
	}
	m_is_running=true;
}

void NewsDownloadPrinter::response_NEWS_DownloadHistoryNews_Failed (ReturnCode rc)
{
	cerr << "Download_Failed, rc="<<error_string(rc)<<endl;
	m_is_running=false;
}

void NewsDownloadPrinter::aborted_NEWS_DownloadHistoryNews (ReturnCode rc)
{
	if (RC_OK != rc) // normal end of the time limited subscription
	{
		std::cerr << "\naborted, rc="<<error_string(rc)<<endl;
	} 
	else 
	{
		if (m_opt_verbose) 
		{
			std::cerr << "\nfinished"<<endl;
		}
	}
	m_is_running=false;
}

void NewsDownloadPrinter::notif_HistoricalNews(FeedOS::Types::ListOfNewsData const & data)
{
	print_news(std::cout, data, m_OriginUTCTime_current, true);
	m_nb_news_downloaded += data.size();
}


void NewsDownloadPrinter::show_progress ()
{
	if (m_opt_show_progress) 
	{
		std::cerr << "news count= "<<m_nb_news_downloaded<<", current origin_utc_time="<< m_OriginUTCTime_current.str_full_allow_microsec() <<" \r"<<flush;
	}
}

void perform_histo_newsdownload (FeedOS::API::Connection & connection, int /*argc*/, char * /*argv*/[]) 
{
	FEEDOS_SCOPER (User, "perform_histo_newsdownload");	

	// Retrieve historical news for the last two days
	Timestamp OriginUTCTime_begin(Timestamp::now_utc());
	OriginUTCTime_begin.add_days(-2);
	Timestamp OriginUTCTime_end(Timestamp::now_utc());

	NewsDownloadPrinter	printer (	std::cout,	// output stream
									false,		// "VERBOSE"
									false		// "SHOW PROGRESS"
								);

	FeedOS::API_NEWS_DownloadHistoryNews_delegate req (printer);

	// start the subscription (synchronous version)
	FeedOS::ReturnCode rc = req.sync_start (	connection,
												OriginUTCTime_begin,
												OriginUTCTime_end
											);

	if (rc != FeedOS::RC_OK) 
	{
		std::cerr << "sync_start error, rc="<< FeedOS::error_string(rc) << '\n';
	} 
	else 
	{
		while (req.subscription_is_in_progress()) 
		{
			FeedOS::API::msleep (1000);
		}
	}

}
