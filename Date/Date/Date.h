#ifndef __Data_h__
#define __Data_h__

#include <iostream>
using namespace std;

class Date
{
public:
	void Print() const;
	inline int GetMonthDay(int year, int month);
	Date(int year = 2019, int month = 1, int day = 1);

	//��������
	Date(const Date& d);

	//��ֵ
	Date& operator=(const Date& d);

	inline bool operator==(const Date& d) const;

	bool operator!=(const Date& d) const;

	inline bool operator>(const Date& d) const;

	bool operator<(const Date& d) const;

	bool operator>=(const Date& d) const;

	bool operator<=(const Date& d) const;

	Date operator+(int day) const;

	inline Date& operator+=(int day);

	Date operator-(int day) const;

	inline Date& operator-=(int day);

	// ǰ��
	Date& operator++();
	Date& operator--();

	// ����
	Date operator++(int);
	Date operator--(int);
	int operator-(const Date& d) const;

private:
	int _year;
	int _month;
	int _day;
};

#endif //__Data_h__