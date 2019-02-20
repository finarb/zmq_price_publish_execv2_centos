
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2011 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_MARKETSHEET_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_MARKETSHEET_DATA_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#	include "InstrumentTagData.h"
#endif

#include <deque>

#include <sstream>

namespace FeedOS {

	/*!
	* @brief dedicated to build a MarketSheet snapshot based on MarketSheet real-time events 
	*/
	class InstrumentMarketSheetData
	{
	public:
		
		typedef std::deque<Types::MarketSheetEntryAndContext> TMarketSheetSide;

		InstrumentMarketSheetData () 
		{
			reset();
		}

		InstrumentMarketSheetData (InstrumentMarketSheetData const &v)
		{
			m_InstrCode = v.m_InstrCode;
			m_Timestamps = v.m_Timestamps;
			m_BidMarketSheetSide = v.m_BidMarketSheetSide;
			m_AskMarketSheetSide = v.m_AskMarketSheetSide;
			m_OtherValues = v.m_OtherValues;
			m_LastUpdateFailedFlag = v.m_LastUpdateFailedFlag;
		}

		InstrumentMarketSheetData (FOSInstrumentCode const & instr_code):
			m_InstrCode (instr_code)
		{
			Types::init_feedos_type (m_Timestamps);
			m_BidMarketSheetSide.clear();
			m_AskMarketSheetSide.clear();
			Types::init_feedos_type (m_OtherValues);
			m_LastUpdateFailedFlag = false;
		}

		void setTimestamps(Timestamp const& server, Timestamp const & market)
		{
			m_Timestamps.setServer (server);
			m_Timestamps.setMarket (market);
		}

		Timestamp const & get_server_utc_timestamp() const	{ return m_Timestamps.getServer(); }
		Timestamp const & get_market_utc_timestamp() const	{ return m_Timestamps.getMarket(); }

		void reset()
		{
#ifdef _DEBUG
			log_incoming_event (m_InstrCode, Timestamp::null(), Timestamp::null(),"reset()");
#endif
			Types::init_feedos_type (m_InstrCode);
			Types::init_feedos_type (m_Timestamps);
			m_BidMarketSheetSide.clear();
			m_AskMarketSheetSide.clear();
			Types::init_feedos_type (m_OtherValues);
			m_LastUpdateFailedFlag = false;
		}

		FOSInstrumentCode get_internal_code() const			{ return m_InstrCode;	}
		void set_internal_code(FOSInstrumentCode const & c) { m_InstrCode=c;		}

		void setName(std::string const & name)				{ m_Name.assign(name); }
		std::string const & getName() const					
		{ 
			static std::string const s_DefaultName("InstrumentMaketSheetData"); 
			return (m_Name.empty() ? s_DefaultName : m_Name); }

		void extractSnapshot (Types::InstrumentStatusMarketSheet& snapshot)
		{
			snapshot.setCode(m_InstrCode);
			snapshot.setServerUTCTimestamp(m_Timestamps.getServer());
			snapshot.setMarketUTCTimestamp(m_Timestamps.getMarket());
			extractMarketSheet(snapshot.getMarketSheet());
			snapshot.setValues(m_OtherValues);
		}

		Types::ListOfQuotationVariable const & getValues() const
		{
			return m_OtherValues;
		}

		Types::ListOfQuotationVariable& getValues() 
		{
			return m_OtherValues;
		}

		template <typename CONTAINER>
		void extractEntriesToLevel(Types::FIXSide side, Types::MarketSheetLevel const inLevel, CONTAINER & entries)
		{
			TMarketSheetSide & sheet_side = getMarketSheetSide(side);
			std::copy(sheet_side.begin(),sheet_side.begin() + inLevel, std::back_inserter(entries));
		}

// Extract deque elements and insert them into target vector side
#define FEEDOS_SET_MARKET_SHEET_FROM_INTERNAL(market_sheet,SIDE) \
	Types::ListOfMarketSheetEntryAndContext & SIDE##_target = market_sheet.get##SIDE##Side(); \
	size_t SIDE##size_entries = m_##SIDE##MarketSheetSide.size(); \
	if (SIDE##size_entries > 0) \
	{ \
	SIDE##_target.reserve(SIDE##size_entries);\
	TMarketSheetSide::const_iterator const end_entry = m_##SIDE##MarketSheetSide.end(); \
	for (TMarketSheetSide::const_iterator cur_entry = m_##SIDE##MarketSheetSide.begin(); end_entry != cur_entry; ++cur_entry) \
		SIDE##_target.push_back( *cur_entry ); \
	}

		void extractMarketSheet(Types::MarketSheet & market_sheet) const	
		{ 
			{
				FEEDOS_SET_MARKET_SHEET_FROM_INTERNAL(market_sheet,Bid);
			}
			{
				FEEDOS_SET_MARKET_SHEET_FROM_INTERNAL(market_sheet,Ask);
			}
		}

// Extract vector elements and insert them into deque side
#define FEEDOS_SET_INTERNAL_FROM_MARKET_SHEET(market_sheet,SIDE) \
	Types::ListOfMarketSheetEntryAndContext const & SIDE##_side = market_sheet.get##SIDE##Side(); \
	Types::ListOfMarketSheetEntryAndContext::const_iterator const SIDE##_end = SIDE##_side.end(); \
	m_##SIDE##MarketSheetSide.clear(); \
	for (Types::ListOfMarketSheetEntryAndContext::const_iterator cur = SIDE##_side.begin(); SIDE##_end != cur; ++cur) \
		m_##SIDE##MarketSheetSide.push_back(*cur);

		void setMarketSheet(Types::MarketSheet const & inSnapshot)
		{
		 	{
				FEEDOS_SET_INTERNAL_FROM_MARKET_SHEET(inSnapshot,Bid);
			}
			{
				FEEDOS_SET_INTERNAL_FROM_MARKET_SHEET(inSnapshot,Ask);
			}
		}

		bool getEntry (Types::FIXSide side, Types::MarketSheetLevel const & in_level, Types::MarketSheetEntry & old_entry)
		{
			TMarketSheetSide & sheet_side = getMarketSheetSide(side);
			if (sheet_side.size() > in_level)
			{
				old_entry = sheet_side[in_level].getOrder();
				return true;
			}
			return false;
		}

		// return true if an error occured while updating market sheet cache
		bool getLastUpdateFailedFlag() const { return m_LastUpdateFailedFlag; }
		void resetLastUpdateFailedFlag() { m_LastUpdateFailedFlag = false; }

		TMarketSheetSide&
		getMarketSheetSide(Types::FIXSide side)
		{
#if FEEDOS_ENABLE_PARANOID_CHECKS
			switch (side) {
			case Types::FIXSide_Buy:
			case Types::FIXSide_Sell:
				break;
			default:
				log_invalid_getMarketSheetSide(side);
			}
#endif
			return (side==Types::FIXSide_Buy) ? m_BidMarketSheetSide : m_AskMarketSheetSide;
		}

		struct MarketSheetErrors
		{
			MarketSheetErrors():m_invalid_getMarketSheetSide(0),m_order_id_mismatch(0),m_out_of_range(0)
			{}

			void reset ()
			{
				m_invalid_getMarketSheetSide = 0;
				m_order_id_mismatch = 0;
				m_out_of_range = 0;
			}

			void incInvalidGetMarketSheetSide() { ++m_invalid_getMarketSheetSide; }
			void incOrderIdMismatch()			{ ++m_order_id_mismatch; }
			void incOutOfRange()				{ ++m_out_of_range; }
			/*!
			 * @brief return overall error counters
			 */
			unsigned int getOverallCounters() const { return (m_invalid_getMarketSheetSide+m_order_id_mismatch+m_out_of_range); }

		private:
			volatile unsigned int m_invalid_getMarketSheetSide;
			volatile unsigned int m_order_id_mismatch;
			volatile unsigned int m_out_of_range;
		};
		static MarketSheetErrors const & getErrorCounters() { return s_ErrorCounters; }
		static void resetErrorCounters() { s_ErrorCounters.reset (); }

	private:
		FOSInstrumentCode							m_InstrCode;
		Types::UTCTimestamps						m_Timestamps;
		TMarketSheetSide							m_BidMarketSheetSide;
		TMarketSheetSide							m_AskMarketSheetSide;
		Types::ListOfQuotationVariable				m_OtherValues;

		bool										m_LastUpdateFailedFlag;
		
		static MarketSheetErrors					s_ErrorCounters;
		std::string									m_Name;

		bool 
			checkMarketSheetLevelLower(	Types::MarketSheetLevel market_sheet_side_size, 
										Types::MarketSheetLevel level, 
										FOSInstrumentCode const & code,
										Timestamp const & server_timestamp,
										Timestamp const & market_timestamp )
		{
			if (market_sheet_side_size > level)
			{
				return true;
			}
			else
			{
				m_LastUpdateFailedFlag = true;
				log_out_of_range (market_sheet_side_size, level, code, server_timestamp, market_timestamp);
				return false;
			}
		}

		bool checkMarketSheetLevelLowerOrEqual(	Types::MarketSheetLevel market_sheet_side_size, 
												Types::MarketSheetLevel level, 
												FOSInstrumentCode const & code,
												Timestamp const & server_timestamp,
												Timestamp const & market_timestamp)
		{
			if (market_sheet_side_size >= level)
			{
				return true;
			}
			else
			{
				m_LastUpdateFailedFlag = true;
				log_out_of_range (market_sheet_side_size, level, code, server_timestamp, market_timestamp);
				return false;
			}
		}

	public:
		Types::FIXSecurityTradingStatus	get_trading_status() const;

		// MarketSheet events consumer responsability
		void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started (FOSInstrumentCode inInternalCode, Timestamp const & inLastUpdateServerUTCTimestamp, Timestamp const & inLastUpdateMarketUTCTimestamp,  Types::MarketSheet const & inSnapshot)
		{
#ifdef _DEBUG
			log_incoming_event (inInternalCode, inLastUpdateServerUTCTimestamp, inLastUpdateMarketUTCTimestamp,"response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started()", dump_market_sheet(&inSnapshot,false));
#else
			static_cast<void> (inInternalCode);
#endif			
			setTimestamps (inLastUpdateServerUTCTimestamp,inLastUpdateMarketUTCTimestamp);
			setMarketSheet (inSnapshot);
			getValues().clear();
		}

		void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed (ReturnCode)
		{
#ifdef _DEBUG
			log_incoming_event (m_InstrCode, Timestamp::null(), Timestamp::null(),"response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed()");
#endif
			reset();
		}

		void aborted_QUOTATION_SubscribeOneInstrumentMarketSheet (ReturnCode)
		{
#ifdef _DEBUG
			log_incoming_event(m_InstrCode, Timestamp::null(), Timestamp::null(),"aborted_QUOTATION_SubscribeOneInstrumentMarketSheet()");
#endif
			reset();
		}

		void notif_NewOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::ListOfQuotationContextFlag const & inContext,  Types::FIXSide inSide,  Types::MarketSheetEntry const & inEntry,  Types::MarketSheetLevel inLevel)
		{
#ifdef _DEBUG
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_NewOrder()",dump_market_sheet(NULL,true));
#endif
			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);
			TMarketSheetSide & market_sheet_side =  getMarketSheetSide(inSide);
			Types::MarketSheetLevel const entries_size = static_cast<Types::MarketSheetLevel>(market_sheet_side.size());
			if (!checkMarketSheetLevelLowerOrEqual(entries_size, inLevel, inCode, inServerUTCTimestamp, inMarketUTCTimestamp))
			{
				return;
			}

			if (entries_size == inLevel)
			{
				market_sheet_side.push_back(Types::MarketSheetEntryAndContext(inEntry, inContext));
			}
			else
			{
				market_sheet_side.insert(market_sheet_side.begin()+inLevel,Types::MarketSheetEntryAndContext(inEntry, inContext));
			}
		}

		void notif_ModifyOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::ListOfQuotationContextFlag const & inContext,  Types::FIXSide inSide,  Types::MarketSheetEntry const & inEntry,  Types::MarketSheetLevel inOldLevel,  Types::MarketSheetLevel inNewLevel)
		{
#ifdef _DEBUG
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_ModifyOrder()",dump_market_sheet(NULL,true));
#endif
			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);
			TMarketSheetSide & market_sheet_side = getMarketSheetSide(inSide);
			Types::MarketSheetLevel const entries_size = static_cast<Types::MarketSheetLevel>(market_sheet_side.size());
			if (inOldLevel == inNewLevel)
			{
				if (! checkMarketSheetLevelLower(entries_size, inOldLevel, inCode, inServerUTCTimestamp, inMarketUTCTimestamp))
				{	
					return;
				}

				Types::MarketSheetEntryAndContext& market_sheet_entry = market_sheet_side[inOldLevel];
				// update context flags vector in place (no alloc): merge new context in current context
				mergeQuotationContextFlags(market_sheet_entry.getContext(), inContext);
				market_sheet_entry.setOrder(inEntry);
			}
			else
			{
				if (!checkMarketSheetLevelLower(entries_size, inNewLevel, inCode, inServerUTCTimestamp, inMarketUTCTimestamp))
				{
					return;
				}
				static std::string const s_ModifyOrder("notif_ModifyOrder");
				if (! checkLevelAndOrderID(
					entries_size,
					market_sheet_side,
					inEntry.getOrderID(),
					inOldLevel, 
					s_ModifyOrder,
					inCode,
					inServerUTCTimestamp,
					inMarketUTCTimestamp))
				{	
					return;
				}
				market_sheet_side.erase(market_sheet_side.begin() + inOldLevel);
				market_sheet_side.insert(market_sheet_side.begin()+ inNewLevel,Types::MarketSheetEntryAndContext(inEntry,inContext));
			}
		}

		void notif_RemoveOneOrder	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::ListOfQuotationContextFlag const &,  Types::FIXSide inSide, String const & inOrderID,  Types::MarketSheetLevel inLevel)
		{
#ifdef _DEBUG
			std::stringstream remove_order_ouputer;
			remove_order_ouputer << " removeOneOrder on" << inOrderID << " at level="<< inLevel << " sheet="<< dump_market_sheet(NULL,true);
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_RemoveOneOrder()",remove_order_ouputer.str());
#endif

			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);

			TMarketSheetSide & market_sheet_side = getMarketSheetSide(inSide);
			Types::MarketSheetLevel const entries_size = static_cast<Types::MarketSheetLevel>(market_sheet_side.size());
			static std::string const s_RemoveOneOrder("notif_RemoveOneOrder");
			if ( !checkLevelAndOrderID(
				entries_size,
				market_sheet_side,
				inOrderID,
				inLevel, 
				s_RemoveOneOrder,
				inCode,
				inServerUTCTimestamp,
				inMarketUTCTimestamp))
			{
				return;
			}
			market_sheet_side.erase(market_sheet_side.begin() + inLevel);
#ifdef _DEBUG
			log_market_sheet(inCode, "notif_RemoveOneOrder()");
#endif
		}

		void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::ListOfQuotationContextFlag const &,  Types::FIXSide inSide, String const & inOrderID,  Types::MarketSheetLevel inLevel)
		{
#ifdef _DEBUG
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_RemoveAllPreviousOrders()");
#endif
			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);

			TMarketSheetSide& market_sheet_side = getMarketSheetSide(inSide);
			Types::MarketSheetLevel const entries_size = static_cast<Types::MarketSheetLevel>(market_sheet_side.size());
			static std::string const s_RemoveAllPreviousOrders("notif_RemoveAllPreviousOrders");
			if ( !checkLevelAndOrderID(
				entries_size,
				market_sheet_side,
				inOrderID, 
				inLevel, 
				s_RemoveAllPreviousOrders,
				inCode,
				inServerUTCTimestamp,
				inMarketUTCTimestamp))
			{
				return;
			}
			market_sheet_side.erase(market_sheet_side.begin(), market_sheet_side.begin() + inLevel + 1);
#ifdef _DEBUG
			log_market_sheet(inCode, "notif_RemoveAllPreviousOrders()");
#endif
		}

		void notif_RemoveAllOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::ListOfQuotationContextFlag const &,  Types::FIXSide inSide)
		{
#ifdef _DEBUG
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_RemoveAllOrders()");
#else
			static_cast<void> (inCode);
#endif
			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);
			switch (inSide)
			{
			case Types::FIXSide_BuyAndSell:
				m_AskMarketSheetSide.clear();
			case Types::FIXSide_Buy:
				m_BidMarketSheetSide.clear();
				break;
			case Types::FIXSide_Sell:
				m_AskMarketSheetSide.clear();
				break;
			default:
				log_invalid_getMarketSheetSide (inSide);
				break;
			}
#ifdef _DEBUG
			log_market_sheet(inCode, "notif_RemoveAllOrders()");
#endif
		}

		void notif_Retransmission	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  Types::MarketSheet const & inSnapshot)
		{
#ifdef _DEBUG
			log_incoming_event(inCode, inServerUTCTimestamp, inMarketUTCTimestamp,"notif_Retransmission()");
#else
			static_cast<void> (inCode);
#endif
			setTimestamps (inServerUTCTimestamp,inMarketUTCTimestamp);
			setMarketSheet(inSnapshot);
#ifdef _DEBUG
			log_market_sheet(inCode, "notif_Retransmission()");
#endif
		}

		void notif_ValuesUpdateOneInstrument(FOSInstrumentCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, Types::ListOfQuotationVariable const & inValues);

		static bool update_value (Types::QuotationVariable const & new_var, Types::ListOfQuotationVariable & values)
		{
			Types::TagNumber tag_num = new_var.getNum();
			Any const & new_value = new_var.getValue();
			Types::ListOfQuotationVariable::iterator const end_values = values.end();
			for (Types::ListOfQuotationVariable::iterator it = values.begin(); end_values != it; ++it)
			{
				Types::QuotationVariable & cur_var = *it;
				if (cur_var.getNum()==tag_num)
				{
					if (Syntax_UNKNOWN == new_value.get_syntax())
					{
						// special case: means "delete value"
						values.erase (it);
					}
					else
					{
						// update value
						cur_var.getValue() = new_value;
					}
					return true;
				}
			}
			return false; // value not found
		}

		static void mergeQuotationContextFlags(	Types::ListOfQuotationContextFlag & inOutContext,
												Types::ListOfQuotationContextFlag const & newContext)
		{
			Types::ListOfQuotationContextFlag::const_iterator const new_context_end = newContext.end();
			for (	Types::ListOfQuotationContextFlag::const_iterator new_item = newContext.begin();
					new_context_end != new_item;
					++new_item)
			{
				// Do not add tag if value syntax is unknown
				if (!update_value(*new_item, inOutContext) && (Syntax_UNKNOWN != new_item->getValue().get_syntax()))
				{
					inOutContext.push_back(*new_item); // add a brand new context value
				}
			}
		}

	protected:
		bool checkLevelAndOrderID(
			Types::MarketSheetLevel market_sheet_side_size,
			TMarketSheetSide const & market_sheet_side,
			String const & order_id,
			Types::MarketSheetLevel level, 
			std::string const & called_from,
			FOSInstrumentCode const & in_code,
			Timestamp const & server_timestamp,
			Timestamp const & market_timestamp)
		{
			if (level < market_sheet_side_size)
			{	
				String const & new_order_id = (market_sheet_side[level]).getOrder().getOrderID();
				if (order_id == new_order_id)
				{
					return true;
				}
				else
				{
					m_LastUpdateFailedFlag = true;
					log_order_id_mismatch (new_order_id, order_id, called_from, in_code, server_timestamp, market_timestamp);	
					return false;
				}
			}
			m_LastUpdateFailedFlag = true;
			log_out_of_range (market_sheet_side_size, level, in_code, server_timestamp, market_timestamp );
			return false;
		}

	private:
		void log_incoming_event	(	FOSInstrumentCode inCode, 
									Timestamp const & inServerUTCTimestamp, 
									Timestamp const & inMarketUTCTimestamp, 
									const char * where, 
									std::string const what = "");
		void log_invalid_getMarketSheetSide  (Types::FIXSide side) const;
		void log_out_of_range (	Types::MarketSheetLevel side_depth, Types::MarketSheetLevel level, FOSInstrumentCode const & code, 
								Timestamp const & server_ts, Timestamp const & market_ts) const;
		void log_order_id_mismatch (String const & new_order_id, String const & old_order_id, std::string const & called_from, FOSInstrumentCode const & code,
								Timestamp const & server_ts, Timestamp const & market_ts) const;
		void log_market_sheet  (FOSInstrumentCode inCode, const char * where);

		std::string dump_market_sheet(Types::MarketSheet const * snapshot, bool dump_mine );
	};

} // namespace FeedOS

#endif
