
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_MARKET_ID_H
#define FEEDOS_COMM_MARKET_ID_H

#ifndef FEEDOS_BASE_BASE_H
#	include "../base/base.h"
#endif

#include <iostream>

namespace FeedOS {

	namespace Types {
		class EnumValueDeclaration;
	}

	typedef uint16	FOSLowLevelMarketId;

	static FOSLowLevelMarketId const	MARKET_ID_unknown	= 0;
	static FOSLowLevelMarketId const	MARKET_ID_MAX_VALUE	= 511;

#define FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)		static FOSLowLevelMarketId const MARKET_ID_##MIC = NUM;
#define FEEDOS_DEF_MARKET_ALIAS(OLD_MIC,NEW_MIC)							static FOSLowLevelMarketId const MARKET_ID_##OLD_MIC = MARKET_ID_##NEW_MIC;
#define	FEEDOS_DEF_MARKET_RENAMED(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB,OLD_MIC,SEQNUM)	\
		FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)							\
		FEEDOS_DEF_MARKET_ALIAS(OLD_MIC,MIC)
#include <feedos_metadata/ids_market.hpp>
#undef  FEEDOS_DEF_MARKET
#undef  FEEDOS_DEF_MARKET_ALIAS
#undef  FEEDOS_DEF_MARKET_RENAMED

	enum Mic
	{
#define FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)							Mic_##NUM = NUM,
#define FEEDOS_DEF_MARKET_ALIAS(OLD_MIC,NEW_MIC)
#define	FEEDOS_DEF_MARKET_RENAMED(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB,OLD_MIC,SEQNUM)	FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)
#include <feedos_metadata/ids_market.hpp>
#undef FEEDOS_DEF_MARKET
#undef FEEDOS_DEF_MARKET_ALIAS
#undef FEEDOS_DEF_MARKET_RENAMED
		LastMic
	};

	class FOSMarketId;

	void							market_id_internal2iso (FOSLowLevelMarketId v, std::ostream & os);
	std::string						market_id_internal2iso (FOSLowLevelMarketId v);
	bool							market_id_iso2internal (std::string const & v, FOSLowLevelMarketId & market_id);
	bool							market_id_iso2internal (std::string const & v, FOSMarketId & market_id);
	inline FOSLowLevelMarketId		market_id_iso2internal (std::string const & v) { FOSLowLevelMarketId market_id; market_id_iso2internal(v,market_id); return market_id; }
	std::string						market_id_internal2description (FOSLowLevelMarketId v);

	// market_id_iso2internal() + accept numeric values
	bool				read_market_id_from_string (std::string const & s, FOSLowLevelMarketId & market_id);

	void				register_MIC  (FOSLowLevelMarketId mic_code, std::string const & mic_name, std::string const & description);
	// define new markets for market_id_iso2internal()
	void				market_id_define_value (FOSLowLevelMarketId internal_numeric, std::string const & iso_mic, std::string const & description);

	void				market_id_define_alias (std::string const & iso_mic_alias, FOSLowLevelMarketId internal_numeric_real);

	// cancel previous calls to "market_id_define_value"
	void				market_id_reload_default_values ();

	unsigned int		extract_mic_version		(FOSLowLevelMarketId internal_numeric, std::string const & declaration);
	
	// try rename MIC with version seqnum, if renaming operation succeeds return true (when MIC has not yet been renamed or renamed with version < seqnum)
	// else return false 
	bool				try_rename_market_id    (FOSLowLevelMarketId internal_numeric, unsigned int & seqnum);

	void				clear_market_ids();

	inline void register_mics()
	{
#define FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)	\
	{																		\
		std::string description(#ACCR);										\
		if (description.empty()) {	description = #DESCRIPTION; }			\
		register_MIC(NUM, #MIC, description);								\
	}
#define FEEDOS_DEF_MARKET_ALIAS(OLD_MIC,NEW_MIC)												market_id_define_alias (#OLD_MIC, MARKET_ID_##NEW_MIC);
#define	FEEDOS_DEF_MARKET_RENAMED(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB,OLD_MIC,SEQNUM)	FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)
#include <feedos_metadata/ids_market.hpp>
#undef FEEDOS_DEF_MARKET
#undef FEEDOS_DEF_MARKET_ALIAS
#undef FEEDOS_DEF_MARKET_RENAMED
	}


	class FOSMarketId
	{
	public:
		inline FOSMarketId() : m_num (MARKET_ID_unknown) {}
		inline FOSMarketId(FOSLowLevelMarketId const & v) : m_num (v) {}
		inline FOSMarketId(FOSMarketId const & v) : m_num (v.m_num) {}
		inline FOSMarketId const & operator= (FOSMarketId const & v) { m_num = v.m_num; return *this; }
		inline FOSMarketId const & operator= (FOSLowLevelMarketId const & v) { m_num = v; return *this; }
		operator FOSLowLevelMarketId () const { return m_num; }

		bool operator== (FOSLowLevelMarketId const & v) const		{ return m_num == v; }
		bool operator!= (FOSLowLevelMarketId const & c) const		{ return ! operator== (c); }
		bool operator<  (FOSLowLevelMarketId const & v) const		{ return m_num <  v; }
		struct Hash { size_t operator()(FOSMarketId const & s) const { return (FOSLowLevelMarketId)s; } };

		inline bool is_valid () const { return m_num != MARKET_ID_unknown; }
		inline void set_invalid () { m_num = MARKET_ID_unknown; }
		inline void set (FOSLowLevelMarketId c) { m_num = c; }

		// return corresponding ISO MIC value (or numeric value if unknown market)
		void dump (std::ostream & os) const;
		std::string to_str() const { return market_id_internal2iso (m_num); }

		// convert an ISO MIC into internal numeric value
		bool read_from_string (std::string const & s) { return read_market_id_from_string (s, m_num); }

		static FOSMarketId	build_from_string (std::string const & v) { FOSMarketId market_id; market_id.read_from_string (v); return market_id; }

		// return the "human readable" description for this market
		std::string get_description() const { return market_id_internal2description (m_num); }

	private:
		FOSLowLevelMarketId	m_num;
	};

}

#endif
