#pragma once

#include "RBTree.h"

template<class K>
struct KeyOfValue
{
	const K operator()(const K& k)
	{
		return k;
	}
};

template<class K>
class MySet
{
	typedef RBTreeIterator<K> Iterator;
public:
	pair<Iterator, bool> Insert(K key)
	{
		return _t.Insert(key);
	}

	Iterator begin()
	{
		return _t.begin();
	}

	Iterator end()
	{
		return _t.end();
	}
private:
	RBTree<K, K, KeyOfValue<K>> _t;
};

void MySetTest()
{
	MySet<int> myset;
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto it : arr)
	{
		myset.Insert(it);
	}
	for (auto it : myset)
	{
		cout << it << " ";
	}
	cout << endl;
}