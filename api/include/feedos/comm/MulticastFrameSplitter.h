
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H
#define FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H

#ifndef FEEDOS_COMM_PDU_CONSUMER_H
#  include "PDU_consumer.h"
#endif

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#	include "MulticastFeedTools.h"
#endif

namespace FeedOS {
	class PDU_consumer;
	// Multicast Frame splitter class 
	class MulticastFrameSplitter 
	{
	public:
		MulticastFrameSplitter();
		MulticastFrameSplitter(PDU_consumer & consumer);
		MulticastFrameSplitter(PDU_consumer & consumer, MulticastFeedCursor_observer & subject);

		virtual ~MulticastFrameSplitter() {}

		void set_Consumer(PDU_consumer & consumer)
		{
			m_consumer = &consumer;
		}

		void set_observer(MsgDispatchingHooksBase *observer) { m_observer = observer; }

		// Split multicast frames and call the PDU consumer
		void splitFrames(std::vector<std::pair<void const *,size_t> > const & frames_ptr);
		void splitFrames(FeedOS::Types::ListOfBinaryBuffer const & inFrames)
		{
			std::vector<std::pair<void const *,size_t> > frames_ptr;
			frames_ptr.resize (inFrames.size());
			for (size_t i=0; i<inFrames.size(); ++i)
			{
				inFrames[i].get_read_access (frames_ptr[i].first, frames_ptr[i].second);
			}
			splitFrames (frames_ptr);
		}

		// Cursor accessor
		MulticastFeedCursor &		getCursor() { return m_TimeStampBeginFrame;}

	private:
		MulticastFeedCursor		m_TimeStampBeginFrame;
		PDU_consumer*			m_consumer;
		MsgDispatchingHooksBase *m_observer;
	};
} // namespace FeedOS

#endif // FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H
