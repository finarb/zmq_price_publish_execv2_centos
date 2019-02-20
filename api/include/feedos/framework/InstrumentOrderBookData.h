
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_ORDER_BOOK_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_ORDER_BOOK_DATA_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#	include "InstrumentTagData.h"
#endif

#include <algorithm>

namespace FeedOS {

	class InstrumentOrderBookData
	{
	public:
		InstrumentOrderBookData ();
		InstrumentOrderBookData (FOSInstrumentCode const & code);
		InstrumentOrderBookData (InstrumentOrderBookData const & v);
		virtual ~InstrumentOrderBookData ();

		InstrumentOrderBookData const & operator= (InstrumentOrderBookData const & v);

		FOSInstrumentCode const &	get_internal_code () const	{ return m_instr_code; }
		FOSInstrumentCode &			get_internal_code ()		{ return m_instr_code; }

		void reset ();
		void reset (FOSInstrumentCode const & code);

		FEEDOS_INLINE void update_with_OrderBookDeltaRefresh (	Timestamp const & inServerUTCTimestamp, 
																Types::OrderBookDeltaRefresh const & inDelta
															);

		FEEDOS_INLINE void update_with_OrderBookRefresh		(	Timestamp const & inServerUTCTimestamp, 
																int inBidIndicator, 
																int inAskIndicator, 
																Types::ListOfOrderBookEntry const & inBidLimits, 
																Types::ListOfOrderBookEntry const & inAskLimits
															);
		//
		// order book
		//

		FEEDOS_INLINE void clear_orderbook();

		// if depth=-1 then retrieve the whole book
		FEEDOS_INLINE void get_orderbook		(Types::OrderBook & v, int depth=-1) const;

		// input data may be truncated after copy. See force_orderbook_max_depth()
		FEEDOS_INLINE void set_orderbook		(Types::OrderBook const & inOrderBook);

		// -1 for "whole book is being received". This is the default
		void set_orderbook_max_visible_depth (int n);	

		// -1 for "whole book is being received". This is the default
		int get_orderbook_max_visible_depth () const;

		ExclusiveLock const &			get_lock4_orderbook() const			{ return m_orderbook_lock; }
		Types::OrderBook const &		get_orderbook_nolock () const		{ return m_orderbook; }
		Types::OrderBook &				get_orderbook_nolock ()				{ return m_orderbook; }

		int get_market_error_nolock()	{ return m_market_error; }

		// return true if all data has been received
		bool get_all_data_has_been_received()	{ return m_is_full; }

	private:
		void fill_default_values();

		FEEDOS_INLINE void clear_orderbook_nolock();
		FEEDOS_INLINE void clear_orderbook_limits_nolock();
		FEEDOS_INLINE void check_orderbook_overflow_after_insert (Types::ListOfOrderBookEntry & side, size_t last_insert_level);
		FEEDOS_INLINE void check_orderbook_overflow_after_overlap (Types::ListOfOrderBookEntry & side);
		FEEDOS_INLINE void update_max_orderbook_depth_after_insert (size_t last_insert_level);	// return true if max_orderbook_depth has been updated
		FEEDOS_INLINE void update_max_orderbook_depth_after_overlap (size_t current_depth);		// return true if max_orderbook_depth has been updated

		FOSInstrumentCode			m_instr_code;
		ExclusiveLock				m_orderbook_lock;
		Types::OrderBook			m_orderbook;
		size_t						m_max_visible_orderbook_depth;
		bool						m_max_visible_orderbook_depth_IS_KNOWN;
		bool						m_is_full;
		int							m_market_error;

		void log_unexpected_null_InternalTimestamp (char const * where) const;
		void log_unexpected_OrderBookDeltaAction(Types::OrderBookDeltaAction action) const;
		void log_RemoveAtPrice_negative_qty		(float64 price, float64 qty) const;
		void log_RemoveAtPrice_price_not_found	(float64 price, float64 qty) const;
		void log_unexpected_new_MaxVisibleDepth	(char const * context, size_t new_value) const;

		FEEDOS_INLINE void strip_order_book_to_visible_depth();
		FEEDOS_INLINE void internal_update_orderbook_delta_ClearFromLevel	(Types::ListOfOrderBookEntry & dest, unsigned int level);
		FEEDOS_INLINE void internal_update_orderbook_delta_RemoveLevel		(Types::ListOfOrderBookEntry & dest, unsigned int level, float64 price, float64 qty);
		FEEDOS_INLINE void internal_update_orderbook_delta_ChangeQtyAtLevel	(Types::ListOfOrderBookEntry & dest, unsigned int level, float64 qty);
		FEEDOS_INLINE void internal_update_orderbook_delta_InsertAtLevel	(Types::ListOfOrderBookEntry & dest, unsigned int level, float64 price, float64 qty);
		FEEDOS_INLINE bool internal_update_orderbook_refresh_one_side		(int source_start_level, Types::ListOfOrderBookEntry const & source, Types::ListOfOrderBookEntry & dest);

		int internal_check_orderbook_consistancy_nolock	(Types::ListOfOrderBookEntry const & source, bool is_ask, bool feedos_log);
		int internal_check_orderbook_price_qty			(float64 cur_price, float64 cur_qty, unsigned int i, bool feedos_log);
		int internal_check_orderbook_bbid_bask			(Types::ListOfOrderBookEntry const &, Types::ListOfOrderBookEntry const &, bool);
	public:

		int internal_check_orderbook_consistancy (bool feedos_log);
	};

#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/InstrumentOrderBookData.inl"
#endif

}


#endif
