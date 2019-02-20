
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_deprecated_NOTIF_OrderBookRefresh_H
#define FEEDOS_deprecated_NOTIF_OrderBookRefresh_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	include "../generated/gen_interface_QUOTATION.h"
#	include "../api/tags.h"
#	include "../api/generated_types.h"
#endif


namespace FeedOS {

	void log_error_unexpected_OrderBookType(FOSInstrumentCode inCode, Types::OrderBookLayerId id);

	inline void assign (Types::OrderBookEntry & d, Types::MBLOrderBookEntry const & s)
	{
		d.getPrice() = s.getPrice();
		d.getQty() = static_cast<float64>(s.getQty().getCumulatedUnits());
	}

	inline void assign (Types::MBLOrderBookEntry & d, Types::OrderBookEntry  const & s)
	{
		d.getPrice() = s.getPrice();
		Types::MBLQty & cumulated_qty = d.getQty();
		cumulated_qty.getCumulatedUnits() = static_cast<uint64>(s.getQty());
		cumulated_qty.getNbOrders() = Types::ORDERBOOK_NB_ORDERS_UNKNOWN;
	}

	template <typename T>
	void notif_OrderBookMaxVisibleDepth_into_MBLMaxVisibleDepth (
														T & target_object,
														FOSInstrumentCode inCode, 
														int8 inMaxVisibleDepth
													)
	{
		target_object.notif_MBLMaxVisibleDepth (FeedOS::Types::MBLMaxVisibleDepth(inCode,0, inMaxVisibleDepth));
	}


	template <typename T>
	void  notif_MBLMaxVisibleDepth_into_OrderBookMaxVisibleDepth (
														T & target_object,
														FeedOS::Types::MBLMaxVisibleDepth const & new_data
													)
	{
		if (0 == new_data.getLayerId())
		{
			target_object.notif_OrderBookMaxVisibleDepth (new_data.getCode(), static_cast<int8>(new_data.getMaxVisibleDepth()));
		}
		else
		{
			log_error_unexpected_OrderBookType(new_data.getCode(), new_data.getLayerId());
		}
	}

	template <typename T>
	void notif_OrderBookRefresh_into_MBLOverlapRefresh (
														T & target_object,
														FOSInstrumentCode inCode,
														Timestamp const & inServerUTCTimestamp,
														int8 inBidChangeIndicator,
														int8 inAskChangeIndicator, 
														FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  
														FeedOS::Types::ListOfOrderBookEntry const & inAskLimits
														)
	{
		Types::ListOfMBLOrderBookEntry ext_bid_limits (inBidLimits.size());
		for (unsigned int i=0; i<inBidLimits.size(); ++i) 
		{
			assign (ext_bid_limits[i],inBidLimits[i]);
		}
		Types::ListOfMBLOrderBookEntry ext_ask_limits(inAskLimits.size());
		for (unsigned int i=0; i<inAskLimits.size(); ++i) 
		{
			assign (ext_ask_limits[i],inAskLimits[i]);
		}
		static Types::ListOfQuotationVariable const other_values;
		static Timestamp const market_time;
		FeedOS::Types::MBLOverlapRefresh new_data (		inCode,
														0,
														Types::UTCTimestamps (inServerUTCTimestamp,market_time),
														inBidChangeIndicator, 
														inAskChangeIndicator, 
														ext_bid_limits, 
														ext_ask_limits, 
														other_values);
		target_object.notif_MBLOverlapRefresh (new_data);
	}

	template <typename T>
	void notif_MBLOverlapRefresh_into_OrderBookRefresh (
														T & target_object,
														FeedOS::Types::MBLOverlapRefresh const & new_data
														)
	{
		if (0 == new_data.getLayerId())
		{
			FeedOS::Types::ListOfMBLOrderBookEntry const & inBidLimits = new_data.getBidLimits();
			FeedOS::Types::ListOfOrderBookEntry old_bid_limits (inBidLimits.size());
			for (unsigned int i=0; i<inBidLimits.size(); ++i) 
			{
				assign (old_bid_limits[i],inBidLimits[i]);
			}
			FeedOS::Types::ListOfMBLOrderBookEntry const & inAskLimits = new_data.getAskLimits();
			FeedOS::Types::ListOfOrderBookEntry old_ask_limits (inAskLimits.size());
			for (unsigned int i=0; i<inAskLimits.size(); ++i) 
			{
				assign (old_ask_limits[i],inAskLimits[i]);
			}
			target_object.notif_OrderBookRefresh (
						new_data.getCode(),
						new_data.getTimestamps().getServer(),
						static_cast<int8>(new_data.getBidChangeIndicator()),
						static_cast<int8>(new_data.getAskChangeIndicator()), 
						old_bid_limits,
						old_ask_limits
						);
		}
		else
		{
			log_error_unexpected_OrderBookType(new_data.getCode(), new_data.getLayerId());
		}
	}

	template <typename T>
	void notif_OrderBookDeltaRefresh_into_MBLDeltaRefresh (
														T & target_object,
														FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta
														)
	{
		static Types::ListOfQuotationVariable const other_values;
		static Timestamp const market_time;

		Types::OrderBookDeltaAction field_action = inDelta.getAction();
		switch (field_action)
		{
		case Types::OrderBookDeltaAction_BidRemoveLevel:
			if (inDelta.getQty() != 0)
			{
				field_action = Types::OrderBookDeltaAction_BidRemoveLevelAndAppend;
			}
			break;
		case Types::OrderBookDeltaAction_AskRemoveLevel:
			if (inDelta.getQty() != 0)
			{
				field_action = Types::OrderBookDeltaAction_AskRemoveLevelAndAppend;
			}
			break;
		default:
			break;
		}
		target_object.notif_MBLDeltaRefresh (
					FeedOS::Types::MBLDeltaRefresh (	inCode,
														0,			// layer_id
														Types::UTCTimestamps(inServerUTCTimestamp,market_time), 
														field_action, 
														inDelta.getLevel(), 
														inDelta.getPrice(), 
														Types::MBLQty (static_cast<FOSLowLevelInteger>(inDelta.getQty()),Types::ORDERBOOK_NB_ORDERS_UNKNOWN),
														false,
														other_values
													)
											);
	}


	template <typename T>
	void notif_MBLDeltaRefresh_into_OrderBookDeltaRefresh (
														T & target_object,
														FeedOS::Types::MBLDeltaRefresh const & new_data
														)
	{
		if (0 == new_data.getLayerId())
		{
			Types::OrderBookDeltaAction field_action = new_data.getAction();
			switch (field_action)
			{
			case Types::OrderBookDeltaAction_BidRemoveLevelAndAppend:	field_action = Types::OrderBookDeltaAction_BidRemoveLevel;	break;
			case Types::OrderBookDeltaAction_AskRemoveLevelAndAppend:	field_action = Types::OrderBookDeltaAction_AskRemoveLevel;	break;
			default: break;
			}
			target_object.notif_OrderBookDeltaRefresh (
						new_data.getCode(),
						new_data.getTimestamps().getServer(),
						Types::OrderBookDeltaRefresh (	field_action,
														static_cast<int8>(new_data.getLevel()), 
														new_data.getPrice(), 
														static_cast<float64>(new_data.getQty().getCumulatedUnits())
													)
						);
		}
		else
		{
			log_error_unexpected_OrderBookType(new_data.getCode(), new_data.getLayerId());
		}
	}


#ifndef FEEDOS_COMPAT_INCLUDE

#define FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_NEW_NOTIF \
		virtual void response_QUOTATION_SubscribeAllOrderBook_Started (); \
		virtual void response_QUOTATION_SubscribeAllOrderBook_Failed (ReturnCode rc); \
		virtual void aborted_QUOTATION_SubscribeAllOrderBook (ReturnCode rc); \
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData); \
		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData); \
		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData); \
		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData); 

	class INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_NEW_NOTIF: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming
	{
	public:
		virtual void notif_OrderBookRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, int8 inBidChangeIndicator, int8 inAskChangeIndicator,  FeedOS::Types::ListOfOrderBookEntry const & inBidLimits,  FeedOS::Types::ListOfOrderBookEntry const & inAskLimits)
		{
			notif_OrderBookRefresh_into_MBLOverlapRefresh (*this, inCode, inServerUTCTimestamp, inBidChangeIndicator, inAskChangeIndicator, inBidLimits, inAskLimits);
		}

		virtual void notif_OrderBookDeltaRefresh	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp,  FeedOS::Types::OrderBookDeltaRefresh const & inDelta)
		{
			notif_OrderBookDeltaRefresh_into_MBLDeltaRefresh (*this, inCode, inServerUTCTimestamp, inDelta);
		}

		virtual void notif_OrderBookMaxVisibleDepth	(FOSInstrumentCode inCode, int8 inMaxVisibleDepth)
		{
			notif_OrderBookMaxVisibleDepth_into_MBLMaxVisibleDepth (*this, inCode, inMaxVisibleDepth);
		}
	};

	class INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_OLD_NOTIF: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming
	{
	public:
		// WARNING: Here we want to simulate a L2 snapshot response (we are in a situatin where
		// a client is subscribing to L2 while native stream is of MBL nature)
		virtual void notif_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData)
		{
			FeedOS::Types::ListOfMBLSnapshot::const_iterator new_datum = inData.begin();
			for (;inData.end() != new_datum; ++new_datum)
			{
				FOSInstrumentCode inCode = new_datum -> getCode();
				FeedOS::Types::ListOfMBLLayer const &  layers = new_datum -> getLayers();
				FeedOS::Types::ListOfMBLLayer::const_iterator layer_iter = layers.begin();
				for (;layers.end() != layer_iter; ++layer_iter)
				{
					if (0 == layer_iter -> getLayerId())
					{
						FeedOS::Types::ListOfMBLOrderBookEntry const & inBidLimits = layer_iter ->getBidLimits();
						FeedOS::Types::ListOfOrderBookEntry old_bid_limits (inBidLimits.size());
						for (unsigned int i=0; i<inBidLimits.size(); ++i) 
						{
							assign (old_bid_limits[i],inBidLimits[i]);
						}
						FeedOS::Types::ListOfMBLOrderBookEntry const & inAskLimits = layer_iter -> getAskLimits();
						FeedOS::Types::ListOfOrderBookEntry old_ask_limits (inAskLimits.size());
						for (unsigned int i=0; i<inAskLimits.size(); ++i) 
						{
							assign (old_ask_limits[i],inAskLimits[i]);
						}
						// TODO: have to drill that behavior, not sure if this will be correct from the subscriber perspective.
						notif_OrderBookRefresh (
									inCode,
									layer_iter -> getTimestamps().getServer(),
									static_cast<int8>(inBidLimits.size()), // we don't know if the book is complete
									static_cast<int8>(inAskLimits.size()),  // we don't know if the book is complete
									old_bid_limits,
									old_ask_limits
									);
						notif_OrderBookMaxVisibleDepth (inCode, static_cast<int8>(layer_iter->getMaxVisibleDepth()));
					}
					else
					{
						log_error_unexpected_OrderBookType(inCode, layer_iter -> getLayerId());
					}
				}
			}
		}
		

		virtual void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData)
		{
			notif_MBLOverlapRefresh_into_OrderBookRefresh (*this, inData);
		}

		virtual void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData)
		{
			notif_MBLDeltaRefresh_into_OrderBookDeltaRefresh (*this, inData);
		}

		virtual void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData)
		{
			notif_MBLMaxVisibleDepth_into_OrderBookMaxVisibleDepth (*this, inData);
		}

	};

#endif


}


#endif
