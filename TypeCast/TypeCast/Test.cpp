#include <iostream>

using namespace std;

////C
//void Test()
//{
//	double a = 1.5;
//	int b = a; //隐式类型转换
//	printf("%d, %d\n", b, a); //b = 1, a = 0(看a的前四个字节)
//
//	int* p = &b;
//	int addr = (int)p; //显示的强制类型转换
//	printf("%d\n", addr);
//}


//C++为了增加类型转换的可视性，引入了四种类型转换操作符
//static_cast
//reinterpret_cast
//const_cast
//dynamic_cast

//
////static_cast
////1.用于基类和派生类之间指针和引用的转换
////2.相关类型之间的转换（char/int/double/...）
////3.将void*转换为目标类型的指针
////编译器隐式进行的任何类型转换都可用static_cast，且都建议使用static_cast标明
////但不能用于两个不相关类型的转换(int* --> int)
//class A
//{
//public:
//	int a = 1;
//};
//
//class B : public A
//{
//public:
//	int b = 2;
//};
//
//void Test()
//{
//	//int a = 1;
//	//double b = static_cast<int>(a);
//	//cout << b << endl;
//
//	A a;
//	B b;
//	A* pa = &a;
//	B* pb = static_cast<B*>(&a); //危险操作，无警告
//	pa = static_cast<B*>(&b);
//	cout << pb->b << endl; //越界操作
//
//	//int a = 1;
//	//int *pa = static_cast<int*>(a); //error：类型转换无效
//}


////reinterpret_cast
////对操作数的位模式进行重新解释
////用于将一种类型转换为另一种可能就不相干的类型
////可以把整型转为指针，指针转为数组
////危险
//void Test()
//{
//	int a = 1;
//	int *pa = reinterpret_cast<int*>(a);
//}

//
////dynamic_cast
////用于将父类对象的指针（引用）转换为子类对象的指针（引用）
////对于将子类对象的指针转换为父类对象的指针（下行转换），dynamic_cast是安全的，
////当不能成功转换时，返回NULL
////dynamic_cast只能用于含有虚函数的类，因为dynamic_cast是运行时类型检查，
////需要运行时类型信息，该信息存储在虚函数表中
////
////RTTI(运行时类型识别):typeid();dynamic_cast
//
//class A
//{
//public:
//	virtual void func(){}
//};
//class B : public A{};
//
//void Test()
//{
//	A a;
//	B b;
//	B* pa = static_cast<B*>(&a); //不进行检查
//
//	B* pb = dynamic_cast<B*>(&a); //下行转换，不安全，转换结果为NULL
//	cout << pa << endl;
//	cout << pb << endl;
//}


//const_cast
//常用于消除变量的const属性
void Test()
{
	const int a = 1;
	int* p = const_cast<int*>(&a);
	*p = 2;
	cout << *p << endl;
}

int main()
{
	Test();
	return 0;
}