
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/************************************/

#include <feedos/zmqpp/SyntheticOrderBook.h>
#include <algorithm>
#include <sstream>

namespace Sample
{
	static int const RESULT_a_GREATER_THAN_b	= 1;
	static int const RESULT_a_EQUALS_b			= 0;
	static int const RESULT_a_LOWER_THAN_b		= -1;

	static inline bool	equalPrices(double const & price_a, double const & price_b)
	{
		return (price_a == price_b);
	}

	int	askPriceCompare(double const & price_a, double const & price_b)
	{
		if (equalPrices(price_a, price_b))				return RESULT_a_EQUALS_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_BEST)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_BEST)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_OPEN)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_OPEN)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_CLOSE)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_CLOSE)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_PEG)		return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_PEG)		return RESULT_a_LOWER_THAN_b;
		if (price_a < price_b)							return RESULT_a_GREATER_THAN_b;

		return RESULT_a_LOWER_THAN_b;
	}

	int	bidPriceCompare(double const & price_a, double const & price_b)
	{
		if (equalPrices(price_a, price_b))				return RESULT_a_EQUALS_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_BEST)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_BEST)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_OPEN)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_OPEN)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_AT_CLOSE)	return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_AT_CLOSE)	return RESULT_a_LOWER_THAN_b;
		if (price_a == ORDERBOOK_MAGIC_PRICE_PEG)		return RESULT_a_GREATER_THAN_b;
		if (price_b == ORDERBOOK_MAGIC_PRICE_PEG)		return RESULT_a_LOWER_THAN_b;
		if (price_a > price_b)							return RESULT_a_GREATER_THAN_b;

		return RESULT_a_LOWER_THAN_b;
	}


	void	SyntheticOrderBookSide::addOrder	(double const & price, double const & quantity)
	{
		unsigned int index;
		if (findPricePos(price, index))
		{
			// add the order
			SyntheticOrderBookEntry & book_entry = getOrderBookEntry(index);
			book_entry.addOrder(quantity);
		}
		else
		{
			// insert a new entry
			m_OrderBookEntries.insert(m_OrderBookEntries.begin() + index, SyntheticOrderBookEntry(price, quantity, 1));
		}

		invariant();
	}


	void	SyntheticOrderBookSide::removeOrder(double const & price, double const & quantity)
	{
		unsigned int index;
		if (findPricePos(price, index))
		{
			SyntheticOrderBookEntry & book_entry = getOrderBookEntry(index);
			double total_quantity = book_entry.getQty();
			if (quantity >= total_quantity)
			{
				if (quantity > total_quantity)
				{
					FEEDOS_LOG(User, Critical, "SyntheticOrderBookSide::removeQuantity() removed more than available: total_quantity="
						<< total_quantity << ", removed_quantity=" << quantity);
				}
				// remove the entry
				m_OrderBookEntries.erase(m_OrderBookEntries.begin() + index);
			}
			else
			{
				// remove the order
				book_entry.removeOrder(quantity);
			}
		}
		else
		{
			FEEDOS_LOG(User, Critical, "SyntheticOrderBookSide::removeQuantity() price is not present in the book: price="
				<< price << ", quantity=" << quantity);
		}

		invariant();
	}

	void	SyntheticOrderBookSide::clearBookSide()
	{
		m_OrderBookEntries.clear();
		invariant();
	}

	SyntheticOrderBookEntry &	SyntheticOrderBookSide::getOrderBookEntry(unsigned int index)
	{
		if (index >= m_OrderBookEntries.size())
		{
			throw FatalException();
		}
		return m_OrderBookEntries[index];
	}

	bool	SyntheticOrderBookSide::findPricePos(double const & price, unsigned int & index)
	{
		unsigned int begin_index = 0;
		unsigned int end_index = static_cast<unsigned int>(m_OrderBookEntries.size());

		while (begin_index < end_index)
		{
			unsigned int test_index = (begin_index + end_index) / 2;
			SyntheticOrderBookEntry & book_entry = getOrderBookEntry(test_index);
			int cmp_result = m_PriceCompareFunc(price, book_entry.getPrice());
			if (cmp_result == 0)
			{
				index = test_index;
				return true;
			}
			else if (cmp_result > 0)
			{
				end_index = test_index;
			}
			else
			{
				begin_index = test_index + 1;
			}
		}

		if (begin_index != end_index)
		{
			throw FatalException();
		}

		if (begin_index < m_OrderBookEntries.size())
		{
			SyntheticOrderBookEntry & book_entry = getOrderBookEntry(begin_index);
			int cmp_result = m_PriceCompareFunc(price, book_entry.getPrice());
			if (cmp_result == 0)
			{
				index = begin_index;
				return true;
			}
			else if (cmp_result > 0)
			{
				index = begin_index;
			}
			else
			{
				index = begin_index + 1;
			}
		}
		else
		{
			index = begin_index;
		}

		return false;
	}

	void	SyntheticOrderBookSide::invariant()
	{
#ifdef _DEBUG

		if (!m_OrderBookEntries.empty())
		{
			double last_price = m_OrderBookEntries.front().getPrice();
			for (std::vector<SyntheticOrderBookEntry>::const_iterator it = m_OrderBookEntries.begin() + 1; it != m_OrderBookEntries.end(); ++it)
			{
				FeedOS::Types::OrderBookEntryExt const & book_entry = *it;
				if (m_PriceCompareFunc(last_price, book_entry.getPrice()) <= 0)
				{
					throw FatalException();
				}
				last_price = book_entry.getPrice();
			}
		}

#endif // _DEBUG
	}


	SyntheticOrderBook::SyntheticOrderBook()
		: m_BidLimits(bidPriceCompare)
		, m_AskLimits(askPriceCompare)
	{
	}


	void	SyntheticOrderBook::addOrder(FeedOS::Types::FIXSide side, double const & price, double const & quantity)
	{
		switch (side)
		{
		case FeedOS::Types::FIXSide_Buy:
			{
				m_BidLimits.addOrder(price, quantity);
			}
			break;

		case FeedOS::Types::FIXSide_Sell:
			{
				m_AskLimits.addOrder(price, quantity);
			}
			break;

		default:
			{
				FEEDOS_LOG(User, Critical, "SyntheticOrderBook::addOrder() invalid side: " << side);
			}
			break;
		}
	}

	void	SyntheticOrderBook::removeOrder(FeedOS::Types::FIXSide side, double const & price, double const & quantity)
	{
		switch (side)
		{
		case FeedOS::Types::FIXSide_Buy:
			{
				m_BidLimits.removeOrder(price, quantity);
			}
			break;

		case FeedOS::Types::FIXSide_Sell:
			{
				m_AskLimits.removeOrder(price, quantity);
			}
			break;

		default:
			{
				FEEDOS_LOG(User, Critical, "SyntheticOrderBook::removeOrder() invalid side: " << side);
			}
			break;
		}
	}

	void	SyntheticOrderBook::clearBook(FeedOS::Types::FIXSide side)
	{
		switch (side)
		{
		case FeedOS::Types::FIXSide_Buy:
			{
				m_BidLimits.clearBookSide();
			}
			break;

		case FeedOS::Types::FIXSide_Sell:
			{
				m_BidLimits.clearBookSide();
			}
			break;

		case FeedOS::Types::FIXSide_BuyAndSell:
			{
				m_BidLimits.clearBookSide();
				m_AskLimits.clearBookSide();
			}
			break;

		default:
			{
				FEEDOS_LOG(User, Critical, "SyntheticOrderBook::clearBook() invalid side: " << side);
			}
			break;
		}
	}


	int
	SyntheticOrderBook::print_price (char *buf, double price)
	{
		std::stringstream s;
		FeedOS::print_price (s, price);	// handles "magic values" like AT_OPEN and AT_BEST
		std::string str = s.str();
		strcpy (buf, str.c_str());
		return (int)str.size();
	}


	void 
	SyntheticOrderBook::print (std::ostream & s, int max_depth) const
	{
		std::vector<SyntheticOrderBookEntry> const & bid_limits = getBidLimits();
		std::vector<SyntheticOrderBookEntry> const & ask_limits = getAskLimits();

		size_t max_level = std::max (bid_limits.size(), ask_limits.size());
		if (-1 != max_depth) {
			max_level = std::max (max_level, (size_t)max_depth);
		}

		// TODO print server/market timestamps
		s << "LVL     *** BID *************    *** ASK *************\n";

		char buffer[128];
		for (size_t i=0; i<max_level; ++i) {
			int buffer_len = 0;
			buffer_len += sprintf (buffer+buffer_len, "%-3u   ", (unsigned int)i);

			if (i<bid_limits.size()) {
				buffer_len += print_price (buffer+buffer_len, bid_limits[i].getPrice());
				buffer_len += sprintf (buffer+buffer_len, " x %6u @%4u", (unsigned int) bid_limits[i].getQty(), (unsigned int) bid_limits[i].getNbOrders());
			} else {
				buffer_len += sprintf (buffer+buffer_len, "                  ");
			}
			buffer_len += sprintf (buffer+buffer_len, "  ");

			if (i<ask_limits.size()) {
				buffer_len += print_price (buffer+buffer_len, ask_limits[i].getPrice());
				buffer_len += sprintf (buffer+buffer_len, " x %6u @%4u", (unsigned int) ask_limits[i].getQty(), (unsigned int) ask_limits[i].getNbOrders());
			} else {
				buffer_len += sprintf (buffer+buffer_len, "                  ");
			}

			s << buffer << '\n';
		}
	}


}

// namespace Sample
