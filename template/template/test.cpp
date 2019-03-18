#include <iostream>

using namespace std;

/*
	������ģ�������
	��һ������(������/�����/�ַ���������)��Ϊ�ࣨ������ģ��Ĳ�����
	��ģ���п��԰Ѹò�������������ʹ�ã�
	�����ڱ���׶ξ���ȷ�����
*/
template<class T, size_t sz = 10>
class Array
{
public:
	Array()
		:size(sz)
	{}
private:
	T arr[sz];
	size_t size;
};

int main()
{
	Array<int, 100> arr;
	return 0;
}


template<class T>
bool isEqual(T& left, T& right)
{
	return left == right;
}
/*
	����ģ���ػ���
	template<>
	������<�ػ�����>(�β����ͱ�����ػ�������ͬ)
*/
//�ַ����Ƚ�Ӧ�ð�ASCIIֵ��һ�Ƚϣ������Ե�ַ�Ƚ�
template<>
bool isEqual<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) == 0)
		return true;
	else
		return false;
}


/*
	��ģ���ػ���
	ȫ�ػ�����ģ������б������в�����ȷ����
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<>
class Data<int, char>
{
public:
	Data()
	{
		cout << "Data<int, char>" << endl;
	}
private:
	int a;
	char b;
};

int main()
{
	Data<int, char> d1;
	Data<int, int> d2;
	return 0;
}


/*
	ƫ�ػ���
	1.�����ػ�����ģ�������һ���ֲ����ػ�
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1>
class Data<T1, int>
{
public:
	Data()
	{
		cout << "Data<T1, int>" << endl;
	}
private:
	T1 a;
	int b;
};

int main()
{
	Data<int, int> d1;
	Data<int, char> d2;
	return 0;
}


/*
	ƫ�ػ���
	2.��������һ��������
*/
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1, class T2>
//��������ƫ�ػ�Ϊָ������
class Data<T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}
private:
	T1 a;
	T2 b;
};

template<class T1, class T2>
//��������ƫ�ػ�Ϊ��������
class Data<T1&, T2&>
{
public:
	Data(const T1& x, const T2& y)
		:a(x)
		, b(y)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1& a;
	const T2& b;
};

int main()
{
	Data<int, int> d1;
	Data<int*, int*> d2;
	Data<int&, int&> d3(1, 2);
	return 0;
}


int main()
{
	int a = 1;
	//��ȡ����������
	cout << typeid(a).name() << endl;
	return 0;
}
/*
	������ȡ
*/
