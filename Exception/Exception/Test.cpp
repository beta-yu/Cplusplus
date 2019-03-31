#include <iostream>
using namespace std;
#include <exception>

//double Divsion(double left, double right)
//{
//	if (right == 0)
//	{
//		throw(string("Error:Divide by 0"));
//	}
//	return left / right;
//}
//
//void test()
//{
//	int* arr = new int[100];
//	double a, b;
//	cin >> a >> b;
//	try{
//		cout << Divsion(a, b) << endl; //如果抛出异常，则arr不会被正常释放
//	}
//	catch (...)
//	{
//		cout << __LINE__ << " delete[]" << endl;
//		delete[] arr;
//		throw; //内存释放后，重新抛出
//	}
//	cout << __LINE__ << " delete[]" << endl;
//	delete[] arr;
//}
//
//int main()
//{
//	try
//	{
//		test();
//	}
//	catch (string& e)
//	{
//		cout << e.c_str() << endl;
//	}
//	catch (...)
//	{
//		cout << "unknown exception" << endl;
//	}
//	return 0;
//}

//自定义异常体系
//namespace QIYU
//{
//	class Exception
//	{
//	protected:
//		string _errmsg;
//	};
//	class SqlException : public Exception //继承基类
//	{};
//	...
//}
//
//int main()
//{
//	try{
//		抛出的一场都是派生类对象
//	}
//	catch (QIYU::Exception& e) //用基类去捕获
//	{}
//	catch (...)
//	{}
//	return 0;
//}

//C++标准库异常体系
#include <vector>
void Test()
{
	vector<int> v;
	try{
		v.reserve(1000000000); //系统内存可能不够，会抛出异常(bad allocation)

		v.at(10) = 100; //越界访问，抛出异常(invalid vector<T> subscript)
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "unknown exception" << endl;
	}
}

int main()
{
	Test();
	return 0;
}