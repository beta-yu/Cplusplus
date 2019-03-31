#include <iostream>
using namespace std;

//使用RAII思想设计的smartptr类
template<class T>
class smartptr
{
public:
	smartptr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~smartptr()
	{
		if (_ptr)
		{
			delete _ptr;
			cout << "deleted!" << endl;
		}
	}

	//需要满足指针的行为
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};

class Date
{
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	int _year;
	int _month;
	int _day;
};


//void Test()
//{
//	int* array = new int[100];
//	smartptr<int> sp(array);  //对象会在作用域结束销毁，自动调用其构造函数，释放空间
//}

void Test()
{
	int* x = new int;
	smartptr<int> sp(x);
	*sp = 10;
	cout << *sp << endl;

	Date* d = new Date(2019, 3, 31);
	smartptr<Date> sp1(d);
	//sp1.operator->()->_year这里编译器优化，可以缺省一个"->"
	cout << sp1->_year << " " << sp1->_month << " " << sp1->_day << endl;
}

int main()
{
	Test();
	return 0;
}