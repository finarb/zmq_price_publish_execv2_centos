
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2007      **/
/************************************/

#include <feedos/zmqpp/MarketSheetClient_text.h>
#include <feedos/zmqpp/tools.h>
#include <feedos/framework/QuotationContext.h>
#include <algorithm>
#include <stdio.h> //sprintf

using namespace FeedOS;

namespace Sample
{
	static int print_price (char *buf, double price)
	{
		std::stringstream s;
		FeedOS::print_price (s, price);	// handles "magic values" like AT_OPEN and AT_BEST
		std::string str = s.str();
		strcpy (buf, str.c_str());
		return (int)str.size();
	}


	MarketSheetClient_text::
	MarketSheetClient_text (	std::ostream & output,
								bool print_counters,
								bool print_updates_description,
								bool reprint_book_after_every_update,
								bool reprint_sheet_after_every_update,
								int print_depth
							)
		: m_output (output)
		, m_print_counters (print_counters)
		, m_print_updates_description (print_updates_description)
		, m_reprint_book_after_every_update (reprint_book_after_every_update)
		, m_reprint_sheet_after_every_update (reprint_sheet_after_every_update)
		, m_print_depth (print_depth)
		, m_counter_updates (0)
		, m_counter_errors (0)
	{}


	void
	MarketSheetClient_text::print_market_sheet () const
	{
		FeedOS::Types::MarketSheet const &	sheet = getMarketSheet();

		ListOfMarketSheetEntryAndContext const & bid_limits = sheet.getBidSide();
		ListOfMarketSheetEntryAndContext const & ask_limits = sheet.getAskSide();

		print_market_sheet_side ("BID", bid_limits);
		print_market_sheet_side ("ASK", ask_limits);
	}


	void
	MarketSheetClient_text::print_market_sheet_side (char const * side_name, ListOfMarketSheetEntryAndContext const & limits) const
	{
		size_t max_level = limits.size();
		if (-1 != m_print_depth) {
			max_level = std::max (max_level, (size_t)m_print_depth);
		}

		m_output << "\n*** " << side_name << '\n';

		QuotationContext c;

		char buffer[128];
		for (size_t i=0; i<max_level; ++i) {
			MarketSheetEntry const & order = limits[i].getOrder();
			ListOfQuotationContextFlag const & context = limits[i].getContext();

			int buffer_len = 0;
			buffer_len += sprintf (buffer+buffer_len, "%-3u   ", (unsigned int)i);

			buffer_len += print_price (buffer+buffer_len, order.getPrice());
			buffer_len += sprintf (	buffer+buffer_len,
									" x %6u (%-20s)",
									(unsigned int) order.getQty(),
									(char const *) order_id2str(order.getOrderID()).c_str()
								);

			m_output << buffer;

			if (!context.empty()) {
				m_output << "\tcontext: ";
				c.load (context);
				c.print_content (m_output, false, true, ",", "+", "=");
			}

			m_output << '\n';
		}

	}


	void
	MarketSheetClient_text::cbMarketSheetChanged	(	Timestamp const & server_utc_timestamp,
														Timestamp const & market_utc_timestamp,
														std::string const & update_desc,
														FeedOS::Types::ListOfQuotationContextFlag const & inContext
													)
	{
		SyntheticOrderBook const &	book = getOrderBook();

		++m_counter_updates;

		if (m_print_counters) {
			std::string update_type = update_desc.substr(0,update_desc.find (':'));
			std::cerr
				<< "updates"
				"(nb="<<m_counter_updates<<
				",last:"<<update_type<<
				",errors="<<m_counter_errors<<
				") "
				<< "current_depth"
				"(bid="<<(unsigned int)book.getBidLimits().size()<<
				",ask="<<(unsigned int)book.getAskLimits().size()<<
				")             \r" << std::flush
				;
		}

		bool should_print_content = (m_print_updates_description || m_reprint_sheet_after_every_update || m_reprint_book_after_every_update);

		if (should_print_content) {
			if (m_print_counters)
			{
				std::cerr << '\n';
			}

			if (m_print_updates_description) {
				m_output << "========== "<<update_desc<<'\n';
				if (!inContext.empty()) {
					// there are "context flags"
					// => dump all the tags received (see list in api/tags_quotation_context.hpp)
					//    different tags are available depending on market
					FeedOS::QuotationContext c;
					c.load (inContext);
					m_output << "=== CONTEXT:\t";
					c.print_content (m_output, true, false, "\n\t\t","+",":\t");
					m_output << '\n';

					// example of looking for value in the "context"
#if 0
					if (c.is_tag_present (FeedOS::TAG_Buyer)) {
						FeedOS::QuotationContext::SetOfValues const & values = c.get_values_for_tag (FeedOS::TAG_Buyer);
						char const * buyer = *values.begin();
						m_output << "= Buyer: "<<buyer<<'\n';
					} else if (c.is_tag_present (FeedOS::TAG_Seller)) {
						FeedOS::QuotationContext::SetOfValues const & values = c.get_values_for_tag (FeedOS::TAG_Seller);
						char const * seller = *values.begin();;
						m_output << "= Seller: "<<seller<<'\n';
					}
#endif
				}
			}
			else
			{
				m_output << "=== server time: "<<server_utc_timestamp<<"\t market time: "<<market_utc_timestamp<<'\n';
			}

			if (m_reprint_sheet_after_every_update) {
				print_market_sheet();
			}
			if (m_reprint_book_after_every_update) {
				book.print (m_output);
			}
		}
	}

	void
	MarketSheetClient_text::cbMarketSheetError		(std::string const & error_msg)
	{
//		m_output << "ERROR: "<<error_msg<<std::endl;
		if (!m_print_counters)
		{
			std::cerr << "ERROR: "<<error_msg<<std::endl;
		}

		FEEDOS_LOG_EVERY_NSEC(1, User, Critical, error_msg);
		++m_counter_errors;
	}

	void
	MarketSheetClient_text::cbValuesUpdate		(	Timestamp const & server_utc_timestamp,
													Timestamp const & market_utc_timestamp,
													FeedOS::Types::ListOfQuotationVariable const & inValues
												)
	{
		if (m_print_updates_description) {
			if (m_print_counters)
			{
				std::cerr << '\n';
			}
			m_output << "========== VALUES\n";
			m_output << "=== server time: "<<server_utc_timestamp<<"\t market time: "<<market_utc_timestamp<<'\n';
			dump_quot_variables (m_output, inValues, /*compact=*/false);
		}
	}


} // namespace Sample
