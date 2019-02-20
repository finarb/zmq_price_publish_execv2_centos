
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_L2_FILTERED_H
#define FEEDOS_FRAMEWORK_FEED_REPLAY_L2_FILTERED_H

#ifndef FEEDOS_FRAMEWORK_FEED_REPLAY_FILTERED_BASE_H
#	include "FeedReplay_filtered_base.h"
#endif

#ifndef FEEDOS_generated_API_QUOTATION_MulticastDataReplayL2_H
#	include "../generated/gen_api_QUOTATION_MulticastDataReplayL2.h"
#endif

namespace FeedOS {

	class FeedReplay_L2_filtered:	public virtual FeedReplay_filtered_base,
									public API_QUOTATION_MulticastDataReplayL2_base
	{
	public:
		FeedReplay_L2_filtered (INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & consumer);
		~FeedReplay_L2_filtered ();

		ReturnCode	sync_start	(	RequestHandler & handler,
									QuotationReplaySubject const & subject,
									QuotationReplayL2Filter const & contentFilter
								);

		void start	(	RequestHandler & handler,
						QuotationReplaySubject const & subject,
						QuotationReplayL2Filter const & contentFilter
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

		// set filter on the given list of instruments (default is to send all instruments)
		void set_filter_Instruments (
										ListOfPolymorphicInstrumentCode const & filter_instrumentCodes,
										bool ignore_invalid_codes = true
									);

		// set filter on the given list of Market IDs (default is to send MIC within the given source)
		void set_filter_MICs (
								ListOfFOSMarketId const & filter_MICs
							);

		// set filter on the given OrderBook depth (default is -1: "everything available")
		void set_filter_OrderBookDepth (int OrderBookDepth);

		// when you used set_filter_Instruments() before starting the replay, you can retrieve the corresponding internal codes here
		FeedOS::Types::ListOfFOSInstrumentCode const & get_filtered_instrument_codes () const { return m_filtered_instr_codes; }

	private:
		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_MulticastDataReplayL2_streaming

		FeedReplay_L2_filtered(FeedReplay_L2_filtered const &);
		FeedReplay_L2_filtered const & operator=(FeedReplay_L2_filtered const &);

		INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming &	m_consumer;

		//  inputs
		FeedOS::Types::QuotationReplaySubject	m_subject;
		FeedOS::Types::QuotationReplayL2Filter	m_L2_filter;

		//  output
		FeedOS::Types::ListOfFOSInstrumentCode	m_filtered_instr_codes;

	};

}


#endif
