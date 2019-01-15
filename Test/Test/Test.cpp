#include <iostream>
using namespace std;

class Date
{
public:
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	int GetMonthDay(int year, int month)
	{
		int arr[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		/*闰年29天，非闰年28天*/
		if (month == 2)
		{
			/*（1）能被4整除但不能被100整除；
			  （2）能被400整除*/
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				return 29;
		}
		return arr[month];
	}
	Date(int year = 2019, int month = 1, int day = 1)
	{
		if (year > 0 && month > 0
			&& month < 13 && day > 0
			&& day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
			cout << "日期非法" << endl;
	}
	
	bool operator==(const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(this->operator==(d));
	}

	bool operator>(const Date& d)
	{
		if (_year > d._year)
			return true;
		else if (_year == d._year)
		{
			if (_month > d._month)
				return true;
			else if (_month == d._month)
			{
				return _day > d._day;
			}
			else
				return false;
		}
		return false;
	}

	bool operator<(const Date& d)
	{
		if (!(this->operator>(d)) && !(this->operator==(d)))
			return true;
		return false;
	}

	bool operator>=(const Date& d)
	{
		return !(this->operator<(d));
	}

	bool operator<=(const Date& d)
	{
		return !(this->operator>(d));
	}

	Date operator+(int day)
	{
		Date ret(*this);
		while (ret._day + day > GetMonthDay(ret._year, ret._month))
		{
			/*1.15-->2.1需要17天*/
			day = day - ((GetMonthDay(ret._year, ret._month)) - ret._day) - 1;
			ret._month++;
			ret._day = 1;

			while (ret._month > 12)
			{
				ret._year++;
				ret._month = 1;
			}
		}
		ret._day += day;
		return ret;
	}

	Date operator+=(int day)
	{
		while (_day + day > GetMonthDay(_year, _month))
		{
			/*1.15-->2.1需要17天*/
			day = day - ((GetMonthDay(_year, _month)) - _day) - 1;
			_month++;
			_day = 1;
			
			while (_month > 12)
			{
				_year++;
				_month = 1;
			}
		}
		_day += day;
		return *this;
	}

	Date operator-(int day)
	{
		Date ret(*this);
		while (ret._day - day < 1)
		{
			day = day - ret._day;
			ret._month--;
			ret._day = GetMonthDay(ret._year, ret._month);

			while (ret._month < 1)
			{
				ret._year--;
				ret._month = 12;
			}
		}
		ret._day -= day;
		return ret;
	}

	Date operator-=(int day)
	{
		while (_day - day < 1)
		{
			day = day - _day;
			_month--;
			_day = GetMonthDay(_year, _month);

			while (_month < 1)
			{
				_year--;
				_month = 12;
			}
		}
		_day -= day;
		return *this;
	}

	// 前置
	Date operator++()
	{
		if (_day + 1 > GetMonthDay(_year, _month))
		{
			_month++;
			_day = 1;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
		}
		else
		{
			_day++;
		}
		return *this;
	}
	Date operator--()
	{
		if (_day - 1 < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = GetMonthDay(_year, _month);
		}
		else
		{
			_day--;
		}
		return *this;
	}

	// 后置
	Date operator++(int)
	{
		Date ret(*this);
		if (_day + 1 > GetMonthDay(_year, _month))
		{
			_month++;
			_day = 1;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
		}
		else
		{
			_day++;
		}
		return ret;
	}
	Date operator--(int)
	{
		Date ret(*this);
		if (_day - 1 < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = GetMonthDay(_year, _month);
		}
		else
		{
			_day--;
		}
		return ret;
	}

	// d1-d2
	//int operator-(const Date& d)
	//{
	//	if (*this < d)
	//		return -1;
	//	if (*this == d)
	//		return 0;
	//	if (_year == d._year && _month == d._month)
	//	{
	//		return _day - d._day;
	//	}
	//	else if (_year == d._year)
	//	{
	//		int n = 0;
	//		for (int i = (d._month) + 1; i < _month; ++i)
	//		{
	//			n += GetMonthDay(_year, i);
	//		}
	//		/*n += (小的月份剩余的天数 + 大的月份的天数)*/
	//		n += ((GetMonthDay(_year, d._month) - d._day) + _day);
	//		return n;
	//	}
	//	else
	//	{
	//		int n = 0;
	//		//中间相差整年的天数
	//		for (int y = d._year + 1; y < _year; ++y)
	//		{
	//			int m = 1;
	//			while (m < 13)
	//			{
	//				n += GetMonthDay(y, m);
	//				++m;
	//			}
	//		}

	//		//小的日期当年剩余的天数
	//		for (int i = (d._month) + 1; i < 13; ++i)
	//		{
	//			n += GetMonthDay(d._year, i);
	//		}
	//		n += (GetMonthDay(d._year, d._month) - d._day);

	//		//大的日期当年经过的天数
	//		for (int i = 1; i < _month; ++i)
	//		{
	//			n += GetMonthDay(_year, i);
	//		}
	//		n += _day;
	//		return n;
	//	}
	//}
	int operator-(const Date& d)
	{
		int n = 0;
		Date ret(d);
		while (!(ret == *this))
		{
			++ret;
			++n;
		}
		return n;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2017, 8, 8);
	Date d2(2019, 8, 8);
	int n = d2 - d1;
	cout << n << endl;
	/*(d1++).Print();
	d1.Print();*/
	//d2.Print();
	/*Date d2(2019, 1, 16);
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;*/
	return 0;
}