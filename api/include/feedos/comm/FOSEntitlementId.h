
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2013 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_FOSENTITLEMENT_ID_H
#define FEEDOS_COMM_FOSENTITLEMENT_ID_H

#ifndef FEEDOS_BASE_BASE_H
#	include "../base/base.h"
#endif

#ifndef FEEDOS_API_GENERATED_CONSTANTS_H
#	include "../api/generated_constants.h"
#endif

#ifndef FEEDOS_API_TAGS_H
#	include "../api/tags.h"
#endif

namespace FeedOS {

	typedef int32 FOSLowLevelEntitlementId;
	class FOSEntitlementId;

	static FOSLowLevelEntitlementId const	EID_unknown	= 0;
	static unsigned int const ENTITLEMENT_INITIAL_VERSION = 1;

#define FEEDOS_DEF_ENTITLEMENT_ID(ENTID,MNEMO,DESCR,VER)	static FOSLowLevelEntitlementId const EID_##MNEMO = ENTID;
#include <feedos_metadata/entitlement_ids.hpp>
#undef  FEEDOS_DEF_ENTITLEMENT_ID

	enum Eid
	{
#define FEEDOS_DEF_ENTITLEMENT_ID(ENTID,MNEMO,DESCR,VER)	Eid_##ENTID ##VER = ENTID,
#include <feedos_metadata/entitlement_ids.hpp>
#undef  FEEDOS_DEF_ENTITLEMENT_ID
		LastEidValue
	};

	void	entitlement_id_define_value (FOSLowLevelEntitlementId entitlement_id, std::string const & mnemo, std::string const & description);

	/* Fill the given list with statically defined entitlement ids */
	void	get_builtin_entitlements (Types::EnumTypeDeclaration & entitlement_values);

	/* Fill the given list with all defined entitlement ids (possibly updated by meta data download) */
	void	get_all_entitlements (Types::EnumTypeDeclaration & entitlement_values);

	void	register_entitlement  (FOSLowLevelEntitlementId entitlement_id, std::string const & mnemo, std::string const & description);
	void	register_entitlements (Types::EnumTypeDeclaration  const & entitlements);

	void							entitlement_id_to_mnemo			(FOSLowLevelEntitlementId v, std::ostream & os);

	std::string						entitlement_id_to_description	(FOSLowLevelEntitlementId v);
	std::string						entitlement_id_to_mnemo			(FOSLowLevelEntitlementId v);
	bool							entitlement_id_is_valid			(FOSLowLevelEntitlementId v);
	
	bool							mnemo_to_entitlement_id (std::string const & v, FOSLowLevelEntitlementId & entitlement_id);
	bool							mnemo_to_entitlement_id (std::string const & v, FOSEntitlementId & entitlement_id);
	inline FOSLowLevelEntitlementId	mnemo_to_entitlement_id (std::string const & v) 
	{ 
		FOSLowLevelEntitlementId entitlement_id; 
		mnemo_to_entitlement_id (v,entitlement_id); 
		return entitlement_id; 
	}

	// mnemo_to_entitlement_id() + accept numeric values
	bool				parse_entitlement_id_from_string (std::string const & s, FOSLowLevelEntitlementId & entitlement_id);

	void				register_entitlement		(FOSLowLevelEntitlementId entitlement_id, std::string const & mnemo, std::string const & description);
	// define new entitlement for entitlement_id_to_mnemo ()
	void				entitlement_id_define_value (FOSLowLevelEntitlementId internal_numeric, std::string const & mnemo, std::string const & description);

	unsigned int		extract_entitlement_details	(FOSLowLevelEntitlementId entitlement_id, std::string const & type_description, std::string & entitlement_description);
	
	// try rename mnemo with version 'version', 
	// if renaming operation succeeds return true (when entitlement id has not yet been renamed or renamed with version < version)
	// else return false 
	bool				try_rename_entitlement_id    (FOSLowLevelEntitlementId internal_numeric, unsigned int & version);

	void				clear_entitlement_ids();

	inline void define_all_eid_values()
	{
#define FEEDOS_DEF_ENTITLEMENT_ID(ENTID,MNEMO,DESCR,VER)	entitlement_id_define_value(ENTID, #MNEMO, #DESCR);
#include <feedos_metadata/entitlement_ids.hpp>
#undef FEEDOS_DEF_ENTITLEMENT_ID
	}

	inline void get_builtin_entitlements(Types::EnumTypeDeclaration & eids)
	{
		eids = Types::EnumTypeDeclaration(	Types::s_METADATA_ENUM_TYPE_DECLARATION_EID_NAME,
											"entitlement ids for FeedOS feed",
											Types::ListOfTagNumber (1, TAG_InternalEntitlementId),
											Types::ListOfEnumValueDeclaration());

#define FEEDOS_DEF_ENTITLEMENT_ID(ENTID,MNEMO,DESCR,VER)	\
		eids.getEnumValues().push_back (Types::EnumValueDeclaration (Any::make_int32(ENTID),#MNEMO,"DESCR="#DESCR",VER="#VER));
#include <feedos_metadata/entitlement_ids.hpp>
#undef FEEDOS_DEF_ENTITLEMENT_ID
	}


	class FOSEntitlementId
	{
	public:
		inline FOSEntitlementId() : m_num (EID_unknown) {}
		inline FOSEntitlementId(FOSLowLevelEntitlementId const & v) : m_num (v) {}
		inline FOSEntitlementId(FOSEntitlementId const & v) : m_num (v.m_num) {}
		inline FOSEntitlementId const & operator= (FOSEntitlementId const & v) { m_num = v.m_num; return *this; }
		inline FOSEntitlementId const & operator= (FOSLowLevelEntitlementId const & v) { m_num = v; return *this; }
		operator FOSLowLevelEntitlementId () const { return m_num; }

		bool operator== (FOSLowLevelEntitlementId const & v) const		{ return m_num == v; }
		bool operator!= (FOSLowLevelEntitlementId const & c) const		{ return ! operator== (c); }
		bool operator<  (FOSLowLevelEntitlementId const & v) const		{ return m_num <  v; }
		struct Hash { size_t operator()(FOSEntitlementId const & s) const { return (FOSLowLevelEntitlementId)s; } };

		inline bool is_valid () const { return m_num != EID_unknown; }
		inline void set_invalid () { m_num = EID_unknown; }
		inline void set (FOSLowLevelEntitlementId c) { m_num = c; }

		void dump (std::ostream & os) const;
		std::string to_str() const { return entitlement_id_to_mnemo (m_num); }

		bool read_from_string (std::string const & s) { return parse_entitlement_id_from_string (s, m_num); }

		static FOSEntitlementId	build_from_string (std::string const & v) 
		{ 
			FOSEntitlementId entitlement_id; 
			entitlement_id.read_from_string (v); 
			return entitlement_id; 
		}

		// return the "human readable" description for this entitlement id
		std::string get_description() const { return entitlement_id_to_mnemo (m_num); }

	private:
		FOSLowLevelEntitlementId	m_num;
	};
}

#endif

