
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** subscribing to "News"		   **/
/**                                **/
/** QuantHouse 2013                **/
/************************************/
#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

/** \cond refguide
 * To perform a News subscription in FeedOS� API C++, you need to provide a set of criteria that
 * acts as filter, a format can be specified to craft news (empty format, means all items will be
 * sent).
 *
 * If a news matches the criteria on server side, it is returned along with the requested format,
 * as described in the sample below:
 *
 * <ol><li>Implement the \c FeedOS::INTERFACE_NEWS_SubscribeNews_streaming interface
 * whose virtual methods are called when the events are received:</li></ol>
 * \snippet perform_subscribe.cpp snippet_sub_news_consumer
 *
 * <ol><li>Add criteria filters specifying the search among news:</li></ol>
 * \snippet perform_subscribe_NEWS.cpp snippet_news_subscribe_criterias
 *
 * <ol><li>List the attributes to retrieve:</li></ol>
 * \snippet perform_subscribe_NEWS.cpp snippet_news_subscribe_format
 *
 * <ol><li>Use the FeedOS API object to perform the lookup:</li></ol>
 * \snippet perform_subscribe_NEWS.cpp snippet_news_subscribe_subscription
 *
 * \endcond
 */

//![snippet_sub_news_consumer]	
class NewsPrinter : public virtual FeedOS::INTERFACE_NEWS_SubscribeNews_streaming
{
public:
	NewsPrinter ()
	{}

	void response_NEWS_SubscribeNews_Started ()
	{
		std::cerr << "SubscribeNews_Started"<<std::endl;
	}

	void response_NEWS_SubscribeNews_Failed (FeedOS::ReturnCode rc)
	{
		std::cerr << "SubscribeNews_Failed, rc="<<rc<<std::endl;
	}

	void aborted_NEWS_SubscribeNews (FeedOS::ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeNews, rc="<<rc<<std::endl;
	}

	virtual void notif_NewsData	(FeedOS::Types::ListOfNewsData const & news)
	{
		// news get printed to the console
		static FeedOS::Timestamp dummy;
		print_news(std::cout, news, dummy, true);
	}
};
//![snippet_sub_news_consumer]	

//
//
//    MAIN function (start the subscription and wait for ENTER key to be pressed)
//
//
void perform_subscribe_NEWS (FeedOS::API::Connection & connection, int /*argc*/, char * /*argv*/[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_NEWS");	
	
	NewsPrinter printer;
	FeedOS::API_NEWS_SubscribeNews_delegate req(printer);

	//![snippet_news_subscribe_criterias]
	// news matching is case insensitive and in general case, all string criterias should be UTF-8 encoded
	// specifying multiple values for the same NewsItem will lead to a logical OR on the server side
	//
	// matching rules description
	// 1) string rule is case insensitive
	// 2) Timestamp rule is greater than
	// 3) basic types rule is equal
	FeedOS::Types::ListOfNewsItem 	news_criteria;
	FeedOS::Timestamp news_sub_time(FeedOS::Timestamp::now_utc());
	news_sub_time.add_minutes(-20); // 20 minutes ago 
	news_criteria.push_back	( FeedOS::NewsItem_OrigUTCTime(news_sub_time) );
	//news_criteria.push_back	( FeedOS::NewsItem_Headline("OIL") );
	//news_criteria.push_back	( FeedOS::NewsItem_Body("OIL") );
	//news_criteria.push_back	( FeedOS::NewsItem_LanguageCode("en") );
	//news_criteria.push_back	( FeedOS::NewsItem_LanguageCode("fr") );
	//![snippet_news_subscribe_criterias]	

	//![snippet_news_subscribe_format]
	FeedOS::Types::ListOfNewsItemId news_format;
	news_format.push_back		( FeedOS::TAG_Submitter );
	news_format.push_back		( FeedOS::TAG_Headline );
	news_format.push_back		( FeedOS::TAG_OrigUTCTime );
	news_format.push_back		( FeedOS::TAG_Urgency );
	news_format.push_back		( FeedOS::TAG_Category );
	news_format.push_back		( FeedOS::TAG_Body );
	//![snippet_news_subscribe_format]	

	//![snippet_news_subscribe_subscription]
	// start the subscription (asynchronous version)
	FeedOS::ReturnCode rc = req.sync_start (connection, news_criteria, news_format );

	if ( FeedOS::RC_OK != rc ) 
	{
		std::cerr << "sync_start error, rc="<< FeedOS::error_string(rc) <<std::endl;
	} 
	else 
	{
		getchar(); // wait for user input
	}
	req.stop (); // stop subscription
	//![snippet_news_subscribe_subscription]
}
