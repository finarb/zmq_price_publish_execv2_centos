
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_deprecated_API_QUOTATION_SubscribeOneInstrumentOrderBook_H
#define FEEDOS_deprecated_API_QUOTATION_SubscribeOneInstrumentOrderBook_H

#include "../generated/gen_api_QUOTATION_SubscribeOneInstrumentOrderBook2.h"

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook_streaming \
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook_Started (FOSInstrumentCode inInternalCode,  FeedOS::Types::OrderBook const & inOrderBook); \
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeOneInstrumentOrderBook (ReturnCode rc); \
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits); \
		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta); \


	class INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook_streaming: public INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook2_streaming
	{
	public:
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook_Started (FOSInstrumentCode inInternalCode,  FeedOS::Types::OrderBook const & inOrderBook) = 0;
		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook_Failed (ReturnCode rc) = 0;
		virtual void aborted_QUOTATION_SubscribeOneInstrumentOrderBook (ReturnCode rc) = 0;

		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Started (FOSInstrumentCode inInternalCode,  FeedOS::Types::OrderBook const & inOrderBook)
		{
			response_QUOTATION_SubscribeOneInstrumentOrderBook_Started (inInternalCode, inOrderBook);
		}

		virtual void response_QUOTATION_SubscribeOneInstrumentOrderBook2_Failed (ReturnCode rc)
		{
			response_QUOTATION_SubscribeOneInstrumentOrderBook_Failed (rc);
		}

		virtual void aborted_QUOTATION_SubscribeOneInstrumentOrderBook2 (ReturnCode rc)
		{
			aborted_QUOTATION_SubscribeOneInstrumentOrderBook (rc);
		}

		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth)
		{
			// ignore
		}
	};


	typedef API_QUOTATION_SubscribeOneInstrumentOrderBook2_delegate API_QUOTATION_SubscribeOneInstrumentOrderBook_delegate;

	class API_QUOTATION_SubscribeOneInstrumentOrderBook_base:
			public API_QUOTATION_SubscribeOneInstrumentOrderBook_delegate,
			public virtual INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook_streaming
	{
		API_QUOTATION_SubscribeOneInstrumentOrderBook_base (API_QUOTATION_SubscribeOneInstrumentOrderBook_base const &);
		void operator=	(API_QUOTATION_SubscribeOneInstrumentOrderBook_base const &);
	public:
		API_QUOTATION_SubscribeOneInstrumentOrderBook_base () :
			API_QUOTATION_SubscribeOneInstrumentOrderBook_delegate ( (INTERFACE_QUOTATION_SubscribeOneInstrumentOrderBook_streaming &) *this)
		{}

	};

}
#endif
