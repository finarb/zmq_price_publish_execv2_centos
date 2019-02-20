
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#define FEEDOS_COMM_MULTICAST_FEED_TOOLS_H

#ifndef FEEDOS_BASE_DATE_H
#  include "../base/date.h"
#endif

#ifndef FEEDOS_BASE_LOCK_H
#	include "../base/lock.h"
#endif

#ifndef FEEDOS_COMM_INSTRUMENT_CODE_H
#	include "FOSInstrumentCode.h"
#endif


namespace FeedOS {

	class MsgDispatchingHooksBase
	{
	public:
		virtual ~MsgDispatchingHooksBase() {}

		// called (by the processing thread) prior processing a batch of incoming messages
		virtual void msg_dispatching_hook_begin (unsigned int /*batch_size*/) {}

		// called (by the processing thread) after a batch of messages has been processed
		virtual void msg_dispatching_hook_end () {}

		// called (by the enqueuer thread) when "warning level" has been reached
		virtual void msg_dispatching_hook_warning_level_reached () {}
	};

	/**
	 * Observer class to be dervived to get called on Multicast Frame Header time stamp modification
	 */
	class MulticastFeedCursor_observer
	{
	public:
		virtual ~MulticastFeedCursor_observer() {}
		virtual void hook_set_timestamp( Timestamp const & frame_timestamp) = 0;
	};
	
	/**
	 * Class dedicated to store a TimeStamp deserialiazed from a Multicast Frame,
	 * if set, an observer is warned along with the TimeStamp value. 
	 */
	class MulticastFeedCursor
	{
	public:
		// Default constructor
		MulticastFeedCursor():m_observer(0) 
		{
		}

		// Constructor with an observer instance
		MulticastFeedCursor(MulticastFeedCursor_observer & observer) 
		{
			set_observer(observer);
		}

		virtual ~MulticastFeedCursor() {}
		// Setting observer
		inline void set_observer (MulticastFeedCursor_observer const & o)
		{
			m_observer = const_cast<MulticastFeedCursor_observer*>(&o);
		}

		// Header time stamp accessor
		inline FeedOS::Timestamp const &	getTimeStamp () const { return m_timestamp; }

		// Setting time stamp from a multicast frame, invoking observer
		inline void setTimeStamp (unsigned int sec, unsigned int millisec, unsigned int microsec)
		{
			m_timestamp.set_timet(sec, millisec, microsec);
			if (m_observer) 
			{
				m_observer->hook_set_timestamp(m_timestamp);
			}
		}

		void initTimeStamp()
		{
			m_timestamp.set_to_null();
		}

	private:
		// forbidding copy and affectation
		MulticastFeedCursor(MulticastFeedCursor const &) ;
		//MulticastFeedCursor const & operator=(MulticastFeedCursor const &);

		FeedOS::Timestamp					m_timestamp;
		MulticastFeedCursor_observer	*	m_observer;
	};

	/**
	 * class holding a timestamp bounds used for replay,
	 * it also points to a MulticastFeedCursor instance
	 */
	class MulticastFeedBounds
	{
		// class cannot be copied
		MulticastFeedBounds(MulticastFeedBounds const &);
		MulticastFeedBounds const & operator=(MulticastFeedBounds const &);
	public:
		MulticastFeedBounds(MulticastFeedCursor & timestamp_holder)
			:m_Cursor(timestamp_holder)
		{}

		virtual ~MulticastFeedBounds() {}

		void setCursor(MulticastFeedCursor & time_stamp_holder)
		{
			m_Cursor = time_stamp_holder;
		}

		inline void initRange (Timestamp const & begin, Timestamp const & end)
		{
			m_Cursor.initTimeStamp();
			m_range_begin	= begin;
			m_range_end		= end;
		}

		inline void getRange (Timestamp & begin, Timestamp & end) const
		{
			begin	= m_range_begin;
			end		= m_range_end;
		}

	private:
		MulticastFeedCursor	&		m_Cursor;
		// Multicast bounds
		FeedOS::Timestamp			m_range_begin;
		FeedOS::Timestamp			m_range_end;
	};

	// Class owning a set of instrument bound to be used to filter notifications based on 
	// incoming instrument internal code.
	class FeedFilterInstrumentSet
	{
		static const size_t INSTRUMENT_LOCATOR_BUCKET_COUNT = 1000003;
	public:
		FeedFilterInstrumentSet();

		bool empty() const { SCOPE_AUTO_LOCK (l, m_InstrumentsLock); return m_instruments.empty(); }

		// Check against filterset an instrument
		bool is_inFilterSet(FOSInstrumentCode inCode) const
		{
			SCOPE_AUTO_LOCK (l,m_InstrumentsLock);
			return 0!=m_instruments.count(inCode);
		}

		// Add to FilterSet an instrument code.
		void add_toFilterSet(FOSInstrumentCode inCode)
		{
			SCOPE_AUTO_LOCK (l,m_InstrumentsLock);
			// Insertion is done if instrument is not yet active
			m_instruments.insert(inCode);
		}

	private:
		FeedFilterInstrumentSet(FeedFilterInstrumentSet const &);

		FEEDOS_STLEXT_NAMESPACE::hash_set< FeedOS::FOSInstrumentCode, FeedOS::FOSInstrumentCode::Hash > m_instruments;
		ExclusiveLock	m_InstrumentsLock;
	};

} // namespace FeedOS

#endif // FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
