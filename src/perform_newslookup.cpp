
/********************************************************/
/** FeedOS sample client code                          **/
/**                                                    **/
/** using "lookup" request to browse news			   **/
/** (with optional filtering/formatting)               **/
/**                                                    **/
/** QuantHouse 2013                                    **/
/********************************************************/


#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>

using namespace FeedOS;	
//using namespace FeedOS::Types;	

/** \cond refguide
 * To perform a News Lookup request in FeedOS API C++, you need to provide a set of criteria that
 * acts as filters on news. News will be returned from newest to oldest with a maximum number of hit,
 * that can be specified in the LookupNews request, a maximum value is also set on server side.
 *
 * If a news matches the query, it is returned along with the requested format,
 * as described in the sample below:
 *
 * <ol><li>Add criteria filters specifying the search among news:</li></ol>
 * \snippet perform_newslookup.cpp snippet_news_lookup_filter
 *
 * <ol><li>List the attributes to retrieve:</li></ol>
 * \snippet perform_newslookup.cpp snippet_news_format_attr
 *
 * <ol><li>Use the FeedOS API object to perform the lookup:</li></ol>
 * \snippet perform_newslookup.cpp snippet_news_lookup_req
 *
 * \endcond
 */
void perform_newslookup (FeedOS::API::Connection & connection, int /*argc*/, char * /*argv*/[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_newslookup");	

	uint16 max_hits = 10;
	
#if 1
	//![snippet_news_lookup_filter]
	FeedOS::Types::ListOfNewsItem news_criterias;
	// Lookup is case insensitive and in general case, all string criterias should be UTF-8 encoded
	// specifying multiple values for the same NewsItem will lead to a logical OR on the server side
	//
	// matching rules description
	// 1) string rule is case insensitive
	// 2) Timestamp rule is greater than
	// 3) basic types rule is equal

	Timestamp from_midnight(Timestamp::now_utc());
	from_midnight.reset_time();
	news_criterias.push_back (NewsItem_OrigUTCTime (from_midnight));	//	AND		OrigUTCTime is older than midnight
	//![snippet_news_lookup_filter]
#else
	FeedOS::Types::ListOfNewsItem filter;
#endif

	// the list of attributes we are interested in, result news will have only the specified items
	//![snippet_news_format_attr]
	FeedOS::Types::ListOfNewsItemId news_format;
	news_format.push_back		( FeedOS::TAG_OrigUTCTime );
	news_format.push_back		( FeedOS::TAG_Submitter );
	news_format.push_back		( FeedOS::TAG_Headline );
	news_format.push_back		( FeedOS::TAG_Urgency );
	news_format.push_back		( FeedOS::TAG_Category );
	//![snippet_news_format_attr]

	//![snippet_news_lookup_req]
	ListOfNewsData result_news;

	// 'result_news' will contain at most maxHits news, and most recent news will come first
	ReturnCode rc =
		API_NEWS_LookupNews (
									connection,
									// outputs
									result_news,
									// inputs
									news_criterias,
									news_format,
									max_hits 
								);

	if (rc != RC_OK) 
	{
		std::cerr << "lookup error, rc=" << error_string(rc) << std::endl;
	}
	else 
	{
		std::cerr << "lookup ok, nb_hits=" << static_cast<unsigned int>(result_news.size()) << std::endl;
		FeedOS::Timestamp dummy;
		print_news (std::cout, result_news, dummy);
	}
	//![snippet_news_lookup_req]
}
