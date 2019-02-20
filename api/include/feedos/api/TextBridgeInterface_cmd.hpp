/************************************/
/** FeedOS TextBridge command      **/
/** copyright QuantHouse 2007      **/
/************************************/

#ifdef FEEDOS_BRIDGE_INTERFACE_PROTOCOL_VERSION
			FEEDOS_BRIDGE_INTERFACE_PROTOCOL_VERSION("1.0")
#undef FEEDOS_BRIDGE_INTERFACE_PROTOCOL_VERSION
#endif

////////////////////////////////////////////////////////////////////
// 
//      ACTION commands
// 
////////////////////////////////////////////////////////////////////

// MISC

// can be used to insert "comments" in a script of commands
FEEDOS_BRIDGE_INTERFACE_CMD("#"			,NOP				,(char const * dummy) )

// declare what is the protocol version
FEEDOS_BRIDGE_INTERFACE_CMD("PROTOCOL_VERSION"	,select_protocol_version	,(char const * version) )

// send an error message
FEEDOS_BRIDGE_INTERFACE_CMD("ERROR"			,error				,(char const * error) )

// send an informative message
FEEDOS_BRIDGE_INTERFACE_CMD("MSG"			,msg				,(char const * msg) )

// sleep for N milliseconds
FEEDOS_BRIDGE_INTERFACE_CMD("s"			,msleep				,(unsigned int nb_millisec) )

// manage instruments
FEEDOS_BRIDGE_INTERFACE_CMD("*REF_CREATE"		,REF_SEND_create_or_update	,(char const * instrument) )
FEEDOS_BRIDGE_INTERFACE_CMD("*REF_DELETE"		,REF_SEND_delete		,(char const * instrument) )

// generate Level1 event (bid/ask/trade and misc values)
FEEDOS_BRIDGE_INTERFACE_CMD("*1"	,QUOT_L1_SEND			, () )

// generate Level2/MBL event: override a set of bid/ask values (based on previous "Level2 declarations")
FEEDOS_BRIDGE_INTERFACE_CMD("*2"	,QUOT_L2_SEND_rt_order_book_override	, () )

 
// generate Level2/MBL event: generate a delta refresh
FEEDOS_BRIDGE_INTERFACE_CMD("2C" ,QUOT_L2_SEND_rt_order_book_clear_FromLevel	,(unsigned int n) )
FEEDOS_BRIDGE_INTERFACE_CMD("2CB",QUOT_L2_SEND_rt_order_book_clear_BidFromLevel	,(unsigned int n) )
FEEDOS_BRIDGE_INTERFACE_CMD("2CA",QUOT_L2_SEND_rt_order_book_clear_AskFromLevel	,(unsigned int n) )
FEEDOS_BRIDGE_INTERFACE_CMD("2IB",QUOT_L2_SEND_rt_order_book_insert_BidAtLevel,(unsigned int n, double price, double qty, int nb_orders))
FEEDOS_BRIDGE_INTERFACE_CMD("2IA",QUOT_L2_SEND_rt_order_book_insert_AskAtLevel,(unsigned int n, double price, double qty, int nb_orders))
FEEDOS_BRIDGE_INTERFACE_CMD("2RB",QUOT_L2_SEND_rt_order_book_remove_BidAtLevel	,(unsigned int n) )
FEEDOS_BRIDGE_INTERFACE_CMD("2RA",QUOT_L2_SEND_rt_order_book_remove_AskAtLevel	,(unsigned int n) )

FEEDOS_BRIDGE_INTERFACE_CMD("2Rb",QUOT_L2_SEND_rt_order_book_remove_BidAtLevel_and_append	,
            (unsigned int n, double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2Ra",QUOT_L2_SEND_rt_order_book_remove_AskAtLevel_and_append	,
            (unsigned int n, double price, double qty, int nb_orders) )

FEEDOS_BRIDGE_INTERFACE_CMD("2QB",QUOT_L2_SEND_rt_order_book_change_BidQtyAtLevel	,(unsigned int n, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2QA",QUOT_L2_SEND_rt_order_book_change_AskQtyAtLevel	,(unsigned int n, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2MVD",QUOT_L2_SEND_rt_order_book_max_visible_depth	,(unsigned int n) )


////////////////////////////////////////////////////////////////////
// 
//      DECLARATION commands
// 
////////////////////////////////////////////////////////////////////


/////////////////////////////////////
// common, volatile commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("I",	select_instrument, (char const * instrument) )	// select an existing instrument


/////////////////////////////////////
// REFERENTIAL, persistent commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("REF_SELECT_MIC"		,REF_select_MarketId		, (char const * mic) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_SET_TIMEOFFSET4MIC"	,REF_set_MarketId_timeoffset	, (char const * mic, int offset_local2UTC_minute))


/////////////////////////////////////
// REFERENTIAL, volatile commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("A/?"	,REF_declare_attribute_Syntax_UNKNOWN		, (unsigned int tag) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/str"	,REF_declare_attribute_Syntax_String		, (unsigned int tag, char const * v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/ui8"	,REF_declare_attribute_Syntax_uint8		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/ui16"	,REF_declare_attribute_Syntax_uint16		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/ui32"	,REF_declare_attribute_Syntax_uint32		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/i8"	,REF_declare_attribute_Syntax_int8		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/i16"	,REF_declare_attribute_Syntax_int16		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/i32"	,REF_declare_attribute_Syntax_int32		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/f64"	,REF_declare_attribute_Syntax_float64		, (unsigned int tag, double v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/t"	,REF_declare_attribute_Syntax_Timestamp	, (unsigned int tag, char const * v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/e"	,REF_declare_attribute_Syntax_Enum		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/b"	,REF_declare_attribute_Syntax_bool		, (unsigned int tag, bool v) )
FEEDOS_BRIDGE_INTERFACE_CMD("A/ch"	,REF_declare_attribute_Syntax_char		, (unsigned int tag, char v) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_Description",REF_declare_Description		, (char const * description) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_Symbol"	,REF_declare_Symbol			, (char const * symbol) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_CFICode"	,REF_declare_CFICode			, (char const * cficode) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_SecurityType"	,REF_declare_SecurityType	, (char const * security_type) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_SecuritySubType"	,REF_declare_SecuritySubType	, (char const * security_subtype) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_ISIN"		,REF_declare_ISIN		, (char const * isin) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_SEDOL"		,REF_declare_SEDOL		, (char const * sedol) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_CUSIP"		,REF_declare_CUSIP		, (char const * cusip) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_MaturityYear"	,REF_declare_MaturityYear	, (unsigned int y) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_MaturityMonth"	,REF_declare_MaturityMonth	, (unsigned int m) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_MaturityDay"	,REF_declare_MaturityDay	, (unsigned int d) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_StrikePrice"	,REF_declare_StrikePrice	, (double strike_price) )
FEEDOS_BRIDGE_INTERFACE_CMD("REF_PriceCurrency"	,REF_declare_PriceCurrency	, (char const * currency) )


/////////////////////////////////////
// QUOTATION, persistent commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("@MD"	,	QUOT_set_market_date		, (char const * date) )
FEEDOS_BRIDGE_INTERFACE_CMD("@MT"	,	QUOT_set_market_time		, (char const * time) )
FEEDOS_BRIDGE_INTERFACE_CMD("@SD"	,	QUOT_set_server_date		, (char const * date) )
FEEDOS_BRIDGE_INTERFACE_CMD("@ST"	,	QUOT_set_server_time		, (char const * time) )


/////////////////////////////////////
// QUOTATION Level 1, volatile commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("V/?"	,QUOT_L1_value_Syntax_UNKNOWN		, (unsigned int tag) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/str"	,QUOT_L1_value_Syntax_String		, (unsigned int tag, char const * v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/ui8"	,QUOT_L1_value_Syntax_uint8		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/ui16"	,QUOT_L1_value_Syntax_uint16		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/ui32"	,QUOT_L1_value_Syntax_uint32		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/i8"	,QUOT_L1_value_Syntax_int8		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/i16"	,QUOT_L1_value_Syntax_int16		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/i32"	,QUOT_L1_value_Syntax_int32		, (unsigned int tag, int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/f64"	,QUOT_L1_value_Syntax_float64		, (unsigned int tag, double v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/t"	,QUOT_L1_value_Syntax_Timestamp	, (unsigned int tag, char const * v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/e"	,QUOT_L1_value_Syntax_Enum		, (unsigned int tag, unsigned int v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/b"	,QUOT_L1_value_Syntax_bool		, (unsigned int tag, bool v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V/ch"	,QUOT_L1_value_Syntax_char		, (unsigned int tag, char v) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_InternalDailyVWAP"	,QUOT_L1_value_InternalDailyVWAP	, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_LastPrice"		,QUOT_L1_value_LastPrice		, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailyOpeningPrice"	,QUOT_L1_value_DailyOpeningPrice	, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailyClosingPrice"	,QUOT_L1_value_DailyClosingPrice	, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailyHighPrice"	,QUOT_L1_value_DailyHighPrice		, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailyLowPrice"	,QUOT_L1_value_DailyLowPrice		, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailyTotalVolumeTraded"		,QUOT_L1_value_DailyTotalVolumeTraded		, (double volume) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_DailySettlementPrice"			,QUOT_L1_value_DailySettlementPrice		, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_OpenInterest"			,QUOT_L1_value_OpenInterest, (double volume) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_PreviousDailyClosingPrice"		,QUOT_L1_value_PreviousDailyClosingPrice	, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("V_PreviousDailyTotalVolumeTraded"	,QUOT_L1_value_PreviousDailyTotalVolumeTraded, (double volume) )
FEEDOS_BRIDGE_INTERFACE_CMD("1X"	,QUOT_L1_rt_context		, (char const * context) )
FEEDOS_BRIDGE_INTERFACE_CMD("1SDO"	,QUOT_L1_rt_signal_DailyOpen	, () )
FEEDOS_BRIDGE_INTERFACE_CMD("1SDC"	,QUOT_L1_rt_signal_DailyClose	, () )
FEEDOS_BRIDGE_INTERFACE_CMD("1SDH"	,QUOT_L1_rt_signal_DailyHigh	, () )
FEEDOS_BRIDGE_INTERFACE_CMD("1SDL"	,QUOT_L1_rt_signal_DailyLow	, () )
FEEDOS_BRIDGE_INTERFACE_CMD("1P"	,QUOT_L1_rt_price		, (double price) )
FEEDOS_BRIDGE_INTERFACE_CMD("1T"	,QUOT_L1_rt_trade		, (double price, double qty) )
FEEDOS_BRIDGE_INTERFACE_CMD("1S"	,QUOT_L1_rt_status		, (::FeedOS::TextBridge::SecurityTradingStatus s) )
FEEDOS_BRIDGE_INTERFACE_CMD("1B"	,QUOT_L1_rt_best_bid		, (double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("1A"	,QUOT_L1_rt_best_ask		, (double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("1b"	,QUOT_L1_rt_best_bid_clear	, () )
FEEDOS_BRIDGE_INTERFACE_CMD("1a"	,QUOT_L1_rt_best_ask_clear	, () )


/////////////////////////////////////
// QUOTATION Level 2, volatile commands
/////////////////////////////////////
FEEDOS_BRIDGE_INTERFACE_CMD("2Ob",QUOT_L2_rt_order_book_override_BidStartAtLevel,	(unsigned int n, bool is_complete) )
FEEDOS_BRIDGE_INTERFACE_CMD("2Oa",QUOT_L2_rt_order_book_override_AskStartAtLevel,	(unsigned int n, bool is_complete) )
FEEDOS_BRIDGE_INTERFACE_CMD("2b", QUOT_L2_rt_order_book_override_BidNextLevel,	(double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2a", QUOT_L2_rt_order_book_override_AskNextLevel,	(double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2B", QUOT_L2_rt_order_book_override_BidAtLevel, (unsigned int n, double price, double qty, int nb_orders) )
FEEDOS_BRIDGE_INTERFACE_CMD("2A", QUOT_L2_rt_order_book_override_AskAtLevel, (unsigned int n, double price, double qty, int nb_orders) )


#undef FEEDOS_BRIDGE_INTERFACE_CMD
