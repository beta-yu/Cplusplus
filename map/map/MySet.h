#pragma once

#include "RBTree.h"

template<class K>
struct SetKeyOfValue
{
	const K operator()(const K& k)
	{
		return k;
	}
};

template<class K>
class MySet
{
public:
	typedef RBTreeIterator<K> Iterator;

	pair<Iterator, bool> Insert(const K& key)
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
	RBTree</*K, */K, SetKeyOfValue<K>> _t;
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

	MySet<int>::Iterator cur = myset.begin();
	while (true)
	{
		MySet<int>::Iterator temp = cur;
		if (++temp == myset.end())
			break;
		++cur;
	}
	//我的end()不支持--
	MySet<int>::Iterator end = cur;
	while (end != nullptr)
	{
		cout << *end << endl;
		--end;
	}
}