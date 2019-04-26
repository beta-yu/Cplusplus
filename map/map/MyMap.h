#pragma once

#include "RBTree.h"

template<class K, class V>
struct KeyOfValue
{
	const K operator()(const pair<K, V>& kv)
	{
		return kv.first;
	}
};

template<class K, class V>
class MyMap
{
	typedef /*typename*/ RBTreeIterator<pair<K, V>> Iterator;
public:
	pair<Iterator, bool> Insert(const pair<K, V>& val)
	{
		return _t.Insert(val);
	}
	
	Iterator begin()
	{
		return _t.begin();
	}

	Iterator end()
	{
		return _t.end();
	}

	V& operator[](const K& key)
	{
		auto ret = _t.Insert(make_pair(key, V()));
		return (*(ret.first)).second;
	}
private:
	RBTree<K, pair<K, V>, KeyOfValue<K, V>> _t;
};


void MyMapTest()
{
	MyMap<string, string> mymap;
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//for (auto it : arr)
	//{
	//	mymap.Insert(make_pair(it, it));
	//}

	mymap[string("sort")] = string("排序");
	mymap[string("left")];
	mymap[string("left")] = string("左");


	for (auto it : mymap)
	{
		cout << it.first << ":" << it.second << endl;
	}
}


//Iterator   operator--()
//那些地方需要const，那些地方不能加
//那些地方需要引用