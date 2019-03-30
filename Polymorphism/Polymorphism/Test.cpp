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
//typedef void(*pFunc) (); //��Ӧfunc()
//
//void PrintVTable(pFunc* vtable)
//{
//	while (*vtable != nullptr) //������һ��Ϊnullptr
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
//	//������ָ��ǿתΪint*���ٽ����ã�ֻ����ǰ�ĸ��ֽڣ���
//	//�õ������׵�ַ��������ڴ洢����ָ�룬���Ը�ָ��ӦΪָ����ָ���ָ��,ǿתΪpFunc*��
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
//	pBase->Base::func(); //Ϊʲô���Ե����������Ѿ����ǵ����𣿻�ȥ������Һ�����ַ��
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

typedef void(*pFunc) (); //��Ӧfunc()

void PrintVTable(pFunc* vtable)
{
	while (*vtable != nullptr) //������һ��Ϊnullptr
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
	//(char*)(int*)&d �����1ָ��ĵ�ַ�Ļ����ϣ�
	//((char*)(int*)&d + sizeof(Base1)) ��ת��Ϊchar*���������һ��Base1�Ĵ�С���õ����2ָ����׵�ַ����
	//(int*)((char*)(int*)&d + sizeof(Base1)) ��ǿתΪint*���õ����2ָ��ĵ�ַ��
	//�������õ����2ָ��
	cout << "vtable2:" << endl;
	PrintVTable(pvtable2);
	return 0;
}