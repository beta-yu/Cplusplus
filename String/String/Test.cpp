#include <iostream>
#include <string>
#include <algorithm>
using namespace std;  /*��ʹ��string��ʱ���������ͷ�ļ��Լ�using namespace std;*/

void constructor_test()
{
	string s1("hello world");
	string s2(s1, 6, 5);  
	/*�ô��±�Ϊ6����ʼ��5���ַ�����string����,ԭ�ͣ�  
	string (const string& str, size_t pos, size_t len = npos);*/
	cout << s2 << endl;

	char *s3 = "xaufe";
	string s4(s3);  /*��һ���ַ�����������string����*/
	cout << s4 << endl;

	string s5(s3, 5); 
	/*��һ���ַ�����������string����,��s3ָ��λ�ÿ�ʼ��ǰ5���ַ�*/
	cout << s5 << endl;
	string s6(s3 + 1, 4); /*ͬ��*/
	cout << s6 << endl;

	string s7(5, 'x');  /*ʹ��5��'x'������*/
	cout << s7 << endl;
}

void assign_test()
{
	string s1("hello");
	string s2;
	s2 = s1; /*��string����ֵ*/
	cout << s2 << endl;
	s2 = "world"; /*�ó����ַ�����ֵ*/
	cout << s2 << endl;
	s2 = 'a';  /*���ַ���ֵ*/
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
	/*reverse_iterator���������
	rbegin(); rend();*/
	while (rit != s1.rend())
	{
		cout << *rit;
		++rit;  /*ע�ⷴ��Ҳ��++*/
	}
	cout << endl;

	string const s2("xaufe");
	string::const_iterator cit = s2.begin(); 
	/*������������ʹ��begin()��cbegin()��ͬ��end()Ҳһ��*/
	while (cit != s2.end())
	{
		cout << *cit;
		++cit;
	}
	cout << endl;

	string::const_reverse_iterator crit = s2.crbegin(); 
	/*�������������������crbegin()��rbeginЧ����ͬ*/
	while (crit != s2.crend())
	{
		cout << *crit;
		++crit;
	}
	cout << endl;

	/*��Χfor�����Ա��������������ײ�����������*/
	for (auto it : s1) 
	{
		cout << it;
	}
	cout << endl;
}

void capacity_test()
{
	string s1("xaufe");
	cout << s1.size() << " " << s1.length() << endl;/*size()��length()�����ͬ*/
	cout << s1.capacity() << endl;
	string s2;
	cout << s2.empty() << endl; /*����ֵΪboolֵ*/
	cout << s2.capacity() << endl;
	
	//s1.resize(8);  /*����size,����ԭsizeС����ض��ַ�������ԭsize��Ĭ����'\0'����*/
	//cout << s1.size() << endl;
	//for (auto it : s1)
	//{
	//	cout << it;
	//}
	//cout << endl;

	s1.resize(8, 'x');  /*��ԭsize��,Ҳ��ָ����ĳ�ַ�����*/
	cout << s1.size() << endl;
	for (auto it : s1)
	{
		cout << it;
	}
	cout << endl;

	s1.reserve(10);/*�ı�capacity,���n����ԭ����������������Ϊn(�����),
				   ����������������������Ż����ú�����size��Ӱ�죬����ı��������*/
	cout << s1.capacity() << " " << s1.size() << endl;
	for (auto it : s1)
	{
		cout << it;
	}
	cout << endl;

	s1.clear();  /*clear()ֻ�ǽ�ֵ��գ�size��0��capacity����*/
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

	cout << s1.at(2) << endl; /*����s1[2]������*/
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
	s1.append(s3);*/  /*�˴���+=��ͬ*/
	cout << s1 << endl;

	s1.append(s2, 2, 5);  /*Appends a copy of a substring of s2, ������Ϊ2����ʼ������Ϊ5*/
	cout << s1 << endl;
	/*s1.append("!");
	cout << s1 << endl;*/

	s1.append("!__", 1); /*string& append (const char* s, size_t n);
						 ׷��ָ��sָ����ַ������ǰn��*/
	cout << s1 << endl;

	s1.append(2, '_');  /*׷��2��'_'*/
	cout << s1 << endl;

	s1.push_back('!'); /*׷���ַ�*/
	cout << s1 << endl;

	/*
	string (1)	string& assign (const string& str);
	substring (2)	string& assign (const string& str, size_t subpos, size_t sublen);
	c-string (3)	string& assign (const char* s);
	buffer (4)	string& assign (const char* s, size_t n);
	fill (5)	string& assign (size_t n, char c)
	*/
	/*Ϊ�ַ���ָ��һ���µ�ֵ���滻��ǰ����*/
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
	s1.insert(it, 5, 'x');  /*��itָ��λ�ÿ�ʼ����...*/
	cout << s1 << endl;

	/*
	sequence (1)	string& erase (size_t pos = 0, size_t len = npos);
	/*�����ַ���ֵ�д��ַ�λ��pos��ʼ����Խlen�ַ��Ĳ���
	(���ߣ��������̫�̻�lenΪstring::npos����������ַ���ĩβ)��
	ע�⣬Ĭ�ϲ���������ַ����е������ַ�(���������Ա����)��
	*/
	/*
	character (2)	iterator erase (iterator p);  //����pָ����ַ�
	range (3)	iterator erase (iterator first, iterator last);  //����[first, last]��Χ�ڵ��ַ�
	*/
	s1.erase(it, s1.end());
	cout << s1 << endl;

	/*��ԭ����ĳһ��Χ�ڵ�ֵ�滻Ϊstr;
	����һ��ԭ��Ϊ��string& replace (size_t pos, size_t len, const string& str);*/
	s1.reserve(30);
	cout << s1.size() << " " << s1.capacity() << endl;
	cout << s2.size() << " " << s2.capacity() << endl;
	s1.swap(s2);  /*����������������ݣ�����size, capacity*/
	cout << s1.size() << " " << s1.capacity() << endl;
	cout << s2.size() << " " << s2.capacity() << endl;

	/*pop_back()  Delete last character*/
}

void operate_test()
{
	string s1("hello");
	cout << s1.c_str() << endl;  //����һ��ָ���ַ������ָ�룬��������s1����ͬ���ַ�����
	char s2[20] = { 0 };
	s1.copy(s2, 5, 0);  /*��s1�д�0��������ʼ��5���ַ�����������s2�У������ڸ������ݵ�ĩλ׷��'\0'*/
	cout << s2 << endl;

	/*
	string (1)	size_t find (const string& str, size_t pos = 0) const;
	c-string (2)	size_t find (const char* s, size_t pos = 0) const;
	buffer (3)	size_t find (const char* s, size_t pos, size_t n) const;
	character (4)	size_t find (char c, size_t pos = 0) const;
	���ַ����������������ָ�������еĵ�һ�������
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

	compare()  ����ֵ>0, ==0, <0
	*/
}

/*string::npos 
  static const size_t npos = -1;  �޷����������ֵ*/


/*
Non-member function overloads
string opreator+(...)
void swap (string& x, string& y);
istream& operator>> (istream& is, string& str);
ostream& operator<< (ostream& os, const string& str);

(1)
istream& getline (istream& is, string& str, char delim);  ����delim�Ż����
(2)
istream& getline (istream& is, string& str);
��is����ȡ�ַ�������洢��str�У�ֱ���ҵ��ָ���delim(��(2)�Ļ����ַ�'\n')
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