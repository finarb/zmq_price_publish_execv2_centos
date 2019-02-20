
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2015 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_FOS_DICTIONARY_ENTRY_ID_H
#define FEEDOS_COMM_FOS_DICTIONARY_ENTRY_ID_H

#include "../api/generated_constants.h"

namespace FeedOS
{
	struct DictionaryEntry
	{
		std::string	m_ShortName;
		std::string	m_LongName;

		DictionaryEntry(std::string const & short_name = std::string(), std::string const & long_name = std::string());
	};
	typedef std::pair<Types::FOSDictionaryEntryId, DictionaryEntry> DictionaryEntryWithId;
	typedef std::vector<DictionaryEntryWithId> DictionaryEntryWithIdList;

	//! registers a dictionary
	void register_dictionary(Types::EnumTypeDeclaration const &);

	//! removes all dictionaries
	void clear_dictionaries();

	//! tell if a tag carries dictionary entry ids
	bool does_tag_carry_dictionary_entry_ids(Types::TagNumber tag_number);
	inline bool does_tag_carry_dictionary_entry_ids(AnySyntax tag_syntax, Types::TagNumber tag_number)
	{
		return (Syntax_uint32 == tag_syntax) && does_tag_carry_dictionary_entry_ids(tag_number);
	}

	//! tells if a dictionary entry is defined
	bool is_dictionary_entry_id_valid(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id);

	//! get a dictionary entry (short/long name(s)) returning true if the entry is defined, false otherwise
	bool dictionary_entry_id_to_short_name(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id, std::string & short_name);
	bool dictionary_entry_id_to_long_name(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id, std::string & long_name);
	bool dictionary_entry_id_to_names(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id, std::string & short_name, std::string & long_name);

	//! get a dictionary entry (short/long name(s))
	std::string dictionary_entry_id_to_short_name(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id);
	std::string dictionary_entry_id_to_long_name(Types::TagNumber tag_number, Types::FOSDictionaryEntryId entry_id);

	//! get a dictionary entry with id (DictionaryEntryWithId) returning true if the entry is defined, false otherwise
	bool get_dictionary_entry_with_id(Types::TagNumber tag_number, uint16 source_id, std::string const & short_name, DictionaryEntryWithId & dict_entry_with_id);
	bool get_dictionary_entry_with_id_list(Types::TagNumber tag_number, uint16 source_id, DictionaryEntryWithIdList & dict_entry_with_id_list);

	DictionaryEntryWithId get_dictionary_entry_with_id(Types::TagNumber tag_number, uint16 source_id, std::string const & short_name);
	DictionaryEntryWithIdList get_dictionary_entry_with_id_list(Types::TagNumber tag_number, uint16 source_id);

	inline Types::FOSDictionaryEntryId make_dictionary_entry_id(uint16 const source_id, uint16 const enum_id)
	{
		return (source_id << 16) | (enum_id & 0xFFFF);
	}

	inline uint16 extract_source_id_from_dictionary_entry_id(Types::FOSDictionaryEntryId const entry_id)
	{
		return static_cast<uint16>(entry_id >> 16);
	}

	inline uint16 extract_enum_id_from_dictionary_entry_id(Types::FOSDictionaryEntryId const entry_id)
	{
		return entry_id & 0xFFFF;
	}
}

#endif
