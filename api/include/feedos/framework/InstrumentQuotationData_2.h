
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**      kannan aroumont           **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_2_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_2_H

#include "InstrumentTagData.h"
#include "../deprecated/deprecated_notif_TradeEvent.h"

#include <algorithm>
#include <set>

//#define CHECK_TAGMAP_CONSISTENCY

namespace UNIT_TEST
{
	struct InstrumentQuotationData_TestSuite;
}

namespace FeedOS
{
	class InstrumentQuotationData_2base: protected InstrumentTagData
	{
	public:
		InstrumentQuotationData_2base();
		InstrumentQuotationData_2base (FOSInstrumentCode const & code);
		InstrumentQuotationData_2base (InstrumentQuotationData_2base const & v);
		virtual ~InstrumentQuotationData_2base (){ }

#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)	\
		FEEDOS_DEF_TAG_GET_ACCESSORS(ATT,RT,S) \
		inline void			set_##ATT##_nolock	(RT const & v)	\
		{ \
			add_tag_updated(NUM);	\
			set_tag_##S##_nolock	(TAG_##ATT, (S) v); \
		}	\
		inline void			set_##ATT			(RT const & v)	\
		{ \
			add_tag_updated(NUM);	\
			set_tag_##S			(TAG_##ATT, (S) v);	\
		}

#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_ACCESSORS(ATT,RT,S,NB)
#include <feedos_metadata/tags_quotation.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST

		ExclusiveLock const &		get_lock4_var_map() const		{ return m_lock; }
		FOSInstrumentCode const &	get_internal_code () const	{ return InstrumentTagData::get_internal_code (); }
		FOSInstrumentCode &			get_internal_code ()		{ return InstrumentTagData::get_internal_code (); }
		InstrumentTagData const &		get_NON_PREFERED_tags_nolock() const	{ return *this; }
		InstrumentTagData &				get_NON_PREFERED_tags_nolock()			{ return *this; }

	protected :
		typedef std::map <Types::TagNumber, Any>	TagMap;

		virtual inline void add_tag_updated(Types::TagNumber const &) {}

	private:
		ExclusiveLock m_lock;
	};

	class InstrumentQuotationData_2: public InstrumentQuotationData_2base
	{
	public:
		template<typename T>
		class TagWithMagicValue
		{
		public:
			TagWithMagicValue(){
				set_is_not_present();
			}

			~TagWithMagicValue(){ }

			T const & magic_value()const;

			bool is_present() const
			{
				return m_value!=magic_value();
			}

			void set_is_not_present()
			{
				m_value=magic_value();
			}

			T const & get_value()const { return m_value;}
			void set_value(const T& value) { m_value = value ;}
		private:
			T m_value;
		};

		InstrumentQuotationData_2();
		InstrumentQuotationData_2(FOSInstrumentCode const & code);
		InstrumentQuotationData_2 (InstrumentQuotationData_2 const & v);
		InstrumentQuotationData_2 const & operator= (InstrumentQuotationData_2 const & v);

		virtual ~InstrumentQuotationData_2 (){ }

		// macro for setters and getters
#define FEEDOS_DEF_PREF_TAG_ACCESSORS(ATT,NUM,RT,S)	\
		inline RT /*const*/		get_##ATT##_nolock	() const		{return (RT) m_preferred_tags_##S	[INDEX_Preferred_Tag_##ATT].get_value(); }		\
		inline RT /*const*/		get_##ATT			() const		{ SCOPE_AUTO_LOCK(l,get_lock4_var_map()); return get_##ATT##_nolock();}		\
		inline bool			get_##ATT##_nolock	(RT & v) const	{ TagWithMagicValue<S> const &tag = m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT];	\
																  if (tag.is_present())	\
																	{	\
																		S t = (RT)tag.get_value();	\
																		syntax_convert_tagvalue (t,v);	\
																		return true;	\
																	}	\
																	return false;	\
																}		\
		inline bool			get_##ATT			(RT & v) const	{ SCOPE_AUTO_LOCK(l,get_lock4_var_map());	return get_##ATT##_nolock(v); }	\
		inline void			set_##ATT##_nolock	(RT const & v) \
																{ \
																	add_tag_updated(NUM);	\
																	m_preferred_tags_##S	[INDEX_Preferred_Tag_##ATT].set_value((S) v);	\
																}	\
		inline void			set_##ATT			(RT const & v)	\
																{ \
																	SCOPE_AUTO_LOCK(l,get_lock4_var_map()); \
																	add_tag_updated(NUM);	\
																	m_preferred_tags_##S	[INDEX_Preferred_Tag_##ATT].set_value((S) v);}

#undef  FEEDOS_DEF_PREF_TAG
#undef	FEEDOS_DEF_PREF_TAG_MAX
#define FEEDOS_DEF_PREF_TAG_MAX(MAX,SYNTAX)				static unsigned int const NB_Preferred_Tags_##SYNTAX = MAX;
#define FEEDOS_DEF_PREF_TAG(ARRAY_INDEX,NUM,ATT,RT,S)	\
		static unsigned int const INDEX_Preferred_Tag_##ATT = ARRAY_INDEX;	\
		FEEDOS_DEF_PREF_TAG_ACCESSORS(ATT,NUM,RT,S)

		#include "InstrumentQuotationData_2_preferred_tag.hpp"

	private:
		TagWithMagicValue<float64>		m_preferred_tags_float64	[NB_Preferred_Tags_float64];	// stored in internal "syntax" format
		TagWithMagicValue<Timestamp>	m_preferred_tags_Timestamp	[NB_Preferred_Tags_Timestamp];	// stored in internal syntax format

		void dump_prefered_tags(unsigned int tag_num,std::vector<Types::TagNumAndValue> & tags ) const;

	public:

		virtual	void reset (FOSInstrumentCode const & code);

		void clear_prefered_tags ();
		void clear_variables ()		{ get_NON_PREFERED_tags_nolock().clear_tags(); clear_prefered_tags(); }
		void clear_best_limits ();

		bool get_tag_nolock	(Types::TagNumber tag_num, Any & tag_value) const
		{
			switch(tag_num)
			{
#undef  FEEDOS_DEF_PREF_TAG
#undef	FEEDOS_DEF_PREF_TAG_MAX
#define FEEDOS_DEF_PREF_TAG_MAX(MAX,SYNTAX)
#define FEEDOS_DEF_PREF_TAG(ARRAY_INDEX,NUM,ATT,RT,S)	\
								case NUM :	\
								{	\
									TagWithMagicValue<RT> const & v = m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT];	\
									if (v.is_present()) \
									{ \
										tag_value.set_##S(v.get_value());	\
										return true; \
									}	\
									else	\
									{	\
										return false; \
									}	\
									break;\
							   }

#include "InstrumentQuotationData_2_preferred_tag.hpp"

					default:
						return get_NON_PREFERED_tags_nolock().get_tag_nolock(tag_num,tag_value);
			}
			return true;

		}

		bool get_tag (Types::TagNumber tag_num, Any & tag_value) const
		{
			switch(tag_num)
			{
#undef  FEEDOS_DEF_PREF_TAG
#undef	FEEDOS_DEF_PREF_TAG_MAX
#define FEEDOS_DEF_PREF_TAG_MAX(MAX,SYNTAX)
#define FEEDOS_DEF_PREF_TAG(ARRAY_INDEX,NUM,ATT,RT,S)					\
				case NUM :												\
					if (m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT].is_present()) \
					{													\
						tag_value = Any (m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT].get_value()); \
						return true;									\
					}													\
					return false;
#include "InstrumentQuotationData_2_preferred_tag.hpp"

			default:{
				SCOPE_AUTO_LOCK(l,get_lock4_var_map());
				return get_NON_PREFERED_tags_nolock().get_tag_nolock(tag_num,tag_value);
			}
			}
		}

		bool set_tag_nolock	(Types::TagNumber tag_num, Any const & tag_value)
		{
			add_tag_updated(tag_num);

			switch(tag_num)
			{
				#undef  FEEDOS_DEF_PREF_TAG
				#undef	FEEDOS_DEF_PREF_TAG_MAX
				#define FEEDOS_DEF_PREF_TAG_MAX(MAX,SYNTAX)
				#define FEEDOS_DEF_PREF_TAG(ARRAY_INDEX,NUM,ATT,RT,S)	\
							case NUM : { m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT].set_value(tag_value.get_##S());	\
											break;\
										}
				#include "InstrumentQuotationData_2_preferred_tag.hpp"

				default:{
					get_NON_PREFERED_tags_nolock().set_tag_nolock(tag_num,tag_value);
					break;
					}
			}
			return true;

		}

		bool set_tag(Types::TagNumber tag_num, Any const & tag_value)
		{
			if (!get_NON_PREFERED_tags_nolock().check_set_tag_syntax (tag_num, tag_value))
				return false;

			add_tag_updated(tag_num);
#if 0
			m_tag_map[tag_num] = tag_value;
#else
			switch(tag_num)
				{
					#undef  FEEDOS_DEF_PREF_TAG
					#undef	FEEDOS_DEF_PREF_TAG_MAX
					#define FEEDOS_DEF_PREF_TAG_MAX(MAX,SYNTAX)
					#define FEEDOS_DEF_PREF_TAG(ARRAY_INDEX,NUM,ATT,RT,S)	\
								case NUM : { m_preferred_tags_##S[INDEX_Preferred_Tag_##ATT].set_value(tag_value.get_##S());	\
											break;	\
										   }
					#include "InstrumentQuotationData_2_preferred_tag.hpp"

					default:{
						get_NON_PREFERED_tags_nolock().set_tag(tag_num,tag_value);
						break;
						}

				}

#endif
			return true;
		}

		void	delete_variable		(Types::ReferentialTagNumber tag_num)
		{
			SCOPE_AUTO_LOCK (l,get_lock4_var_map());
			delete_tag_nolock(tag_num);
		}

		void	delete_tag			(Types::TagNumber tag_num)
		{
			delete_variable(tag_num);
		}

		//////////////////////////
		// update methods
		//////////////////////////

		void update_with_TradeEventExt ( Timestamp const & inServerUTCTimestamp,
										 Timestamp const & inMarketUTCTimestamp,
										 Types::QuotationTradeEventExt const & data
									   )
		{
			Timestamp t = inServerUTCTimestamp;
			if (t.is_null()) {
				t.set_to_now_utc();
			}
			SCOPE_AUTO_LOCK (l, get_lock4_var_map());
			update_with_TradeEventExt_impl(t, inMarketUTCTimestamp, data);
		}

		void update_with_TradeEventExt_nolock ( Timestamp const & inServerUTCTimestamp,
										        Timestamp const & inMarketUTCTimestamp,
												Types::QuotationTradeEventExt const & data
											  )
		{
			Timestamp t = inServerUTCTimestamp;
			if (t.is_null()) {
				t.set_to_now_utc();
			}
			update_with_TradeEventExt_impl(t, inMarketUTCTimestamp, data);
		}

		void update_with_TradeCancelCorrection (
			Timestamp const & server_timestamp,
			Types::QuotationTradeCancelCorrection const & data
			)
		{
			if ( ! m_process_trade_cancel_correction_enabled.get())
			{
				return;
			}
			Timestamp t = server_timestamp;
			if (t.is_null()) {
				t.set_to_now_utc();
			}
			SCOPE_AUTO_LOCK (l, get_lock4_var_map());
			update_with_TradeCancelCorrection_impl(
				t,
				data
			);
		}

		void update_with_TradeCancelCorrection_nolock (
			Timestamp const & server_timestamp,
			Types::QuotationTradeCancelCorrection const & data
			)
		{
			if ( ! m_process_trade_cancel_correction_enabled.get())
			{
				return;
			}
			Timestamp t = server_timestamp;
			if (t.is_null()) {
				t.set_to_now_utc();
			}
			update_with_TradeCancelCorrection_impl(
				t,
				data
			);
		}

		// deprecated
		void update_with_TradeEvent			(
												Timestamp const & inMarketUTCTimestamp,
												Types::QuotationTradeEvent const & data
											)
		{
			notif_TradeEvent_into_TradeEventExt (*this, 0, inMarketUTCTimestamp, data/*, Timestamp()*/); // let the default serverUTCTimestamp be set to "now"
		}

		inline void	get_best_limits (Types::OrderBookBestLimitsExt & limits) const
		{
			SCOPE_AUTO_LOCK (l,get_lock4_var_map());
			get_best_limits_nolock (limits);
		}

		Types::OrderBookBestLimitsExt const & get_best_limits_nolock () const
		{
			return m_best_limits;
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
									Timestamp const & trade_execution_timestamp,
									Types::ListOfQuotationVariable const & values
								);

		typedef std::set< Types::TagNumber > SetOfTagNumber;

		inline void	reset_tracking()									{ m_best_bid_was_updated = m_best_ask_was_updated = false; m_tags_of_values_updated.clear(); }
		inline bool bid_updated() const								{ return m_best_bid_was_updated; }
		inline bool ask_updated() const								{ return m_best_ask_was_updated; }
		inline SetOfTagNumber const& tags_updated() const				{ return m_tags_of_values_updated; }
		inline bool tag_updated(Types::TagNumber const & tag)	const	{ return (m_tags_of_values_updated.find(tag) != m_tags_of_values_updated.end()); }

		// session and extended hours management
		static Types::FOSTradingSessionId const	s_SessionIdUndefined = 0;

	private:
		LockedBool		m_process_trade_cancel_correction_enabled;

		// Tracking values ​​that have changed
		LockedBool		m_track_updates_enabled;
		bool			m_best_bid_was_updated;
		bool			m_best_ask_was_updated;
		SetOfTagNumber	m_tags_of_values_updated;

		void add_tag_updated(Types::TagNumber const & tag);
		void add_tag_deleted(Types::TagNumber const & tag);

		Types::OrderBookBestLimitsExt		m_best_limits;

		void fill_default_values();

		void update_with_TradeEventExt_impl(Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, Types::QuotationTradeEventExt const & data);
		void update_with_TradeCancelCorrection_impl(Timestamp const & server_timestamp, Types::QuotationTradeCancelCorrection const & data);

		void consume_trade_event ( float64 price
		                         , float64 qty
		                         , Timestamp const & trade_execution_timestamp
		                         , Types::QuotationContentMask content_mask
		                         , bool has_actual_trading_session_id
		                         , Types::QuotationTradeImpactIndicatorMask trade_impact_indicator
		                         );
		void extract_trade_context (Types::ListOfQuotationVariable const & data
		                           , bool & has_actual_trading_session_id
		                           , Types::QuotationTradeImpactIndicatorMask & trade_impact_indicator
		                           , Timestamp & trade_execution_timestamp
		                           ) const;
		void extract_trade_execution_timestamp(Types::ListOfQuotationVariable const & data
											   , Timestamp & trade_execution_timestamp) const;
		void reset_session_aggregates(Types::QuotationContentMask content_mask);
		void reset_daily_aggregates(Timestamp const & srv_ts, FeedOS::Types::QuotationContentMask content_mask);

		void update_values_nolock (
									Timestamp const & inServerUTCTimestamp,
									Timestamp const & inMarketUTCTimestamp,
									Timestamp const & trade_execution_timestamp,
									Types::ListOfQuotationVariable const & values,
									bool update_session_tags
								);
		inline void	set_or_delete_timestamp_tag_nolock(Types::TagNumber tag_num, Timestamp const & ts)
		{
			if (ts.is_null())
			{
				delete_tag_nolock(tag_num);
			}
			else
			{
				set_tag_nolock(tag_num, Any(ts));
			}
		}

	public:
		static bool is_session_regular (int8 s) { return s > s_SessionIdUndefined; }
		static bool is_session_extended (int8 s) { return s < s_SessionIdUndefined; }

		bool operator== (FeedOS::InstrumentQuotationData_2 const &) const;

		// overloaded from InstrumentTagData
		virtual void load (std::vector<Types::TagNumAndValue> const & tags, bool allow_tag_reset = false);
		virtual void load_hook() { }

		// Load all tags given in parameters (no tag removal)
		void load_all (std::vector<Types::TagNumAndValue> const & tags);

		void load(Types::InstrumentStatus const & status);

		void delete_tag_nolock(Types::TagNumber tag_num);
		bool tag_is_present_nolock(Types::TagNumber tag_num) const;
		bool tag_is_present(Types::TagNumber tag_num) const;
		void dump (std::vector<Types::TagNumAndValue> & tags) const;
		void dump (std::vector<Types::TagNumAndValue> & tags, std::vector<Types::TagNumber> const & requested_list) const;

		void check_tagmap_consistency () const;
		void set_track_updates_enabled(bool v) { m_track_updates_enabled = v; }
		void set_trade_cancel_correction_processing(bool v) { m_process_trade_cancel_correction_enabled = v; }

		// needed for notif_TradeEvent_into_TradeEventExt() to work
		virtual void notif_TradeEventExt	(
												FOSInstrumentCode,
												Timestamp const & inServerUTCTimestamp,
												Timestamp const & inMarketUTCTimestamp,
												Types::QuotationTradeEventExt const & data
									)
		{
			update_with_TradeEventExt (inServerUTCTimestamp, inMarketUTCTimestamp, data);
		}

		virtual void notif_TradeCancelCorrection(
				  FOSInstrumentCode
				, Timestamp const & server_timestamp
				, Types::QuotationTradeCancelCorrection const & data
			)
		{
			if ( ! m_process_trade_cancel_correction_enabled.get())
			{
				return;
			}
			update_with_TradeCancelCorrection(server_timestamp, data);
		}

	private:
		// for tests purpose
		friend struct UNIT_TEST::InstrumentQuotationData_TestSuite;
	};

} // end namespace feedos

#endif // end if FEEDOS_FRAMEWORK_INSTRUMENT_QUOTATION_DATA_2_H
