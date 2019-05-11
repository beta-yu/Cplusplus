#pragma once
#include "hashtable.h"
template<class K, class V, class HashFunc = HashFunc<int>>
class UnorderedMap
{
	class MapKeyOfValue
	{
	public:
		const K& operator()(const std::pair<K, V>& kv)
		{
			return kv.first;
		}
	};
public:
	typedef HashNode<std::pair<K, V>> Node;
	typedef HashTableIterator<K, std::pair<K, V>, MapKeyOfValue, HashFunc> Iterator;
	std::pair<Iterator, bool> Insert(const std::pair<K, V>& kv)
	{
		return _ht.Insert(kv);
	}

	bool Erase(const K& key)
	{
		return _ht.Erase(key);
	}

	Iterator Find(const K& key)
	{
		return _ht.Find(key);
	}

	V& operator[](const K& key)
	{
		auto ret = Insert(std::make_pair(key, V()));
		return (*(ret.first)).second;
	}

	Iterator& begin()
	{
		return _ht.begin();
	}

	Iterator& end()
	{
		return _ht.end();
	}
private:
	HashTable<K, std::pair<K, V>, MapKeyOfValue, HashFunc> _ht;
};

void Test()
{
	UnorderedMap<int, int> map;
	map.Insert(std::make_pair(11, 1));
	map.Insert(std::make_pair(21, 1));
	map.Insert(std::make_pair(12, 2));
	map.Insert(std::make_pair(13, 3));
	map.Insert(std::make_pair(15, 15));
	map.Insert(std::make_pair(17, 17));
	map.Insert(std::make_pair(2, 2));
	map.Insert(std::make_pair(1, 1));
	map.Insert(std::make_pair(3, 3));
	map.Insert(std::make_pair(22, 2));
	map.Insert(std::make_pair(10, 0));
	map[0] = 1;
	for (auto it : map)
	{
		cout << it.first << ":"<< it.second << endl;
	}

	UnorderedMap<std::string, std::string, HashFunc<std::string>> map_s;
	map_s["sort"] = "排序";
	for (auto it : map_s)
	{
		cout << it.first.c_str() << ":" << it.second.c_str() << endl;
	}
}