
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_FILTERED_BASE_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_FILTERED_BASE_H

#ifndef FEEDOS_BASE_DATE_H
#  include "../base/date.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H
#	include "../comm/MulticastFrameSplitter.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#	include "../comm/MulticastFeedTools.h"
#endif

namespace FeedOS {

	class FeedReplay_filtered_base 
	{
	public:
		FeedReplay_filtered_base();
		FeedReplay_filtered_base(MulticastFeedCursor_observer & observer);

		virtual ~FeedReplay_filtered_base() {}

		// TimeStampRange accessor
		inline MulticastFeedCursor & getCursor() { return m_Cursor; }

		// TimeStampRange accessor
		inline MulticastFeedBounds & getBounds() { return m_FeedReplayBounds; }

	private:
		FeedReplay_filtered_base(FeedReplay_filtered_base const &);
		FeedReplay_filtered_base const & operator=(FeedReplay_filtered_base const &);

		MulticastFeedCursor				m_Cursor;
		MulticastFeedBounds				m_FeedReplayBounds;
	};
} // namespace FeedOS

#endif // FEEDOS_FRAMEWORK_FEED_REPLAY_FILTERED_BASE_H
