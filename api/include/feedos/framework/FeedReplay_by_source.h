
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H

#ifndef FEEDOS_generated_API_CONNECTION_MulticastDataReplayBySource_H
#	include "../generated/gen_api_CONNECTION_MulticastDataReplayBySource.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H
#	include "../comm/MulticastFrameSplitter.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_DEFINITIONS_H
#	include "../comm/multicast_definitions.h"
#endif

namespace FeedOS {

	class FeedReplay_by_source_consumer
	{
	public:
		virtual ~FeedReplay_by_source_consumer () {}

		virtual void replay_Started () = 0;
		virtual void replay_Failed (ReturnCode rc) = 0;
		virtual void replay_Aborted (ReturnCode rc) = 0;

		void replay_ProcessOneFrame (void const * p, size_t l)
		{
			m_frames[0]= std::make_pair(p,l);
			m_splitter.splitFrames(m_frames);
		}

		MulticastFeedCursor & getCursor() { return m_splitter.getCursor(); }
	protected:
		FeedReplay_by_source_consumer (PDU_consumer & consumer, Multicast_definitions::PredefinedServices channel);

		Multicast_definitions::PredefinedServices const	m_channel;
		FeedOS::MulticastFrameSplitter					m_splitter;

	private:
		std::vector<std::pair<void const *,size_t> >	m_frames;

	};


	class FeedReplay_from_files;

	// base class for both "replay-from-files" and "replay-through-API-request"
	class FeedReplay_by_source: public FeedReplay_by_source_consumer
	{
	public:

		// start a replay-from-files in a background thread
		ReturnCode	start_replay_from_files (
											std::string const & feed_storage_dir,
											std::string const & source_name,
											Timestamp const & RangeBeginServerDate,
											Timestamp const & RangeEndServerDate,
											float64 AccelerationFactor = 0	// 0=MAX SPEED
										);

		void stop_replay_from_files();
		bool replay_from_files_is_in_progress() const;

		ReturnCode get_replay_status() const;

	protected:
		FeedReplay_by_source (PDU_consumer & consumer, Multicast_definitions::PredefinedServices channel);
		~FeedReplay_by_source ();

		// TimeStampRange accessor
		inline MulticastFeedBounds & getBounds() { return m_FeedReplayBounds; }

	private:
		MulticastFeedBounds				m_FeedReplayBounds;
		FeedReplay_from_files		&	m_file_replayer;
	};


	class FeedReplay_by_source_through_API: 
				public FeedReplay_by_source,
				public API_CONNECTION_MulticastDataReplayBySource_base
	{
	public:
		ReturnCode	sync_start	(RequestHandler & handler, uint16 InternalSourceId, Timestamp const & RangeBeginServerDate, Timestamp const & RangeEndServerDate, float64 AccelerationFactor = 0);
		void		start		(RequestHandler & handler, uint16 InternalSourceId, Timestamp const & RangeBeginServerDate, Timestamp const & RangeEndServerDate, float64 AccelerationFactor = 0);

	protected:
		FeedReplay_by_source_through_API (PDU_consumer & consumer, Multicast_definitions::PredefinedServices channel)
			: FeedReplay_by_source (consumer, channel)
		{}

// implement only the notif_XXX() callbacks
//		FEEDOS_GEN_DECL_INTERFACE_CONNECTION_MulticastDataReplayBySource_streaming
		virtual void notif_ReplayData	(FeedOS::Types::ListOfBinaryBuffer const & inFrames)
		{
			m_splitter.splitFrames(inFrames);
		}

		// inherited from FeedReplay_by_source_consumer
		virtual void replay_Started ()
		{
			response_CONNECTION_MulticastDataReplayBySource_Started ();
		}
		virtual void replay_Failed (ReturnCode rc)
		{
			response_CONNECTION_MulticastDataReplayBySource_Failed (rc);
		}
		virtual void replay_Aborted (ReturnCode rc)
		{
			aborted_CONNECTION_MulticastDataReplayBySource (rc);
		}

	};

} // namespace FeedOS


#endif // FEEDOS_FRAMEWORK_FEED_REPLAY_BY_SOURCE_H
