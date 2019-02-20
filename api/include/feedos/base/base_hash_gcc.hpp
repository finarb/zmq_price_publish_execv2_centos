/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/** Author: Olivier Grant          **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_GCC_HPP
#define FEEDOS_BASE_BASE_HASH_GCC_HPP

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || (defined(__clang__) && !defined _LIBCPP_VERSION) // GCC >= 4.3.x

#  include <backward/hash_map>
#  include <backward/hash_set>
#  include <backward/hash_fun.h>

# elif (__GNUC__ == 3 && __GNUC_MINOR__ <= 3) // GCC <= 3.3.x

#  include <ext/hash_map>
#  include <ext/hash_set>
#  include <ext/stl_hash_fun.h>

# else // 3.3.x < GCC < 4.4.x

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-W#warnings"
#endif

#  include <ext/hash_map>
#  include <ext/hash_set>
#  ifndef _LIBCPP_VERSION // clang libc++
#    include <ext/hash_fun.h>
#  endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

# endif

namespace FEEDOS_STLEXT_NAMESPACE {

/**
 * Hash structure to allow specialization.
 */
template< typename Tp >
    struct hash
    {
        std::size_t operator()( Tp const &x ) const
        { return __gnu_cxx::hash<Tp>()(x); }
    };

// Provide a definition for hash<std::string> as it is not standard.
template< >
	struct hash<std::string>
	{
		std::size_t operator()( std::string const &x ) const
		{ return __gnu_cxx::hash<char const *>()(x.c_str()); }
	};

/**
 * Hash map wrapper.
 */
template<
	typename K,
	typename V,
	typename H = hash<K>,
	typename E = std::equal_to<K>,
	typename A = std::allocator<std::pair<K const,V> >
>
	class hash_map
		: public __gnu_cxx::hash_map<K,V,H,E,A>
	{
	public:
		hash_map( )
		    : __gnu_cxx::hash_map<K,V,H,E,A>()
		{ }

		hash_map( typename __gnu_cxx::hash_map<K,V,H,E,A>::size_type bucket_count_ )
			: __gnu_cxx::hash_map<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename __gnu_cxx::hash_map<K,V,H,E,A>::size_type bucket_count_)
		{
			__gnu_cxx::hash_map<K,V,H,E,A>::resize(bucket_count_);
		}
	};

/**
 * Hash multimap wrapper.
 */
template<
	typename K,
	typename V,
	typename H = hash<K>,
	typename E = std::equal_to<K>,
	typename A = std::allocator<std::pair<K const,V> >
>
	class hash_multimap
		: public __gnu_cxx::hash_multimap<K,V,H,E,A>
	{
	public:
		hash_multimap( )
		    : __gnu_cxx::hash_multimap<K,V,H,E,A>()
		{ }

		hash_multimap( typename __gnu_cxx::hash_multimap<K,V,H,E,A>::size_type bucket_count_ )
			: __gnu_cxx::hash_multimap<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename __gnu_cxx::hash_multimap<K,V,H,E,A>::size_type bucket_count_)
		{
			__gnu_cxx::hash_multimap<K,V,H,E,A>::resize(bucket_count_);
		}
	};

/**
 * Hash set wrapper.
 */
template<
	typename V,
	typename H = hash<V>,
	typename E = std::equal_to<V>,
	typename A = std::allocator<V>
>
	class hash_set
		: public __gnu_cxx::hash_set<V,H,E,A>
	{
	public:
		hash_set( )
		    : __gnu_cxx::hash_set<V,H,E,A>()
		{ }

		hash_set( typename __gnu_cxx::hash_set<V,H,E,A>::size_type bucket_count_ )
			: __gnu_cxx::hash_set<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename __gnu_cxx::hash_set<V,H,E,A>::size_type bucket_count_)
		{
			__gnu_cxx::hash_set<V,H,E,A>::resize(bucket_count_);
		}
	};

/**
 * Hash multiset wrapper.
 */
template<
	typename V,
	typename H = hash<V>,
	typename E = std::equal_to<V>,
	typename A = std::allocator<V>
>
	class hash_multiset
		: public __gnu_cxx::hash_multiset<V,H,E,A>
	{
	public:
		hash_multiset( )
		    : __gnu_cxx::hash_multiset<V,H,E,A>()
		{ }

		hash_multiset(typename __gnu_cxx::hash_multiset<V,H,E,A>::size_type bucket_count_ )
			: __gnu_cxx::hash_multiset<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename __gnu_cxx::hash_multiset<V,H,E,A>::size_type bucket_count_)
		{
			__gnu_cxx::hash_multiset<V,H,E,A>::resize(bucket_count_);
		}
	};

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // !FEEDOS_BASE_BASE_HASH_GCC_HPP
