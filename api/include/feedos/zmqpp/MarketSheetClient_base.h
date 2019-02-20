
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/************************************/

#ifndef FEEDOS_SAMPLE_MARKET_SHEET_CLIENT_H
#define FEEDOS_SAMPLE_MARKET_SHEET_CLIENT_H

#include "SyntheticOrderBook.h"
#include <feedos/framework/FeedPrinter_MBO.h>

using namespace FeedOS;

namespace Sample
{


/**
 * MarketSheetClient_base
 *
 */
//![snippet_sub_MBO_subclass]
class MarketSheetClient_base:
		public FeedOS::API_QUOTATION_SubscribeOneInstrumentMarketSheet_base
//![snippet_sub_MBO_subclass]
{
public:
	/// ctor
	MarketSheetClient_base();

	/// virtual dtor
	virtual ~MarketSheetClient_base();

	/// get the object lock (use that in a multithread context to ensure consistent access)
	ExclusiveLock const &	getLock() const	{ return m_Lock; }

	/// get the market sheet
	FeedOS::Types::MarketSheet const &	getMarketSheet() const	{ return m_MarketSheet; }

	/// get the synthetic order book (built by merging quantities of all orders at the same price)
	Sample::SyntheticOrderBook const &	getOrderBook() const	{ return m_OrderBook; }

protected:
	/// called each time the market sheet has changed
	virtual void	cbMarketSheetChanged	(	Timestamp const & server_utc_timestamp,
												Timestamp const & market_utc_timestamp,
												std::string const & update_desc,
												FeedOS::Types::ListOfQuotationContextFlag const & inContext
											) =0;
	/// called when 'some values' are updated (basically: TradingStatus)
	virtual void	cbValuesUpdate			(	Timestamp const & server_utc_timestamp,
												Timestamp const & market_utc_timestamp,
												FeedOS::Types::ListOfQuotationVariable const & inValues
											) =0;
	/// called if an error happens
	virtual void	cbMarketSheetError		(std::string const & error_msg) =0;

private:
	/// @name INTERFACE_QUOTATION_SubscribeOneInstrumentMarketSheet_streaming implementation.
	//@{
	void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started (FOSInstrumentCode inInternalCode, Timestamp const & inLastUpdateServerUTCTimestamp, Timestamp const & inLastUpdateMarketUTCTimestamp, FeedOS::Types::MarketSheet const & inSnapshot);
	void response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed (ReturnCode rc);
	void aborted_QUOTATION_SubscribeOneInstrumentMarketSheet (ReturnCode rc);
	void notif_NewOrder					(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inLevel);
	void notif_ModifyOrder				(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, FeedOS::Types::MarketSheetEntry const & inEntry, FeedOS::Types::MarketSheetLevel inOldLevel, FeedOS::Types::MarketSheetLevel inNewLevel);
	void notif_RemoveOneOrder			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel);
	void notif_RemoveAllPreviousOrders	(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide, String const & inOrderID, FeedOS::Types::MarketSheetLevel inLevel);
	void notif_RemoveAllOrders			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationContextFlag const & inContext, FeedOS::Types::FIXSide inSide);
	void notif_Retransmission			(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::MarketSheet const & inSnapshot);
	void notif_ValuesUpdateOneInstrument(FOSInstrumentCode inCode, Timestamp const & inServerUTCTimestamp, Timestamp const & inMarketUTCTimestamp, FeedOS::Types::ListOfQuotationVariable const & inValues);
	//@}

	bool	checkMarketSheetLevel(ListOfMarketSheetEntryAndContext const & market_sheet_side, FeedOS::Types::MarketSheetLevel level, bool allow_end = false);
	bool	checkOrderID(ListOfMarketSheetEntryAndContext const & market_sheet_side, FeedOS::Types::MarketSheetLevel level, String const & order_id);
	ListOfMarketSheetEntryAndContext *	getMarketSheetSide(FeedOS::Types::FIXSide side);
	void	getMarketSheetSides(FeedOS::Types::FIXSide side, std::vector<ListOfMarketSheetEntryAndContext *> & market_sheet_sides);
	std::string	getPriceAsString(double const & price) const;

	/// @name Order book management.
	//@{
	void	book_addOrder			(FeedOS::Types::FIXSide side, double const & price, double const & quantity);
	void	book_removeOrder		(FeedOS::Types::FIXSide side, double const & price, double const & quantity);
	void	book_clear				(FeedOS::Types::FIXSide side);
	void	rebuild_synthetic_book	();
	//@}

private:
	FeedOS::ExclusiveLock		m_Lock;
	FeedOS::Types::MarketSheet	m_MarketSheet;
	Sample::SyntheticOrderBook	m_OrderBook;
};

} // namespace Sample


#endif
