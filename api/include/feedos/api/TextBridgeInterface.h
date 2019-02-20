
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2007      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_BRIDGE_INTERFACE_H
#define FEEDOS_BRIDGE_INTERFACE_H


namespace FeedOS {

	namespace TextBridge {

///////////////////////////////////////////////////////////
// copied from C++ API "comm/FOSPrice.h"
///////////////////////////////////////////////////////////
		static double const UNQUOTED						= 666666.666;	// used when price or quantity is unknown (in history requests)
		static double const ORDERBOOK_MAGIC_PRICE_AT_BEST	= 999999.999;
		static double const ORDERBOOK_MAGIC_PRICE_AT_OPEN	= 999999.989;
		static double const ORDERBOOK_MAGIC_PRICE_AT_CLOSE	= 999999.988;
		static double const ORDERBOOK_MAGIC_PRICE_PEG		= 999999.979;
///////////////////////////////////////////////////////////
// copied from C++ API "comm/FOSQty.h"
///////////////////////////////////////////////////////////
		static int const ORDERBOOK_NB_ORDERS_UNKNOWN = -1;
		static int const ORDERBOOK_NB_ORDERS_EMPTY = 0;


		double const MAGIC_PRICE_UNQUOTED			= UNQUOTED;	// for backward compatibility

		char const str_UNQUOTED [] = "UNQUOTED";
		char const str_AT_BEST  [] = "AT_BEST";
		char const str_AT_OPEN  [] = "AT_OPEN";
		char const str_AT_CLOSE [] = "AT_CLOSE";
		char const str_PEG      [] = "PEG";

		char const char_LINE_SEPARATOR	= '\0';
		char const char_TOKEN_SEPARATOR	= ' ';

		typedef enum {
			FIXSecurityTradingStatus_UNKNOWN,
			FIXSecurityTradingStatus_OpeningDelay,
			FIXSecurityTradingStatus_TradingHalt,
			FIXSecurityTradingStatus_Resume,
			FIXSecurityTradingStatus_NoOpenNoResume,
			FIXSecurityTradingStatus_PriceIndication,
			FIXSecurityTradingStatus_TradingRangeIndication,
			FIXSecurityTradingStatus_MarketImbalanceBuy,
			FIXSecurityTradingStatus_MarketImbalanceSell,
			FIXSecurityTradingStatus_MarketOnCloseImbalanceBuy,
			FIXSecurityTradingStatus_MarketOnCloseImbalanceSell,
			FIXSecurityTradingStatus_NOT_ASSIGNED_11,
			FIXSecurityTradingStatus_NoMarketImbalance,
			FIXSecurityTradingStatus_NoMarketOnCloseImbalance,
			FIXSecurityTradingStatus_ITSPreOpening,
			FIXSecurityTradingStatus_NewPriceIndication,
			FIXSecurityTradingStatus_TradeDisseminationTime,
			FIXSecurityTradingStatus_ReadyToTrade /** start of session */,
			FIXSecurityTradingStatus_NotAvailableForTrading /** end of session */,
			FIXSecurityTradingStatus_NotTradedOnThisMarket,
			FIXSecurityTradingStatus_UnknownOrInvalid,
			FIXSecurityTradingStatus_PreOpen,
			FIXSecurityTradingStatus_OpeningRotation,
			FIXSecurityTradingStatus_FastMarket,
			FIXSecurityTradingStatus_PreCross,
			FIXSecurityTradingStatus_Cross
		} SecurityTradingStatus;
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////


#	define FEEDOS_BRIDGE_INTERFACE_PROTOCOL_VERSION(VERSION_STRING)	extern char const CurrentProtocolVersion [];
#	define FEEDOS_BRIDGE_INTERFACE_CMD(CMD,NAME,ARGS)				extern char const Cmd_##NAME [];
#	include "TextBridgeInterface_cmd.hpp"


		// the abstract class for implementing a "Text Feed receiver"
		class Interface
		{
		public:
			Interface () {}
			virtual ~Interface() {}

#		define FEEDOS_BRIDGE_INTERFACE_CMD(CMD, NAME, ARGS) virtual void bridge_cmd_##NAME ARGS = 0;
#		include "TextBridgeInterface_cmd.hpp"

			/// HELPERS
			void bridge_cmd_QUOT_set_market_date	(int year, int month, int day);
			void bridge_cmd_QUOT_set_server_date	(int year, int month, int day);
			void bridge_cmd_QUOT_set_market_time	(int hour, int minute, int second, int millisec);
			void bridge_cmd_QUOT_set_server_time	(int hour, int minute, int second, int millisec);

		};

	}
}

#endif
