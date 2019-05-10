#pragma once
#include "hashtable.h"
template<class K, class V>
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
	typedef HashTableIterator<std::pair<K, V>, MapKeyOfValue> iterator;
	std::pair<Node*, bool> Insert(const std::pair<K, V>& kv)
	{
		return _ht.Insert(kv);
	}

	iterator& begin()
	{
		return _ht.begin();
	}

	iterator& end()
	{
		return _ht.end();
	}
private:
	HashTable<int, std::pair<int, int>, MapKeyOfValue> _ht;
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

	for (auto it : map)
	{
		cout << it.first << ":"<< it.second << endl;
	}
	cout << endl;
}