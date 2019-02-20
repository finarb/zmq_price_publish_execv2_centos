/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_STLPORT_HPP
#define FEEDOS_BASE_BASE_HASH_STLPORT_HPP

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

# include <hash_map>
# include <hash_set>

namespace FEEDOS_STLEXT_NAMESPACE
{	

/**
 * Hash structure to allow specialization.
 */
template< typename Tp >
    struct hash
    {
        std::size_t operator()( Tp const &x ) const
        { return std::hash<Tp>()(x); }
    };

// Provide a definition for hash<std::string> as it is not standard.
template< >
	struct hash<std::string>
	{
		std::size_t operator()( std::string const &x ) const
		{ return std::hash<char const *>()(x.c_str()); }
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
		: public std::hash_map<K,V,H,E,A>
	{
	public:
		hash_map( )
		    : std::hash_map<K,V,H,E,A>()
		{ }

		hash_map( typename std::hash_map<K,V,H,E,A>::size_type bucket_count_ )
			: std::hash_map<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::hash_map<K,V,H,E,A>::size_type bucket_count_)
		{
			std::hash_map<K,V,H,E,A>::resize(bucket_count_);
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
		: public std::hash_multimap<K,V,H,E,A>
	{
	public:
		hash_multimap( )
		    : std::hash_multimap<K,V,H,E,A>()
		{ }

		hash_multimap( typename std::hash_multimap<K,V,H,E,A>::size_type bucket_count_ )
			: std::hash_multimap<K,V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::hash_multimap<K,V,H,E,A>::size_type bucket_count_)
		{
			std::hash_multimap<K,V,H,E,A>::resize(bucket_count_);
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
		: public std::hash_set<V,H,E,A>
	{
	public:
		hash_set( )
		    : std::hash_set<V,H,E,A>()
		{ }

		hash_set( typename std::hash_set<V,H,E,A>::size_type bucket_count_ )
			: std::hash_set<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::hash_set<V,H,E,A>::size_type bucket_count_)
		{
			std::hash_set<V,H,E,A>::resize(bucket_count_);
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
		: public std::hash_multiset<V,H,E,A>
	{
	public:
		hash_multiset( )
		    : std::hash_multiset<V,H,E,A>()
		{ }

		hash_multiset(typename std::hash_multiset<V,H,E,A>::size_type bucket_count_ )
			: std::hash_multiset<V,H,E,A>(bucket_count_)
		{ }

		void reserve(typename std::hash_multiset<V,H,E,A>::size_type bucket_count_)
		{
			std::hash_multiset<V,H,E,A>::resize(bucket_count_);
		}
	};

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // !FEEDOS_BASE_BASE_HASH_STLPORT_HPP
