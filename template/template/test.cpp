#include <iostream>

using namespace std;

/*
	非类型模板参数：
	用一个常量(浮点数/类对象/字符串不可以)作为类（函数）模板的参数，
	在模板中可以把该参数当作常量来使用，
	必须在编译阶段就能确定结果
*/
template<class T, size_t sz = 10>
class Array
{
public:
	Array()
		:size(sz)
	{}
private:
	T arr[sz];
	size_t size;
};

int main()
{
	Array<int, 100> arr;
	return 0;
}


template<class T>
bool isEqual(T& left, T& right)
{
	return left == right;
}
/*
	函数模板特化：
	template<>
	函数名<特化类型>(形参类型必须和特化类型相同)
*/
//字符串比较应该按ASCII值逐一比较，不能以地址比较
template<>
bool isEqual<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) == 0)
		return true;
	else
		return false;
}


/*
	类模板特化：
	全特化：将模板参数列表中所有参数都确定化
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<>
class Data<int, char>
{
public:
	Data()
	{
		cout << "Data<int, char>" << endl;
	}
private:
	int a;
	char b;
};

int main()
{
	Data<int, char> d1;
	Data<int, int> d2;
	return 0;
}


/*
	偏特化：
	1.部分特化：将模板参数的一部分参数特化
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1>
class Data<T1, int>
{
public:
	Data()
	{
		cout << "Data<T1, int>" << endl;
	}
private:
	T1 a;
	int b;
};

int main()
{
	Data<int, int> d1;
	Data<int, char> d2;
	return 0;
}


/*
	偏特化：
	2.参数更进一步的限制
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1, class T2>
//两个参数偏特化为指针类型
class Data<T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1, class T2>
//两个参数偏特化为引用类型
class Data<T1&, T2&>
{
public:
	Data(const T1& x, const T2& y)
		:a(x)
		, b(y)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1& a;
	const T2& b;
};

int main()
{
	Data<int, int> d1;
	Data<int*, int*> d2;
	Data<int&, int&> d3(1, 2);
	return 0;
}


int main()
{
	int a = 1;
	//获取变量类型名
	cout << typeid(a).name() << endl;
	return 0;
}
/*
	类型萃取
*/
