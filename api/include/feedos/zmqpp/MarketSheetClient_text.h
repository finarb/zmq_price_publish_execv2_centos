
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2007      **/
/************************************/

#ifndef FEEDOS_SAMPLE_MARKET_SHEET_CLIENT_TEXT_H
#define FEEDOS_SAMPLE_MARKET_SHEET_CLIENT_TEXT_H

#include "MarketSheetClient_base.h"

using namespace FeedOS;

namespace Sample
{


/**
 * MarketSheetClient: text display
 *
 */
class MarketSheetClient_text: public MarketSheetClient_base
{
public:
	MarketSheetClient_text (	std::ostream & output, 
								bool print_counters = false,
								bool print_updates_description = true,
								bool reprint_book_after_every_update = true,
								bool reprint_sheet_after_every_update = false,
								int print_depth = -1	// -1 means "print full depth"
							);

	void print_market_sheet () const;

protected:
	/// called each time the market sheet has changed
	virtual void	cbMarketSheetChanged	(	Timestamp const & server_utc_timestamp,
												Timestamp const & market_utc_timestamp, 
												std::string const & update_desc,
												FeedOS::Types::ListOfQuotationContextFlag const & inContext
											);
	virtual void	cbValuesUpdate			(	Timestamp const & server_utc_timestamp,
												Timestamp const & market_utc_timestamp, 
												FeedOS::Types::ListOfQuotationVariable const & inValues
											);
	/// called if an error happens
	virtual void	cbMarketSheetError		(std::string const & error_msg);

private:

	void print_market_sheet_side (char const * side_name, ListOfMarketSheetEntryAndContext const & limits) const;

	std::ostream &	m_output;
	bool			m_print_counters;
	bool			m_print_updates_description;
	bool			m_reprint_book_after_every_update;
	bool			m_reprint_sheet_after_every_update;
	int				m_print_depth;
	unsigned int	m_counter_updates;
	unsigned int	m_counter_errors;
};


} // namespace Sample


#endif
