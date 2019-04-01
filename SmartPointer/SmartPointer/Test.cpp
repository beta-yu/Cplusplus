#include <iostream>
#include <memory>
using namespace std;
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
//
////使用RAII思想设计的smartptr类
//template<class T>
//class smartptr
//{
//public:
//	smartptr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//
//	~smartptr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			cout << "deleted!" << endl;
//		}
//	}
//
//	//需要满足指针的行为
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//private:
//	T* _ptr;
//};

//
//
////void Test()
////{
////	int* array = new int[100];
////	smartptr<int> sp(array);  //对象会在作用域结束销毁，自动调用其构造函数，释放空间
////}
//
//void Test()
//{
//	int* x = new int;
//	smartptr<int> sp(x);
//	*sp = 10;
//	cout << *sp << endl;
//
//	Date* d = new Date(2019, 3, 31);
//	smartptr<Date> sp1(d);
//	//sp1.operator->()->_year这里编译器优化，可以缺省一个"->"
//	cout << sp1->_year << " " << sp1->_month << " " << sp1->_day << endl;
//}

/* auto_ptr */

//void Test()
//{
//	int *pint = new int;
//	auto_ptr<int> ap(pint);
//	*ap = 10;
//	cout << *ap << endl;
//
//	auto_ptr<Date> apd(new Date(2019, 4, 1));
//	cout << apd->_year << endl;
//	cout << apd->_month << endl;
//	cout << apd->_day << endl;
//
//	auto_ptr<Date> apd1(apd); //return wrapped pointer and give up ownership
//	cout << apd1->_year << endl;
//	cout << apd1->_month << endl;
//	cout << apd1->_day << endl;
//
//	//
//	cout << apd->_year << endl;
//	cout << apd->_month << endl;
//	cout << apd->_day << endl;
//}

///* unique_ptr */
//void Test()
//{
//	unique_ptr<int> upi(new int);
//	*upi = 10;
//	cout << *upi << endl;
//
//	unique_ptr<Date> upd(new Date(2019, 4, 1));
//	//unique_ptr<Date> upd1(upd);
//	unique_ptr<Date> upd1;
//	upd1 = upd;
//
//}

///* shared_ptr */
//void Test()
//{
//	shared_ptr<Date> spd(new Date(2019, 4, 1));
//	shared_ptr<Date> spd1(spd);
//
//	cout << spd1->_year << endl;
//	cout << spd1->_month << endl;
//	cout << spd1->_day << endl;
//	
//	//
//	cout << spd->_year << endl;
//	cout << spd->_month << endl;
//	cout << spd->_day << endl;
//}

///* 模拟实现auto_ptr */
//namespace QIYU
//{
//	template<class T>
//	class AutoPtr
//	{
//	public:
//		AutoPtr(T* ptr = nullptr)
//			:_ptr(ptr)
//		{}
//
//		//copy()
//		AutoPtr(AutoPtr<T>& ap)
//			:_ptr(ap._ptr)
//		{
//			ap._ptr = nullptr;
//		}
//
//		//=
//		AutoPtr<T>& operator=(AutoPtr<T>& ap)
//		{
//			if (this != &ap) //检查是否为自己给自己赋值
//			{
//				if (_ptr) //释放掉原来的
//					delete _ptr;
//
//				_ptr = ap._ptr;
//				ap._ptr = nullptr; //置空，资源转移
//			}
//			return *this;
//		}
//
//		~AutoPtr()
//		{
//			if (_ptr)
//			{
//				delete _ptr;
//			}
//		}
//
//		T& operator*()
//		{
//			return *_ptr;
//		}
//
//		T* operator->()
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//	};
//}
//
//void Test()
//{
//	QIYU::AutoPtr<Date> apd(new Date(2019, 4, 1));
//	QIYU::AutoPtr<Date> apd1;
//	apd1 = apd;
//	cout << apd1->_year << endl;
//	cout << apd1->_month << endl;
//	cout << apd1->_day << endl;
//	
//	//
//	cout << apd->_year << endl;
//	cout << apd->_month << endl;
//	cout << apd->_day << endl;
//}

///* 模拟实现unique_ptr */
//namespace QIYU
//{
//	template<class T>
//	class UniquePtr
//	{
//	public:
//		UniquePtr(T* ptr = nullptr)
//			:_ptr(ptr)
//		{}
//
//		//C++11可在想要 “禁止使用” 的特殊成员函数声明后加 “= delete”
//		UniquePtr(const UniquePtr<T>& up) = delete;
//		UniquePtr<T>& operator=(const UniquePtr<T>& up) = delete;
//
//		~UniquePtr()
//		{
//			if (_ptr)
//			{
//				delete _ptr;
//			}
//		}
//
//		T& operator*()
//		{
//			return *_ptr;
//		}
//
//		T* operator->()
//		{
//			return _ptr;
//		}
//
//	private:
//		T* _ptr;
//	};
//}
//
//void Test()
//{
//	QIYU::UniquePtr<Date> upd(new Date(2019, 4, 1));
//	//QIYU::UniquePtr<Date> upd1(upd);
//
//	QIYU::UniquePtr<Date> upd2 = upd;
//}

/* 模拟实现shared_ptr */
namespace QIYU
{
	template<class T>
	class SharedPtr
	{
	public:
		SharedPtr(T* ptr)
			:_ptr(ptr)
			, _count(new int)
		{
			*_count = 1; //新资源刚被放进对象，引用计数为1
		}

		~SharedPtr()
		{
			if (_ptr != nullptr)
			{
				--(*_count);
				if (*_count == 0)
				{
					delete _ptr;
					delete _count;
					cout << "deleted!" << endl;
				}
			}
		}

		SharedPtr(SharedPtr<T>& sp)
			:_ptr(sp._ptr)
			, _count(sp._count)
		{
			++(*_count);
		}

		SharedPtr<T>& operator=(SharedPtr<T>& sp)
		{
			if (_ptr != sp._ptr) //如果原本两对象就指向同一资源，就不用做什么了
			{
				--(*_count);
				//如果引用计数减为0，释放资源
				if (*_count == 0)
				{
					delete _ptr;
				}
				_ptr = sp._ptr;
				_count = sp._count;
				++(*_count);
			}
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator*()
		{
			return *_ptr;
		}


	private:
		T* _ptr;
		int* _count;
	};
}

void Test()
{
	QIYU::SharedPtr<Date> spd(new Date(2019, 4, 1));
	QIYU::SharedPtr<Date> spd1(spd);
	cout << spd1->_year << endl;
	cout << spd1->_month << endl;
	cout << spd1->_day << endl;
		
	//
	cout << spd->_year << endl;
	cout << spd->_month << endl;
	cout << spd->_day << endl;
}

int main()
{
	Test();
	return 0;
}
