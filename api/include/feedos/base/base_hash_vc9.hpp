/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/** Author: Olivier Grant          **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_VC9_HPP
#define FEEDOS_BASE_BASE_HASH_VC9_HPP

#include <unordered_map>
#include <unordered_set>
#include <functional> // for hash

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

namespace FEEDOS_STLEXT_NAMESPACE {

/**
 * Hash structure to allow specialization.
 */
template< typename Tp >
    struct hash
    {
        std::size_t operator()( Tp const &x ) const
        { return std::tr1::hash<Tp>()(x); }
    };

/**
 * Unordered map wrapper.
 */
template<
	typename K,
	typename V,
	typename H = hash<K>,
	typename E = std::equal_to<K>,
	typename A = std::allocator<std::pair<K const,V> >
>
	class hash_map
		: public std::tr1::unordered_map<K,V,H,E,A>
	{
	public:
		hash_map( )
		{ }

		hash_map( typename std::tr1::unordered_map<K,V,H,E,A>::size_type bucket_count )
			: std::tr1::unordered_map<K,V,H,E,A>(bucket_count)
		{ }

		void reserve( typename std::tr1::unordered_map<K,V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }

		void resize( typename std::tr1::unordered_map<K,V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }
	};

/**
 * Unordered multimap wrapper.
 */
template<
	typename K,
	typename V,
	typename H = hash<K>,
	typename E = std::equal_to<K>,
	typename A = std::allocator<std::pair<K const,V> >
>
	class hash_multimap
		: public std::tr1::unordered_multimap<K,V,H,E,A>
	{
	public:
		hash_multimap( )
		{ }

		hash_multimap( typename std::tr1::unordered_multimap<K,V,H,E,A>::size_type bucket_count )
			: std::tr1::unordered_multimap<K,V,H,E,A>(bucket_count)
		{ }

		void reserve( typename std::tr1::unordered_multimap<K,V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }

		void resize( typename std::tr1::unordered_multimap<K,V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }
	};

/**
 * Unordered set wrapper.
 */
template<
	typename V,
	typename H = hash<V>,
	typename E = std::equal_to<V>,
	typename A = std::allocator<V>
>
	class hash_set
		: public std::tr1::unordered_set<V,H,E,A>
	{
	public:
		hash_set( )
		{ }

		hash_set( typename std::tr1::unordered_set<V,H,E,A>::size_type bucket_count )
			: std::tr1::unordered_set<V,H,E,A>(bucket_count)
		{ }

		void reserve( typename std::tr1::unordered_set<V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }

		void resize( typename std::tr1::unordered_set<V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }
	};

/**
 * Unordered multiset wrapper.
 */
template<
	typename V,
	typename H = hash<V>,
	typename E = std::equal_to<V>,
	typename A = std::allocator<V>
>
	class hash_multiset
		: public std::tr1::unordered_multiset<V,H,E,A>
	{
	public:
		hash_multiset( )
		{ }

		hash_multiset( typename std::tr1::unordered_multiset<V,H,E,A>::size_type bucket_count )
			: std::tr1::unordered_multiset<V,H,E,A>(bucket_count)
		{ }

		void reserve( typename std::tr1::unordered_multiset<V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }

		void resize( typename std::tr1::unordered_multiset<V,H,E,A>::size_type bucket_count )
		{ rehash(bucket_count); }
	};

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // !FEEDOS_BASE_BASE_HASH_VC9_HPP
