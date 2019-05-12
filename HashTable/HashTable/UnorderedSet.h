#pragma once

template<class K, class HashFunc = HashFunc<int>>
class UnorderedSet
{
	class SetKeyOfValue
	{
	public:
		K operator()(const K& key)
		{
			return key;
		}
	};

public:
	typedef HashTableIterator<K, K, SetKeyOfValue, HashFunc> Iterator;
	pair<Iterator, bool> Insert(const K& key)
	{
		return _ht.Insert(key);
	}

	bool Erase(const K& key)
	{
		return _ht.Erase(key);
	}

	Iterator Find(const K& key)
	{
		return _ht.Find(key);
	}

	Iterator begin()
	{
		return _ht.begin();
	}

	Iterator end()
	{
		return _ht.end();
	}

private:
	HashTable<K, K, SetKeyOfValue, HashFunc> _ht;
};

void Test()
{
	UnorderedSet<int> myset;
	myset.Insert(1);
	myset.Insert(2);
	myset.Insert(3);
	myset.Insert(4);
	myset.Insert(5);
	myset.Erase(3);
	cout << *(myset.Find(2)) << endl;

	for (const auto& it : myset)
	{
		cout << it << endl;
	}

	UnorderedSet<string, HashFunc<string>> myset_s;
	myset_s.Insert("qiyu");
	cout << (*(myset_s.Find("qiyu"))).c_str() << endl;
}