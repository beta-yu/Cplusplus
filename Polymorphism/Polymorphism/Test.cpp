#include <iostream>
using namespace std;

//class Base {
//public:
//	virtual void func1() { cout << "Base::func1" << endl; }
//	virtual void func2() { cout << "Base::func2" << endl; }
//private:
//	int a;
//};
//class Derive :public Base {
//public:
//	virtual void func1() { cout << "Derive::func1" << endl; }
//	virtual void func3() { cout << "Derive::func3" << endl; }
//	virtual void func4() { cout << "Derive::func4" << endl; }
//private:
//	int b;
//};
//
//typedef void(*pFunc) (); //对应func()
//
//void PrintVTable(pFunc* vtable)
//{
//	while (*vtable != nullptr) //虚表最后一项为nullptr
//	{
//		printf("%p -> ", *vtable);
//		(*vtable)();
//		++vtable;
//	}
//}
//
//void Test()
//{
//	Base b;
//	Derive s;
//	Base* ptr1 = &b;
//	Base* ptr2 = &s;
//	//将对象指针强转为int*，再解引用（只看其前四个字节），
//	//拿到虚表的首地址（因虚表内存储函数指针，所以该指针应为指向函数指针的指针,强转为pFunc*）
//	pFunc* pvtable1 = (pFunc*)(*((int*)ptr1));
//	PrintVTable(pvtable1);
//	pFunc* pvtable2 = (pFunc*)(*((int*)ptr2));
//	PrintVTable(pvtable2);
//}

//class A
//{};
//class B : public A
//{};

//class Base {
//public:
//	virtual void func1()
//	{
//		cout << "Base::func1()" << endl;
//	}
//	virtual void func2()
//	{
//		cout << "Base::func2()" << endl;
//	}
//	void func3()
//	{
//		cout << "Base::func3()" << endl;
//	}
//};
//class Derive :public Base {
//public:
//	virtual void func1() override
//	{
//		cout << "Derive::func1()" << endl;
//	}
//	virtual void func4()
//	{
//		cout << "Derive::func4()" << endl;
//	}
//private:
//	int a;
//};

//void Test()
//{
//	Base b;
//	Derive d;
//
//	pFunc* pvftab = (pFunc*)(*(int*)&d);
//	PrintVTable(pvftab);
//}
//
//class Base {
//public:
//	virtual void func()
//	{
//		cout << "Base::func()" << endl;
//	}
//};
//class Derive :public Base {
//public:
//	virtual void func() override
//	{
//		cout << "Derive::func()" << endl;
//	}
//private:
//	int a;
//};
//
//void Test(Base* pBase)
//{
//	pBase->func();
//	pBase->Base::func(); //为什么可以调到？不是已经覆盖掉了吗？会去虚表里找函数地址吗？
//}

class Base1
{
public:
	virtual void func1(){ cout << "Base1:func1()" << endl; }
	virtual void func2(){ cout << "Base1:func2()" << endl; }
private:
	int b1;
};

class Base2
{
public:
	virtual void func1(){ cout << "Base2:func1()" << endl; }
	virtual void func2(){ cout << "Base2:func2()" << endl; }
private:
	int b2;
};

class Derive :public Base1, public Base2
{
public:
	virtual void func1(){ cout << "Derive:func1()" << endl; }
	virtual void func3(){ cout << "Derive:func3()" << endl; }
private:
	int d1;
};

typedef void(*pFunc) (); //对应func()

void PrintVTable(pFunc* vtable)
{
	while (*vtable != nullptr) //虚表最后一项为nullptr
	{
		printf("%p -> ", *vtable);
		(*vtable)();
		++vtable;
	}
}

int main()
{
	//Base b;
	//Derive d;
	////Test(&b);
	////Test(&d);
	//Test();
	Derive d;
	pFunc* pvtable1 = (pFunc*)(*(int*)&d);
	cout << "vtable1:" << endl;
	PrintVTable(pvtable1);
	pFunc* pvtable2 = (pFunc*)(*(int*)((char*)(int*)&d + sizeof(Base1))); 
	//(char*)(int*)&d 在虚表1指针的地址的基础上，
	//((char*)(int*)&d + sizeof(Base1)) 先转化为char*，再往后加一个Base1的大小，得到虚表2指针的首地址处，
	//(int*)((char*)(int*)&d + sizeof(Base1)) 再强转为int*，拿到虚表2指针的地址，
	//解引用拿到虚表2指针
	cout << "vtable2:" << endl;
	PrintVTable(pvtable2);
	return 0;
}