#include <iostream>
#include <string>
#include <algorithm>
using namespace std;  /*在使用string类时，必须包含头文件以及using namespace std;*/

void constructor_test()
{
	string s1("hello world");
	string s2(s1, 6, 5);  
	/*用从下标为6处开始的5个字符构造string对象,原型：  
	string (const string& str, size_t pos, size_t len = npos);*/
	cout << s2 << endl;

	char *s3 = "xaufe";
	string s4(s3);  /*用一个字符串常量构造string对象*/
	cout << s4 << endl;

	string s5(s3, 5); 
	/*用一个字符串常量构造string对象,从s3指向位置开始的前5个字符*/
	cout << s5 << endl;
	string s6(s3 + 1, 4); /*同上*/
	cout << s6 << endl;

	string s7(5, 'x');  /*使用5个'x'来构造*/
	cout << s7 << endl;
}

void assign_test()
{
	string s1("hello");
	string s2;
	s2 = s1; /*用string对象赋值*/
	cout << s2 << endl;
	s2 = "world"; /*用常量字符串赋值*/
	cout << s2 << endl;
	s2 = 'a';  /*用字符赋值*/
	cout << s2 << endl;
}

void iterator_test()
{
	string s1("hello world");
	string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it;
		++it;
	}
	cout << endl;

	string::reverse_iterator rit = s1.rbegin();  
	/*reverse_iterator反向迭代器
	rbegin(); rend();*/
	while (rit != s1.rend())
	{
		cout << *rit;
		++rit;  /*注意反向也是++*/
	}
	cout << endl;

	string const s2("xaufe");
	string::const_iterator cit = s2.begin(); 
	/*常迭代器其中使用begin()和cbegin()相同，end()也一样*/
	while (cit != s2.end())
	{
		cout << *cit;
		++cit;
	}
	cout << endl;

	string::const_reverse_iterator crit = s2.crbegin(); 
	/*常量反向迭代器，这里crbegin()与rbegin效果相同*/
	while (crit != s2.crend())
	{
		cout << *crit;
		++crit;
	}
	cout << endl;

	/*范围for，可以遍历所有容器，底层依赖迭代器*/
	for (auto it : s1) 
	{
		cout << it;
	}
	cout << endl;
}

void capacity_test()
{
	string s1("xaufe");
	cout << s1.size() << " " << s1.length() << endl;/*size()和length()结果相同*/
	cout << s1.capacity() << endl;
	string s2;
	cout << s2.empty() << endl; /*返回值为bool值*/
	cout << s2.capacity() << endl;
	
	//s1.resize(8);  /*设置size,若比原size小，会截断字符串，比原size大默认用'\0'补充*/
	//cout << s1.size() << endl;
	//for (auto it : s1)
	//{
	//	cout << it;
	//}
	//cout << endl;

	s1.resize(8, 'x');  /*比原size大,也可指定用某字符补充*/
	cout << s1.size() << endl;
	for (auto it : s1)
	{
		cout << it;
	}
	cout << endl;

	s1.reserve(10);/*改变capacity,如果n大于原容量，则将容量设置为n(或更大),
				   其他情况编译器会对其进行优化，该函数对size无影响，不会改变对象内容*/
	cout << s1.capacity() << " " << s1.size() << endl;
	for (auto it : s1)
	{
		cout << it;
	}
	cout << endl;

	s1.clear();  /*clear()只是将值清空，size清0，capacity不变*/
	cout << s1.size() << " " << s1.capacity() << endl;
	for (auto it : s1)
	{
		cout << it;
	}
	cout << endl;
}

void access_test()
{
	string s1("xaufe");
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i];
	}
	cout << endl;

	cout << s1.at(2) << endl; /*返回s1[2]的引用*/
	cout << s1.front() << endl;
	cout << s1.back() << endl;
}

void modify_test()
{
	string s1("hello ");
	string s2("__xaufe");
	/*s1 += s2;
	cout << s1 << endl;

	string s3("!");
	s1.append(s3);*/  /*此处与+=相同*/
	cout << s1 << endl;

	s1.append(s2, 2, 5);  /*Appends a copy of a substring of s2, 从索引为2处开始，长度为5*/
	cout << s1 << endl;
	/*s1.append("!");
	cout << s1 << endl;*/

	s1.append("!__", 1); /*string& append (const char* s, size_t n);
						 追加指针s指向的字符数组的前n个*/
	cout << s1 << endl;

	s1.append(2, '_');  /*追加2个'_'*/
	cout << s1 << endl;

	s1.push_back('!'); /*追加字符*/
	cout << s1 << endl;

	/*
	string (1)	string& assign (const string& str);
	substring (2)	string& assign (const string& str, size_t subpos, size_t sublen);
	c-string (3)	string& assign (const char* s);
	buffer (4)	string& assign (const char* s, size_t n);
	fill (5)	string& assign (size_t n, char c)
	*/
	/*为字符串指定一个新的值，替换当前内容*/
	s1.assign("hello");
	cout << s1 << endl;

	/*
	string (1)	string& insert (size_t pos, const string& str);
	substring (2)	string& insert (size_t pos, const string& str, size_t subpos, size_t sublen);
	c-string (3)	string& insert (size_t pos, const char* s);
	buffer (4)	string& insert (size_t pos, const char* s, size_t n);
	fill (5)	string& insert (size_t pos, size_t n, char c);
				void insert (iterator p, size_t n, char c);
	single character (6)	iterator insert (iterator p, char c);
	*/
	string s3("__world__");
	/*s1.insert(5, s3, 1, 6);
	cout << s1 << endl;*/

	string::iterator it = s1.end();
	s1.insert(it, 5, 'x');  /*从it指向位置开始插入...*/
	cout << s1 << endl;

	/*
	sequence (1)	string& erase (size_t pos = 0, size_t len = npos);
	/*擦除字符串值中从字符位置pos开始并跨越len字符的部分
	(或者，如果内容太短或len为string::npos，则擦除到字符串末尾)。
	注意，默认参数会擦除字符串中的所有字符(比如清除成员函数)。
	*/
	/*
	character (2)	iterator erase (iterator p);  //擦除p指向的字符
	range (3)	iterator erase (iterator first, iterator last);  //擦除[first, last]范围内的字符
	*/
	s1.erase(it, s1.end());
	cout << s1 << endl;

	/*将原对象某一范围内的值替换为str;
	其中一个原型为：string& replace (size_t pos, size_t len, const string& str);*/
	s1.reserve(30);
	cout << s1.size() << " " << s1.capacity() << endl;
	cout << s2.size() << " " << s2.capacity() << endl;
	s1.swap(s2);  /*交换两个对象的内容，包括size, capacity*/
	cout << s1.size() << " " << s1.capacity() << endl;
	cout << s2.size() << " " << s2.capacity() << endl;

	/*pop_back()  Delete last character*/
}

void operate_test()
{
	string s1("hello");
	cout << s1.c_str() << endl;  //返回一个指向字符数组的指针，该数组与s1有相同的字符序列
	char s2[20] = { 0 };
	s1.copy(s2, 5, 0);  /*将s1中从0索引处开始的5个字符拷贝到数组s2中，不会在复制内容的末位追加'\0'*/
	cout << s2 << endl;

	/*
	string (1)	size_t find (const string& str, size_t pos = 0) const;
	c-string (2)	size_t find (const char* s, size_t pos = 0) const;
	buffer (3)	size_t find (const char* s, size_t pos, size_t n) const;
	character (4)	size_t find (char c, size_t pos = 0) const;
	在字符串中搜索由其参数指定的序列的第一个出现项。
	*/
	string s3("hello world hello");
	size_t pos1 = s3.find("hello");
	cout << "First 'hello' found at: " << pos1 << endl;
	size_t pos2 = s3.find("hello", pos1 + 1);
	cout << "Second 'hello' found at: " << pos2 << endl;

	/*
	rfind()  
	find_first_of()   Find character in string
	find_last_of()	  Find character in string from the end

	string substr (size_t pos = 0, size_t len = npos) const;
	Returns a newly constructed string object with its value initialized to a copy of a substring of this object.

	compare()  返回值>0, ==0, <0
	*/
}

/*string::npos 
  static const size_t npos = -1;  无符号整型最大值*/


/*
Non-member function overloads
string opreator+(...)
void swap (string& x, string& y);
istream& operator>> (istream& is, string& str);
ostream& operator<< (ostream& os, const string& str);

(1)
istream& getline (istream& is, string& str, char delim);  遇到delim才会结束
(2)
istream& getline (istream& is, string& str);
从is中提取字符并将其存储到str中，直到找到分隔符delim(或(2)的换行字符'\n')
*/

void test()
{
	string s;
	getline(cin, s, '.');
	cout << s << endl;
}

void swap_test()
{
	string s1("abc");
	string s2("bcd");
	//cout << s1.c_str() << " " << s2.c_str() << endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
	swap(s1, s2);
	//s1.swap(s2);
	//cout << s1.c_str() << " " << s2.c_str() << endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());

}

int main()
{
	//constructor_test();
	//assign_test();
	//iterator_test();
	//capacity_test();
	//access_test();
	//modify_test();
	//operate_test();
	//test();
	swap_test();
	return 0;
}