
/*********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** get generic tag by source id            **/
/**                                         **/
/** QuantHouse 2017                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>
#include <feedos/comm/FOSDictionaryEntryId.h>

using namespace FeedOS;
using namespace FeedOS::Types;

//![snippet_sub_L1_generic_tags_entry_id_by_source_id]
static void print_generic_tag_entry_for_source_id(Types::TagNumber const tag_number, uint16 const source_id, std::string const & short_name)
{
		FeedOS::DictionaryEntryWithId dictionary_entry_with_id;

		std::cout << "\trelated_tags=" << tag_number
				  << "\n\tsource_id=" << source_id
				  << "\n";
		// Get the entry_id, short_name and long_name of the tag associated to a short name, tag number and source id provided
		if (FeedOS::get_dictionary_entry_with_id(tag_number, source_id, short_name, dictionary_entry_with_id))
		{
			std::cout << "\n\n\t\tvalue=" << dictionary_entry_with_id.first
					  << "\n\t\t\tname=" << dictionary_entry_with_id.second.m_ShortName
					  << "\n\t\t\tdescription=" <<  dictionary_entry_with_id.second.m_LongName
					  << std::endl;
		}
		std::cout << std::endl;
}

static void print_generic_tag_entry_list_for_source_id(Types::TagNumber const tag_number, uint16 const source_id)
{
	FeedOS::DictionaryEntryWithIdList dictionary_entry_with_id_list;

	std::cout << "\trelated_tags=" << tag_number
			  << "\n\tsource_id=" << source_id
			  << "\n";
	// Get a list of the entry_id, short_name and long_name of a tag associated to the tag number and the source id provided
	if (FeedOS::get_dictionary_entry_with_id_list(tag_number, source_id, dictionary_entry_with_id_list))
	{
		FeedOS::DictionaryEntryWithIdList::const_iterator it = dictionary_entry_with_id_list.begin();
		FeedOS::DictionaryEntryWithIdList::const_iterator const it_end = dictionary_entry_with_id_list.end();

		for (; it != it_end; ++it)
		{
			FeedOS::DictionaryEntryWithId const & dictionary_entry_with_id = *it;

			std::cout << "\n\t\tvalue=" << dictionary_entry_with_id.first
					  << "\n\t\t\tname=" << dictionary_entry_with_id.second.m_ShortName
					  << "\n\t\t\tdescription=" <<  dictionary_entry_with_id.second.m_LongName
					  << "\n";
		}
	}
	std::cout << std::endl;
}
//![snippet_sub_L1_generic_tags_entry_id_by_source_id]

/**
 * This sample demonstrates how to get generic tags by source id
 * See perform_subscribe.cpp for documentation
 */
void perform_get_generic_tag_by_source_id(API::Connection & connection, int const argc, char const * const argv[])
{
	FEEDOS_SCOPER(User, "perform_get_generic_tag_by_source_id");

	if (argc < 3 || argc > 4) {
		std::cerr << "Usage: tag_number source_id [short_name]" << std::endl;
		return;
	}

	Types::TagNumber const tag_number = atoi(argv[1]);
	uint16 const source_id = atoi(argv[2]);

	if (argc > 3)
	{
		std::string const short_name = argv[3];

		print_generic_tag_entry_for_source_id(tag_number, source_id, short_name);
	}
	else
	{
		print_generic_tag_entry_list_for_source_id(tag_number, source_id);
	}
}
