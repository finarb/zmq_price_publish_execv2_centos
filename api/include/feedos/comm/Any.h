
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_ANY_H
#define FEEDOS_COMM_ANY_H

#ifndef FEEDOS_COMM_TYPES_H
#	include "types.h"
#endif

#ifndef FEEDOS_COMM_INTEGER_H
#	include "FOSInteger.h"
#endif

#ifndef FEEDOS_BASE_REF_COUNT_STRING_H
#	include "../base/refcount_string.h"
#endif

#define	FEEDOS_ANY_USE_REFCOUNT_STRING		1

#ifndef FEEDOS_CTOR_EXPLICIT_ANY
#	define	FEEDOS_CTOR_EXPLICIT_ANY
#endif

#include <iostream>

namespace FeedOS {

	typedef enum AnySyntax {
		Syntax_UNKNOWN,
		Syntax_String,
		Syntax_uint8,
		Syntax_uint16,
		Syntax_uint32,
		Syntax_int8,
		Syntax_int16,
		Syntax_int32,
		Syntax_float64,
		Syntax_Timestamp,
		Syntax_Enum,
		Syntax_bool,
		Syntax_char,
		Syntax_int,			// this is a FOSLowLevelInteger (int64)
		Syntax_int64 = Syntax_int,
		Syntax_uint64,
		NumberOfSupportedSyntaxes
	} AnySyntax;


	char const * syntax2string(AnySyntax s);

	// return false in case of error
	bool parse_syntax_str (std::string const & syntax_str, AnySyntax & s);


	/** A union of several basic types
	*/

	/*class Any;
	ostream & operator<< (ostream & os, Any const & v);
	*/

	class Any
	{
	//	friend ostream & operator<< (ostream & os, Any const & v);
	public:
		void dump (std::ostream & os, bool show_syntax=true) const;

		std::string to_str(bool show_syntax=true) const;

		inline void set_invalid() { m_float64=0; m_syntax = Syntax_UNKNOWN; }

		/// return the syntax of this value
		/** based on this, use appropriate accessor */
		inline AnySyntax	get_syntax () const { return m_syntax; }

		/// default constructor
		inline /*FEEDOS_CTOR_EXPLICIT_ANY*/ Any () : m_float64 (0),m_syntax (Syntax_UNKNOWN) {}

		/// constructor: default value for the given syntax
		inline   FEEDOS_CTOR_EXPLICIT_ANY   Any (AnySyntax s) : m_float64 (0),m_syntax (s) {}

		/// copy constructor
		inline /*FEEDOS_CTOR_EXPLICIT_ANY*/ Any (Any const & v) { operator=(v); }

		/// assign operator
		FEEDOS_INLINE Any const & operator= (Any const & v);

		/// equality operator
		FEEDOS_INLINE bool operator== (Any const & v) const;

		inline bool operator!= (Any const & v) const { return !operator==(v); }

		/// comparison operator
		FEEDOS_INLINE bool operator< (Any const & v) const;

		/** a macro that defines for each available syntax : a constructor and get/set accessors
		*
		*  generated methods (for each Syntax_XXX):
		*
		* -   
		* -   XXX const & getXXX()             return the value.			Check that current syntax is XXX
		* -   void        setXXX(XXX const &)  set the value.				Set the current syntax to 'XXX'
		*
		*/
	#define ANY_SYNTAX2(SYNTAX2,SYNTAX,MEMBER,GETMODE)						\
		inline static Any make_##SYNTAX (SYNTAX2 const & value) { return Any (value); }	\
		inline SYNTAX2 GETMODE	get_##SYNTAX () const	{ check_syntax("get_"#SYNTAX,Syntax_##SYNTAX);return m_##MEMBER; } \
		inline SYNTAX2 &		_ref_##SYNTAX ()		{ set_syntax(Syntax_##SYNTAX); return m_##MEMBER; } \
		inline void set_##SYNTAX (SYNTAX2 const & value) { set_syntax  (Syntax_##SYNTAX);m_##MEMBER=value;  }

	#define ANY_SYNTAX(SYNTAX,GETMODE) ANY_SYNTAX2(SYNTAX,SYNTAX,SYNTAX,GETMODE) \
		inline FEEDOS_CTOR_EXPLICIT_ANY Any(SYNTAX const & value) : m_##SYNTAX(value), m_syntax(Syntax_##SYNTAX) {}
		

//		inline Any const & operator= (SYNTAX const & value) { set_##SYNTAX(value); return *this; }

		ANY_SYNTAX (uint8,	const &)
		ANY_SYNTAX (uint16,	const &)
		ANY_SYNTAX (uint32,	const &)
		ANY_SYNTAX (int8,	const &)
		ANY_SYNTAX (int16,	const &)
		ANY_SYNTAX (int32,	const &)
		ANY_SYNTAX (float64,const &)
		ANY_SYNTAX (bool,	const &)
		ANY_SYNTAX (char,	const &)
		ANY_SYNTAX (uint64,	const &)
		ANY_SYNTAX2 (FOSLowLevelInteger, int,	int, const &)
		ANY_SYNTAX2 (FOSLowLevelInteger, int64,	int, const &)
		inline FEEDOS_CTOR_EXPLICIT_ANY Any(FOSLowLevelInteger const & value) : m_int(value), m_syntax(Syntax_int) {}


		/** @name Enum accessors
		*/
		//@{
		inline static Any make_Enum (Enum const & value) { return Any (value); }
		inline FEEDOS_CTOR_EXPLICIT_ANY Any(Enum const & value)						{ set_Enum(value); }
		inline unsigned int get_Enum () const				{ check_syntax("get_Enum",Syntax_Enum); return m_Enum; }
		inline uint32 &		_ref_Enum ()					{ set_syntax(Syntax_Enum); return m_Enum; }
		inline void	set_Enum (Enum const & value)			{ set_syntax(Syntax_Enum); m_Enum=value; }
		inline Any const & operator= (Enum const & value)	{ set_Enum(value); return *this; }
		//@}

		/** @name Timestamp accessors
		*/
		//@{
		inline static Any make_Timestamp (Timestamp const & value) { return Any (value); }
		inline FEEDOS_CTOR_EXPLICIT_ANY Any (Timestamp const & value)			{ set_Timestamp(value); }
		inline Timestamp	get_Timestamp () const				{ check_syntax("get_Timestamp",Syntax_Timestamp);Timestamp t; t.set_timet(m_date.sec, m_date.milli, m_date.micro); return t;}
		inline void	set_Timestamp (Timestamp const & value)		{ set_syntax  (Syntax_Timestamp);value.get_Smu(m_date.sec,m_date.milli,m_date.micro); }
		inline Any const & operator= (Timestamp const & value)	{ set_Timestamp(value); return *this; }
		//@}

		/** @name string accessors
		*/
		//@{
		inline static Any make_String (std::string const & value) { return Any (value); }
		inline FEEDOS_CTOR_EXPLICIT_ANY Any (char const * value) :				m_string(value),m_syntax(Syntax_String) {}
		inline FEEDOS_CTOR_EXPLICIT_ANY Any (char * value) :					m_string(value),m_syntax(Syntax_String) {}
#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		inline FEEDOS_CTOR_EXPLICIT_ANY Any(refcount_string const & value) :				m_string(value),m_syntax(Syntax_String) {}
#endif
		inline FEEDOS_CTOR_EXPLICIT_ANY Any(std::string const & value) :					m_string(value),m_syntax(Syntax_String) {}
		inline Any const & operator= (char const * value)				{ set_syntax  (Syntax_String); m_string=value; return *this; }
#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		inline Any const & operator= (refcount_string const & value)	{ set_syntax  (Syntax_String); m_string=value; return *this; }
#endif
		inline Any const & operator= (std::string const & value)		{ set_syntax  (Syntax_String); m_string=value; return *this; }

#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		inline refcount_string const & get_String () const		{ check_syntax("get_string",Syntax_String);return m_string; }
#else
		inline std::string const & get_String () const			{ check_syntax("get_string",Syntax_String);return m_string; }
#endif
		inline void set_String (char const * value)				{ set_syntax (Syntax_String); m_string=value; }
#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		inline void set_String (refcount_string const & value)	{ set_syntax (Syntax_String); m_string=value; }
#endif
		inline void set_String (std::string const & value)		{ set_syntax (Syntax_String); m_string=value; }
#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		inline refcount_string &	_ref_String ()				{ set_syntax (Syntax_String); return m_string; }
#else
		inline std::string &		_ref_String ()				{ set_syntax (Syntax_String); return m_string; }
#endif
		//@}

		inline void set_syntax (AnySyntax s) { m_syntax=s; }
	private:

#if	FEEDOS_ANY_USE_REFCOUNT_STRING
		refcount_string	m_string;
#else
		std::string		m_string;
#endif

		struct Any_date {
			uint32	sec;
			uint16	milli;
			uint16	micro;
		};

		union {
			bool		m_bool;
			char		m_char;
			uint8		m_uint8;
			uint16		m_uint16;
			uint32		m_uint32;
			int8		m_int8;
			int16		m_int16;
			int32		m_int32;
			float64		m_float64;
			Any_date	m_date;
			uint32 m_Enum;
			FOSLowLevelInteger	m_int;
			uint64		m_uint64;
		};

		AnySyntax m_syntax;
#if defined (FEEDOS_ENABLE_PARANOID_CHECKS) || defined (FEEDOS_COMPAT_INCLUDE)
		inline void check_syntax (char const * where, AnySyntax s) const { if (s!=m_syntax) log_syntax_mismatch (where, s, m_syntax); }
#else
		inline void check_syntax (char const * /*where*/, AnySyntax /*s*/) const {}
#endif

	public:
		static void log_syntax_mismatch (char const * where, AnySyntax expected, AnySyntax current);
	};


#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/Any.inl"
#endif

}


inline std::ostream & operator<< (std::ostream & os, FeedOS::Any const & v)
{
	v.dump (os);
	return os;
}


#endif
