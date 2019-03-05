#include <iostream>
#include <assert.h>
using namespace std;

//class Date
//{
//public:
//	Date *operator&()
//	{
//		return this;
//	}
//
//	const Date *operator&() const
//	{
//		return this;  //this的类型为const Date*，与函数返回类型相同
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};

//class Array
//{
//public:
//	Array(int size)
//		:_size(size)
//		, _array((int*)malloc(sizeof(int)*_size))
//	{}
//private:
//	int _size;
//	int* _array;
//};
//
//int main()
//{
//	Array arr(10);
//	return 0;
//}

//class Time
//{
//public:
//	Time(int hour)
//		:_hour(hour)
//	{}
//private:
//	int _hour;
//};
//
//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//		, _a(1)  //由于Time类没有默认的构造函数，所以应该这样初始化
//	{
//		/*Time b(1);
//		_a = b;*/  //报错“Time”: 没有合适的默认构造函数可用
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _a;
//};

//class Array
//{
//public:
//	Array(int size)
//		: _size(size)
//		, _arr((int *)malloc(sizeof(int)* _size))
//	{}
//
//private:
//	int _size;
//	int *_arr;  /*如果_arr声明在_size之前，则在初始化列表中会先初始化_arr,
//				而此时_size还未被初始化，_size为随机值，
//				会导致_arr开辟一块巨大的空间，因此应该先声明_size，先初始化_size*/
//};

//class Time
//{
//public:
//	Time(int hour, int minute, int second)
//		: _hour(hour)
//		, _minute(minute)
//		, _second(second)
//	{}
//
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//
//int main()
//{
//	Time t(1, 2, 3);
//	t = {2, 3, 4};
//	return 0;
//}

//class A
//{
//private:
//	int i = 0;
//	int j = 1;
//	int *p = (int *)malloc(4);
//	static int count;
//};
//int A::count = 0;
//
//int main()
//{
//	cout << A::getCount() << endl; //静态成员函数可通过类名访问
//	A a1;
//	A a2(a1);
//	A a3;
//	cout << A::getCount() << endl;
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{}
//	friend ostream& operator<<(ostream& cout, const Date& d);
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//ostream& operator<<(ostream& cout, const Date& d)
//{
//	cout << d._year << "-" << d._month << "-" << d._day << endl;
//	return cout;
//}
//
//int main()
//{
//	Date d(2019, 1, 17);
//	cout << d;
//	return 0;
//}

//class Time
//{
//	friend class Date;
//public:
//	Time(int hour, int minute, int second)
//		: _hour(hour)
//		, _minute(minute)
//		, _second(second)
//	{}
//
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//
//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//		, _t(12, 0, 0)
//	{}
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << "-"
//			<< _t._hour << "-" << _t._minute << "-" << _t._second << endl;
//		/*作为Time类的友元类，可直接访问Time类的私有成员变量*/
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t;
//};
//
//int main()
//{
//	Date d(2018, 1, 17);
//	d.Print();
//	return 0;
//}

//class A
//{
//private:
//	static int k;
//	int m = 0;
//public:
//	class B
//	{
//	public:
//		void Print(const A& a)
//		{
//			cout << k << endl; //访问外部类的静态成员变量可以不加类名/对象
//			cout << a.m << endl;
//		}
//	};
//};
//int A::k = 0;
//
//int main()
//{
//	//A::B b;  //要能访问到B，需要把内部类B定义在外部类的public作用域
//	//b.Print(A());
//	cout << sizeof(A::B) << endl;
//	return 0;
//}

//int GetMonthDay(int year, int month)
//{
//	int arr[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//	if (month == 2)
//	{
//		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
//			return 29;
//	}
//	return arr[month];
//}
//int main()
//{
//	int year, month, day;
//	while (cin >> year >> month >> day)
//	{
//		int n = 0;
//		for (int i = 1; i<month; ++i)
//		{
//			n += GetMonthDay(year, i);
//		}
//		n += day;
//		cout << n << endl;
//	}
//	return 0;
//}

//int main()
//{
//	int a = 20;
//	if (1 <= a <= 10)  /*会先计算1 <= a得 1 ，表达式变为 1 <= 10,表达式成立*/
//		printf("In range\n");
//	else
//		printf("Out of range\n");
//	/*printf("%d", 1 <= a);*/
//	return 0;
//}

///*将一个数的二进制形式左右翻转*/
//unsigned int reverse_bits(unsigned int value)
//{
//	int answer = 0;
//	int i = 1;
//	for (i = 1; i != 0; i <<= 1)  //i从等于1开始左移，等到i == 0时，遍历了所有的位
//	{
//		answer <<= 1;  //answer左移1位，末端空出一位用来接受
//		if (value % 2 == 1) //value末位为1
//		{
//			answer |= 1;  //answer当前末位也赋值为1，下次循环answer左移
//		}
//		value >>= 1; //value右移，接着判断前一位
//	}
//	return answer;
//}
//
//int main()
//{
//	printf("%d\n", reverse_bits(25));
//	return 0;
//}

//int main()
//{
//	//char *ch = "hello\\\0";
//	cout << strlen("\t") << endl;
//	//cout << ch << endl;
//	return 0;
//}

//class A
//{
//public:
//	A()
//		:_value(0)
//	{
//		cout << "A()" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _value;
//};
//
//void Test1()
//{
//	A *p1 = (A *)malloc(sizeof(A));/*空间没有被初始化*/
//
//	new(p1) A;  //构造函数有参数时此处要传参
//	free(p1);
//}
//
//void Test2()
//{
//	A *p1 = new A;
//	delete p1;
//}
//
//int main()
//{
//	//Test1();
//	Test1();
//	return 0;
//}

//int main()
//{
//	void *p = NULL;
//	if (p == 0)
//	{
//		printf("NULL == 0\n");
//	}
//	return 0;
//}

//int main()
//{
//	int arr[] = { 1, 2, 3, 4, 5 };
//	/*使用ptr试图从1开始下标访问数组arr*/
//	int *ptr = arr - 1;  
//	for (int i = 1; i <= sizeof(arr) / sizeof(arr[0]); ++i)
//	{
//		cout << ptr[i] << endl;
//	}
//	return 0;
//}

//#include <iostream>
//#include <string>
//using namespace std;
//
//void firstUniqChar(string const s)
//{
//	int countchar[256] = { 0 };
//	for (size_t i = 0; i<s.size(); ++i)
//	{
//		countchar[s[i]]++;
//	}
//	for (size_t i = 0; i<s.size(); ++i)
//	{
//		if (countchar[s[i]] == 1)
//		{
//			cout << s[i] << endl;
//			return;
//		}
//	}
//	cout << -1 << endl;
//}
//
//int main()
//{
//	string s;
//	getline(cin, s);
//	firstUniqChar(s);
//	return 0;
//}

//int main()
//{
//	printf("%d - %d\n", '0', 'P');
//	return 0;
//}

//#include <iostream>
//#include <string>
//using namespace std;
//
//void reverseString(string& s, int begin, int end)
//{
//	while (begin < end)
//	{
//		swap(s[begin], s[end]);
//		begin++;
//		end--;
//	}
//}
//
//string reverseWords(string s) {
//	int begin = 0;
//	while (s.find(' ', begin) != -1)
//	{
//		int end = s.find(' ', begin) - 1;
//		reverseString(s, begin, end);
//		begin = end + 2;
//	}
//	reverseString(s, begin, s.size() - 1);
//	return s;
//}
//
//int main()
//{
//	string s;
//	getline(cin, s);
//	s = reverseWords(s);
//	cout << s << endl;
//	return 0;
//}

//int add(const int& a, const int& b)
//{
//	return a + b;
//}
//
//template<class T1, class T2>
//T1 add(const T1& a, const T2& b)
//{
//	return a + b;
//}
//
//int main()
//{
//	add(1, 2);
//	add<int>(1, 2);
//	add(1, 2.0);
//	return 0;
//}

//template<class T1, class T2>
//class Test
//{
//private:
//	T1 a;
//	T2 s;
//public:
//	Test();
//	~Test();
//};
//
//template<class T1, class T2>
//Test<T1, T2>::Test()
//{
//	cout << "Test()" << endl;
//}
//template<class T1, class T2>
//Test<T1, T2>::~Test()
//{
//	cout << "~Test()" << endl;
//}
//
//int main()
//{
//	Test<int, float> a;
//	return 0;
//}

//int main()
//{
//	/*char s[] = "hello";
//	int length = (char *)memchr(s, 0, sizeof(s)) - s;
//	cout << length << endl;*/
//	printf("%d\n", '\0');
//	return 0;
//}
#include <vector>

//void Find2Nums(vector<int>& nums, int& num1, int& num2)
//{
//	int ret = 0;
//	for (size_t i = 0; i < nums.size(); ++i)
//	{
//		ret ^= nums[i];
//	}
//	size_t n = 1;
//	while (1)  //两个数不相等，肯定至少有一位是1
//	{
//		if ((ret & 1) == 1)
//		{
//			break;
//		}
//		else
//		{
//			ret = ret >> 1;
//			++n;
//		}
//	}
//	vector<int> v1;
//	vector<int> v2;
//	int x = (1 << (n-1));
//	for (size_t i = 0; i < nums.size(); ++i)
//	{
//		if ((nums[i] & x) >= 1)
//		{
//			v1.push_back(nums[i]);
//		}
//		else
//		{
//			v2.push_back(nums[i]);
//		}
//	}
//	for (size_t i = 0; i < v1.size(); ++i)
//	{
//		num1 ^= v1[i];
//	}
//	for (size_t i = 0; i < v2.size(); ++i)
//	{
//		num2 ^= v2[i];
//	}
//}
//
//int main()
//{
//	//int arr[] = { 1, 2, 3, 8, 1, 2, 3, 4, 4, 5, 5, 6, 7, 7 };
//	int arr[] = { 1, 2, 1, 3, 2, 5 };
//	vector<int> nums(arr, arr + sizeof(arr) / sizeof(arr[0]));
//	int num1 = 0;
//	int num2 = 0;
//	Find2Nums(nums, num1, num2);
//	cout << num1 << " " << num2 << endl;
//	return 0;
//}

//vector<vector<int>> generate(int numRows) {
//	vector<vector<int>> result;
//	if (numRows == 0)
//		return result;
//	vector<int> ret;
//	ret.push_back(1);
//	result.push_back(ret);
//	if (numRows == 1)
//	{
//		return result;
//	}
//	for (int i = 1; i < numRows; ++i)
//	{
//		vector<int> v;
//		v.push_back(0 + result[i - 1][0]);
//		size_t j = 0;
//		for (j = 1; j < result[i - 1].size(); ++j)
//		{
//			v.push_back(result[i - 1][j - 1] + result[i - 1][j]);
//		}
//		v.push_back(result[i - 1][j - 1] + 0);
//		result.push_back(v);
//	}
//	return result;
//}
//
//int main()
//{
//	vector<vector<int>> ret = generate(5);
//	for (size_t i = 0; i < ret.size(); ++i)
//	{
//		for (size_t j = 0; j < ret[i].size(); ++j)
//		{
//			cout << ret[i][j] << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}

class Test
{
public:
	Test(char *src = "")
		:_size(strlen(src))
		, _capacity(_size)
	{
		_str = new char[_size + 1];
		strcpy(_str, src);
	}

	Test(const Test& s)
	{
		_str = new char[s._capacity + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}

	void operator=(Test s)
	{
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}

	char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	const char* c_str() const
	{
		return _str;
	}

	~Test()
	{
		if (_str != nullptr)
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

int main()
{
	Test s1("hello");
	char *p = &s1[0];
	*p = 'j';
	s1[1] = 'i';
	cout << s1.c_str() << endl;

	return 0;
}