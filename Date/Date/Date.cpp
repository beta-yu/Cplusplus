#include "Date.h"

void Date::Print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}
inline int Date::GetMonthDay(int year, int month)
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
Date::Date(int year, int month, int day)
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

//拷贝构造
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//赋值
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

inline bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

inline bool Date::operator>(const Date& d) const
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

bool Date::operator<(const Date& d) const
{
	if (!(this->operator>(d)) && !(this->operator==(d)))
		return true;
	return false;
}

bool Date::operator>=(const Date& d) const
{
	return !(this->operator<(d));
}

bool Date::operator<=(const Date& d) const
{
	return !(*this > d);
}

Date Date::operator+(int day) const
{
	Date ret(*this);
	if (day < 0)
	{
		ret -= (-day);
	}
	else
	{
		ret += day;
	}
	return ret;
}

inline Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
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

Date Date::operator-(int day) const
{
	Date ret(*this);
	if (day < 0)
	{
		ret += (-day);
	}
	else
	{
		ret -= day;
	}
	return ret;
}

inline Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += (-day);
	}
	while (_day - day < 1)
	{
		day = day - _day;
		_month--;
		while (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day = GetMonthDay(_year, _month);
	}
	_day -= day;
	return *this;
}

// 前置
Date& Date::operator++()
{
	return *this += 1;
}
Date& Date::operator--()
{
	return *this -= 1;
}

// 后置
Date Date::operator++(int)
{
	Date ret(*this);
	*this += 1;
	return ret;
}
Date Date::operator--(int)
{
	Date ret(*this);
	*this -= 1;
	return ret;
}

int Date::operator-(const Date& d) const
{
	Date max = *this;
	Date min = d;
	int n = 0;
	int flag = 1;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	while (min != max)
	{
		min++;
		n++;
	}

	return n * flag;
}