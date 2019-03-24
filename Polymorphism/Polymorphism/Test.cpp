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

void Test()
{
	Base b;
	Derive s;
	Base* ptr1 = &b;
	Base* ptr2 = &s;
	//������ָ��ǿתΪint*���ٽ����ã�ֻ����ǰ�ĸ��ֽڣ���
	//�õ������׵�ַ��������ڴ洢����ָ�룬���Ը�ָ��ӦΪָ����ָ���ָ��(pvtable)��
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