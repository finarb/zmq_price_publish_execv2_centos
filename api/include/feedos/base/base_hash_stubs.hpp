/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2009      **/
/** Author: Olivier Grant          **/
/************************************/

#ifndef FEEDOS_BASE_BASE_HASH_STUBS_HPP
#define FEEDOS_BASE_BASE_HASH_STUBS_HPP

#include <map>
#include <set>

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

namespace FEEDOS_STLEXT_NAMESPACE {

/**
 * Undefined to create linkage error.
 */
void invalid_use_of_fake_hash_structure( );

/**
 * Fake hash.
 */
template< typename Tp >
    struct hash
    {
        std::size_t operator()( Tp const & ) const
        {
            invalid_use_of_fake_hash_structure();
            return std::size_t();
        }
    };

/**
 * Fake hash map.
 */
template<
    typename K,
    typename V,
    typename H = hash<K>,
    typename E = std::equal_to<K>,
    typename A = typename std::map<K,V>::allocator_type
>
    class hash_map
        : public std::map<
              K,
              V,
              typename std::map<K,V>::key_compare,
              A
          >
    {
    public:
        hash_map( ) { }
        explicit hash_map( std::size_t /*bucket_count*/ ) { }

		void reserve( std::size_t ) { }
		void resize( std::size_t ) { }
    };

/**
 * Fake hash multimap
 */
template<
    typename K,
    typename V,
    typename H = hash<K>,
    typename E = std::equal_to<K>,
    typename A = typename std::multimap<K,V>::allocator_type
>
    class hash_multimap
        : public std::multimap<
              K,
              V,
              typename std::multimap<K,V>::key_compare,
              A
          >
    {
    public:
        hash_multimap( ) { }
        explicit hash_multimap( std::size_t /*bucket_count*/ ) { }

		void reserve( std::size_t ) { }
		void resize( std::size_t ) { }
    };

/**
 * Fake hash set.
 */
template<
    typename K,
    typename H = hash<K>,
    typename E = std::equal_to<K>,
    typename A = typename std::set<K>::allocator_type
>
    class hash_set
        : public std::set<
              K,
              typename std::set<K>::key_compare,
              A
          >
    {
    public:
        hash_set( ) { }
        explicit hash_set( std::size_t /*bucket_count*/ ) { }

		void reserve( std::size_t ) { }
		void resize( std::size_t ) { }
    };

/**
 * Fake hash multiset.
 */
template<
    typename K,
    typename H = hash<K>,
    typename E = std::equal_to<K>,
    typename A = typename std::multiset<K>::allocator_type
>
    class hash_multiset
        : public std::multiset<
              K,
              typename std::multiset<K>::key_compare,
              A
          >
    {
    public:
        hash_multiset( ) { }
        explicit hash_multiset( std::size_t /*bucket_count*/ ) { }

		void reserve( std::size_t ) { }
		void resize( std::size_t ) { }
    };

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // !FEEDOS_BASE_BASE_HASH_STUBS_HPP
