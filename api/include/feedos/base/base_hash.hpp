/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/** Author: Olivier Grant          **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_HPP
#define FEEDOS_BASE_BASE_HASH_HPP

// Include protection
#if !defined(TOPFEED_FTTOOLS_H) && !defined(FEEDOS_BASE_BASE_H)
# error This header file should not be included directly, but instead please include either FTTools.h or base.h
#endif

// Make sure STLPort has been detected.
#ifndef HAVE_STLPORT
# include <string>
# ifdef STLPORT
#  define HAVE_STLPORT 1
# else
#  define HAVE_STLPORT 0
# endif
#endif

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#if (__cplusplus < 201103L) && (GCC_VERSION >= 40704)
# define HAVE_TR1
#endif
#if ((__cplusplus >= 201103L) && ((GCC_VERSION >= 40704) || __clang__))
// Use STL objects if C++11 is used. But only if gcc version is greater or equal to 4.7.4
// because there was a performance regression with gcc 4.7 in unordered_map::reserve()
# define HAVE_CPP11
#endif

#undef GCC_VERSION

// Adjust necessary includes to have unified hash maps and sets.
#if HAVE_STLPORT
# include "base_hash_stlport.hpp"
#elif defined(HAVE_TR1)
# include "base_hash_tr1.hpp"
#elif defined(HAVE_CPP11)
# include "base_hash_cxx11.hpp"
#else

# if defined(TARGET_PLATFORM_WIN32)
#  if (_MSC_VER >= 1800)
	// Visual 2013 and above
#   define HAVE_CPP11
#   include "base_hash_cxx11.hpp"
#  elif ((_MSC_VER == 1600) || (_MSC_VER == 1500))
	// Visual 2008 / 2010
#   ifdef _DEBUG
//hash_map is broken on Visual 2008 when iterator_debugging is activated. Futhermore, two libs that have been built with and without iterator_debugging can not cohabit
#    ifdef FEEDOS_COMPAT_INCLUDE //Compile checks are done in the framework -- Fixed by forcing iterator_debugging to be 0 and defined before any STL header is included, generates an #error otherwise
#     include "base_hash_vc9.hpp"
#    else //Customer's App -- unexpected behavior with iterator_debugging -- Lower perf in DEBUG, use std::map but otherwise, all dependencies (external libs) of customer's app would need to be recompiled with iterator_debugging disabled
#     include "base_hash_stubs.hpp"
#    endif
#   else
#    include "base_hash_vc9.hpp"
#   endif

#  else
	// older versions
#   include "base_hash_stubs.hpp"
#  endif

# elif defined(TARGET_PLATFORM_LINUX) || defined(TARGET_PLATFORM_SOLARIS) || defined(TARGET_PLATFORM_MACOSX) || defined(TARGET_PLATFORM_FREEBSD)

#  if defined(__GNUC__)
#   include "base_hash_gcc.hpp"
#  else
#   include "base_hash_stubs.hpp"
#  endif // __GNUC__

# endif // LINUX || SOLARIS || MACOSX || FREEBSD

#endif // !HAVE_STLPORT && !HAVE_CPP11

#endif // !FEEDOS_BASE_BASE_HASH_HPP
