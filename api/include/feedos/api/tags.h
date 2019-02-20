
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2016      **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_TAGS_H
#define FEEDOS_API_TAGS_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "generated_types.h"
#endif

#include <stdio.h>

namespace FeedOS {

#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_ALIAS
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			static Types::TagNumber const	TAG_##ATT		=	NUM;
#define FEEDOS_DEF_TAG_ALIAS(NUM,ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	static Types::TagNumber const	TAG_##ATT##_0	=	NUM;		\
												static Types::TagNumber const	TAG_##ATT##_LAST=	NUM+NB-1;	\
												static unsigned int const		NB_TAG_##ATT	=	NB;
#include <feedos_metadata/tags_referential.hpp>
#include <feedos_metadata/tags_quotation.hpp>
#include <feedos_metadata/tags_quotation_context.hpp>
#include <feedos_metadata/tags_news_item.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_ALIAS
#undef  FEEDOS_DEF_TAG_LIST

	static unsigned int const FEEDOS_MAX_TAG_NUM = 0x10000;

	static Types::TagNumber const TAG_INVALID = 0;

	// base class for REFERENTIAL tag/value class
	class ReferentialAttribute_typed: public Types::TagNumAndValue
	{
	public:
		ReferentialAttribute_typed (Types::TagNumber num, Any const & value)
			:Types::TagNumAndValue (num, value)
		{}
	};

	// base class for QUOTATION tag/value class
	class QuotationVariable_typed: public Types::TagNumAndValue
	{
	public:
		QuotationVariable_typed (Types::TagNumber num, Any const & value)
			:Types::TagNumAndValue (num, value)
		{}
	};

	// base class for CONTEXT tag/value class
	class QuotationContextFlag_typed: public Types::TagNumAndValue
	{
	public:
		QuotationContextFlag_typed (Types::TagNumber num, Any const & value)
			:Types::TagNumAndValue (num, value)
		{}
	};

	// base class for News field tag/value class
	class NewsItem_typed: public Types::TagNumAndValue
	{
	public:
		NewsItem_typed (Types::TagNumber num, Any const & value)
			:Types::TagNumAndValue (num, value)
		{}
	};

#define FEEDOS_DEF_TAG_CLASS(PREFIX,ATT,RT,S)	\
	class PREFIX##_##ATT: public PREFIX##_typed	\
	{	\
	public:	\
		PREFIX##_##ATT(RT const & v) : PREFIX##_typed (TAG_##ATT, Any((S)v)) {}	\
		RT		get_value() const { return (RT) getValue().get_##S(); }	\
		void	set_value(RT const & v) { getValue().set_##S((S)v); }	\
	};

#define FEEDOS_DEF_TAG_LIST_CLASS(PREFIX,ATT,RT,S,NB)	\
	class PREFIX##_##ATT: public PREFIX##_typed	\
	{	\
	public:	\
		PREFIX##_##ATT(unsigned int n, RT const & v) : PREFIX##_typed (static_cast<Types::TagNumber>(TAG_##ATT##_0+n), Any((S)v)) {} \
		RT		get_value() const { return (RT) getValue().get_##S(); }	\
		void	set_value(RT const & v) { getValue().set_##S((S)v); }	\
	};

#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_CLASS(ReferentialAttribute,ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_CLASS(ReferentialAttribute,ATT,RT,S,NB)
#include <feedos_metadata/tags_referential.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_CLASS(QuotationVariable,ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_CLASS(QuotationVariable,ATT,RT,S,NB)
#include <feedos_metadata/tags_quotation.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_CLASS(QuotationContextFlag,ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_CLASS(QuotationContextFlag,ATT,RT,S,NB)
#include <feedos_metadata/tags_quotation_context.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_ALIAS
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			FEEDOS_DEF_TAG_CLASS(NewsItem,ATT,RT,S)
#define FEEDOS_DEF_TAG_ALIAS(NUM,ATT,RT,S)		FEEDOS_DEF_TAG_CLASS(NewsItem,ATT,RT,S)
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	FEEDOS_DEF_TAG_LIST_CLASS(NewsItem,ATT,RT,S,NB)
#include <feedos_metadata/tags_news_item.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_ALIAS
#undef  FEEDOS_DEF_TAG_LIST

#undef  FEEDOS_DEF_TAG_CLASS
#undef  FEEDOS_DEF_TAG_LIST_CLASS

	// return false in case of "unknown tag"
	bool					tag_num2str (Types::TagNumber v, std::ostream & os);
	bool					tag_num2str (Types::TagNumber v, std::string & tagname);
	bool					tag_str2num (std::string const & v, Types::TagNumber & tagnum);

	inline std::string		tag_num2str (Types::TagNumber v) { std::string tagname; tag_num2str (v,tagname); return tagname; }
	inline Types::TagNumber	tag_str2num (std::string const & v) { Types::TagNumber tagnum; tag_str2num (v,tagnum); return tagnum; }

	AnySyntax			tag_expected_syntax (Types::TagNumber v);

	void					tag_define (Types::TagNumber num, std::string const & name, AnySyntax expected_syntax, bool warn_if_duplicate = true);

	// tag_str2num() + accept numeric values
	bool	read_tagnum_from_string (std::string const & s, Types::TagNumber & tagnum);

	void	dump_supported_tags (std::ostream &os);

	void	register_tags (Types::ListOfTagDeclaration const & tags);

	void	register_MICs (Types::EnumTypeDeclaration  const & mic_values);

	// load metadata (tags, MIC, various enums) so numeric values can be translated to human-readable strings
	void register_metadata (Types::ListOfTagDeclaration const & tags, Types::ListOfEnumTypeDeclaration  const & enums);

	void clear_metadata();
	void clear_tags();

	inline void get_builtin_tags(Types::ListOfTagDeclaration & tags)
	{
#define FEEDOS_DECLARE_TAG(USAGE,NUM,ATT,S)				Types::TagDeclaration(USAGE,Enum(Syntax_##S),TAG_##ATT,		#ATT,"")
#define FEEDOS_DECLARE_TAG_LIST(USAGE,NUM,ATT,S)		Types::TagDeclaration(USAGE,Enum(Syntax_##S),TAG_##ATT##_0,	#ATT,"")

#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)					tags.push_back (FEEDOS_DECLARE_TAG("R",NUM,ATT,S));
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)			tags.push_back (FEEDOS_DECLARE_TAG_LIST("R",NUM,ATT,S));
#include <feedos_metadata/tags_referential.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)					tags.push_back (FEEDOS_DECLARE_TAG("Q",NUM,ATT,S));
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)			tags.push_back (FEEDOS_DECLARE_TAG_LIST("Q",NUM,ATT,S));
#include <feedos_metadata/tags_quotation.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)					tags.push_back (FEEDOS_DECLARE_TAG("C",NUM,ATT,S));
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)			tags.push_back (FEEDOS_DECLARE_TAG_LIST("C",NUM,ATT,S));
#include <feedos_metadata/tags_quotation_context.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
	// TODO: news?
	}

	inline void define_all_tags()
	{
#define FEEDOS_DEF_TAG(NUM,ATT,RT,S)			tag_define(NUM,#ATT,Syntax_##S);
#define FEEDOS_DEF_TAG_LIST(NUM,ATT,RT,S,NB)	for (unsigned int i=0;i<(NB);++i) { char buffer[256]; tag_define(static_cast<Types::TagNumber> (NUM+i),std::string(buffer,sprintf(buffer,#ATT"_%u",i)),Syntax_##S); }
#define FEEDOS_DEF_TAG_ALIAS(NUM,ATT,RT,S)
#include <feedos_metadata/tags_referential.hpp>
#include <feedos_metadata/tags_quotation.hpp>
#include <feedos_metadata/tags_quotation_context.hpp>
#include <feedos_metadata/tags_news_item.hpp>
#undef  FEEDOS_DEF_TAG
#undef  FEEDOS_DEF_TAG_LIST
#undef  FEEDOS_DEF_TAG_ALIAS
	}

	inline void get_builtin_MICs(Types::EnumTypeDeclaration & mic_values)
	{
		Types::ListOfTagNumber related_tags;
		related_tags.push_back(TAG_FOSMarketId);
		related_tags.push_back(TAG_ForeignFOSMarketId);
		related_tags.push_back(TAG_UnderlyingFOSMarketId);

		mic_values = Types::EnumTypeDeclaration(Types::s_METADATA_ENUM_TYPE_DECLARATION_MIC_NAME,
												"http://www.iso15022.org/MIC/homepageMIC.htm",
												related_tags,
												Types::ListOfEnumValueDeclaration());

#define FEEDOS_DEF_MARKET(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB)							mic_values.getEnumValues().push_back (Types::EnumValueDeclaration (Any((uint16)NUM),#MIC,"CC="#CC"/"#COUNTRY"/"#CITY",DESCR="#DESCRIPTION",WEB="#WEB));
#define FEEDOS_DEF_MARKET_RENAMED(NUM,COUNTRY,CC,MIC,DESCRIPTION,ACCR,CITY,WEB,OLD_MIC,SEQNUM)	mic_values.getEnumValues().push_back (Types::EnumValueDeclaration (Any((uint16)NUM),#MIC,"CC="#CC"/"#COUNTRY"/"#CITY",DESCR="#DESCRIPTION",WEB="#WEB",OLD="#OLD_MIC",SEQNUM="#SEQNUM));
#define FEEDOS_DEF_MARKET_ALIAS(OLD_MIC,NEW_MIC)
#include <feedos_metadata/ids_market.hpp>
#undef  FEEDOS_DEF_MARKET_RENAMED
#undef  FEEDOS_DEF_MARKET
#undef  FEEDOS_DEF_MARKET_ALIAS
	}
}

#endif
