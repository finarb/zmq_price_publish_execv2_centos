
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2007      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_QUOTATION_CONTEXT_H
#define FEEDOS_FRAMEWORK_QUOTATION_CONTEXT_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	ifndef FEEDOS_API_API_H
#		include "../api/api.h"
#	endif
#endif

#ifndef FEEDOS_FRAMEWORK_MARKETS_ALL_DEFINITIONS_H
#	include "markets/all_definitions.h"
#endif

#include <map>
#include <set>
#include <list>
#include <string.h>

namespace FeedOS {

	class QuotationContext
	{
		QuotationContext const & operator=(QuotationContext const &);
	public:
		static bool const DEFAULT_value_for_show_syntax = true;

		QuotationContext (bool show_syntax_for_nonstring_values=DEFAULT_value_for_show_syntax, TagDisplayFormat tag_display_format=TagDisplayFormat_ShortName);

		// load a set of values
		// WARNING: the list should not be deallocated
		QuotationContext (Types::ListOfQuotationContextFlag const & list, bool show_syntax_for_nonstring_values=DEFAULT_value_for_show_syntax,
				TagDisplayFormat tag_display_format=TagDisplayFormat_ShortName);

		virtual ~QuotationContext ();

		// load a new set of values
		// WARNING: the list should not be deallocated
		void load (Types::ListOfQuotationContextFlag const & list);

		// clear current values
		void clear ();

		struct lt_str { bool operator()(char const * a, char const * b) const { return ::strcmp (a,b)<0; } };
		typedef std::set<char const *, lt_str>	SetOfValues;

		bool is_empty () const													{ return m_map_of_values.empty(); }
		bool is_tag_present (Types::TagNumber t) const;
		bool is_value_present_for_tag (std::string const & value, Types::TagNumber t) const;

		SetOfValues const & get_values_for_tag (Types::TagNumber t) const;

		// print all values (uses market_value2name() to convert values)
		void print_content (	std::ostream & os,
								bool print_raw_values,
								bool print_verbose_name,
								char const * inter_tag_separator = "\n",
								char const * inter_value_separator = "|",
								char const * inter_value_list_prefix = "="
							) const;

	private:
		bool const m_opt_show_syntax;
		TagDisplayFormat const m_tag_display_format;

		typedef std::map<Types::TagNumber, SetOfValues>	ValuesPerTag;
		ValuesPerTag		m_map_of_values;

		// StringCache must guarantee that elements will not be reallocated (unlike std::vector when growing)
		typedef std::list<std::string>	StringCache;
		StringCache			m_temp_strings;

		inline std::string & cache_value (std::string & s)
		{
			m_temp_strings.push_back (std::string());
			m_temp_strings.back ().swap (s);
			return m_temp_strings.back ();
		}

		inline void insert_persistent_value (Types::TagNumber t, char const * s)
		{
			m_map_of_values[t].insert (s);
		}

		inline void insert_volatile_value (Types::TagNumber t, std::string & s)
		{
			insert_persistent_value (t, cache_value(s).c_str());
		}

	};

}


#endif
