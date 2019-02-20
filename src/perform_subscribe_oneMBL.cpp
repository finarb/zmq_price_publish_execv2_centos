
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** subscribing to MarketByLevel   **/
/**                                **/
/** QuantHouse 2010                **/
/************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>
#include <algorithm>

// TODO: allow subscription to several instruments
// TODO: then use reverse map for translating internal codes
// (see perform_subscribe)
//![snippet_sub_MBL_subclass]
class MyBookPrinter:
		public FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
//![snippet_sub_MBL_subclass]
{
public:
	enum OutputMode
	{
		Events,
		Cache,
		EventsAndCache
	};

private:
	// utility class: 1 order book entry (price X qty @ nbOrders)
	struct Limit
	{
		Limit() : m_Price(0.0),m_Qty(0),m_NbOrders(0) {}
		Limit(	FeedOS::FOSPrice const & rPrice,
				FeedOS::Types::FOSQty const & rQuantity,
				FeedOS::Types::FOSQty const & rNbOrders) :
			m_Price(rPrice),
			m_Qty(rQuantity),
			m_NbOrders(rNbOrders) {}

		FeedOS::FOSLowLevelPrice	price() const		{ return (FeedOS::FOSLowLevelPrice) m_Price; }
		FeedOS::FOSLowLevelInteger	qty() const			{ return (FeedOS::FOSLowLevelInteger) m_Qty;	}
		FeedOS::FOSLowLevelInteger	nbOrders() const	{ return (FeedOS::FOSLowLevelInteger) m_NbOrders;}

		void		setQty(FeedOS::Types::FOSQty const & qty, FeedOS::Types::FOSQty const & nbOrders)
		{
			m_Qty		= qty;
			m_NbOrders	= nbOrders;
		}

	private:
		FeedOS::FOSPrice		m_Price;
		FeedOS::Types::FOSQty	m_Qty;
		FeedOS::Types::FOSQty	m_NbOrders;
	};

	// utility class: 1 side of the order book
	struct HalfBook: public std::vector<Limit>
	{
		HalfBook(FeedOS::Types::FIXSide s) :
			side(s)
		{}

		HalfBook(HalfBook const & v) :
			std::vector<Limit> (v),
			side (v.side)
		{}

		HalfBook const & operator= (HalfBook const & v)
		{
			std::vector<Limit>::operator=(v);
			side = v.side;
			return *this;
		}

		FeedOS::Types::FIXSide side;

		char const * side_str() const { return (side==FeedOS::Types::FIXSide_Buy)?"Bid":"Ask"; }
	};

	// utility class: 1 layer of the order book
	struct BookLayer
	{
		BookLayer()
		:	m_CachedBid(FeedOS::Types::FIXSide_Buy),
			m_CachedAsk(FeedOS::Types::FIXSide_Sell),
			m_max_depth_received_is_known(false),
			m_max_depth_received(0),
			m_continuation_flag_set(false)
		{
		}

		HalfBook		m_CachedBid;	// stores the best bid limits
		HalfBook		m_CachedAsk;	// stores the best ask limits
		bool			m_max_depth_received_is_known;	// new feature, with API v3.2.0.0
		unsigned int	m_max_depth_received;	// remember what is the max depth available (computed from what we receive from the server)
		bool			m_continuation_flag_set;
	};

	FeedOS::PolymorphicInstrumentCode m_target_instr_code;
	OutputMode m_OutputMode;
	std::map<int,BookLayer> m_BookLayerMap;

public:
	// Construction
	MyBookPrinter(OutputMode outputMode)
	: m_OutputMode(outputMode)
	{
	}

	void set_target_instrument (FeedOS::PolymorphicInstrumentCode instr_code)
	{
		m_target_instr_code = instr_code;
	}

	FeedOS::PolymorphicInstrumentCode get_target_instrument () const
	{
		return m_target_instr_code;		
	}

	// inherited from INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
	void response_QUOTATION_SubscribeInstrumentsMBL_Started (FeedOS::uint32 inTicket, FeedOS::Types::ListOfFOSInstrumentCode const & codes);
	void response_QUOTATION_SubscribeInstrumentsMBL_Failed (FeedOS::ReturnCode rc);
	void aborted_QUOTATION_SubscribeInstrumentsMBL (FeedOS::ReturnCode rc);

	void notif_MBLFullRefresh		(	FeedOS::ListOfMBLSnapshot const & inSnapshots				);
	void notif_MBLOverlapRefresh	(	FeedOS::Types::MBLOverlapRefresh	const & inOverlap		);
	void notif_MBLDeltaRefresh		(	FeedOS::Types::MBLDeltaRefresh		const & inDelta			);

	//![snippet_sub_MBL_mvd]
	void notif_MBLMaxVisibleDepth(
			FeedOS::Types::MBLMaxVisibleDepth const & inDepth)
	{
		// Process event
		BookLayer& rBookLayer = m_BookLayerMap[inDepth.getLayerId()];
		if (inDepth.getMaxVisibleDepth().get() < 0)
		{
			rBookLayer.m_max_depth_received = static_cast<unsigned int>(
					std::max(rBookLayer.m_CachedAsk.size(),
							rBookLayer.m_CachedBid.size()));
			rBookLayer.m_max_depth_received_is_known = false;
		}
		else
		{
			rBookLayer.m_max_depth_received = static_cast<unsigned int>(inDepth.getMaxVisibleDepth());
			rBookLayer.m_max_depth_received_is_known = true;
		}

		// Show event
		if( m_OutputMode != Cache )
		{
			std::cout << "LAYER(" << inDepth.getLayerId() <<
					") notif_MBLMaxVisibleDepth, MaxVisibleDepth=" <<
					static_cast<int>(inDepth.getMaxVisibleDepth()) <<
					" => m_max_depth_received=" <<
					rBookLayer.m_max_depth_received << std::endl;
		}

		// Show cache
		if (m_OutputMode != Events)
		{
			print_orderbook();
		}
	}
	//![snippet_sub_MBL_mvd]

private:
	// handling of book data
	void truncate_orderbook_if_needed();
	
	void print_orderbook() const;
	
	void signal_OOB(	HalfBook const & cache,
						FeedOS::Types::FOSOrderBookLevel const & level,
						char const * where);
	
	void halfBook_Refresh(	BookLayer & layer,
							FeedOS::Types::FIXSide side,
							FeedOS::FOSInteger const & inChangeIndicator,
							FeedOS::Types::ListOfMBLOrderBookEntry const & inLimits);
	
	void halfBook_InsertAtLevel(	BookLayer & layer,
									FeedOS::Types::FIXSide side,
									FeedOS::Types::FOSOrderBookLevel const & level, 
									FeedOS::FOSPrice const & price,
									FeedOS::Types::FOSQty const & qty,
									FeedOS::Types::FOSQty const & nbOrders);
	
	void halfBook_RemoveLevel(	HalfBook &	cache,
								FeedOS::Types::FOSOrderBookLevel const & level);
	
	void halfBook_ChangeQtyAtLevel(	HalfBook &	cache,
									FeedOS::Types::FOSOrderBookLevel const & level, 
									FeedOS::Types::FOSQty const & qty,
									FeedOS::Types::FOSQty const & nbOrders);
	
	void halfBook_RemoveLevelAndAppend(	HalfBook &	cache,
										FeedOS::Types::FOSOrderBookLevel const & level, 
										FeedOS::FOSPrice const & price,
										FeedOS::Types::FOSQty const & qty,
										FeedOS::Types::FOSQty const & nbOrders);
};


void MyBookPrinter::truncate_orderbook_if_needed()
{
	// truncate the data in case it has grown over the "real" depth available from the server
	for(	std::map<int,BookLayer>::iterator itLayer = m_BookLayerMap.begin() ;
			itLayer != m_BookLayerMap.end() ;
			++itLayer )
	{
		BookLayer& rBookLayer = itLayer->second;

		if (rBookLayer.m_max_depth_received_is_known) {
			if (rBookLayer.m_CachedBid.size() > rBookLayer.m_max_depth_received) {
				rBookLayer.m_CachedBid.resize (rBookLayer.m_max_depth_received);
			}
			if (rBookLayer.m_CachedAsk.size() > rBookLayer.m_max_depth_received) {
				rBookLayer.m_CachedAsk.resize (rBookLayer.m_max_depth_received);
			}
		}
	}
}

void MyBookPrinter::print_orderbook() const
{
	for(	std::map<int,BookLayer>::const_iterator itLayer = m_BookLayerMap.begin() ;
			itLayer != m_BookLayerMap.end() ;
			++itLayer )
	{
		BookLayer const & rBookLayer = itLayer->second;

		size_t max_level = std::max (rBookLayer.m_CachedBid.size(), rBookLayer.m_CachedAsk.size());

		printf ("LAYER(%d)     *** BID **************    *** ASK ************** depth=%d (%s) local_receive_time=%s\n",
					(int) itLayer->first,
					(int) rBookLayer.m_max_depth_received,
					(char const *)(rBookLayer.m_max_depth_received_is_known ? "mvd" : "computed"),
					(char const*) FeedOS::Timestamp::now_utc().str_full_no_millisec().c_str()
		);

		for (size_t i=0; i<max_level; ++i) {
			printf ("%-3u   ", static_cast<unsigned int>(i));

			if (i < rBookLayer.m_CachedBid.size()) {
				print_price_83f (rBookLayer.m_CachedBid[i].price());
				print_qty		(rBookLayer.m_CachedBid[i].qty());
				print_nb_orders (rBookLayer.m_CachedBid[i].nbOrders());
			} else {
				printf ("                        ");
			}
			printf ("  ");

			if (i < rBookLayer.m_CachedAsk.size()) {
				print_price_83f (rBookLayer.m_CachedAsk[i].price());
				print_qty		(rBookLayer.m_CachedAsk[i].qty());
				print_nb_orders (rBookLayer.m_CachedAsk[i].nbOrders());
			} else {
				printf ("                        ");
			}
			printf ("\n");
		}
		printf ("continuationFlag=%s\n", rBookLayer.m_continuation_flag_set ? "true" : "false");
	}

	fflush(stdout);
}

void MyBookPrinter::signal_OOB(	HalfBook const & cache,
								FeedOS::Types::FOSOrderBookLevel const & level, 
								char const * where)
{
	std::cerr << FeedOS::Timestamp::now_utc().str_full_no_millisec() << ' ' <<
		where << '/' << cache.side_str() <<
		": received OutOfBound data, level="<<level<<
		" whereas current_size="<<(unsigned int)cache.size()<<
		std::endl
		;
}

void MyBookPrinter::halfBook_Refresh	(	BookLayer & layer,
											FeedOS::Types::FIXSide side, // side to update
											FeedOS::FOSInteger const & inChangeIndicator,
											FeedOS::Types::ListOfMBLOrderBookEntry const & inLimits
											)
{
	unsigned int start_level;	// depth at which the cached data should be overidden with inLimits
	bool is_complete;			// true if the given inLimits spread up to the last available limit

	HalfBook & cache = (side == layer.m_CachedBid.side) ? layer.m_CachedBid : layer.m_CachedAsk;

	FeedOS::split_OrderBookChangeIndicator (static_cast<int>(inChangeIndicator), is_complete, start_level);

	// here we should process data:
	// - update starts at "start_level" (0-based)
	// - "is_complete" indicates whether the given data contains the last available entry

	unsigned int new_depth = start_level + static_cast<unsigned int>(inLimits.size());
	if (!layer.m_max_depth_received_is_known)
	{
		layer.m_max_depth_received = static_cast<unsigned int>(std::max(layer.m_max_depth_received, new_depth));
	}

	if ( (cache.size() < new_depth) ||	// should make more room
		is_complete )					// should crop cached data
	{
		cache.resize (new_depth);
	}

	if (!inLimits.empty()) {
		// some of the limits should be updated
		for (unsigned int index = 0; index<inLimits.size(); ++index) {
			FeedOS::Types::MBLOrderBookEntry const & current = inLimits[index];
			cache [index+start_level] = Limit (	current.getPrice(), 
												current.getQty().getCumulatedUnits(),
												current.getQty().getNbOrders());
		}
	}
}

void MyBookPrinter::halfBook_InsertAtLevel (	BookLayer & layer,
												FeedOS::Types::FIXSide side,
												FeedOS::Types::FOSOrderBookLevel const & level, 
												FeedOS::FOSPrice const & price,
												FeedOS::Types::FOSQty const & qty,
												FeedOS::Types::FOSQty const & nbOrders)
{
	HalfBook & cache = (side == layer.m_CachedBid.side) ? layer.m_CachedBid : layer.m_CachedAsk;
	HalfBook::size_type levelIdx = static_cast<HalfBook::size_type>(level);

	if (levelIdx <= cache.size()) {	
		cache.insert (cache.begin() + levelIdx, Limit (price, qty, nbOrders));
		if (cache.size()>layer.m_max_depth_received && layer.m_max_depth_received_is_known) {
			cache.resize (layer.m_max_depth_received);	// drop the last entry in case of "overflow"
		}
	} else {
		signal_OOB (cache, level, "InsertAtLevel");
	}
}

void	MyBookPrinter::halfBook_RemoveLevel (	HalfBook &	cache,
												FeedOS::Types::FOSOrderBookLevel const & level)
{
	HalfBook::size_type levelIdx = static_cast<HalfBook::size_type>(level);

	if (levelIdx < cache.size()) {
		cache.erase (cache.begin() + levelIdx); 
		// Since API version v3.6.4.4, RemoveLevel has no more append semantic see halfBook_RemoveLevelAndAppend
	} else {
		signal_OOB (cache, level, "RemoveLevel");
	}
}

// Since API version v3.6.4.4, RemoveLevelAndAppend has been introduced 
void	MyBookPrinter::halfBook_RemoveLevelAndAppend (	HalfBook &	cache,
														FeedOS::Types::FOSOrderBookLevel const & level, 
														FeedOS::FOSPrice const & price,
														FeedOS::Types::FOSQty const & qty,
														FeedOS::Types::FOSQty const & nbOrders)
{
	HalfBook::size_type levelIdx = static_cast<HalfBook::size_type>(level);

	if (levelIdx < cache.size()) {
		cache.erase (cache.begin() + levelIdx); 
		cache.push_back (Limit (price, qty, nbOrders));
	} else {
		signal_OOB (cache, level, "RemoveLevelAndAppend");
	}
}

void	MyBookPrinter::halfBook_ChangeQtyAtLevel (	HalfBook &	cache,
													FeedOS::Types::FOSOrderBookLevel const & level, 
													FeedOS::Types::FOSQty const & qty,
													FeedOS::Types::FOSQty const & nbOrders)
{
	HalfBook::size_type levelIdx = static_cast<HalfBook::size_type>(level);

	if (levelIdx < cache.size()) {
		cache[levelIdx].setQty(qty,nbOrders);
	} else {
		signal_OOB (cache, level, "ChangeQtyAtLevel");
	}
}


//
//  callback for "subscription accepted by server"
//
//![snippet_sub_MBL_started]
void MyBookPrinter::response_QUOTATION_SubscribeInstrumentsMBL_Started(
		FeedOS::uint32 /*inTicket*/,
		FeedOS::Types::ListOfFOSInstrumentCode const & /*codes*/)
{
}
//![snippet_sub_MBL_started]

//
//  callback for "subscription refused by server"
//
//![snippet_sub_MBL_failed]
void MyBookPrinter::response_QUOTATION_SubscribeInstrumentsMBL_Failed(
		FeedOS::ReturnCode rc)
{
	std::cerr << "SubscribeInstrumentsL2_Failed, rc="<<rc<<std::endl;
}
//![snippet_sub_MBL_failed]

//
//  callback for "subscription aborted by server" (after it had been accepted)
//
//![snippet_sub_MBL_aborted]
void MyBookPrinter::aborted_QUOTATION_SubscribeInstrumentsMBL(
		FeedOS::ReturnCode rc)
{
	std::cerr << "aborted_SubscribeInstrumentsL2, rc="<<rc<<std::endl;
}
//![snippet_sub_MBL_aborted]


static bool is_continuation_flag(FeedOS::Types::QuotationVariable const &qv)
{
	return qv.getNum() == FeedOS::TAG_HasContinuationFlag;
}

//
//  callback for "all order book initialization"
//
//![snippet_sub_MBL_fullref]
void MyBookPrinter::notif_MBLFullRefresh(
		FeedOS::ListOfMBLSnapshot const & inSnapshots)
{
	if (inSnapshots.empty()) return;

	m_BookLayerMap.clear();

	// Process all snapshots
	for(FeedOS::ListOfMBLSnapshot::const_iterator itSnapshot =
			inSnapshots.begin(); itSnapshot != inSnapshots.end(); ++itSnapshot)
	{
		FeedOS::Types::MBLSnapshot const & rSnapshot = *itSnapshot;
		FeedOS::FOSInstrumentCode const & inInternalCode = rSnapshot.getCode();

		// merge the 2 flavours of the instrument code
		m_target_instr_code.merge_internal(inInternalCode);

		// Show event
		if (m_OutputMode != Cache)
		{
			std::cout << "\ninitial snapshot for " <<
					rSnapshot.getCode().to_str().c_str() << std::endl;
		}

		// Process event
		if (!rSnapshot.getLayers().empty())
		{
			// Process all layers
			std::vector<FeedOS::Types::MBLLayer> const & rvecLayers =
					rSnapshot.getLayers();
			for(FeedOS::ListOfMBLLayer::const_iterator itLayer =
					rvecLayers.begin(); itLayer != rvecLayers.end(); ++itLayer)
			{
				FeedOS::Types::MBLLayer const & rLayer = *itLayer;

				BookLayer& rBookLayer = m_BookLayerMap[rLayer.getLayerId()];

				{
					// When a layer's Other Values list contains tag HasContinuationFlag, then the Full Refresh was built using incomplete 'continuation' data.
					// Expect a series of Delta Refresh notifications will follow, and will finalize the image: The first Delta Refresh with getContinuationFlag()==true
					// indicates all chunks were received.
					// In the meantime, the received book is only partially correct.

					FeedOS::Types::ListOfQuotationVariable const & other_values = rLayer.getOtherValues();
					rBookLayer.m_continuation_flag_set = std::find_if(other_values.begin(), other_values.end(), is_continuation_flag) != other_values.end();
				}

				FeedOS::UTCTimestamps const & inUTCTimestamps =
						rLayer.getTimestamps();

				std::cout << " MarketUTC=" << inUTCTimestamps.getMarket() <<
						" ,ServerUTC=" <<  inUTCTimestamps.getServer() <<
						" ,LocalReceiveUTC =" <<
						FeedOS::Timestamp::now_utc().str_full_no_millisec().c_str()
						<< std::endl;

				unsigned int const nb_bid = static_cast<unsigned int>(
						rLayer.getBidLimits().size());
				unsigned int const nb_ask = static_cast<unsigned int>(
						rLayer.getAskLimits().size());


				FeedOS::FOSOrderBookLevel const depth = rLayer.getMaxVisibleDepth();
				if (depth.get() < 0)
				{
					rBookLayer.m_max_depth_received = static_cast<unsigned int>(std::max<unsigned int>(nb_bid, nb_ask));
					rBookLayer.m_max_depth_received_is_known = false;
				}
				else
				{
					rBookLayer.m_max_depth_received = static_cast<unsigned int>(depth);
					rBookLayer.m_max_depth_received_is_known = true;
				}

				// store current limits
				for (size_t bid_index = 0; bid_index < nb_bid; ++bid_index)
				{
					FeedOS::Types::MBLOrderBookEntry const & current =
							rLayer.getBidLimits()[bid_index];
					rBookLayer.m_CachedBid.push_back(Limit(
							current.getPrice(),
							current.getQty().getCumulatedUnits(),
							current.getQty().getNbOrders()));
				}
				for (size_t ask_index = 0; ask_index<nb_ask; ++ask_index)
				{
					FeedOS::Types::MBLOrderBookEntry const & current =
							rLayer.getAskLimits()[ask_index];
					rBookLayer.m_CachedAsk.push_back(Limit(
							current.getPrice(),
							current.getQty().getCumulatedUnits(),
							current.getQty().getNbOrders()));
				}
			}
		}
	}
	
	// Show cache
	if( m_OutputMode != Events )
	{
		print_orderbook();
	}
}
//![snippet_sub_MBL_fullref]

//
//  callback for "all or part of the order book was updated"
//
//![snippet_sub_MBL_overlap]
void MyBookPrinter::notif_MBLOverlapRefresh(
		FeedOS::Types::MBLOverlapRefresh const & inOverlap)
{
	// Process event
	BookLayer& rBookLayer = m_BookLayerMap[inOverlap.getLayerId()];

	FeedOS::UTCTimestamps const & inUTCTimestamps = inOverlap.getTimestamps();
	FeedOS::FOSInteger const & inBidChangeIndicator =
			inOverlap.getBidChangeIndicator();
	FeedOS::FOSInteger const & inAskChangeIndicator =
			inOverlap.getAskChangeIndicator();
	FeedOS::Types::ListOfMBLOrderBookEntry const & inBidLimits =
			inOverlap.getBidLimits();
	FeedOS::Types::ListOfMBLOrderBookEntry const & inAskLimits =
			inOverlap.getAskLimits();

	// This is a refresh of the order book: all or some of the ASK and BID
	// entries should be updated.
	halfBook_Refresh(rBookLayer,rBookLayer.m_CachedBid.side,
			inBidChangeIndicator,inBidLimits);
	halfBook_Refresh(rBookLayer,rBookLayer.m_CachedAsk.side,
			inAskChangeIndicator,inAskLimits);
	truncate_orderbook_if_needed();

	// Show event
	if( m_OutputMode != Cache )
	{
		std::cout << "\nMBLOverlapRefresh MarketUTC=" <<
				inUTCTimestamps.getMarket() << " ,ServerUTC=" <<
				inUTCTimestamps.getServer() << std::endl;
	}
	
	// Show cache
	if( m_OutputMode != Events )
	{
		print_orderbook();
	}
}
//![snippet_sub_MBL_overlap]

//
//  callback for "a small part of the order book was updated"
//
//![snippet_sub_MBL_delta]
void MyBookPrinter::notif_MBLDeltaRefresh(
		FeedOS::Types::MBLDeltaRefresh const & inDelta)
{
	// Process event
	BookLayer& rBookLayer = m_BookLayerMap[inDelta.getLayerId()];
	FeedOS::UTCTimestamps const & inUTCTimestamps = inDelta.getTimestamps();

	FeedOS::Types::OrderBookDeltaAction	action = inDelta.getAction();
	FeedOS::FOSOrderBookLevel const & level	= inDelta.getLevel();
	FeedOS::FOSPrice const & price = inDelta.getPrice();
	FeedOS::Types::FOSQty const & qty = inDelta.getQty().getCumulatedUnits();
	FeedOS::Types::FOSQty const & nbOrders = inDelta.getQty().getNbOrders();

	rBookLayer.m_continuation_flag_set = inDelta.getContinuationFlag();

	char const * action_str = "?";
	switch (action) {

	// some limits (both ASK and BID) in the cache should be removed, starting
	// from "level" (included)
	case FeedOS::Types::OrderBookDeltaAction_ALLClearFromLevel:
		action_str="ALLClearFromLevel";
		rBookLayer.m_CachedBid.resize (static_cast<size_t>(level));
		rBookLayer.m_CachedAsk.resize (static_cast<size_t>(level));
		break;

	// some limits in the cache should be removed, starting from "level"
	// (included)
	case FeedOS::Types::OrderBookDeltaAction_BidClearFromLevel:
		action_str="BidClearFromLevel";
		rBookLayer.m_CachedBid.resize (static_cast<size_t>(level));
		break;
	case FeedOS::Types::OrderBookDeltaAction_AskClearFromLevel:
		action_str="AskClearFromLevel";
		rBookLayer.m_CachedAsk.resize (static_cast<size_t>(level));
		break;

	// a new limit (price X qty @ nbOrders) should be inserted at "level",
	// all current limits (if any) starting at this level (included) are
	// shifted one level deeper
	case FeedOS::Types::OrderBookDeltaAction_BidInsertAtLevel:
		action_str="BidInsertAtLevel";
		halfBook_InsertAtLevel(rBookLayer, rBookLayer.m_CachedBid.side, level,
				price, qty, nbOrders);
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskInsertAtLevel:
		action_str="AskInsertAtLevel";
		halfBook_InsertAtLevel (rBookLayer, rBookLayer.m_CachedAsk.side, level,
				price, qty, nbOrders);
		break;

	// the limit at "level" should be removed,
	// all limits after (if any) are shifted one level up
	case FeedOS::Types::OrderBookDeltaAction_BidRemoveLevel:
		action_str="BidRemoveLevel";
		halfBook_RemoveLevel (rBookLayer.m_CachedBid, level);
		break;
	case FeedOS::Types::OrderBookDeltaAction_AskRemoveLevel:
		action_str="AskRemoveLevel";
		halfBook_RemoveLevel (rBookLayer.m_CachedAsk, level);
		break;

	// the quantity associated to limit at "level" is now "qty @ nbOrders"
	case FeedOS::Types::OrderBookDeltaAction_BidChangeQtyAtLevel:
		action_str="BidChangeQtyAtLevel";
		halfBook_ChangeQtyAtLevel (rBookLayer.m_CachedBid, level, qty,
				nbOrders);
		break;
	case FeedOS::Types::OrderBookDeltaAction_AskChangeQtyAtLevel:
		action_str="AskChangeQtyAtLevel";
		halfBook_ChangeQtyAtLevel (rBookLayer.m_CachedAsk, level, qty,
				nbOrders);
		break;

	// the limit at "level" should be removed,
	// all limits after (if any) are shifted one level up
	// a new limit (price X qty @ nbOrders) should be appended",
	case FeedOS::Types::OrderBookDeltaAction_BidRemoveLevelAndAppend:
		action_str="BidRemoveLevelAndAppend";
		halfBook_RemoveLevelAndAppend (rBookLayer.m_CachedBid, level, price,
				qty, nbOrders);
		break;
	case FeedOS::Types::OrderBookDeltaAction_AskRemoveLevelAndAppend:
		action_str="AskRemoveLevelAndAppend";
		halfBook_RemoveLevelAndAppend (rBookLayer.m_CachedAsk, level, price,
				qty, nbOrders);
		break;

	default:
		std::cerr << "\nOrderBookDeltaRefresh MarketUTC=" <<
			inUTCTimestamps.getMarket() << " ,ServerUTC=" <<
			inUTCTimestamps.getServer() << " unexpected action=" << action <<
			" level="<< (int)level;
		return;
	}
	truncate_orderbook_if_needed();

	// Show event
	if (m_OutputMode != Cache)
	{
		std::cout << std::endl
				<< "MBLDeltaRefresh MarketUTC=" << inUTCTimestamps.getMarket()
				<< " ,ServerUTC=" << inUTCTimestamps.getServer()
				<< " action=" << action_str
				<< " level=" << (int)level
				<< " price="; print_price_83f (price);
		std::cout << " qty="; print_qty (qty);
		std::cout << " nbOrders=";print_nb_orders (nbOrders);
		std::cout << " continuationFlag=" << std::boolalpha <<
				rBookLayer.m_continuation_flag_set << " nb_values="
				<< inDelta.getOtherValues().size() << std::endl;
	}

	// Show cache
	if (m_OutputMode != Events)
	{
		print_orderbook();
	}
}
//![snippet_sub_MBL_delta]

//
//
//    MAIN function (start the subscription and wait for ENTER key to be pressed)
//
//
/** \cond refguide
 * To perform an MBL instrument subscription in FeedOS API C++, you need to implement an
 * interface and several callbacks that handle the request and responses, as described in the
 * procedure below:
 *
 * <ol><li>Implement the \c FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
 * interface whose virtual methods are called when the events are received:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_subclass
 *
 * <ol><li>Implement the started callback to be called when the server acknowledges
 * the query, as shown below:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_started
 *
 * <ol><li>Implement the failed callback to be called if there is an error during
 * the query:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_failed
 *
 * <ol><li>Implement the aborted callback to be called when the subscription completes
 * (return code is \c RC_OK) or if an error occurs during the subscription:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_aborted
 *
 * <ol><li>Implement the real-time callback \c MBLFullRefresh to be called to initialize
 * the book:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_fullref
 *
 * <ol><li>Implement the real-time callback \c MBLOverlapRefresh to be called when
 * a part of the order book was updated:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_overlap
 *
 * <ol><li>Implement the real-time callback \c MBLDeltaRefresh to be called when a small
 * part of the order book was updated:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_delta
 *
 * <ol><li>Implement the real-time callback \c MBLMaxVisibleDepth to be called when the
 * max visible depth of the book was updated:</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_mvd
 *
 * <ol><li>Customize the MBL subscription (instruments, layers):</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_custom
 *
 * <ol><li>Perform the request (synchronous):</li></ol>
 * \snippet perform_subscribe_oneMBL.cpp snippet_sub_MBL_req
 *
 * \endcond
 */
void perform_subscribe_oneMBL (FeedOS::API::Connection & connection, int argc, char * argv[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_oneMBL");

	// Extract instrument codes
	if (argc < 2) {
		std::cerr <<"? CODE"<<std::endl;
		return;
	}
	FeedOS::PolymorphicInstrumentCode instr_code;
	if( !instr_code.read_from_string(argv[1]) )
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCodes from: "<< argv[1] << std::endl;
		return;
	}

	// Extract output options
	MyBookPrinter::OutputMode outputMode = MyBookPrinter::Events;
	if (argc == 3)
	{
		if( strcmp(argv[2],"-cache") == 0 )
		{
			outputMode = MyBookPrinter::Cache;
		}
		else if( strcmp(argv[2],"-events_and_cache") == 0 )
		{
			outputMode = MyBookPrinter::EventsAndCache;
		}
		// default is events mode
	}

	MyBookPrinter	printer(outputMode);
	FeedOS::API_QUOTATION_SubscribeInstrumentsMBL_delegate req (printer);

	// start the subscription (synchronous version)
	printer.set_target_instrument (instr_code);

	//![snippet_sub_MBL_custom]
	FeedOS::ListOfPolymorphicInstrumentCode code_list;
	code_list.push_back(instr_code); // Single instrument
	// Empty list means we want ALL layers
	FeedOS::ListOfOrderBookLayerId requestedLayerIds;
	// "Invalid code" policy on the server side
	bool ignoreInvalidCodes = false;
	//![snippet_sub_MBL_custom]

	//![snippet_sub_MBL_req]
	FeedOS::ReturnCode rc = req.sync_start(
			connection, code_list, requestedLayerIds, ignoreInvalidCodes);
	//![snippet_sub_MBL_req]

	if (rc == FeedOS::RC_OK) {
		getchar();
		req.stop ();
	}
}
