
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_REVERSE_INSTRUMENT_CODE_MAP_H
#define FEEDOS_FRAMEWORK_REVERSE_INSTRUMENT_CODE_MAP_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#include <iostream>

namespace FeedOS {

	class ReverseInstrumentCodeMap
	{
		typedef ReverseInstrumentCodeMap Me;
	public:

		ReverseInstrumentCodeMap ();
		ReverseInstrumentCodeMap const & operator= (ReverseInstrumentCodeMap const & right)
		{
			m_internal_map = right.m_internal_map;
			return *this;
		}

		ReverseInstrumentCodeMap (ReverseInstrumentCodeMap const & right)
		{
			m_internal_map = right.m_internal_map;
		}
		// clear the translation map
		void clear ();

		// unload one item from the translation map
		void unload (FOSInstrumentCode inInternalCode)
		{
			m_internal_map.erase (inInternalCode);
		}

		// load items from a file
		bool load_from_file (char const * input_filename);

		// load items from a stream (one per line, 1st column is the internal code)
		bool load (std::istream & input_stream);

		// load items into the translation map
		void load (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes, std::vector<std::string> const & translated_forms);

		// load items into the translation map
		void load (FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes, ListOfPolymorphicInstrumentCode const & translated_forms);

		// load one item into the translation map
		void load (FOSInstrumentCode inInternalCode, std::string const & translated_form);

		// translate instrument code into a string. Returns empty string if instrument is not known
		inline std::string const & try_translate_instr_code (FOSInstrumentCode inInternalCode) const 
		{
			InternalMap::const_iterator it = m_internal_map.find (inInternalCode);
			if (it != m_internal_map.end()) {
				return it->second;
			}
			static std::string const empty;
			return empty;
		}

		// translate instrument code into a string. Returns false if instrument is not known
		inline bool try_translate_instr_code (FOSInstrumentCode inInternalCode, std::string & instr_code_str) const 
		{
			InternalMap::const_iterator const it = m_internal_map.find (inInternalCode);
			if (it != m_internal_map.end()) {
				instr_code_str = it->second;
				return true;
			}
			instr_code_str.clear();
			return false;
		}

		// request translation of the given internal code
		inline std::string translate_instr_code (FOSInstrumentCode inInternalCode) const 
		{
			InternalMap::const_iterator it = m_internal_map.find (inInternalCode);
			if (it != m_internal_map.end()) {
				return it->second;
			}
			return inInternalCode.to_str();
		}

		// query the translation map
		void dump (std::ostream & s) const;

		// internal map accessor, should not be needed
		typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSLowLevelInstrumentCode, std::string> InternalMap;
		InternalMap const & get_internal_map() const { return m_internal_map; }
	private:
		InternalMap		m_internal_map;
	};

}


#endif


