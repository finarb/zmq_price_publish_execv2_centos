
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to quotation events         **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>
#include <feedos/framework/InstrumentMarketSheetData.h>
#include <stdio.h>
#include <cstring>
#include <iomanip>

// uncomment the following "using" statements to simplify code
//using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;

/** \cond refguide
 * \endcond
 */


static char const * side2str(FeedOS::Types::FIXSide s)
{
	switch (s)
	{
	case FeedOS::Types::FIXSide_Buy:		return "BID";
	case FeedOS::Types::FIXSide_Sell:		return "ASK";
	case FeedOS::Types::FIXSide_BuyAndSell:	return "***";
	}
	return "???";
}

class FeedMBOMultiInstrumentsPrinter : public FeedOS::API_QUOTATION_SubscribeInstrumentsMBO_base
{
public:
	FeedMBOMultiInstrumentsPrinter()
	{
	}

	// Callback implementation for QUOTATION.InstrumentsMBO subscription
	void response_QUOTATION_SubscribeInstrumentsMBO_Started(
						uint32 inTicket,
						FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes)
	{
		std::cout << "SubscribeInstrumentsMBO_Started" << std::endl;
		std::cout << "ticket = " << inTicket << std::endl;
		std::cout << "instr_list = ";
		for (size_t i = 0; i<inInternalCodes.size(); ++i)
		{
			if (i)
			{
				std::cout << ' ';
			}
			std::cout << inInternalCodes[i];
		}
		std::cout << '\n';
	}

	void response_QUOTATION_SubscribeInstrumentsMBO_Failed(ReturnCode rc)
	{
		std::cout << "SubscribeInstrumentsMBO_Failed, rc=" << rc << '\n';
	}

	void aborted_QUOTATION_SubscribeInstrumentsMBO(ReturnCode rc)
	{
		std::cout << "SubscribeInstrumentsMBO_Abored, rc=" << rc << '\n';
	}

	void notif_NewOrder(FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationContextFlag const & inContext,
						FeedOS::Types::FIXSide inSide,
						FeedOS::Types::MarketSheetEntry const & inEntry,
						FeedOS::Types::MarketSheetLevel inLevel)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		std::cout	<< "NO"													// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< '\t' << side2str(inSide)								// SIDE
					<< '\t' << FeedOS::order_id2str(inEntry.getOrderID())	// ORDER ID
					<< '\t' << FeedOS::FOSPrice(inEntry.getPrice())			// PRICE
					<< '\t' << inEntry.getQty()								// QTY
					<< '\t' << inLevel										// LEVEL
					<< '\n';
		printContextValues(inContext);

		instr_market_sheet.notif_NewOrder(	inCode,
											inServerUTCTimestamp,
											inMarketUTCTimestamp,
											inContext,
											inSide,
											inEntry,
											inLevel);
	}


	void notif_ModifyOrder(
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationContextFlag const & inContext,
						FeedOS::Types::FIXSide inSide,
						FeedOS::Types::MarketSheetEntry const & inEntry,
						FeedOS::Types::MarketSheetLevel inOldLevel,
						FeedOS::Types::MarketSheetLevel inNewLevel)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		std::cout	<< "MO"													// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< '\t' << side2str(inSide)								// SIDE
					<< '\t' << FeedOS::order_id2str(inEntry.getOrderID())	// ORDER ID
					<< '\t' << FeedOS::FOSPrice(inEntry.getPrice())			// PRICE
					<< '\t' << inEntry.getQty()								// QTY
					<< '\t' << inOldLevel									// OLD_LEVEL
					<< '\t' << inNewLevel									// LEW_LEVEL
					<< '\n';
		printContextValues(inContext);

		instr_market_sheet.notif_ModifyOrder(	inCode,
												inServerUTCTimestamp,
												inMarketUTCTimestamp,
												inContext,
												inSide,
												inEntry,
												inOldLevel,
												inNewLevel);
	}


	void notif_RemoveOneOrder(
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationContextFlag const & inContext,
						FeedOS::Types::FIXSide inSide,
						String const & inOrderID,
						FeedOS::Types::MarketSheetLevel inLevel)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		std::cout	<< "RO"													// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< '\t' << side2str(inSide)								// SIDE
					<< '\t' << FeedOS::order_id2str(inOrderID)				// ORDER_ID
					<< '\t' << inLevel										// LEVEL
					<< '\n';
		printContextValues(inContext);

		instr_market_sheet.notif_RemoveOneOrder(inCode,
												inServerUTCTimestamp,
												inMarketUTCTimestamp,
												inContext,
												inSide,
												inOrderID,
												inLevel);
	}


	void notif_RemoveAllPreviousOrders(
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationContextFlag const & inContext,
						FeedOS::Types::FIXSide inSide,
						String const & inOrderID,
						FeedOS::Types::MarketSheetLevel inLevel)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		std::cout	<< "RAP"												// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< '\t' << side2str(inSide)								// SIDE
					<< '\t' << FeedOS::order_id2str(inOrderID)				// ORDER_ID
					<< '\t' << inLevel										// LEVEL
					<< std::endl;
		printContextValues(inContext);

		instr_market_sheet.notif_RemoveAllPreviousOrders(	inCode,
															inServerUTCTimestamp,
															inMarketUTCTimestamp,
															inContext,
															inSide,
															inOrderID,
															inLevel);
	}


	void notif_RemoveAllOrders (
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationContextFlag const & inContext,
						FeedOS::Types::FIXSide inSide)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		std::cout	<< "RAO"												// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< '\t' << side2str(inSide)								// SIDE
					<< '\n';
		printContextValues(inContext);

		// Process event
		instr_market_sheet.notif_RemoveAllOrders(inCode,
												inServerUTCTimestamp,
												inMarketUTCTimestamp,
												inContext,
												inSide);
	}


	void notif_Retransmission(
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::MarketSheet const & inSnapshot)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);
		ListOfMarketSheetEntryAndContext const & bid = inSnapshot.getBidSide();
		ListOfMarketSheetEntryAndContext const & ask = inSnapshot.getAskSide();

		std::cout	<< "MBORET"												// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< "\tBIDx" << (uint32)(bid.size())
					<< "\tASKx" << (uint32)(ask.size())
					<< std::endl;

		// Process event
		instr_market_sheet.notif_Retransmission(inCode,
												inServerUTCTimestamp,
												inMarketUTCTimestamp,
												inSnapshot);
	}

	void notif_ValuesUpdateOneInstrument(
						FOSInstrumentCode inCode,
						Timestamp const & inServerUTCTimestamp,
						Timestamp const & inMarketUTCTimestamp,
						FeedOS::Types::ListOfQuotationVariable const & inValues)
	{
		FeedOS::InstrumentMarketSheetData & instr_market_sheet = getOrCreateInstrumentMarketSheetData(inCode);

		// Show event
		std::cout	<< "VUO"												// EVENT TYPE
					<< '\t' << inServerUTCTimestamp							// SERVER TIMESTAMP
					<< '\t' << inMarketUTCTimestamp							// MARKET TIMESTAMP
					<< '\t' << inCode.get_numeric()							// INSTRUMENT CODE
					<< std::endl;
		printContextValues(inValues);

		// Process event
		instr_market_sheet.notif_ValuesUpdateOneInstrument(	inCode,
															inServerUTCTimestamp,
															inMarketUTCTimestamp,
															inValues);
	}

private:
	static void printContextValues(FeedOS::Types::ListOfQuotationContextFlag const & values)
	{
		for (	ListOfQuotationVariable::const_iterator it = values.begin();
				it != values.end();
				++it )
		{
			std::cout << '\t';
			QuotationVariable const & var = *it;
			TagNumber tag_num = var.getNum();
			std::cout << tag_num2str (tag_num) << '=';
			Any const & value = var.getValue();
			if (value.get_syntax() == Syntax_float64)
			{
				std::cout << FeedOS::FOSPrice(value.get_float64());
			}
			else
			{
				std::cout << value.to_str(false);
			}
		}

		std::cout << '\n';
	}


	std::map<FOSInstrumentCode,FeedOS::InstrumentMarketSheetData> m_MarketData;

	inline
	FeedOS::InstrumentMarketSheetData & getOrCreateInstrumentMarketSheetData(FOSInstrumentCode const & code)
	{
		if( m_MarketData.find(code) == m_MarketData.end() )
		{
			m_MarketData[code].set_internal_code(code); 
		}
		return m_MarketData[code];
	}
};

static void usage()
{
	std::cerr << "usage: <instruments>" << std::endl;
}


void perform_subscribe_instruments_MBO (FeedOS::API::Connection & connection, int argc, char * argv[])
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_instruments_MBO");

	if( argc < 2 )
	{	// No enough arguments given
		std::cerr << "Not enough arguments" << std::endl;
		usage();
		return;
	}

	//![snippet_sub_MBO_many_custom]
	ListOfPolymorphicInstrumentCode input_codes;
	if (!extract_codes (input_codes, argc, argv))	// read them from command-line arguments
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCodes" << std::endl;
		usage();
		return;
	}
	//![snippet_sub_MBO_many_custom]

	//![snippet_sub_MBO_many_req]
	FeedMBOMultiInstrumentsPrinter req;

	// Start the subscription (synchronous version).
	ReturnCode rc = req.sync_start (connection, input_codes);

	if (rc != RC_OK)
	{
		std::cerr << "sync_start error, rc=" << error_string(rc) << std::endl;
	}
	else
	{
		getchar();
		std::cout << "Exiting ..." << std::endl;
	}
	req.stop ();
	//![snippet_sub_MBO_many_req]
}
