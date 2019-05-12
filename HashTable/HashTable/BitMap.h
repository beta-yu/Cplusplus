#pragma once

class BitMap
{
public:
	BitMap(const size_t range)
		:_range(range)
	{
		_v.resize((range >> 5) + 1);
	}

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