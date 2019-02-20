
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_REFERENTIAL_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_REFERENTIAL_DATA_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#	include "InstrumentTagData.h"
#endif


namespace FeedOS {

	class InstrumentReferentialData: public InstrumentTagData
	{
	public:
		InstrumentReferentialData ();
		InstrumentReferentialData (FOSInstrumentCode const & code,	bool load_default_values = true);
		InstrumentReferentialData (InstrumentReferentialData const & v);
		virtual ~InstrumentReferentialData ();

		InstrumentReferentialData const & operator= (InstrumentReferentialData const & v);

				void reset (FOSInstrumentCode const & code,	bool load_default_values);

		// inherited from InstrumentTagData
		virtual	void reset (FOSInstrumentCode const & code)
		{
			reset (code, true);
		}

		void clear_attributes (bool should_load_default_values = true);	

		virtual void load (std::vector<Types::TagNumAndValue> const & tags, bool allow_tag_reset = false);

		LocalInstrumentCode				get_local_code () const;
		PolymorphicInstrumentCode		get_full_polymorphic_code () const;

		void get_branch_id(Types::MarketBranchId & branch_id) const;

		Types::MarketBranchId get_branch_id() const
		{
			Types::MarketBranchId v;
			get_branch_id(v);
			return v;
		}

		typedef TagMap	AttributeMap;
		ExclusiveLock const &	get_lock4_attr_map() const		{ return get_lock4_tag_map(); }
		AttributeMap const &	get_attr_map_nolock() const		{ return get_tag_map_nolock(); }
		AttributeMap &			get_attr_map_nolock()			{ return get_tag_map_nolock(); }

		bool						get_attribute (Types::ReferentialTagNumber tag_num, Any & attr_value) const { return get_tag(tag_num,attr_value); }
		bool						get_attribute (Types::ReferentialTagNumber tag_num, Types::ReferentialAttribute & attr) const { return get_tag(tag_num,attr); }
		Types::ReferentialAttribute	get_attribute (Types::ReferentialTagNumber tag_num) const { return get_tag(tag_num); }

		bool	set_attribute			(Types::ReferentialTagNumber tag_num, Any const & attr_value)	{ return set_tag (tag_num,attr_value); }
		bool	set_attribute			(Types::ReferentialAttribute const & attr)						{ return set_tag (attr); }
		void	delete_attribute		(Types::ReferentialTagNumber tag_num)							{ delete_tag(tag_num); }
		bool	attribute_is_present	(Types::ReferentialTagNumber tag_num) const						{ return tag_is_present(tag_num); }


#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_ACCESSORS(ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_ACCESSORS(ATT,RT,S,NB)
#include <feedos_metadata/tags_referential.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST

	public:
		virtual void	load_default_values();

	public:
		// overloaded from InstrumentTagData
		virtual void load_hook();
	};

}


#endif
