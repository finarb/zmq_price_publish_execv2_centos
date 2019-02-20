
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2013      **/
/** Author: Sebastien Rannou       **/
/************************************/

#ifndef FEEDOS_BASE_HASH_CXX11_HPP
#define FEEDOS_BASE_HASH_CXX11_HPP

#include <unordered_set>
#include <unordered_map>
#include <functional>

#define FEEDOS_STLEXT_NAMESPACE FeedOS_fake_stdext

namespace FEEDOS_STLEXT_NAMESPACE
{	
	template <typename T> using hash = std::hash<T>;

	template <
		typename K,
		typename V,
		typename H = std::hash<K>,
		typename E = std::equal_to<K>,
		typename A = std::allocator<std::pair<K const,V>>> using hash_map = std::unordered_map<K, V, H, E, A>;

	template <
		typename K,
		typename V,
		typename H = hash<K>,
		typename E = std::equal_to<K>,
		typename A = std::allocator<std::pair<K const,V> >
		> using hash_multimap = std::unordered_multimap<K, V, H, E, A>;

	template <
		typename V,
		typename H = std::hash<V>,
		typename E = std::equal_to<V>,
		typename A = std::allocator<V>
		> using hash_set = std::unordered_set<V, H, E, A>;

	template <
		typename V,
		typename H = std::hash<V>,
		typename E = std::equal_to<V>,
		typename A = std::allocator<V>
		> using hash_multiset = std::unordered_multiset<V, H, E, A>;

} // namespace FEEDOS_STLEXT_NAMESPACE

#endif // FEEDOS_BASE_HASH_CXX11_HPP
