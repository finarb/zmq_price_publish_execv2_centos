
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H

#ifndef FEEDOS_BASE_LOCK_H
#	include "../base/lock.h"
#endif

#ifndef FEEDOS_API_TAGS_H
#	include "../api/tags.h"
#endif

#include <map>
#include <set>
#include <vector>

namespace FeedOS {
	class InstrumentTagData;
}

bool operator== (FeedOS::InstrumentTagData const &, FeedOS::InstrumentTagData const &);

namespace FeedOS {

	template <typename RT>
	inline void syntax_convert_tagvalue (Enum const & s, RT & t) { t=(RT)(unsigned int)s; }

	template <typename S,typename RT>
	inline void syntax_convert_tagvalue (S const & s, RT & t) { t=s; }

	class InstrumentTagData
	{
	public:
		InstrumentTagData ();
		InstrumentTagData (FOSInstrumentCode const & code);
		InstrumentTagData (InstrumentTagData const & v);
		virtual ~InstrumentTagData ();

		InstrumentTagData const & operator= (InstrumentTagData const & v);

		virtual void reset (FOSInstrumentCode const & code);

		FEEDOS_INLINE void clear_tags ();

		virtual void load (std::vector<Types::TagNumAndValue> const & tags, bool allow_tag_reset = false);
		void dump (std::vector<Types::TagNumAndValue> & tags) const;
		void dump (std::vector<Types::TagNumAndValue> & tags, std::vector<Types::TagNumber> const & requested_list) const;

		FOSInstrumentCode const &	get_internal_code () const	{ return m_instr_code; }
		FOSInstrumentCode &			get_internal_code ()		{ return m_instr_code; }

		FEEDOS_INLINE bool			get_tag_nolock	(Types::TagNumber tag_num, Any & tag_value) const;
		FEEDOS_INLINE bool			get_tag			(Types::TagNumber tag_num, Any & tag_value) const;
		bool						get_tag			(Types::TagNumber tag_num, Types::TagNumAndValue & v) const;
		Types::TagNumAndValue const	get_tag			(Types::TagNumber tag_num) const;
		FEEDOS_INLINE Any &			ref_tag_nolock	(Types::TagNumber tag_num);

		FEEDOS_INLINE	bool	set_tag_nolock	(Types::TagNumber tag_num, Any const & tag_value);
		FEEDOS_INLINE	bool	set_tag			(Types::TagNumber tag_num, Any const & tag_value);
		inline			bool	set_tag_nolock	(Types::TagNumAndValue const & tag)	{ return set_tag_nolock(tag.getNum(),tag.getValue()); }
		inline			bool	set_tag			(Types::TagNumAndValue const & tag)	{ return set_tag(tag.getNum(),tag.getValue()); }

		FEEDOS_INLINE	void	delete_tag_nolock		(Types::TagNumber tag_num);
		FEEDOS_INLINE	void	delete_tag				(Types::TagNumber tag_num);
		FEEDOS_INLINE	bool	tag_is_present_nolock	(Types::TagNumber tag_num) const;
		FEEDOS_INLINE	bool	tag_is_present			(Types::TagNumber tag_num) const;

#	define FEEDOS_DEF_SYNTAX_ACCESSORS(RT,S,S2)	\
		FEEDOS_INLINE bool		get_tag_##S				(Types::TagNumber tag_num, S2 & value) const;	\
		FEEDOS_INLINE bool		get_tag_##S##_nolock	(Types::TagNumber tag_num, S2 & value) const;	\
		FEEDOS_INLINE RT const	get_tag_##S				(Types::TagNumber tag_num) const { S2 value; get_tag_##S			(tag_num,value); return /*(RT)*/value; }	\
		FEEDOS_INLINE RT const	get_tag_##S##_nolock	(Types::TagNumber tag_num) const { S2 value; get_tag_##S##_nolock(tag_num,value); return /*(RT)*/value; }	\
		FEEDOS_INLINE Any &		ref_tag_##S##_nolock	(Types::TagNumber tag_num);			\
		FEEDOS_INLINE void		set_tag_##S				(Types::TagNumber tag_num, RT const & v);	\
		FEEDOS_INLINE void		set_tag_##S##_nolock	(Types::TagNumber tag_num, RT const & v);

		FEEDOS_DEF_SYNTAX_ACCESSORS (std::string			,String		,String		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (Timestamp				,Timestamp	,Timestamp	)

#	undef FEEDOS_DEF_SYNTAX_ACCESSORS
// POD cannot be returned const
#	define FEEDOS_DEF_SYNTAX_ACCESSORS(RT,S,S2)	\
		FEEDOS_INLINE bool		get_tag_##S				(Types::TagNumber tag_num, S2 & value) const;	\
		FEEDOS_INLINE bool		get_tag_##S##_nolock	(Types::TagNumber tag_num, S2 & value) const;	\
		FEEDOS_INLINE RT 		get_tag_##S				(Types::TagNumber tag_num) const { S2 value; get_tag_##S			(tag_num,value); return /*(RT)*/value; }	\
		FEEDOS_INLINE RT 		get_tag_##S##_nolock	(Types::TagNumber tag_num) const { S2 value; get_tag_##S##_nolock(tag_num,value); return /*(RT)*/value; }	\
		FEEDOS_INLINE Any &		ref_tag_##S##_nolock	(Types::TagNumber tag_num);			\
		FEEDOS_INLINE void		set_tag_##S				(Types::TagNumber tag_num, RT const & v);	\
		FEEDOS_INLINE void		set_tag_##S##_nolock	(Types::TagNumber tag_num, RT const & v);

		FEEDOS_DEF_SYNTAX_ACCESSORS (float64				,float64	,float64	)
		FEEDOS_DEF_SYNTAX_ACCESSORS (unsigned int			,uint32		,uint32		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (unsigned int			,uint16		,uint16		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (unsigned int			,uint8		,uint8		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (int					,int32		,int32		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (int					,int16		,int16		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (int					,int8		,int8		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (char					,char		,char		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (unsigned int			,Enum		,Enum		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (bool					,bool		,bool		)
		FEEDOS_DEF_SYNTAX_ACCESSORS (FOSLowLevelInteger		,int64		,FOSLowLevelInteger	)

#	undef FEEDOS_DEF_SYNTAX_ACCESSORS


#	define FEEDOS_DEF_TAG_ACCESSORS(ATT,RT,S)	\
		FEEDOS_DEF_TAG_GET_ACCESSORS(ATT,RT,S)	\
		FEEDOS_DEF_TAG_SET_ACCESSORS(ATT,RT,S)

#	define FEEDOS_DEF_TAG_GET_ACCESSORS(ATT,RT,S)	\
		inline RT /*const*/		get_##ATT##_nolock	() const		{ return (RT) get_tag_##S##_nolock	(TAG_##ATT); }		\
		inline RT /*const*/		get_##ATT			() const		{ return (RT) get_tag_##S			(TAG_##ATT); }		\
		inline bool			get_##ATT##_nolock	(RT & v) const	{ S t; if (get_tag_##S##_nolock	(TAG_##ATT,t)) { syntax_convert_tagvalue (t,v); return true; } return false; }		\
		inline bool			get_##ATT			(RT & v) const	{ S t; if (get_tag_##S			(TAG_##ATT,t)) { syntax_convert_tagvalue (t,v); return true; } return false; }		\
		inline Any &		ref_##ATT##_nolock	()				{ return ref_tag_##S##_nolock (TAG_##ATT); }

#	define FEEDOS_DEF_TAG_SET_ACCESSORS(ATT,RT,S)	\
		inline void			set_##ATT##_nolock	(RT const & v)	{ set_tag_##S##_nolock	(TAG_##ATT, (S) v); }	\
		inline void			set_##ATT			(RT const & v)	{ set_tag_##S			(TAG_##ATT, (S) v); }

		// TODO: use parameter NB to check bounds at runtime ?  (see FEEDOS_DEF_TAG_LIST_CLASS, too)
#	define FEEDOS_DEF_TAG_LIST_ACCESSORS(ATT,RT,S,NB)	\
		inline RT				get_##ATT(unsigned int n) const		{ return (RT) get_tag_##S (static_cast<Types::TagNumber> (TAG_##ATT##_0+n)); } \
		inline void				set_##ATT(unsigned int n, RT const & v)	{ set_tag_##S (static_cast<Types::TagNumber> (TAG_##ATT##_0+n), (S) v); }

//	protected:
		virtual void load_hook () {}

		typedef std::map <Types::TagNumber, Any>	TagMap;

		ExclusiveLock const &	get_lock4_tag_map() const	{ return m_tag_map_lock; }
		TagMap const &			get_tag_map_nolock() const	{ return m_tag_map; }
		TagMap &				get_tag_map_nolock()		{ return m_tag_map; }

	public:
		inline bool check_set_tag_syntax (Types::TagNumber
#if FEEDOS_ENABLE_PARANOID_CHECKS
				tag_num
#endif
				, Any const &
#if FEEDOS_ENABLE_PARANOID_CHECKS
				tag_value
#endif
				) const
		{
#if FEEDOS_ENABLE_PARANOID_CHECKS
			AnySyntax expected_syntax = tag_expected_syntax (tag_num);
			if ( (expected_syntax != Syntax_UNKNOWN) && (tag_value.get_syntax() != expected_syntax) ) {
				log_set_tag_unexpected_syntax(tag_num,tag_value.get_syntax(),expected_syntax);
				return false;
			}
#endif
			return true;
		}

	private:
		FOSInstrumentCode			m_instr_code;
		ExclusiveLock				m_tag_map_lock;
		TagMap						m_tag_map;

		static void log_set_tag_unexpected_syntax (Types::TagNumber tag_num, AnySyntax actual, AnySyntax expected);

	public:

		class Filter
		{
		public:
			Filter (std::vector<Types::TagNumAndValue> const & filter);
			inline bool is_null() const { return scope_filter.empty(); }
			typedef std::set <Any> SetOfAnyValue;
			typedef std::map <unsigned int, SetOfAnyValue > ScopeFilter;
			ScopeFilter		scope_filter;
		private:
			friend class InstrumentTagData;
		};

		inline bool matches_filter_nolock	(Filter const & filter) const
		{
			return (filter.is_null()) ? true : perform_matches_filter_nolock (filter);
		}

		inline bool matches_filter			(Filter const & filter) const
		{
			SCOPE_AUTO_LOCK (l,get_lock4_tag_map());
			return matches_filter_nolock (filter);
		}

	private:
		bool perform_matches_filter_nolock	(Filter const & filter) const;

		friend bool ::operator== (FeedOS::InstrumentTagData const &, FeedOS::InstrumentTagData const &);

	};

	bool perform_matches_filter_CFICode (bool tag_present, Any & tag_value, InstrumentTagData::Filter::SetOfAnyValue const & tag_allowed_values);
	bool perform_matches_filter_pattern (bool tag_present, Any & tag_value, InstrumentTagData::Filter::SetOfAnyValue const & tag_allowed_values, Types::TagNumber tag_id);

	template<class TagData>
	inline bool perform_matches_filter_nolock (TagData const &instr,
											   InstrumentTagData::Filter::ScopeFilter const & scope_filter)
	{
		Any tag_value;
		bool tag_present;

		for (InstrumentTagData::Filter::ScopeFilter::const_iterator it = scope_filter.begin(); it != scope_filter.end(); ++it) {
			Types::TagNumber tag_id = static_cast<Types::TagNumber> (it->first);
			InstrumentTagData::Filter::SetOfAnyValue const & tag_allowed_values = it->second;

			tag_present = instr.get_tag_nolock (tag_id, tag_value);

			switch (tag_id) {
			case TAG_CFICode:
				///////////////////////
				// SPECIAL PROCESSING for CFICode: prefix allowed, and '.' acts as a wildcard 
				///////////////////////
				if (!perform_matches_filter_CFICode (tag_present, tag_value, tag_allowed_values)) {
					return false;
				}
				break;

			case TAG_StdMaturity:
			case TAG_Issuer:
			case TAG_Description:
			case TAG_SecuritySubType:
				///////////////////////
				// SPECIAL PROCESSING: evaluate using a FilePattern
				///////////////////////
				if (!perform_matches_filter_pattern (tag_present, tag_value, tag_allowed_values, tag_id)) {
					return false;
				}
				break;

			default:
				///////////////////////
				// normal processing: operator==
				///////////////////////
				if (!tag_present) {
					// support "syntax_unknown" meaning "tag not set"
					static Any const any_unknown (Syntax_UNKNOWN);
					if (tag_allowed_values.find(any_unknown) == tag_allowed_values.end()) {
						// value not found in filter list : not in scope
						return false;
					}
				} else {
					if (tag_allowed_values.find(tag_value) == tag_allowed_values.end()) {
						// value not found in filter list : not in scope
						return false;
					}
				}
			}
		}

		return true;
	}

#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/InstrumentTagData.inl"
#endif


}


#endif
