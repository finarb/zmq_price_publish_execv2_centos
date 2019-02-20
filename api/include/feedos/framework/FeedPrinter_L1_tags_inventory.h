/**************************/
/** FeedOS               **/
/**                      **/
/** copyright QuantHouse **/
/**************************/

#ifndef FEEDOS_FEED_PRINTER_L1_TAGS_INVENTORY_H
#define FEEDOS_FEED_PRINTER_L1_TAGS_INVENTORY_H

#include "FeedPrinter_base.h"

namespace FeedOS {

	class FeedPrinter_L1_tags_inventory
		: public FeedPrinter_base
		, public INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
	{
	public:
		FeedPrinter_L1_tags_inventory(std::ostream & outstream, bool feed_is_realtime = DEFAULT_feed_is_realtime);

		FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming

		virtual void shutdown();

	private:
		std::set<TagNumber> m_EncounteredTags;
		std::map<TagNumber, std::set<Any> > m_EncounteredValues;

		void recordListOfQuotvariable(ListOfQuotationVariable const & l);
		void recordTagValue(TagNumAndValue const & tag_n_value);
	};
}

#endif /* FEEDOS_FEED_PRINTER_L1_TAGS_INVENTORY_H */
