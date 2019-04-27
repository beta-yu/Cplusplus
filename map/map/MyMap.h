#pragma once

#include "RBTree.h"

template<class K, class V>
struct MapKeyOfValue
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

	V& operator[](const K& key) //reference，可能会修改
	{
		auto ret = _t.Insert(make_pair(key, V()));
		return (*(ret.first)).second;
	}
private:
	RBTree</*K, */pair<K, V>, MapKeyOfValue<K, V>> _t; 
	//Map中RBTreeNode.val为pair<K, V>，利用MapKeyOfValue取得key
	//Set中RBTreeNode.val为Key, 利用SetKeyOfValue取得Key，可达到，一个RBTree的实现可供set和map使用。
};


void MyMapTest()
{
	MyMap<int, int> mymap;
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int arr[] = { 1, 2, 1, 2, 3, 4, 3, 4, 5, 6, 5, 6, 7 };
	for (auto it : arr)
	{
		mymap[it]++;
	}

	//mymap[string("sort")] = string("排序");
	//mymap[string("left")];
	//mymap[string("left")] = string("左");


	for (auto it : mymap)
	{
		cout << it.first << ":" << it.second << endl;
	}
}


//Iterator   operator--()
//那些地方需要const，那些地方不能加
//那些地方需要引用