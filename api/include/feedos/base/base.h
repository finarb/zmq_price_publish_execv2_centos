
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_BASE_H
#define FEEDOS_BASE_BASE_H

#define FEEDOS_ENABLE_PARANOID_CHECKS_DEFAULT_VALUE		0

#ifndef		FEEDOS_INLINE
#	define	FEEDOS_INLINE
#endif

#ifndef FEEDOS_ENABLE_PARANOID_CHECKS
#  define FEEDOS_ENABLE_PARANOID_CHECKS		FEEDOS_ENABLE_PARANOID_CHECKS_DEFAULT_VALUE
#endif

namespace FeedOS {
	namespace Base {

		void init ();
		void shutdown ();
		void check_init_done ();

		char const * platform_name ();

	}
}

////////////////////////////////////
//
//
//   CHECKING/COMPUTING OF PLATFORM DEFINES
//
//
////////////////////////////////////

#if defined TARGET_PLATFORM_DARWIN
#	define TARGET_PLATFORM_MACOSX	TARGET_PLATFORM_DARWIN
#endif

#if defined TARGET_PLATFORM_SUNOS
#	define 	TARGET_PLATFORM_SOLARIS	TARGET_PLATFORM_SUNOS
#endif

#if ! defined TARGET_PLATFORM_WIN32 && ! defined TARGET_PLATFORM_LINUX && ! defined TARGET_PLATFORM_SOLARIS && ! defined TARGET_PLATFORM_CYGWIN && ! defined TARGET_PLATFORM_FREEBSD && ! defined TARGET_PLATFORM_MACOSX
#  ifdef _MSC_VER
#    define TARGET_PLATFORM_WIN32  1
#  else
#    error (base.h) unsupported operating system
#  endif
#endif




////////////////////////////////////
//
//
//   PER-PLATFORM SETTINGS
//
//
////////////////////////////////////

#if defined (TARGET_PLATFORM_WIN32) || defined (TARGET_PLATFORM_CYGWIN)
//
//   WINDOWS
//
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#	define NOMINMAX
#endif

#ifdef max
#	error WIN32: should define NOMINMAX or include <feedos/api/api.h> first
#endif

#else
//
//   UNIX
//
#if defined (TARGET_PLATFORM_SOLARIS)
#	include <strings.h>
#endif

#include <time.h>

namespace FeedOS {
	int unix_clock_gettime(timespec & ts);
}


#endif




////////////////////////////////////
//
//
//   STLPORT
//
//
////////////////////////////////////

//  <hash_map> depends on definition of STLPORT and WINDOWS/LINUX Platform 
#include "base_hash.hpp"



////////////////////////////////////
//
//
//   ENDIANISM
//
//
////////////////////////////////////

#if defined (TARGET_PLATFORM_WIN32) || defined (TARGET_PLATFORM_CYGWIN)
	// WIN32 or CYGWIN
#   define FEEDOS_BIG_ENDIAN		0
#   define FEEDOS_LITTLE_ENDIAN		1

#elif defined TARGET_PLATFORM_SOLARIS
	// SOLARIS
#  ifndef _SYS_ISA_DEFS_H
#  include <sys/isa_defs.h>
#  endif
#  if defined (_LITTLE_ENDIAN)
#    define FEEDOS_BIG_ENDIAN		0
#    define FEEDOS_LITTLE_ENDIAN	1
#  elif defined (_BIG_ENDIAN)
#    define FEEDOS_BIG_ENDIAN		1
#    define FEEDOS_LITTLE_ENDIAN	0
#  else
#    error CANNOT ASSERT ENDIANISM for this Operating System
#  endif

#elif defined (TARGET_PLATFORM_LINUX)
	// LINUX
#  if defined (__LITTLE_ENDIAN)
#    define FEEDOS_BIG_ENDIAN		0
#    define FEEDOS_LITTLE_ENDIAN	1
#  elif defined (__BIG_ENDIAN)
#    define FEEDOS_BIG_ENDIAN		1
#    define FEEDOS_LITTLE_ENDIAN	0
#  else
#    error CANNOT ASSERT ENDIANISM for this Operating System
#  endif

#elif defined (TARGET_PLATFORM_FREEBSD) || defined (TARGET_PLATFORM_MACOSX)
	// FREEBSD
#  if BYTE_ORDER == LITTLE_ENDIAN
#    define FEEDOS_BIG_ENDIAN		0
#    define FEEDOS_LITTLE_ENDIAN	1
#  elif BYTE_ORDER == BIG_ENDIAN
#    define FEEDOS_BIG_ENDIAN		1
#    define FEEDOS_LITTLE_ENDIAN	0
#  else
#    error CANNOT ASSERT ENDIANISM for this Operating System
#  endif


#else

#    error SHOULD ASSERT ENDIANISM for this Operating System

#endif



////////////////////////////////////
//
//
//   PER-COMPILER SETTINGS
//
//
////////////////////////////////////
namespace FeedOS {

#ifdef _MSC_VER
//
//
//   MS VISUAL
//
//
#	pragma warning (disable:4100)	// unreferenced formal parameter
#	pragma warning (disable:4250)	// X : inherits Y::foo via dominance
#	pragma warning (disable:4355)	// 'this' : used in base member initializer list
#	pragma warning (disable:4996)	// 'BLAH' was declared deprecated
/*
#	pragma warning (disable:4786)	// long template-generated symbols truncated
#	pragma warning (disable:4250)	// inherits method via dominance
#	pragma warning (disable:4503)	// decorated name length exceeded, name was truncated
#	pragma warning (disable:4073)	// initializers put in library initialization area
*/

	typedef unsigned __int64	uint64;
	typedef __int64				int64;

#	define FEEDOS_MAKE_INT64(X)  (X##i64)
#	define FEEDOS_MAKE_UINT64(X) (X##ui64)


#elif defined __GNUC__
//
//
//   GCC
//
//
#	define FEEDOS_MAKE_INT64(X)  (X##LL)
#	define FEEDOS_MAKE_UINT64(X) (X##ULL)

	typedef unsigned long long	uint64;
	typedef long long			int64;


#elif defined __SUNPRO_CC
//
//
//   SUN FORTE
//
//
#	define FEEDOS_MAKE_INT64(X)  (X##LL)
#	define FEEDOS_MAKE_UINT64(X) (X##ULL)

	typedef unsigned long long	uint64;
	typedef long long			int64;


#else

#	error (FeedOS_types.h) Unknown compiler

#endif







///////////////////////////// 




#ifndef _REENTRANT
#  define _REENTRANT
//#	error macro _REENTRANT must be defined globally
#endif


typedef unsigned int		uint32;
typedef unsigned short int	uint16;
typedef unsigned char		uint8;
typedef signed int			int32;
typedef signed short int	int16;
typedef signed char			int8;

typedef float				float32;
typedef double				float64;


/*

// a "enum" type that allows only assignment/comparison/conversion
class Enum
{
public:
	inline Enum ()			: m_value(0) {}
	inline explicit Enum (uint32 v) : m_value(v) {}
	inline Enum (Enum const & v) : m_value(v.m_value) {}
	inline Enum const& operator= (uint32 v) { m_value=v; return *this; }
	inline operator uint32 () const { return m_value; }
	inline bool operator== (Enum const & v) const { return m_value==v.m_value; }
	inline bool operator!= (Enum const & v) const { return m_value!=v.m_value; }
	bool operator< (Enum const & v) const { return m_value<v.m_value; }
private:
	uint32 m_value;
};
*/




}

#include <stdlib.h>
#include <stdexcept>

#endif
