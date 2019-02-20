/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/** Author: Olivier Grant          **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_TR1_HPP
#define FEEDOS_BASE_BASE_HASH_TR1_HPP

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

#include <tr1/unordered_set>
#include <tr1/unordered_map>
#include <functional>

namespace FEEDOS_STLEXT_NAMESPACE
{	

/**
 * Hash structure to allow specialization.
 */
template< typename Tp >
    struct hash
    {
        std::size_t operator()( Tp const &x ) const
        { return std::tr1::hash<Tp>()(x); }
    };

// Provide a definition for hash<std::string> as it is not standard.
template< >
	struct hash<std::string>
	{
		std::size_t operator()( std::string const &x ) const
		{ return std::tr1::hash<char const *>()(x.c_str()); }
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
		: public std::tr1::unordered_map<K,V,H,E,A>
	{
	public:
		hash_map( )
		    : std::tr1::unordered_map<K,V,H,E,A>()
		{ }

		hash_map( typename std::tr1::unordered_map<K,V,H,E,A>::size_type bucket_count_ )
			: std::tr1::unordered_map<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::tr1::unordered_map<K,V,H,E,A>::size_type bucket_count_)
		{
			std::tr1::unordered_map<K,V,H,E,A>::rehash(bucket_count_);
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
		: public std::tr1::unordered_multimap<K,V,H,E,A>
	{
	public:
		hash_multimap( )
		    : std::tr1::unordered_multimap<K,V,H,E,A>()
		{ }

		hash_multimap( typename std::tr1::unordered_multimap<K,V,H,E,A>::size_type bucket_count_ )
			: std::tr1::unordered_multimap<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::tr1::unordered_multimap<K,V,H,E,A>::size_type bucket_count_)
		{
			std::tr1::unordered_multimap<K,V,H,E,A>::rehash(bucket_count_);
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
		: public std::tr1::unordered_set<V,H,E,A>
	{
	public:
		hash_set( )
		    : std::tr1::unordered_set<V,H,E,A>()
		{ }

		hash_set( typename std::tr1::unordered_set<V,H,E,A>::size_type bucket_count_ )
			: std::tr1::unordered_set<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::tr1::unordered_set<V,H,E,A>::size_type bucket_count_)
		{
			std::tr1::unordered_set<V,H,E,A>::rehash(bucket_count_);
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
		: public std::tr1::unordered_multiset<V,H,E,A>
	{
	public:
		hash_multiset( )
		    : std::tr1::unordered_multiset<V,H,E,A>()
		{ }

		hash_multiset(typename std::tr1::unordered_multiset<V,H,E,A>::size_type bucket_count_ )
			: std::tr1::unordered_multiset<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::tr1::unordered_multiset<V,H,E,A>::size_type bucket_count_)
		{
			std::tr1::unordered_multiset<V,H,E,A>::rehash(bucket_count_);
		}
	};

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // !FEEDOS_BASE_BASE_HASH_TR1_HPP
