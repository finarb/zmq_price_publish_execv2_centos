
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2008 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FEED_PUBLISHER_H
#define FEEDOS_FRAMEWORK_FEED_PUBLISHER_H

#ifndef FEEDOS_BASE_OBJECT_H
#  include "../base/Object.h"
#endif

#ifndef FEEDOS_FRAMEWORK_FRAMEWORK_H
#  include "framework.h"
#endif

#ifndef FEEDOS_API_REQUESTER_H
#  include "../api/Requester.h"
#endif

#ifndef FEEDOS_API_GENERATED_TYPES_H
#	include "../api/generated_types.h"
#endif

namespace FeedOS
{
	class FeedPublisher: public StartableObject
	{
		class GenerateTradeEventExt;
		class GenerateOrderBookRefresh;
		class GenerateOrderBookDeltaRefresh;
		class GenerateOrderBookMaxVisibleDepth;
		class GenerateMBLFullRefresh;
		class GenerateMBLOverlapRefresh;
		class GenerateMBLDeltaRefresh;
		class GenerateMBLMaxVisibleDepth;
		GenerateTradeEventExt				& m_gen_TradeEventExt;
		GenerateOrderBookRefresh			& m_gen_OrderBookRefresh;
		GenerateOrderBookDeltaRefresh		& m_gen_OrderBookDeltaRefresh;
		GenerateOrderBookMaxVisibleDepth	& m_gen_OrderBookMaxVisibleDepth;
		GenerateMBLFullRefresh				& m_gen_MBLFullRefresh;
		GenerateMBLOverlapRefresh			& m_gen_MBLOverlapRefresh;
		GenerateMBLDeltaRefresh				& m_gen_MBLDeltaRefresh;
		GenerateMBLMaxVisibleDepth			& m_gen_MBLMaxVisibleDepth;

	public:
		FeedPublisher();
		virtual ~FeedPublisher();


		// number of asynchronous requests in progress (not responded yet)
		unsigned int nb_pending_requests () const;

		// number of events generated since last start_object()
		unsigned int nb_events_generated () const { return m_nb_events_generated; }


		//
		// REFERENTIAL: creation of instruments (synchronous requests)
		//

		ReturnCode ref_AllocateNewInstrument
				(
					RequestHandler & req_handler,
					// outputs
					FOSInstrumentCode & Code,
					// inputs
					FeedOS::Types::ListOfReferentialAttribute const & Attributes,
					FeedOS::Types::AllocateNewInstrumentPolicy OverwritePolicy = FeedOS::Types::AllocateNewInstrumentPolicy_DoNotOverwrite
				);

		ReturnCode ref_UnallocateInstruments
				(	RequestHandler & req_handler,
					FeedOS::Types::ListOfPolymorphicInstrumentCode const & Codes
				);

		ReturnCode ref_UpdateInstrumentAttributes
				(
					RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					FeedOS::Types::ListOfReferentialAttribute const & Attributes
				);



		//
		// STATUS: (synchronous requests)
		//

		// generate a FeedStatus message (to inform clients of failure or degradation)
		ReturnCode status_GenerateFeedStatusUpdate
				(
					RequestHandler & req_handler,
					String const & Sender, Timestamp const & SenderUTCTimestamp,  FeedOS::Types::FeedStatus const & Status					
				);

		// generate a free-text market news
		ReturnCode status_GenerateMarketNews
				(
					RequestHandler & req_handler,
					FeedOS::Types::MarketNews const & News
				);

		// generate a news
		ReturnCode status_GenerateNews
				(
					RequestHandler & req_handler,
					FeedOS::Types::NewsDetails const & News
				);

		//
		// QUOTATION: publishing prices (ASYNChronous requests)
		//

		//
		// Level 1: protocol-level functions
		//

		// all purpose "Level 1" event
		void quot_GenerateTradeEventExt
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & ServerUTCTimestamp,
					Timestamp const & MarketUTCTimestamp,
					FeedOS::Types::QuotationTradeEventExt const & Data
				);

		//
		// Level 2: protocol-level functions
		//

		// (deprecated) update whole or part of order book
		void quot_GenerateOrderBookRefresh
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & ServerUTCTimestamp,
					int BidChangeIndicator,
					int AskChangeIndicator,
					FeedOS::Types::ListOfOrderBookEntry const & partial_BidLimits,
					FeedOS::Types::ListOfOrderBookEntry const & partial_AskLimits
				);

		// (deprecated) small incremental update of order book
		void quot_GenerateOrderBookDeltaRefresh
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & ServerUTCTimestamp,
					FeedOS::Types::OrderBookDeltaRefresh const & Delta
				);

		// (deprecated) declare what is the maximum visible depth of the order book for this instrument
		void quot_GenerateOrderBookMaxVisibleDepth
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					int maxVisibleDepth
				);

		// full refresh of an order book
		void quot_GenerateMBLFullRefresh
				(	RequestHandler & req_handler,
					Types::ListOfMBLSnapshot const & full_refresh
				);

		// update whole or part of an order book
		void quot_GenerateMBLOverlapRefresh
				(	RequestHandler & req_handler,
					Types::MBLOverlapRefresh const & overlap_refresh
				);

		// small update of an order book
		void quot_GenerateMBLDeltaRefresh
				(	RequestHandler & req_handler,
					Types::MBLDeltaRefresh const & delta_refresh
				);

		// declare what it the "Max Visible Depth" of an order book layer
		void quot_GenerateMBLMaxVisibleDepth
				(	RequestHandler & req_handler,
					Types::MBLMaxVisibleDepth const & mvd
				);


		//
		// Level 1: simplified functions
		//

		// generate a trade: LastPrice + LastTradeQty
		void quot_simple_generate_trade
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & MarketUTCTimestamp,
					float64 price,
					float64 qty
				);

		// update LastPrice
		void quot_simple_generate_last_price
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & MarketUTCTimestamp,
					float64 price
				);

		// update a single value (syntax: float64)
		void quot_simple_generate_other_value
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & MarketUTCTimestamp,
					FeedOS::Types::TagNumber	quotation_tag_number,
					float64						tag_value
				);

		// update a list of values
		void quot_simple_generate_other_values
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & MarketUTCTimestamp,
					FeedOS::Types::ListOfQuotationVariable const & variables
				);

		// update best limits
		void quot_simple_generate_best_limits
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					Timestamp const & MarketUTCTimestamp,
					FeedOS::Types::OrderBookEntryExt const & bid,
					FeedOS::Types::OrderBookEntryExt const & ask
				);

		//
		// Level 2: simplified functions
		//

		// (deprecated) update order book as a whole
		void quot_simple_generate_full_book
				(	RequestHandler & req_handler,
					PolymorphicInstrumentCode const & Code,
					FeedOS::Types::ListOfOrderBookEntry const & full_BidLimits,
					FeedOS::Types::ListOfOrderBookEntry const & full_AskLimits
				);

		// update one order book layer as a whole
		void quot_simple_generate_MBL_layer_prices
				(	RequestHandler & req_handler,
					FOSInstrumentCode const & Code,
					Types::OrderBookLayerId const & LayerId,
					Timestamp const & MarketUTCTimestamp,
					FeedOS::Types::ListOfMBLOrderBookEntry const & full_BidLimits,
					FeedOS::Types::ListOfMBLOrderBookEntry const & full_AskLimits
				);

		// update variables attached to a given order book layer
		void quot_simple_generate_MBL_layer_other_values
				(	RequestHandler & req_handler,
					FOSInstrumentCode const & Code,
					Types::OrderBookLayerId const & LayerId,
					Timestamp const & MarketUTCTimestamp,
					Types::ListOfQuotationVariable const & OtherValues
				);

	private:
		// inherited from StartableObject
		virtual bool	impl_start_object();
		virtual bool	impl_stop_object();
		
		unsigned int	m_nb_events_generated;

	};

}


#endif


