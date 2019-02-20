
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/************************************/

#include <feedos/zmqpp/MarketSheetClient_base.h>


namespace Sample
{

#define MARKET_SHEET_LOG(msg)				\
	std::string updateDesc;					\
	{										\
		std::stringstream os;				\
		(os << msg);						\
		updateDesc = os.str();				\
	}										\
	FEEDOS_LOG(User, Info, updateDesc);

#define MARKET_SHEET_ERROR(level, msg)		\
	{										\
		std::stringstream os;				\
		(os << msg);						\
		std::string s = os.str();			\
		FEEDOS_LOG(User, level, s);			\
		cbMarketSheetError(s);				\
	}

MarketSheetClient_base::MarketSheetClient_base()
{
}

MarketSheetClient_base::~MarketSheetClient_base()
{
}

//![snippet_sub_MBO_started]
void MarketSheetClient_base::
response_QUOTATION_SubscribeOneInstrumentMarketSheet_Started(
		FOSInstrumentCode /*inInternalCode*/,
		Timestamp const & inLastUpdateServerUTCTimestamp,
		Timestamp const & inLastUpdateMarketUTCTimestamp,
		FeedOS::Types::MarketSheet const & inSnapshot)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("subscription_Started: "
			<< "last_update_server_utc_timestamp='" <<
			inLastUpdateServerUTCTimestamp << "'"
			<< ", last_update_market_utc_timestamp='" <<
			inLastUpdateMarketUTCTimestamp << "'");

	m_MarketSheet = inSnapshot;
	rebuild_synthetic_book();

	static FeedOS::Types::ListOfQuotationContextFlag const emptyContext;
	cbMarketSheetChanged(Timestamp::null(), Timestamp::null(), updateDesc,
			emptyContext);
}
//![snippet_sub_MBO_started]

//![snippet_sub_MBO_failed]
void MarketSheetClient_base::
response_QUOTATION_SubscribeOneInstrumentMarketSheet_Failed(
		FeedOS::ReturnCode rc)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_ERROR(Warning, "subscription refused by the server: "
			<< FeedOS::error_string(rc));
}
//![snippet_sub_MBO_failed]

//![snippet_sub_MBO_aborted]
void MarketSheetClient_base::
aborted_QUOTATION_SubscribeOneInstrumentMarketSheet(
		FeedOS::ReturnCode rc)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_ERROR(Warning, "subscription aborted by the server: "
			<< FeedOS::error_string(rc));
}
//![snippet_sub_MBO_aborted]

//![snippet_sub_MBO_neworder]
void MarketSheetClient_base::notif_NewOrder(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationContextFlag const & inContext,
		FeedOS::Types::FIXSide inSide,
		FeedOS::Types::MarketSheetEntry const & inEntry,
		FeedOS::Types::MarketSheetLevel inLevel)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_NewOrder: "
			<< "UTC_timestamps"
				"(srv=" << inServerUTCTimestamp <<
				",mkt=" << inMarketUTCTimestamp
			<< ") side=" << inSide
			<< ", order_id=" << order_id2str (inEntry.getOrderID())
			<< ", price=" << getPriceAsString(inEntry.getPrice())
			<< ", qty=" << inEntry.getQty()
			<< ", level=" << inLevel);
	//![snippet_sub_MBO_neworder]

	ListOfMarketSheetEntryAndContext * market_sheet_side_ptr = getMarketSheetSide(inSide);
	if (market_sheet_side_ptr == NULL)
	{
		return;
	}
	ListOfMarketSheetEntryAndContext & market_sheet_side = *market_sheet_side_ptr;
	if (!checkMarketSheetLevel(market_sheet_side, inLevel, true))
	{
		return;
	}

	book_addOrder(inSide, inEntry.getPrice(), inEntry.getQty());

	market_sheet_side.insert(market_sheet_side.begin() + inLevel, MarketSheetEntryAndContext(inEntry, inContext));
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, inContext);
}

//![snippet_sub_MBO_modifyorder]
void MarketSheetClient_base::notif_ModifyOrder(
		FOSInstrumentCode inCode,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationContextFlag const & inContext,
		FeedOS::Types::FIXSide inSide,
		FeedOS::Types::MarketSheetEntry const & inEntry,
		FeedOS::Types::MarketSheetLevel inOldLevel,
		FeedOS::Types::MarketSheetLevel inNewLevel)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_ModifyOrder: "
			<< "UTC_timestamps"
				"(srv=" << inServerUTCTimestamp <<
				",mkt=" << inMarketUTCTimestamp
			<< ") side=" << inSide
			<< ", order_id=" << order_id2str (inEntry.getOrderID())
			<< ", price=" << getPriceAsString(inEntry.getPrice())
			<< ", qty=" << inEntry.getQty()
			<< ", old_level=" << inOldLevel
			<< ", new_level=" << inNewLevel);
	//![snippet_sub_MBO_modifyorder]

	ListOfMarketSheetEntryAndContext * market_sheet_side_ptr = getMarketSheetSide(inSide);
	if (market_sheet_side_ptr == NULL)
	{
		return;
	}
	ListOfMarketSheetEntryAndContext & market_sheet_side = *market_sheet_side_ptr;

	if (inOldLevel == inNewLevel)
	{
		if (!checkMarketSheetLevel(market_sheet_side, inOldLevel))
		{
			return;
		}

		// Check that the modify is not modifying an already existing and valid order (same price/qty)
		// May be valid in case of an iceberg order impacting an Order
		if( market_sheet_side[inOldLevel].getOrder() == inEntry )
		{
			std::stringstream os;
			os << "Received possibly redundant ModifyOrder notification for " << inCode << " OrderId: " << inEntry.getOrderID() << " @level " << inOldLevel << " - Old: Price " << market_sheet_side[inOldLevel].getOrder().getPrice() << " Qty " << market_sheet_side[inOldLevel].getOrder().getQty()
				<< " - New: Price " << inEntry.getPrice() << " Qty " << inEntry.getQty();
			cbMarketSheetError(os.str());
		}

		book_removeOrder(inSide, market_sheet_side[inOldLevel].getOrder().getPrice(), market_sheet_side[inOldLevel].getOrder().getQty());
		book_addOrder(inSide, inEntry.getPrice(), inEntry.getQty());

		market_sheet_side[inOldLevel] = MarketSheetEntryAndContext(inEntry, inContext);
	}
	else
	{
		if (	!checkMarketSheetLevel(market_sheet_side, inOldLevel)
			||	!checkMarketSheetLevel(market_sheet_side, inNewLevel))
		{
			return;
		}

		if (!checkOrderID(market_sheet_side, inOldLevel, inEntry.getOrderID()))
		{
			return;
		}

		book_removeOrder(inSide, market_sheet_side[inOldLevel].getOrder().getPrice(), market_sheet_side[inOldLevel].getOrder().getQty());
		book_addOrder(inSide, inEntry.getPrice(), inEntry.getQty());

		market_sheet_side.erase(market_sheet_side.begin() + inOldLevel);
		market_sheet_side.insert(market_sheet_side.begin() + inNewLevel, MarketSheetEntryAndContext(inEntry, inContext));
	}
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, inContext);
}

//![snippet_sub_MBO_remove1order]
void MarketSheetClient_base::notif_RemoveOneOrder(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationContextFlag const & inContext,
		FeedOS::Types::FIXSide inSide,
		String const & inOrderID,
		FeedOS::Types::MarketSheetLevel inLevel)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_RemoveOneOrder: "
		<< "UTC_timestamps"
				"(srv=" << inServerUTCTimestamp <<
				",mkt=" << inMarketUTCTimestamp
		<< ") side=" << inSide
		<< ", order_id=" << order_id2str (inOrderID)
		<< ", level=" << inLevel
		);
	//![snippet_sub_MBO_remove1order]

	ListOfMarketSheetEntryAndContext * market_sheet_side_ptr = getMarketSheetSide(inSide);
	if (market_sheet_side_ptr == NULL)
	{
		return;
	}
	ListOfMarketSheetEntryAndContext & market_sheet_side = *market_sheet_side_ptr;
	if (!checkOrderID(market_sheet_side, inLevel, inOrderID))
	{
		return;
	}

	MarketSheetEntry const & order = market_sheet_side[inLevel].getOrder();
	book_removeOrder(inSide, order.getPrice(), order.getQty());

	market_sheet_side.erase(market_sheet_side.begin() + inLevel);
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, inContext);
}

//![snippet_sub_MBO_removeallpreviousorders]
void MarketSheetClient_base::notif_RemoveAllPreviousOrders(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationContextFlag const & inContext,
		FeedOS::Types::FIXSide inSide,
		String const & inOrderID,
		FeedOS::Types::MarketSheetLevel inLevel)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_RemoveAllPreviousOrders: "
			<< "UTC_timestamps"
				"(srv=" << inServerUTCTimestamp <<
				",mkt=" << inMarketUTCTimestamp
			<< ") side=" << inSide
			<< ", order_id=" << order_id2str (inOrderID)
			<< ", level=" << inLevel);
	//![snippet_sub_MBO_removeallpreviousorders]

	ListOfMarketSheetEntryAndContext * market_sheet_side_ptr = getMarketSheetSide(inSide);
	if (market_sheet_side_ptr == NULL)
	{
		return;
	}
	ListOfMarketSheetEntryAndContext & market_sheet_side = *market_sheet_side_ptr;
	if (!checkOrderID(market_sheet_side, inLevel, inOrderID))
	{
		return;
	}

	ListOfMarketSheetEntryAndContext::iterator it_end = market_sheet_side.begin() + inLevel + 1;
	for (ListOfMarketSheetEntryAndContext::const_iterator it = market_sheet_side.begin(); it != it_end; ++it)
	{
		MarketSheetEntry const & order = it->getOrder();
		book_removeOrder(inSide, order.getPrice(), order.getQty());
	}

	market_sheet_side.erase(market_sheet_side.begin(), it_end);
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, inContext);
}

//![snippet_sub_MBO_removeallorders]
void MarketSheetClient_base::notif_RemoveAllOrders(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationContextFlag const & inContext,
		FeedOS::Types::FIXSide inSide)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_RemoveAllPreviousOrders: "
			<< "server_utc_timestamp='" << inServerUTCTimestamp << "'"
			<< ", market_utc_timestamp='" << inMarketUTCTimestamp << "'"
			<< ", side='" << inSide << "'");
	//![snippet_sub_MBO_removeallorders]

	std::vector<ListOfMarketSheetEntryAndContext *> market_sheet_sides;
	getMarketSheetSides(inSide, market_sheet_sides);
	for (	std::vector<ListOfMarketSheetEntryAndContext *>::const_iterator it = market_sheet_sides.begin();
			it != market_sheet_sides.end();
			++it)
	{
		ListOfMarketSheetEntryAndContext & market_sheet_side = **it;
		market_sheet_side.clear();
	}
	book_clear(inSide);
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, inContext);
}

//![snippet_sub_MBO_retransmit]
void MarketSheetClient_base::notif_Retransmission(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::MarketSheet const & inSnapshot)
{
	SCOPE_AUTO_LOCK(l, m_Lock);

	MARKET_SHEET_LOG("notif_Retransmission: "
			<< "server_utc_timestamp='" << inServerUTCTimestamp << "'"
			<< ", market_utc_timestamp='" << inMarketUTCTimestamp << "'");
	//![snippet_sub_MBO_retransmit]

	m_MarketSheet = inSnapshot;

	rebuild_synthetic_book();

	static FeedOS::Types::ListOfQuotationContextFlag const emptyContext;
	cbMarketSheetChanged(inServerUTCTimestamp, inMarketUTCTimestamp, updateDesc, emptyContext);
}


//![snippet_sub_MBO_vu]
void MarketSheetClient_base::notif_ValuesUpdateOneInstrument(
		FOSInstrumentCode /*inCode*/,
		Timestamp const & inServerUTCTimestamp,
		Timestamp const & inMarketUTCTimestamp,
		FeedOS::Types::ListOfQuotationVariable const & inValues)
{
	MARKET_SHEET_LOG("notif_ValuesUpdateOneInstrument: "
		<< "server_utc_timestamp='" << inServerUTCTimestamp << "'"
		<< ", market_utc_timestamp='" << inMarketUTCTimestamp << "'");
	//![snippet_sub_MBO_vu]
	cbValuesUpdate		(	inServerUTCTimestamp,
							inMarketUTCTimestamp,
							inValues
						);
}


bool	MarketSheetClient_base::checkMarketSheetLevel(ListOfMarketSheetEntryAndContext const & market_sheet_side, FeedOS::Types::MarketSheetLevel level, bool allow_end)
{
	bool is_valid_level;
	if (allow_end)
	{
		is_valid_level = (level <= market_sheet_side.size());
	}
	else
	{
		is_valid_level = (level < market_sheet_side.size());
	}

	if (!is_valid_level)
	{
		MARKET_SHEET_ERROR(Critical, "invalid market sheet: out of range level: level=" << level << " > size=" << static_cast<unsigned int>(market_sheet_side.size()));
		return false;
	}
	return true;
}

bool	MarketSheetClient_base::checkOrderID(ListOfMarketSheetEntryAndContext const & market_sheet_side, FeedOS::Types::MarketSheetLevel level, String const & order_id)
{
	if (checkMarketSheetLevel(market_sheet_side, level))
	{
		if (market_sheet_side[level].getOrder().getOrderID() == order_id)
		{
			return true;
		}
	}
	MARKET_SHEET_ERROR(Critical, "invalid market sheet: order id does not match");
	return false;
}

ListOfMarketSheetEntryAndContext *	MarketSheetClient_base::getMarketSheetSide(FeedOS::Types::FIXSide side)
{
	switch (side)
	{
	case FIXSide_Buy:	return &m_MarketSheet.getBidSide();
	case FIXSide_Sell:	return &m_MarketSheet.getAskSide();

	default:
		{
			MARKET_SHEET_ERROR(Critical, "invalid side: " << side);
		}
		break;
	}

	return NULL;
}

void	MarketSheetClient_base::getMarketSheetSides(FeedOS::Types::FIXSide side, std::vector<ListOfMarketSheetEntryAndContext *> & market_sheet_sides)
{
	market_sheet_sides.clear();
	switch (side)
	{
	case FIXSide_Buy:
		{
			market_sheet_sides.push_back(&m_MarketSheet.getBidSide());
		}
		break;

	case FIXSide_Sell:
		{
			market_sheet_sides.push_back(&m_MarketSheet.getAskSide());
		}
		break;

	case FIXSide_BuyAndSell:
		{
			market_sheet_sides.push_back(&m_MarketSheet.getBidSide());
			market_sheet_sides.push_back(&m_MarketSheet.getAskSide());
		}
		break;

	default:
		{
			MARKET_SHEET_ERROR(Critical, "invalid side: " << side);
		}
		break;
	}
}

std::string	MarketSheetClient_base::getPriceAsString(double const & price) const
{
	std::stringstream os;
	FeedOS::print_price(os, price);
	return os.str();
}

void	MarketSheetClient_base::book_addOrder(FeedOS::Types::FIXSide side, double const & price, double const & quantity)
{
	m_OrderBook.addOrder(side, price, quantity);
}

void	MarketSheetClient_base::book_removeOrder(FeedOS::Types::FIXSide side, double const & price, double const & quantity)
{
	m_OrderBook.removeOrder(side, price, quantity);
}

void	MarketSheetClient_base::book_clear(FeedOS::Types::FIXSide side)
{
	m_OrderBook.clearBook(side);
}

void	MarketSheetClient_base::rebuild_synthetic_book()
{
	m_OrderBook.clearBook(FIXSide_BuyAndSell);

	ListOfMarketSheetEntryAndContext const & bid_side= m_MarketSheet.getBidSide();
	for (ListOfMarketSheetEntryAndContext::const_iterator it = bid_side.begin(); it != bid_side.end(); ++it)
	{
		MarketSheetEntry const & order = it->getOrder();
		m_OrderBook.addOrder(FIXSide_Buy, order.getPrice(), order.getQty());
	}

	ListOfMarketSheetEntryAndContext const & ask_side = m_MarketSheet.getAskSide();
	for (ListOfMarketSheetEntryAndContext::const_iterator it = ask_side.begin(); it != ask_side.end(); ++it)
	{
		MarketSheetEntry const & order = it->getOrder();
		m_OrderBook.addOrder(FIXSide_Sell, order.getPrice(), order.getQty());
	}
}

} // namespace Sample
