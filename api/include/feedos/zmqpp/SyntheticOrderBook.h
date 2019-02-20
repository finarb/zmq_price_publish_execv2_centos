
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/************************************/

#ifndef FEEDOS_SAMPLE_SYNTHETIC_BOOK_H
#define FEEDOS_SAMPLE_SYNTHETIC_BOOK_H

#include <feedos/api/api.h>
#include <cstring>
#include <stdio.h>

using namespace FeedOS;

namespace Sample
{

int	askPriceCompare(double const & price_a, double const & price_b);
int	bidPriceCompare(double const & price_a, double const & price_b);

/**
 * SyntheticOrderBookEntry
 *
 */
class SyntheticOrderBookEntry: public FeedOS::Types::OrderBookEntryExt
{
public:
	SyntheticOrderBookEntry(float64 price, float64 qty, int32 nborders)
		: FeedOS::Types::OrderBookEntryExt(price,qty,nborders)
	{}

	void	addOrder	(double const & quantity)	{ getQty() += quantity; ++getNbOrders(); }
	void	removeOrder	(double const & quantity)	{ getQty() -= quantity; --getNbOrders(); }
};


/**
 * SyntheticOrderBookSide
 *
 */
class SyntheticOrderBookSide
{
public:
	typedef int	(*PriceCompareFunc) (double const & price_a, double const & price_b);

public:
	/// ctor
	SyntheticOrderBookSide(PriceCompareFunc price_compare_func)
		: m_PriceCompareFunc(price_compare_func)
	{}

	virtual ~SyntheticOrderBookSide() {}

	/// get the book entries
	std::vector<SyntheticOrderBookEntry> const &	getOrderBookEntries() const	{ return m_OrderBookEntries; }

	/// add an order
	void	addOrder	(double const & price, double const & quantity);

	/// remove an order
	void	removeOrder	(double const & price, double const & quantity);

	/// clear the book side
	void	clearBookSide();

private:
	/// FatalException
	struct FatalException
	{
	};

private:
	/// get a book entry (out of range throws a FatalException)
	SyntheticOrderBookEntry &	getOrderBookEntry(unsigned int index);

	/// find the position of the given price
	bool	findPricePos(double const & price, unsigned int & index);

	void	invariant();

private:
	PriceCompareFunc						m_PriceCompareFunc;
	std::vector<SyntheticOrderBookEntry>	m_OrderBookEntries;
};

/**
 * SyntheticOrderBook
 *
 */
class SyntheticOrderBook
{
public:
	/// ctor
	SyntheticOrderBook();

	/// dtor
	virtual ~SyntheticOrderBook() {}

	/// get the bid limits
	std::vector<SyntheticOrderBookEntry> const &	getBidLimits() const	{ return m_BidLimits.getOrderBookEntries(); }
	/// get the ask limits
	std::vector<SyntheticOrderBookEntry> const &	getAskLimits() const	{ return m_AskLimits.getOrderBookEntries(); }

	/// add an order
	void	addOrder		(FeedOS::Types::FIXSide side, double const & price, double const & quantity);
	/// remove an order
	void	removeOrder		(FeedOS::Types::FIXSide side, double const & price, double const & quantity);

	/// clear the book
	void clearBook		(FeedOS::Types::FIXSide side);

	void print (	std::ostream & s,
					int max_depth = -1	// -1 means "print full depth"
				) const;

private:
	static int print_price (char *buf, double price);

	SyntheticOrderBookSide		m_BidLimits;
	SyntheticOrderBookSide		m_AskLimits;
};


} // namespace Sample


#endif
