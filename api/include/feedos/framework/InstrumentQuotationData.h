
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#	include "InstrumentTagData.h"
#endif

#ifndef FEEDOS_deprecated_NOTIF_TradeEvent_H
#	include "../deprecated/deprecated_notif_TradeEvent.h"
#endif

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_2_H
#	include "InstrumentQuotationData_2.h"
#endif

#include <algorithm>

namespace FeedOS {

	typedef InstrumentQuotationData_2 InstrumentQuotationData;

	namespace DEPRECATED {
	/*!
	  @brief superseded by InstrumentQuotationData_2 class
	  @deprecated
	 */
	class InstrumentQuotationData: public InstrumentTagData
	{
	public:
		InstrumentQuotationData ();
		InstrumentQuotationData (FOSInstrumentCode const & code);
		InstrumentQuotationData (InstrumentQuotationData const & v);
		virtual ~InstrumentQuotationData ();

		InstrumentQuotationData const & operator= (InstrumentQuotationData const & v);

		// inherited from InstrumentTagData
		virtual	void reset (FOSInstrumentCode const & code);

		typedef TagMap	VariableMap;
		ExclusiveLock const &	get_lock4_var_map() const	{ return get_lock4_tag_map(); }
		VariableMap const &		get_var_map_nolock() const	{ return get_tag_map_nolock(); }
		VariableMap &			get_var_map_nolock()		{ return get_tag_map_nolock(); }

		void clear_variables ()		{ clear_tags(); }
		void clear_best_limits ();

		bool						get_variable (Types::ReferentialTagNumber tag_num, Any & var_value) const	{ return get_tag(tag_num,var_value); }
		bool						get_variable (Types::ReferentialTagNumber tag_num, Types::QuotationVariable & attr) const { return get_tag(tag_num,attr); }
		Types::QuotationVariable	get_variable (Types::ReferentialTagNumber tag_num) const	{ return get_tag(tag_num); }

		bool	set_variable		(Types::ReferentialTagNumber tag_num, Any const & var_value){ return set_tag (tag_num,var_value); }
		bool	set_variable		(Types::QuotationVariable const & attr)						{ return set_tag (attr); }
		void	delete_variable		(Types::ReferentialTagNumber tag_num)						{ delete_tag(tag_num); }
		bool	variable_is_present	(Types::ReferentialTagNumber tag_num) const					{ return tag_is_present(tag_num); }

		bool	received_daily_open () const { return m_received_daily_open; }
		bool	received_daily_close () const { return m_received_daily_close; }

#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_ACCESSORS(ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_ACCESSORS(ATT,RT,S,NB)
#include <feedos_metadata/tags_quotation.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST

		//////////////////////////
		// update methods
		//////////////////////////

		void update_with_TradeEventExt	(
												Timestamp const & inServerUTCTimestamp,
												Timestamp const & inMarketUTCTimestamp,  
												Types::QuotationTradeEventExt const & data
											);

		// deprecated
		void update_with_TradeEvent			(
												Timestamp const & inMarketUTCTimestamp,
												Types::QuotationTradeEvent const & data
											)
		{
			notif_TradeEvent_into_TradeEventExt (*this, 0, inMarketUTCTimestamp, data/*, Timestamp()*/); // let the default serverUTCTimestamp be set to "now"
		}

		// deprecated
		void update_with_ValuesUpdate		(
												Timestamp const & inMarketUTCTimestamp, 
												Types::QuotationValuesUpdate const & data
											)
		{
			SCOPE_AUTO_LOCK (l, get_lock4_tag_map());
			update_values_nolock (Timestamp::null(), inMarketUTCTimestamp, data.getValues());
		}

		inline void	get_best_limits (Types::OrderBookBestLimitsExt & limits) const
		{
			SCOPE_AUTO_LOCK (l,get_lock4_var_map()); 
			get_best_limits_nolock (limits);
		}

		inline void set_best_limits (Types::OrderBookBestLimitsExt const & limits)
		{
			SCOPE_AUTO_LOCK (l,get_lock4_var_map()); 
			m_best_limits = limits;
		}

		// deprecated
		void set_orderbook		(Types::OrderBook const & book) { set_best_limits (book); }
		void set_best_limits	(Types::OrderBook const & book);
		void set_best_limits	(Types::OrderBookBestLimits const & best_limits);

		inline void get_best_limits_nolock (Types::OrderBookBestLimitsExt & limits) const	{ limits = m_best_limits; }
		inline void set_best_limits_nolock (Types::OrderBookBestLimitsExt const & limits)	{ m_best_limits = limits; }

		inline void set_best_bid_nolock	(Types::OrderBookEntryExt const & best_bid) {	m_best_limits.getBestBid() = best_bid; }
		inline void set_best_ask_nolock	(Types::OrderBookEntryExt const & best_ask) {	m_best_limits.getBestAsk() = best_ask; }

		void update_values_nolock (	
									Timestamp const & inServerUTCTimestamp, 
									Timestamp const & inMarketUTCTimestamp,  
									Types::ListOfQuotationVariable const & values
								);

	private:

		bool								m_received_daily_open;
		bool								m_received_daily_close;
		bool								m_extrapolate_session_values;
		Types::OrderBookBestLimitsExt	m_best_limits;

		void fill_default_values();
		void log_unexpected_tradingstatus		(Types::FIXSecurityTradingStatus s) const;
		void log_inconsistant_event				(char const * inconsistant_what, float64 last_trade_price, float64 inconsistant_value) const;

		FEEDOS_INLINE void internal_extrapolate_TotalVolumeAndAsset_after_transaction (float64 price, float64 qty);
		FEEDOS_INLINE void internal_extrapolate_TotalOffBookVolumeAndOffBookAsset_after_transaction (float64 price, float64 qty);

		// update TradingStatus, and perform any task related to the new status (FastMarket => clear book)
		void consistant_update_TradingStatus_nolock	 (Types::FIXSecurityTradingStatus s);

		// update TradingSessionId (-1 => clear Session Values)
		void consistant_update_TradingSessionId_nolock (int8 session_id);

	public:
		// overloaded from InstrumentTagData
		virtual void load_hook();
		using InstrumentTagData::load;
		void load(Types::InstrumentStatus const & status);

		// needed for notif_TradeEvent_into_TradeEventExt() to work
		void notif_TradeEventExt	(
												FOSInstrumentCode,
												Timestamp const & inServerUTCTimestamp,
												Timestamp const & inMarketUTCTimestamp,  
												Types::QuotationTradeEventExt const & data
									)
		{
			update_with_TradeEventExt (inServerUTCTimestamp, inMarketUTCTimestamp, data);
		}
	};


#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/InstrumentQuotationData.inl"
#endif
   } // namespace DEPRECATED
}  // namespace FeedOS


#endif
