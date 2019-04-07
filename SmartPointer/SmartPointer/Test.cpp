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

#include <mutex>
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
			, _pmutex(new mutex)
		{
			*_count = 1; //新资源刚被放进对象，引用计数为1
		}

		~SharedPtr()
		{
			if (_ptr != nullptr)
			{
				Release();
			}
		}

		SharedPtr(SharedPtr<T>& sp)
			:_ptr(sp._ptr)
			, _count(sp._count)
			, _pmutex(sp._pmutex)
		{
			AddCount();
		}

		SharedPtr<T>& operator=(SharedPtr<T>& sp)
		{
			if (_ptr != sp._ptr) //如果原本两对象就指向同一资源，就不用做什么了
			{
				Release();
				_ptr = sp._ptr;
				_count = sp._count;
				_pmutex = sp._pmutex;
				AddCount();
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

		int use_count()
		{
			return *_count;
		}


	private:
		T* _ptr;
		int* _count;
		mutex* _pmutex;  //互斥锁，所对象共享同一把锁

		void AddCount()
		{
			_pmutex->lock();
			++(*_count);
			_pmutex->unlock();
		}

		void Release()
		{
			bool deleteflag = false;
			_pmutex->lock();
			--(*_count);
			if (*_count == 0)
			{
				delete _ptr;
				deleteflag = true;
				cout << "deleted!" << endl;
			}
			_pmutex->unlock();
			/*如果只对（--(*_count);）加锁，可能会导致资源被释放两次
			（当线程1减操作刚完成被切出，假如此时刚好被减为1，线程2在进行减操作，到0，释放资源，
			等到线程1再次执行，在if (*_count == 0)时读到引用计数为0，再次释放）*/
			if (deleteflag == true)
				delete _pmutex;  //释放锁资源
		}
	};
}

//void Test()
//{
//	QIYU::SharedPtr<Date> spd(new Date(2019, 4, 1));
//	QIYU::SharedPtr<Date> spd1(spd);
//	cout << spd1->_year << endl;
//	cout << spd1->_month << endl;
//	cout << spd1->_day << endl;
//		
//	//
//	cout << spd->_year << endl;
//	cout << spd->_month << endl;
//	cout << spd->_day << endl;
//}

#include <thread>

//void SharedPtrFunc(QIYU::SharedPtr<int>& p, int n)
//{
//	while (n--)
//	{
//		QIYU::SharedPtr<int> copy(p);
//		
//	}
//}
//
//void Test()
//{
//	QIYU::SharedPtr<int> spi(new int(0));
//	int n = 10000;
//	thread t1(SharedPtrFunc, spi, n);
//	thread t2(SharedPtrFunc, spi, n);
//
//	t1.join();
//	t2.join();
//}

//void SharedPtrFunc(QIYU::SharedPtr<Date>& p, int n)
//{
//	while (n--)
//	{
//		++(p->_year);
//		++(p->_month);
//		++(p->_day);
//	}
//}
//
//void Test()
//{
//	QIYU::SharedPtr<Date> spd(new Date(1, 1, 1));
//	int n = 10000;
//	thread t1(SharedPtrFunc, spd, n);
//	thread t2(SharedPtrFunc, spd, n);
//
//	t1.join();
//	t2.join();
//
//	cout << spd->_year << " " << spd->_month << " " << spd->_day << endl;
//}

//void SharedPtrFunc(shared_ptr<Date>& p, int n)
//{
//	while (n--)
//	{
//		++(p->_year);
//		++(p->_month);
//		++(p->_day);
//	}
//}
//
//void Test()
//{
//	shared_ptr<Date> spd(new Date(1, 1, 1));
//	int n = 10000;
//	thread t1(SharedPtrFunc, spd, n);
//	thread t2(SharedPtrFunc, spd, n);
//
//	t1.join();
//	t2.join();
//
//	cout << spd->_year << " " << spd->_month << " " << spd->_day << endl;
//}

//struct ListNode
//{
//	int _val;
//	weak_ptr<ListNode> _next;
//	weak_ptr<ListNode> _prev;
//
//	~ListNode()
//	{
//		cout << "~ListNode" << endl;
//	}
//};
//
//void Test()
//{
//	shared_ptr<ListNode> Node1(new ListNode);
//	shared_ptr<ListNode> Node2(new ListNode);
//
//	cout << Node1.use_count() << endl;
//	cout << Node2.use_count() << endl;
//
//	Node1->_next = Node2;
//	Node2->_prev = Node1;
//
//	cout << Node1.use_count() << endl;
//	cout << Node2.use_count() << endl;
//}

//template<class T>
//class FreeDel
//{
//public:
//	void operator()(T* ptr)
//	{
//		free(ptr);
//		cout << "free" << endl;
//	}
//};
//
//void Test()
//{
//	FreeDel<int> freefunc; //仿函数删除器
//	//malloc产生的资源，应通过free释放
//	shared_ptr<int> spi((int*)malloc(sizeof(int)* 100), freefunc);
//}

template <class Mutex>
class LockGuard
{
public:
	LockGuard(Mutex& mtx)
		:_mutex(mtx)
	{
		_mutex.lock();
	}

	~LockGuard()
	{
		_mutex.unlock();
	}

	LockGuard(const LockGuard<Mutex>& lg) = delete;

private:
	Mutex& _mutex; //必须是引用，否则会发生拷贝构造，管理的锁不是实际new得到的锁。
};

int main()
{
	Test();
	return 0;
}
