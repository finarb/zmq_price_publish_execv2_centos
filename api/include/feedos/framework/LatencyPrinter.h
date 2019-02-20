
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2010			**/
/**										**/
/*****************************************/

#ifndef FEEDOS_FRAMEWORK_LATENCY_PRINTER_H
#define FEEDOS_FRAMEWORK_LATENCY_PRINTER_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#include "FeedPrinter_L1.h"
#include "FeedPrinter_L2.h"
#include "FeedPrinter_MBO.h"

#include <limits>

namespace FeedOS
{

typedef enum
{
	FeedKind_legacy_L1,
	FeedKind_L1,
	FeedKind_legacy_MBL,
	FeedKind_MBL,
	FeedKind_MBO,

	FeedKind__last_value
} FeedKind;

inline
char const * kind2str(FeedKind sub_kind)
{
	static char const * const str[FeedKind__last_value] =
		{
			"l1",
			"L1",
			"mbl",
			"MBL",
			"MBO",
		};
	return str[sub_kind];
}

class LatencyStats
{
	int64 m_delta_cumulated_latency_us;
	int64 m_delta_cumulated_latency_us_nb_points;
	int64 m_delta_max_latency_us;
	int64 m_delta_min_latency_us;

public:

	static char const * print_unit_str () { return "milliseconds"; }
	static void print_latency (std::ostream & os, int64 v_microsec)
	{
		double const v_millisec = static_cast<double>(v_microsec)/1000;
		os.flags(static_cast<std::ios::fmtflags> (std::ios::right+std::ios::fixed));
		os.width(10);
		os.precision(3);
		os << v_millisec;
	}

	LatencyStats()
	{
		reset();
	}

	void reset()
	{
		m_delta_max_latency_us = (int64)std::numeric_limits<int64>::min();
		m_delta_min_latency_us = (int64)std::numeric_limits<int64>::max();
		m_delta_cumulated_latency_us=0;
		m_delta_cumulated_latency_us_nb_points=0;
	}

	void inc (int64 latency_us)
	{
		m_delta_max_latency_us = std::max(latency_us,m_delta_max_latency_us);
		m_delta_min_latency_us = std::min(latency_us,m_delta_min_latency_us);
		++m_delta_cumulated_latency_us_nb_points;
		m_delta_cumulated_latency_us += latency_us;
	}

	void print_stats (std::ostream & os, bool const doReset);
};



class AllLatencyStats
{
public:
	AllLatencyStats()
	{}

	LatencyStats	recv_VS_server;
	LatencyStats	server_VS_market;

	void print_stats(std::ostream & os, bool const with_legend, bool const doReset);
};


class LatencyPrinter
{
public:

	LatencyPrinter (
						bool opt_silent, 
						std::ostream * stream_log_timestamps,
						std::ostream * stream_log_events
					);

	virtual ~LatencyPrinter();

	void intermediate_feedback();
	virtual void final_feedback();

	void reset_stat_max_counters();

	class DeltaBytesReporter
	{
	public:
		virtual ~DeltaBytesReporter() {}

		// return number of bytes received since last call
		virtual uint64 get_delta_bytes_received() const = 0;
	};

	void register_delta_bytes_reporter (DeltaBytesReporter & r);

protected:
	virtual void intermediate_feedback_HOOK	(std::ostream & ) {}
	virtual void final_feedback_HOOK		(std::ostream & ) {}
	virtual void feedback_msgs_per_sec_HOOK	(std::ostream & ) {}

public:

	//
	// L1 events
	//

	void process_TradeEventExt	(	FeedOS::FOSInstrumentCode inCode, 
									FeedOS::Timestamp const & inServerUTCTimestamp,
									FeedOS::Timestamp const & inMarketUTCTimestamp, 
									FeedOS::Types::QuotationTradeEventExt const & inData
								);

	void process_TradeCancelCorrection(	FeedOS::FOSInstrumentCode inCode,
									FeedOS::Timestamp const & inServerTimestamp,
									FeedOS::Types::QuotationTradeCancelCorrection const & inData
								);

	void process_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus);
	void process_MarketNews	(FeedOS::Types::MarketNews const & inNews);
	void process_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData);
	void process_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData);


	//
	// L2 events (legacy MBL)
	//

	void process_OrderBookRefresh	(	FeedOS::FOSInstrumentCode inCode, 
										FeedOS::Timestamp const & inServerUTCTimestamp, 
										FeedOS::int8 inBidChangeIndicator, 
										FeedOS::int8 inAskChangeIndicator, 
										FeedOS::Types::ListOfOrderBookEntry const & inBidLimits, 
										FeedOS::Types::ListOfOrderBookEntry const & inAskLimits
									);
	void process_OrderBookDeltaRefresh	(	FeedOS::FOSInstrumentCode inCode,
											FeedOS::Timestamp const & inServerUTCTimestamp, 
											FeedOS::Types::OrderBookDeltaRefresh const & inDelta
										);
	void process_OrderBookMaxVisibleDepth(	FeedOS::FOSInstrumentCode inCode,
											FeedOS::int8 inMaxVisibleDepth
										);


	//
	// MBL events
	//

	void process_MBLFullRefresh	(FeedOS::Types::ListOfMBLSnapshot const & inData);

	void process_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData)
	{
		static FeedKind const sub_kind = FeedKind_MBL;
		process_point (sub_kind, inData.getCode(), inData.getTimestamps().getServer(), inData.getTimestamps().getMarket());
		++m_counter_delta_nb_msg;	feedback_if_needed();
		if (m_feed_printer_L2)
		{
			m_feed_printer_L2->notif_MBLOverlapRefresh(inData);
		}
	}

	void process_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData)
	{
		static FeedKind const sub_kind = FeedKind_MBL;
		process_point (sub_kind, inData.getCode(), inData.getTimestamps().getServer(), inData.getTimestamps().getMarket());
		++m_counter_delta_nb_msg;	feedback_if_needed();
		if (m_feed_printer_L2)
		{
			m_feed_printer_L2->notif_MBLDeltaRefresh(inData);
		}
	}

	void process_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData);


	//
	// MBO events
	//

	void process_MBO_NewOrder					(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inLevel)
	{
		static FeedKind const sub_kind = FeedKind_MBO;
		process_point (sub_kind, inCode, inServerUTCTimestamp, inMarketUTCTimestamp);
		++m_counter_delta_nb_msg;	feedback_if_needed();
		if (m_feed_printer_MBO)
		{
			m_feed_printer_MBO->notif_NewOrder(inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inEntry, inLevel);
		}
	}

	void process_MBO_ModifyOrder				(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inOldLevel, FeedOS::Types::MarketSheetLevel inNewLevel)
	{
		static FeedKind const sub_kind = FeedKind_MBO;
		process_point (sub_kind, inCode, inServerUTCTimestamp, inMarketUTCTimestamp);
		++m_counter_delta_nb_msg;	feedback_if_needed();
		if (m_feed_printer_MBO)
		{
			m_feed_printer_MBO->notif_ModifyOrder(inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inEntry, inOldLevel, inNewLevel);
		}
	}

	void process_MBO_RemoveOneOrder			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel)
	{
		static FeedKind const sub_kind = FeedKind_MBO;
		process_point (sub_kind, inCode, inServerUTCTimestamp, inMarketUTCTimestamp);
		++m_counter_delta_nb_msg;	feedback_if_needed();
		if (m_feed_printer_MBO)
		{
			m_feed_printer_MBO->notif_RemoveOneOrder(inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inOrderID, inLevel);
		}
	}

	void process_MBO_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel);
	void process_MBO_RemoveAllOrders			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide);
	void process_MBO_Retransmission				(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::MarketSheet const & inSnapshot);
	void process_MBO_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues);

private:
	uint64 m_counter_sub_OK;
	uint64 m_counter_sub_FAILED;
	uint64 m_counter_instr_total_OK;
	uint64 m_counter_instr_total_FAILED;
	uint64 m_counter_delta_nb_msg;
	uint64 m_max_nb_msgs_per_sec;
	uint64 m_max_nb_bytes_per_sec;
	uint64 m_total_msgs;
	uint64 m_total_bytes;
	uint64 m_total_duration_in_sec;
	std::ostream * const m_stream_log_timestamps;
	std::ostream * const m_stream_log_events;

	FeedPrinter_L1_base		* const m_feed_printer_L1;
	FeedPrinter_L2_base		* const m_feed_printer_L2;
	FeedPrinter_MBO_base	* const m_feed_printer_MBO;

	bool const m_opt_silent;

	typedef std::map<FeedKind, AllLatencyStats> StatsPerKind;
	typedef std::map<FOSMarketId, StatsPerKind> StatsPerMIC;
	StatsPerMIC	m_latency_per_mic_per_kind;

	typedef std::map<FeedKind, std::pair<unsigned int,unsigned int> > InstrSubscriptionSuccessMap;
	InstrSubscriptionSuccessMap	m_counter_instruments_per_kind;

	static int const PERIOD_FEEDBACK_SEC = 1;

	Timestamp		m_start_time;
	Timestamp		m_receive_timestamp;
	Timestamp		m_feedback_last_update;
	Timestamp		m_lag_last_update;

	DeltaBytesReporter *	m_delta_bytes_reporter;

	virtual uint64 get_delta_bytes_received() const
	{
		return m_delta_bytes_reporter ? m_delta_bytes_reporter->get_delta_bytes_received() : 0;
	}

	void dump_stats_report_and_reset_lags	(std::ostream & s);

	void print_msgs_per_sec(std::ostream & s);

	inline void feedback_if_needed()
	{
		if (m_opt_silent)
			return;

		// assume that a "receive timestamp" has been taken recently
		Timestamp const & feedback_now = m_receive_timestamp;

		if (feedback_now.diff_seconds (m_feedback_last_update) >= PERIOD_FEEDBACK_SEC) {
			m_total_duration_in_sec = feedback_now.diff_seconds (m_start_time);
			m_feedback_last_update = feedback_now;
			feedback_msgs_per_sec();
		}
	}

	void feedback_msgs_per_sec();
	void feedback_sub_counters();

	void log_timestamps (	FeedKind sub_kind,
							FOSInstrumentCode const & instr_code,
							Timestamp const & reception_time,
							Timestamp const & server_time,
							Timestamp const & market_time,
							ListOfQuotationContextFlag const & context,
							bool suspicious_market_timestamp
						);

	inline void process_point (	FeedKind sub_kind,
								FOSInstrumentCode const & instr_code,
								Timestamp const & server_time,
								Timestamp const & market_time
							)
	{
		static ListOfQuotationContextFlag const null_context;
		process_point (	sub_kind, instr_code, server_time, market_time, null_context, 
						false	// TODO -- try to assess if market_time is suspicious (i.e. may not be realtime)
						);
	}

	void process_point (	FeedKind sub_kind,
							FOSInstrumentCode const & instr_code,
							Timestamp const & server_time,
							Timestamp const & market_time,
							ListOfQuotationContextFlag const & context,
							bool suspicious_market_timestamp
						)
	{
		m_receive_timestamp.set_to_now_utc();

		AllLatencyStats & stats = m_latency_per_mic_per_kind[instr_code.get_market_id()][sub_kind];

		if (!server_time.is_null()) {
			stats.recv_VS_server.inc (m_receive_timestamp.diff_microsec (server_time));
			if (!market_time.is_null() && !suspicious_market_timestamp) {
				stats.server_VS_market.inc (server_time.diff_microsec (market_time));
			}
		}

		if (m_stream_log_timestamps) {
			log_timestamps (sub_kind, instr_code, m_receive_timestamp, server_time, market_time, context, suspicious_market_timestamp);
		}
	}



protected:
	FeedOS::ExclusiveLock m_screen_lock;

	void inc_sub(FeedKind sub_kind, bool success);
	void inc_instr(FeedKind sub_kind, bool success);
	void dec_sub (FeedKind const sub_kind, bool success);

};


template <typename A, typename B, typename C, typename D>
class LatencyPrinter_notifs_adapter:
	public LatencyPrinter,
	public virtual A,
	public virtual B,
	public virtual C,
	public virtual D
{

public:
	LatencyPrinter_notifs_adapter(
													bool opt_silent, 
													std::ostream * stream_log_timestamps,
													std::ostream * stream_log_events
												)
		:LatencyPrinter (opt_silent, stream_log_timestamps, stream_log_events)
	{}

	///////// L1
	void notif_TradeEventExt	(	FeedOS::FOSInstrumentCode inCode, 
										FeedOS::Timestamp const & inServerUTCTimestamp,
										FeedOS::Timestamp const & inMarketUTCTimestamp, 
										FeedOS::Types::QuotationTradeEventExt const & inData
									)
	{
		process_TradeEventExt	(inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inData);
	}

	void notif_TradeCancelCorrection(	FeedOS::FOSInstrumentCode inCode,
										FeedOS::Timestamp const & inServerTimestamp,
										FeedOS::Types::QuotationTradeCancelCorrection const & inData
									)
	{
		process_TradeCancelCorrection(inCode, inServerTimestamp, inData);
	}

	void notif_MarketStatus	(FeedOS::Types::MarketStatus const & inStatus)
	{
		process_MarketStatus(inStatus);
	}

	void notif_MarketNews	(FeedOS::Types::MarketNews const & inNews)
	{
		process_MarketNews(inNews);
	}

	///////// legacy L1
	void notif_ValuesUpdate	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationValuesUpdate const & inData)
	{
		process_ValuesUpdate(inCode, inMarketUTCTimestamp, inData);
	}

	void notif_TradeEvent	(FOSInstrumentCode inCode, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::QuotationTradeEvent const & inData)
	{
		process_TradeEvent(inCode, inMarketUTCTimestamp, inData);
	}


	///////// legacy MBL
	void notif_OrderBookRefresh	(	FeedOS::FOSInstrumentCode inCode, 
									FeedOS::Timestamp const & inServerUTCTimestamp, 
									FeedOS::int8 inBidChangeIndicator, 
									FeedOS::int8 inAskChangeIndicator, 
									FeedOS::Types::ListOfOrderBookEntry const & inBidLimits, 
									FeedOS::Types::ListOfOrderBookEntry const & inAskLimits
								)
	{
		process_OrderBookRefresh	(inCode, inServerUTCTimestamp, inBidChangeIndicator, inAskChangeIndicator, inBidLimits, inAskLimits);
	}

	void notif_OrderBookDeltaRefresh	(	FeedOS::FOSInstrumentCode inCode,
											FeedOS::Timestamp const & inServerUTCTimestamp, 
											FeedOS::Types::OrderBookDeltaRefresh const & inDelta
										)
	{
		process_OrderBookDeltaRefresh	(inCode, inServerUTCTimestamp, inDelta);
	}

	void notif_OrderBookMaxVisibleDepth(	FeedOS::FOSInstrumentCode inCode,
											FeedOS::int8 inMaxVisibleDepth
										)
	{
		process_OrderBookMaxVisibleDepth	(inCode, inMaxVisibleDepth);
	}

	// MBL
	void notif_MBLFullRefresh(FeedOS::Types::ListOfMBLSnapshot const & inData)
	{
		process_MBLFullRefresh(inData);
	}

	void notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inData)
	{
		process_MBLOverlapRefresh(inData);
	}

	void notif_MBLDeltaRefresh	(FeedOS::Types::MBLDeltaRefresh const & inData)
	{
		process_MBLDeltaRefresh(inData);
	}

	void notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inData)
	{
		process_MBLMaxVisibleDepth(inData);
	}

	// MBO
	void notif_NewOrder					(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inLevel)
	{
		process_MBO_NewOrder (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inEntry, inLevel);
	}

	void notif_ModifyOrder				(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inOldLevel, FeedOS::Types::MarketSheetLevel inNewLevel)
	{
		process_MBO_ModifyOrder (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inEntry, inOldLevel, inNewLevel);
	}

	void notif_RemoveOneOrder			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel)
	{
		process_MBO_RemoveOneOrder (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inOrderID, inLevel);
	}

	void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel)
	{
		process_MBO_RemoveAllPreviousOrders (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide, inOrderID, inLevel);
	}

	void notif_RemoveAllOrders			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide)
	{
		process_MBO_RemoveAllOrders (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inContext, inSide);
	}

	void notif_Retransmission			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::MarketSheet const & inSnapshot)
	{
		process_MBO_Retransmission (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inSnapshot);
	}

	void notif_ValuesUpdateOneInstrument	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp,  FeedOS::Types::ListOfQuotationVariable const & inValues)
	{
		process_MBO_ValuesUpdateOneInstrument (inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inValues);
	}

};


struct Dummy_interface_1 {};
struct Dummy_interface_2 {};

class LatencyPrinter_broadcast_feeds:
	public LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming,
		FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming,
		FeedOS::INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming,
		Dummy_interface_1
		>
{
	typedef LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming,
		FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming,
		FeedOS::INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming,
		Dummy_interface_1
		> Parent;
public:

	LatencyPrinter_broadcast_feeds(
													bool opt_silent, 
													std::ostream * stream_log_timestamps,
													std::ostream * stream_log_events
												)
		:Parent (opt_silent, stream_log_timestamps, stream_log_events)
	{}

	// L1 subscription: start/stop callbacks
	void response_QUOTATION_SubscribeAllDataAndStatus_Started	() { inc_sub(FeedKind_L1, true); }
	void response_QUOTATION_SubscribeAllDataAndStatus_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_L1, false); }
	void aborted_QUOTATION_SubscribeAllDataAndStatus			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_L1, rc==RC_OK); }

	// L2 subscription: start/stop callbacks
	void response_QUOTATION_SubscribeAllOrderBook_Started	() { inc_sub(FeedKind_MBL, true); }
	void response_QUOTATION_SubscribeAllOrderBook_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_MBL, false); }
	void aborted_QUOTATION_SubscribeAllOrderBook			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_MBL, rc==RC_OK); }

	// MBO subscription: start/stop callbacks
	void response_QUOTATION_SubscribeAllMarketSheet_Started	() { inc_sub(FeedKind_MBO, true); }
	void response_QUOTATION_SubscribeAllMarketSheet_Failed	(ReturnCode /*rc*/) { inc_sub(FeedKind_MBO, false); }
	void aborted_QUOTATION_SubscribeAllMarketSheet			(ReturnCode rc) { dec_sub(FeedKind_MBO, rc==RC_OK); }



};



class LatencyPrinter_per_instrument_subscriptions:
	public LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming,			// Level 1
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming,			// MarketByLevel (legacy)
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming,			// MarketByLevel (new flavour)
		FeedOS::INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming	// MarketByOrder
		>
{
	typedef LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming,			
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL2_streaming,			
		FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming,			
		FeedOS::INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming
		> Parent;

	unsigned int	m_ticket_sub_L1;
	unsigned int	m_ticket_sub_L2;
	unsigned int	m_ticket_sub_MBL;

public:

	LatencyPrinter_per_instrument_subscriptions (
													bool opt_silent, 
													std::ostream * stream_log_timestamps,
													std::ostream * stream_log_events
												)
		:Parent (opt_silent, stream_log_timestamps, stream_log_events)
		,m_ticket_sub_L1(0)
		,m_ticket_sub_L2(0)
		,m_ticket_sub_MBL(0)
	{}

	void response_QUOTATION_SubscribeInstrumentsL1_Started (FeedOS::uint32 inTicket, FeedOS::Types::ListOfInstrumentStatusL1 const & inSnapshot);
	void response_QUOTATION_SubscribeInstrumentsL1_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_L1, false); }
	void aborted_QUOTATION_SubscribeInstrumentsL1			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_L1, rc==RC_OK); }

	void response_QUOTATION_SubscribeInstrumentsL2_Started (FeedOS::uint32 inTicket, FeedOS::Types::ListOfInstrumentStatusL2 const & inSnapshot);
	void response_QUOTATION_SubscribeInstrumentsL2_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_legacy_MBL, false); }
	void aborted_QUOTATION_SubscribeInstrumentsL2			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_legacy_MBL, rc==RC_OK); }

	void response_QUOTATION_SubscribeInstrumentsMBL_Started (FeedOS::uint32 inTicket, FeedOS::Types::ListOfFOSInstrumentCode const & instrumentCodes);
	void response_QUOTATION_SubscribeInstrumentsMBL_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_MBL, false); }
	void aborted_QUOTATION_SubscribeInstrumentsMBL			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_MBL, rc==RC_OK); }

	void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started (FOSInstrumentCode inInternalCode, Timestamp const & inLastUpdateServerUTCTimestamp, Timestamp const & inLastUpdateMarketUTCTimestamp, FeedOS::Types::MarketSheet const & inSnapshot);
	void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed	(FeedOS::ReturnCode /*rc*/) { inc_sub(FeedKind_MBO, false); }
	void aborted_QUOTATION_SubscribeOneInstrumentMarketSheet			(FeedOS::ReturnCode rc) { dec_sub(FeedKind_MBO, rc==RC_OK); }

};


class LatencyPrinter_per_MIC_subscriptions_adapter:
	public LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming,	// Level 1
		FeedOS::INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming,		// MBL
		Dummy_interface_1,
		Dummy_interface_2
		>
{
	typedef LatencyPrinter_notifs_adapter<
		FeedOS::INTERFACE_QUOTATION_SubscribeMarketsDataAndStatus_streaming,	// Level 1
		FeedOS::INTERFACE_QUOTATION_SubscribeMarketsOrderBook_streaming,		// MBL
		Dummy_interface_1,
		Dummy_interface_2
		> Parent;

public:

	LatencyPrinter_per_MIC_subscriptions_adapter (
													bool opt_silent, 
													std::ostream * stream_log_timestamps,
													std::ostream * stream_log_events
												)
		:Parent (opt_silent, stream_log_timestamps, stream_log_events)
	{}

	virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Started	(FeedOS::Types::ListOfMarketStatus const & /*inMarketsStatus*/) { inc_sub(FeedKind_L1, true); }
	virtual void response_QUOTATION_SubscribeMarketsDataAndStatus_Failed	(ReturnCode /*rc*/) { inc_sub(FeedKind_L1, false); }
	virtual void aborted_QUOTATION_SubscribeMarketsDataAndStatus			(ReturnCode rc) { dec_sub(FeedKind_L1, rc==RC_OK); }

	virtual void response_QUOTATION_SubscribeMarketsOrderBook_Started		() { inc_sub(FeedKind_MBL, true); }
	virtual void response_QUOTATION_SubscribeMarketsOrderBook_Failed		(ReturnCode /*rc*/) { inc_sub(FeedKind_L1, false); }
	virtual void aborted_QUOTATION_SubscribeMarketsOrderBook				(ReturnCode rc) { dec_sub(FeedKind_L1, rc==RC_OK); }

};




} // namespace FeedOS

#endif

