
class Goods
{
public:
	/*这里可以不用友元函数，因为成员变量被设为公有，只是练习一下*/
	friend ostream& operator<<(ostream& out, const Goods& A);
	Goods(int price, int sales_volume, int evaluation, int comprehensive)
		:_price(price)
		, _sales_volume(sales_volume)
		, _evaluation(evaluation)
		, _comprehensive(comprehensive)
	{}

	int _price;
	int _sales_volume;
	int _evaluation;
	int _comprehensive;
};

ostream& operator<<(ostream& out, const Goods& A)
{
	out << A._price << " " << A._sales_volume <<
		" " << A._evaluation << " " << A._comprehensive << endl;
	return out;
}

//函数对象
class GoodsPriceLess
{
public:
	inline bool operator()(Goods A, Goods B)
	{
		return A._price < B._price;
	}
};

class GoodsPriceGreater
{
public:
	inline bool operator()(Goods A, Goods B)
	{
		return A._price > B._price;
	}
};

class GoodsSalesLess
{
public:
	inline bool operator()(Goods A, Goods B)
	{
		return A._sales_volume < B._sales_volume;
	}
};

class GoodsSalesGreater
{
public:
	inline bool operator()(Goods A, Goods B)
	{
		return A._sales_volume > B._sales_volume;
	}
};