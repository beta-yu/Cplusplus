#pragma once

//位图的映射方法是直接定制法，0映射第1位，n映射n+1位，因此不存在哈希冲突，
//但是位图只能解决整数在不在的问题(直接定制)
class BitMap  
{
public:
	BitMap(const size_t range)
		:_v((range >> 5) + 1)
		,_range(range)
	{}

	//置1
	void Set(size_t val)
	{
		size_t index = val >> 5;
		size_t bitindex = val % 32;

		_v[index] |= (1 << bitindex);
		//如果val == 5, index = 0, bitindex = 5,
		//32位中，第1位为0表示0不存在，为1表示0存在，第2位用来表示1是否存在；
		//则第6位用来表示5是否存在
		//需要表示5存在, 则1 << 5，得到第6位为1，其他全0，再
		//00000000 00000000 00000000 00100000 | _v[index]，使得_v[index]第6位为1
	}

	//置0
	void Reset(size_t val)
	{
		size_t index = val >> 5;
		size_t bitindex = val % 32;

		_v[index] &= (~(1 << bitindex));
		//val == 5时, (~(1 << bitindex))表示：
		//11111111 11111111 11111111 11011111
	}

	//在不在
	bool Test(size_t val)
	{
		size_t index = val >> 5;
		size_t bitindex = val % 32;

		if ((_v[index] & (1 << bitindex)) > 0)
			return true;
		else
			return false;
		//val = 5, (1 << bitindex):
		//00000000 00000000 00000000 00100000
	}

	size_t bitCount()
	{
		return _range;
	}


private:
	std::vector<size_t> _v;
	size_t _range;
};

void Test()
{
	BitMap bm(1000);
	bm.Set(1);
	bm.Set(5);
	bm.Reset(5);
	cout << bm.Test(5) << endl;
}

struct HashFunc1 
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto it : s)
		{
			hash = hash * 131 + it;
		}
		return hash;
	}
};

struct HashFunc2
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto it : s)
		{
			hash = hash * 65599 + it;
		}
		return hash;
	}
};

struct HashFunc3
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto it : s)
		{
			hash = hash * magic + it;
			magic *= 378551;
		}
		return hash;
	}
};

//布隆过滤器：将哈希与位图结合，利用多个哈希函数将一个数据映射到位图结构中，
//有几个哈希函数，一个数据就被映射到几个bit位, 哈希函数越多，误判率越低，
template<class K, class HashFunc1, class HashFunc2, class HashFunc3>
class BloomFilter
{
public:
	BloomFilter(size_t size)
		:_bm(size * 10) //位图空间为10倍（也可以是其他倍数）于数据个数个bit位，一个数据映射几个位
		, _size(0)
	{}

	void Set(const K& key)
	{
		size_t bitcount = _bm.bitCount();
		size_t index1 = HashFunc1()(key) % bitcount;
		size_t index2 = HashFunc2()(key) % bitcount;
		size_t index3 = HashFunc3()(key) % bitcount;

		_bm.Set(index1);
		_bm.Set(index2);
		_bm.Set(index3);
		++_size;
	}

	//void Reset(); BloomFilter不支持删除操作，因为可能会影响其他数据
	//一个bit位可能被不同数据同时映射到

	bool Test(const K& key)
	{
		size_t bitcount = _bm.bitCount();
		size_t index1 = HashFunc1()(key) % bitcount;
		if (_bm.Test(index1) == false)
			return false;
		size_t index2 = HashFunc2()(key) % bitcount;
		if (_bm.Test(index2) == false)
			return false;
		size_t index3 = HashFunc3()(key) % bitcount;
		if (_bm.Test(index3) == false)
			return false;

		return true; //有可能在，存在误判，有可能不同数据映射到的几个位完全相同
	}

private:
	BitMap _bm;
	size_t _size; //有多少个元素在
};

void TestBloomFilter()
{
	BloomFilter<string, HashFunc1, HashFunc2, HashFunc3> bf(100);
	string s1("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html");
	string s2("https://leetcode-cn.com/problems/sort-characters-by-frequency/");
	string s3("http://www.cnblogs.com/-clq/archive/2012/05/31/2528152.html");

	bf.Set(s1);
	bf.Set(s2);
	//bf.Set(s3);

	cout << bf.Test(s1) << endl;
	cout << bf.Test(s2) << endl;
	cout << bf.Test(s3) << endl;
}