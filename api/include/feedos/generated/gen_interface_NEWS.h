/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_NEWS_H
#define FEEDOS_generated_INTERFACE_NEWS_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_NEWS_Subscribe_OBSOLETE_streaming \
		virtual void response_NEWS_Subscribe_OBSOLETE_Started (); \
		virtual void response_NEWS_Subscribe_OBSOLETE_Failed (ReturnCode rc); \
		virtual void aborted_NEWS_Subscribe_OBSOLETE (ReturnCode rc); \
		virtual void notif_NewsAdded_OBSOLETE	(FeedOS::Types::News const & inNews); \
		virtual void notif_NewsUpdated_OBSOLETE	(FeedOS::Types::News const & inNews); \
		virtual void notif_NewsRemoved_OBSOLETE	(FeedOS::Types::ListOfNewsId const & inIds); \


	class INTERFACE_NEWS_Subscribe_OBSOLETE_streaming
	{
	public:
		virtual ~INTERFACE_NEWS_Subscribe_OBSOLETE_streaming() {}

		virtual void response_NEWS_Subscribe_OBSOLETE_Started () = 0;
		virtual void response_NEWS_Subscribe_OBSOLETE_Failed (ReturnCode rc) = 0;
		virtual void aborted_NEWS_Subscribe_OBSOLETE (ReturnCode rc) = 0;
		virtual void notif_NewsAdded_OBSOLETE	(FeedOS::Types::News const & inNews) = 0;
		virtual void notif_NewsUpdated_OBSOLETE	(FeedOS::Types::News const & inNews) = 0;
		virtual void notif_NewsRemoved_OBSOLETE	(FeedOS::Types::ListOfNewsId const & inIds) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_NEWS_SubscribeNews_streaming \
		virtual void response_NEWS_SubscribeNews_Started (); \
		virtual void response_NEWS_SubscribeNews_Failed (ReturnCode rc); \
		virtual void aborted_NEWS_SubscribeNews (ReturnCode rc); \
		virtual void notif_NewsData	(FeedOS::Types::ListOfNewsData const & inNews); \


	class INTERFACE_NEWS_SubscribeNews_streaming
	{
	public:
		virtual ~INTERFACE_NEWS_SubscribeNews_streaming() {}

		virtual void response_NEWS_SubscribeNews_Started () = 0;
		virtual void response_NEWS_SubscribeNews_Failed (ReturnCode rc) = 0;
		virtual void aborted_NEWS_SubscribeNews (ReturnCode rc) = 0;
		virtual void notif_NewsData	(FeedOS::Types::ListOfNewsData const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_NEWS_DownloadHistoryNews_streaming \
		virtual void response_NEWS_DownloadHistoryNews_Started (); \
		virtual void response_NEWS_DownloadHistoryNews_Failed (ReturnCode rc); \
		virtual void aborted_NEWS_DownloadHistoryNews (ReturnCode rc); \
		virtual void notif_HistoricalNews	(FeedOS::Types::ListOfNewsData const & inNews); \


	class INTERFACE_NEWS_DownloadHistoryNews_streaming
	{
	public:
		virtual ~INTERFACE_NEWS_DownloadHistoryNews_streaming() {}

		virtual void response_NEWS_DownloadHistoryNews_Started () = 0;
		virtual void response_NEWS_DownloadHistoryNews_Failed (ReturnCode rc) = 0;
		virtual void aborted_NEWS_DownloadHistoryNews (ReturnCode rc) = 0;
		virtual void notif_HistoricalNews	(FeedOS::Types::ListOfNewsData const & inNews) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_NEWS_SubscribeAllNews_streaming \
		virtual void response_NEWS_SubscribeAllNews_Started (); \
		virtual void response_NEWS_SubscribeAllNews_Failed (ReturnCode rc); \
		virtual void aborted_NEWS_SubscribeAllNews (ReturnCode rc); \
		virtual void notif_NewsData	(FeedOS::Types::ListOfNewsData const & inNews); \


	class INTERFACE_NEWS_SubscribeAllNews_streaming
	{
	public:
		virtual ~INTERFACE_NEWS_SubscribeAllNews_streaming() {}

		virtual void response_NEWS_SubscribeAllNews_Started () = 0;
		virtual void response_NEWS_SubscribeAllNews_Failed (ReturnCode rc) = 0;
		virtual void aborted_NEWS_SubscribeAllNews (ReturnCode rc) = 0;
		virtual void notif_NewsData	(FeedOS::Types::ListOfNewsData const & inNews) = 0;

	};
}
#endif
