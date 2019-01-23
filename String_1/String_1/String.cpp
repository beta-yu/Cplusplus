#include <iostream>
#include "String.h"
using namespace std;

size_t qiyu::String::npos = -1;

qiyu::String::String(const char *str = "")
{
	_size = strlen(str);
	_capacity = _size;
	_str = new char[_capacity + 1];
	strcpy(_str, str);
}
qiyu::String::~String()
{
	if (_str != nullptr)
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
	}
}

/*copy*/
qiyu::String::String(const String& s)
: _str(nullptr)
, _size(s._size)
, _capacity(s._capacity)
{
	String tmp(s._str);
	swap(_str, tmp._str);
}

qiyu::String& qiyu::String::operator=(String s)
{
	Swap(s);
	return *this;
}

void qiyu::String::Swap(String& s)
{
	swap(_str, s._str);
	swap(_size, s._size);
	swap(_capacity, s._capacity);
}

const char * qiyu::String::C_str() const
{
	return _str;
}

char& qiyu::String::operator[](size_t pos)  /*返回引用，可读可改*/
{
	assert(pos < _size);
	return _str[pos];
}

size_t qiyu::String::Size()
{
	return _size;
}

size_t qiyu::String::Capacity()
{
	return _capacity;
}

qiyu::String::iterator qiyu::String::begin()
{
	return _str;
}

qiyu::String::iterator qiyu::String::end()
{
	return _str + _size;
}

using namespace qiyu;

String::const_iterator String::cbegin() const
{
	return _str;
}
String::const_iterator String::cend() const
{
	return (_str + _size);
}

String::const_iterator String::begin() const
{
	return _str;
}
String::const_iterator String::end() const
{
	return (_str + _size);
}

void String::Reserve(size_t n)
{
	if (n > _capacity)
	{
		_str = (char *)realloc(_str, n+1);
		_capacity = n;
	}
}
void String::Pushback(char ch)
{
	if (_size == _capacity)
	{
		Reserve(_capacity * 2);
	}
	_str[_size] = ch;
	++_size;
	_str[_size] = '\0';
}

void String::Append(const char *str)
{
	assert(str);
	size_t len = strlen(str);
	if (_capacity < _size + len)
	{
		Reserve(_size + len);
	}
	strcat(_str, str);
	_size += strlen(str);
}


String& String::operator+=(char ch)
{
	Pushback(ch);
	return *this;
}
String& String::operator+=(const char* str)
{
	Append(str);
	return *this;
}

void String::Insert(size_t pos, char ch)
{
	assert(pos <= _size);
	if (pos == _size)
	{
		Pushback(ch);
		return;
	}
	Pushback(_str[_size - 1]);
	for (size_t i = _size - 1; i > pos; --i)
	{
		_str[i] = _str[i - 1];
	}
	_str[pos] = ch;
}

void String::Insert(size_t pos, const char* str)
{
	char *ret = new char[_size - pos];
	strcpy(ret, _str + pos);  //把从pos开始到末尾的子串拷贝到ret
	_str[pos] = '\0';
	_size = pos;
	Append(str);
	Append(ret);
	//delete[] ret;  为什么会崩？
}
//
void String::Erase(size_t pos, size_t len)
{
	assert(pos < _size);

	if (pos + len >= _size)
	{
		_size = pos;
		_str[_size] = '\0';
	}
	else
	{
		_str[pos] = '\0';
		strcat(_str, _str + pos + len);
		_size -= len;
	}
}

size_t String::Find(char ch, size_t pos = 0) const
{
	assert(pos < _size);
	for (size_t i = pos; i < _size; ++i)
	{
		if (_str[i] == ch)
			return i;
	}
	return npos;
}

size_t String::Find(const char* str, size_t pos = 0) const
{
	assert(pos < _size);
	size_t len = strlen(str);
	for (size_t i = pos; i < _size - len + 1; ++i)
	{
		size_t index = i;
		int flag = 1;
		for (size_t j = 0; j < len; ++j)
		{
			if (_str[index++] != str[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return i;
	} 
	return npos;
}

bool String::operator<(const String& s) const
{
	return !(*this > s || *this == s);
}

bool String::operator>(const String& s) const
{
	size_t ssize = _size;
	if (s._size < ssize)
		ssize = s._size;
	for (size_t i = 0; i < ssize; ++i)
	{
		if (_str[i] > s._str[i])
			return true;
		else if (_str[i] < s._str[i])
			return false;
	}
	return _size > s._size ? true : false;
}

bool String::operator<=(const String& s) const
{
	return (*this < s || *this == s);
}

bool String::operator>=(const String& s) const
{
	return (*this > s || *this == s);
}

bool String::operator==(const String& s) const
{
	if (_size == s._size)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_str[i] != s._str[i])
				return false;
		}
		return true;
	}
	return false;
}

bool String::operator!=(const String& s) const
{
	return !(*this == s);
}


//ostream& qiyu::operator<<(ostream& out, const String& s)
//{
//	out << s._str;
//	return out;
//}


//using namespace qiyu;
void qiyu::testString()
{
	String s1("hello");
	String s2("hellp");
	String s3;
	s3 = s2;

	/*cout << s1.C_str() << endl;
	s1 += "world";
	s1 += " !";
	s1 += " !";
	s1 += " !";

	cout << s1.C_str() << endl;*/
	//cout << s1.Find('a', 0) << endl;
	//cout << s1.Find('l', 4) << endl;

	/*for (auto it : s1)
	{
		cout << it << " ";
	}
	cout << endl;*/
	//cout << s1.Find("llo", 0) << endl;
	/*s1.Insert(0, '_');
	cout << s1.C_str() << endl;
	cout << s1.Size() << endl;
	cout << s1.Capacity() << endl;*/
/*	s1.Erase(2, 4);
	cout << s1.C_str() << endl;
	cout << s1.Size() << endl;
	cout << s1.Capacity() << endl*/;
	/*cout << (s1 > s2) << endl;*/
	//String s4("0123456");
	//s4.Erase(3, 4);
	//cout << s4.C_str() << endl;

	const String s4("xaufe");
	/*String::const_iterator it = s4.cbegin();
	while (it != s4.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;*/

	for (auto it : s4)   /*调试发现范围for会去调用const_iterator begin() end(), 为什么不会调用cbegin()...?*/
	{
		cout << it << " ";
	}
	cout << endl;
}