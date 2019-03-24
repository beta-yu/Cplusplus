#include <iostream>
using namespace std;

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
private:
	int a;
};
class Derive :public Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }
private:
	int b;
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

void Test()
{
	Base b;
	Derive s;
	Base* ptr1 = &b;
	Base* ptr2 = &s;
	//将对象指针强转为int*，再解引用（只看其前四个字节），
	//拿到虚表的首地址（因虚表内存储函数指针，所以该指针应为指向函数指针的指针(pvtable)）
	pFunc* pvtable1 = (pFunc*)(*((int*)ptr1));
	PrintVTable(pvtable1);
	pFunc* pvtable2 = (pFunc*)(*((int*)ptr2));
	PrintVTable(pvtable2);
}

int main()
{
	Test();
	return 0;
}