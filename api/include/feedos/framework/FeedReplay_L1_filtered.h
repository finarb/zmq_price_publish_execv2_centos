
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_L1_FILTERED_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_L1_FILTERED_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_FILTERED_BASE_H
#	include "FeedReplay_filtered_base.h"
#endif

#ifndef FEEDOS_generated_API_QUOTATION_MulticastDataReplayL1_H
#	include "../generated/gen_api_QUOTATION_MulticastDataReplayL1.h"
#endif

namespace FeedOS {

	class FeedReplay_L1_filtered:	public virtual FeedReplay_filtered_base,
									public API_QUOTATION_MulticastDataReplayL1_base
	{
	public:
		FeedReplay_L1_filtered (INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & consumer);
		~FeedReplay_L1_filtered ();

		ReturnCode	sync_start	(	RequestHandler & handler,
									QuotationReplaySubject const & subject,
									QuotationReplayL1Filter const & contentFilter
								);

		void start	(	RequestHandler & handler,
						QuotationReplaySubject const & subject,
						QuotationReplayL1Filter const & contentFilter
					);

		ReturnCode	sync_start	(	RequestHandler & handler,
									uint16 InternalSourceId, 
									Timestamp const & RangeBeginServerDate, 
									Timestamp const & RangeEndServerDate, 
									float64 AccelerationFactor = 0
								);

		void		start		(	RequestHandler & handler,
									uint16 InternalSourceId, 
									Timestamp const & RangeBeginServerDate, 
									Timestamp const & RangeEndServerDate, 
									float64 AccelerationFactor = 0
								);

		// disable sending of "frame header" (this carries the low-level timestamps)
		void disable_SendMulticastFrameHeader ();

		// set filter on message types (default is to process all messages)
		//TODO use base class FeedReplay_L1_dispatcher
		void set_filter_MessageTypes (
										bool notif_TradeEvent,
										bool notif_ValuesUpdate,	
										bool notif_MarketStatus,
										bool notif_MarketNews,
										bool notif_TradeCancelCorrection
									);

		// set filter on the given list of instruments (default is to send all instruments)
		void set_filter_Instruments (
										ListOfPolymorphicInstrumentCode const & filter_instrumentCodes,
										bool ignore_invalid_codes = true
									);

		// set filter on the given list of Market IDs (default is to send MIC within the given source)
		void set_filter_MICs (
								ListOfFOSMarketId const & filter_MICs
							);

		// set filter on the given "content mask" (default is QuotationContentMask_EVERYTHING)
		void set_filter_ContentMask (
								QuotationContentMask filter_contentmask
							);

		// when you used set_filter_Instruments() before starting the replay, you can retrieve the corresponding internal codes here
		FeedOS::Types::ListOfFOSInstrumentCode const & get_filtered_instrument_codes () const { return m_filtered_instr_codes; }

	private:
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_MulticastDataReplayL1_streaming

		INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming &	m_consumer;

		FeedReplay_L1_filtered( FeedReplay_L1_filtered const &);
		FeedReplay_L1_filtered const & operator=(FeedReplay_L1_filtered const &);

		//  client-side filtering
		bool	m_filter_process_notif_TradeEvent;
		bool	m_filter_process_notif_ValuesUpdate;
		bool	m_filter_process_notif_MarketStatus;
		bool	m_filter_process_notif_MarketNews;
		bool	m_filter_process_notif_TradeCancelCorrection;

		//  inputs
		FeedOS::Types::QuotationReplaySubject	m_subject;
		FeedOS::Types::QuotationReplayL1Filter	m_L1_filter;

		//  output
		FeedOS::Types::ListOfFOSInstrumentCode	m_filtered_instr_codes;

	};

}


#endif
