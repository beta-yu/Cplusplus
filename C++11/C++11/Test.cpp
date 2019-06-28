#include "Common.h"

//template <class T>
//void printvector(const vector<T>& v)
//{
//	for (const auto& it : v)
//	{
//		cout << it << " ";
//	}
//	cout << endl;
//}
//int main()
//{
//	int a = { 1 }; //多此一举
//	int b{ 2 };
//	int c{ 1 + 2 };
//	int d{ a + b };
//	vector<int> v = { 1, 2, 3, 4 };
//	vector<string> vs = { "string", "vector" };
//	int *arr = new int[]{1, 2, 3, 4};
//	map<int, int> mymap{ { 1, 1 }, { 2, 2 } };
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year, int month, int day)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1{ 2019, 6, 26 };
//	return 0;
//}

#include <initializer_list>
//
//int main()
//{
//	initializer_list<int> initlist{ 1, 2, 3, 4 };
//	auto it = initlist.begin();
//	for (; it != initlist.end(); ++it)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	cout << initlist.size() << endl;
//	return 0;
//}

//template <class T>
//class Vector
//{
//public:
//	Vector(initializer_list<T> l) //包含一个带有initializer_list参数的构造函数
//		:_capacity(l.size())
//		, _size(0)
//	{
//		_arr = new T[_capacity];
//		for (const auto& it : l)
//		{
//			_arr[_size++] = it;
//		}
//	}
//
//	size_t size()
//	{
//		return _size;
//	}
//	T& operator[](size_t i)
//	{
//		return *(_arr + i);
//	}
//private:
//	T *_arr;
//	size_t _size;
//	size_t _capacity;
//};
//
//int main()
//{
//	Vector<int> V{ 1, 2, 3, 4 }; //用{}内容构建了一个initializer_list对象
//	for (size_t i = 0; i < V.size(); ++i)
//	{
//		cout << V[i] << " ";
//	}
//	cout << endl;
//	return 0;
//}

//int main()
//{
//	short a = 32760;
//	short b = 32765;
//	//若指定c的类型为short，则会造成数据丢失，
//	//使用auto，让编译器自己推演c的实际类型，就不会存在问题
//	auto c = a + b; //c的类型为int
//
//	unordered_map<int, int> mymap{ { 1, 1 }, { 2, 2 } };
//	//unordered_map<int, int>::iterator it = mymap.begin(); 
//	auto it = mymap.begin(); //使用auto可避免如上复杂的写法
//	return 0;
//}


//void *func()
//{
//	return (void *)0;
//}
//
//int main()
//{
//	//不带参数列表是，返回函数的类型
//	cout << typeid(decltype(func)).name() << endl; //void * __cdecl(void)
//	//带参数列表时，返回函数返回值类型
//	cout << typeid(decltype(func())).name() << endl; //void *
//	return 0;
//}

//int main()
//{
//	vector<int> v{ 1, 2, 3, 4 };
//	for (auto it : v)
//	{
//		//...
//	}
//}

//class A
//{
//public:
//	A(int data = 1)
//		:_data(data)
//	{}
//
//	virtual void print() 
//	{
//		cout << _data << endl;
//	}
//private:
//	int _data;
//};
//
//class B : public A
//{
//public:
//	virtual void print() override;
//};
//
//int main()
//{
//	B b;
//	b.print();
//	return 0;
//}

//class Info
//{
//public:
//	//目标构造函数：将构造函数体中重复的代码提出来作为一个基础版本，用于在其它构造函数中调用
//	Info() //被委派
//		:_a(1)
//		, _c('c')
//	{
//		Init();//一些初始化行为
//	}
//
//	//委派构造函数
//	Info(int a)
//		:Info() //委派
//	{
//		_a = a;
//	}
//
//	Info(char c)
//		:Info() //委派
//	{
//		_c = c;
//	}
//private:
//	void Init()
//	{
//		//...
//	}
//private:
//	int _a;
//	char _c;
//};

//class Info{
//public:
//	// 目标构造函数
//	Info()
//		: _type(0)
//		, _a('a') {
//		InitRSet();
//	}
//	// 委派构造函数
//	Info(int type)
//		: Info() {
//		_type = type;
//	}
//	// 委派构造函数
//	Info(char a)
//		: Info() {
//		_a = a;
//	}
//private:
//	void InitRSet(){
//		//初始化其他变量
//	}
//private:
//	int _type = 0;
//	char _a = 'a';
//	//...
//};

//class A
//{
//public:
//	/*explicit */A(int a) = delete;
//
//	A() = default;
//
//	A& operator=(const A& a) = delete;
//private:
//	int _a;
//};
//
////A& A::operator=(const A& a) = default; //定义时让编译器生成默认版本
//
//int main()
//{
//	A a;
//	a = 1; //无法引用 函数 "A::operator=(const A &a)"它是已删除的函数
//	return 0;
//}
#include <cstring>
class String
{
public:
	String(const char *str = "")
	{
		if (str == nullptr)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		cout << "String(const char *str = "")" << endl;
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
		cout << "String(const String& s)" << endl;
	}

	String(String&& s)
	{
		swap(_str, s._str);
		cout << "String(String&& s)" << endl;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			if (_str != nullptr)
				delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}

		return *this;
	}

	~String()
	{
		if (_str != nullptr)
			delete[] _str;
	}
private:
	char *_str = nullptr;
};

String get(const char *str)
{
	String ret(str);
	return ret;
}

int main()
{
	String s1("hello");
	String s2(get("world"));
	return 0;
}