**命名空间**

```c++
namespace std; //C++标准库命名空间
```

> 为避免命名与标准库中命名冲突，可定义本地的命名空间：

```C++
namespace Name
{
    //可以定义变量也可以定义函数
    int a = 10;
    int b = 20;
    int Add(int a, int b)
    {
        return a+b;
    }
}
```

> 一个命名空间可以嵌套一个命名空间
>
> 同一个工程内，允许定义多个相同名称的命名空间，编译器最后会将其合成为一个命名空间

> 命名空间的使用方式：

```C++
int main()
{
    printf("%d\n", Name::a); //1.加命名空间名称及作用域限定符
    return 0;
}

using namespace Name;  //2.将命名空间引入
int main()
{
    int x = 10, y = 5;
    int c = Add(x, y);
    return 0;
}

using Name::a;     //3.使用using将命名空间中要用到成员引入
using Name::b;
int main()
{
    printf("%d %d\n", a, b);
}
```



> 使用C++输入输出更加方便，不用加数据格式控制



**函数重载**

> C++允许在同一作用域内，出现多个函数名相同，但参数**类型**或**顺序**或**个数**必须不同的函数，用来实现功能类似但参数有差异的多个函数

```C++
int Add(int a, int b)
{
    return a+b;
}

short Add(short a, short b)
{
    return a+b;
}
/*上述两个函数由于参数类型不同，属于函数重载*/

int Add(int a, int b)
{
    return a+b;
}

short Add(int a, int b)
{
    return a+b;
}
/*由于参数无任何差异，所以上述两个函数不属于函数重载*/
```

**名字修饰 (name Mangling)**

> 在C/C++中，程序运行需要经历**预处理、编译、汇编、链接**几个阶段
>
> 名字修饰一种在编译过程中，将**函数、变量名称**重新改编的机制，编译器为了区分各个函数，通过某种算法将函数名重新修饰为一个全局唯一的名称。
>
> C语言对函数名的修饰只是在函数名前加一个下划线 '_'。
>
> 由于C++要支持函数重载、命名空间等复杂情况，因此C++的名字修饰会变得复杂，不同编译器的修饰规则可能会有差异 

```C++
int Add(int a, int b);
double Add(double a, double b);
int main()
{
	Add(1, 2);
	Add(1.0, 2.0);
	return 0;
}
```

> 执行上面的程序，由于只有函数声明没有具体实现，因此执行时报错，我们可以看到编译器对两个重载了的函数函数名的修饰：
>
> ![1547452626072](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547452626072.png)
>
> ?Add@@YAHHH@Z  和  ?Add@@YANNN@Z  分别是对两个函数名的修饰结果
>
> 被修饰过的函数名包含函数的名字及参数类型及参数个数，因此C++可以实现函数重载，同名函数只要函数参数类型或个数或顺序不同就会被修饰为不同的名称，从而在链接时被指向不同的函数。
>
> 也因此C语言不支持函数重载（由于命名修饰规则不能区分同名函数）



**extern "C"**

> 有时，在C++工程中定义的函数，若需要用C来调用，因为使用C++的规则进行编译的，用C不能调用执行，因此需要在函数前加extern "C"，意思是告诉编译器使用C的规则进行编译，这样就可以使用C来调用执行该函数，C++向下兼容是支持C的规则的，用C的规则编译的程序C++可以调用执行。

```C++
extern "C" int Add(int a, int b);
int main()
{
	Add(1, 2);
	return 0;
}
```

> error LNK2019: 无法解析的外部符号 _Add，该符号在函数 _main 中被引用
>
> 由_Add的命名修饰规则可以看出该函数使用了C的规则进行编译。



**引用**

> **引用不是新定义了一个变量，只是给变量起了一个别名**，编译器不会为引用开辟一块内存空间，它和被引用变量**占用同一块内存空间**。

```c++
int main()
{
	int a = 0;
	int& ra = a;  //定义引用类型,引用类型必须和引用实体的类型相同
	printf("%d~%d\n", a, ra);
	printf("%p~%p\n", &a, &ra);
}
```

![1547454247574](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547454247574.png)

> 引用在定义时必须初始化；
>
> 一个变量可以有多个引用；
>
> 引用一个实体后，不能再引用其他实体

**常引用**

```C++
int main()
{
	const int a = 0;
	//int& ra = a;   //编译时出错，使用int&引用a,const限定符丢失 
	const int& ra = a;
	//int& b = 10;   //出错，10为常量
	const int& b = 10;
	double c = 3.14;
	//int& rc = c;   //出错，rc与c类型不同
	const int& rc = c;    //编译器到底做了什么？？？
}
```

**引用的使用场景**

```C++
/*做函数参数*/
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

/*做返回值*/
int& Func(int& a)
{
	a += 10;
	return a;
}

/*下面函数会出错，因为在Func函数结束后，变量c已不存在，返回c的引用，访问不到c*/
int& Func(int a, int b)
{
	int c = a + b;
	return c;
}

int main()
{
	int a = 10;
	int b = 2;
	printf("%d\n", Func(a, b));
	return 0;
}
```

> 如果以引用类型返回，返回值的生命周期必须不受函数的限制（不会因为函数结束而被销毁，比函数的生命周期长）

> 用值作为函数参数和返回值时，在传参和返回时，函数**不是直接传递实参和返回变量本身**（局部变量也不可能返回其本身），而传递的是实参或者变量的**一份临时拷贝**，因此用值作为参数或者返回值类型，效率是非常低的。

> **引用和指针在传参和作为返回值类型时效率几乎相同**

**引用和指针的区别**

> 在**语法概念**上，引用是起了一个别名，没有独立的空间，和其引用实体共用同一块空间，拥有相同的地址
>
> 但是在**底层实现**上，引用实际上是有空间开销的，因为引用在底层还是用指针方式实现的。

```c++
int main()
{
	int a = 1;
	int& ra = a;
	ra = 10;

	int b = 2;
	int *pb = &b;
	*pb = 20;

	return 0;
}
```

![1547457499414](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547457499414.png)

>通过查看汇编代码可以发现，引用和指针在底层实现上完全相同。

> **引用和指针的区别**
>
> 1. 引用在定义时必须初始化，指针则没有要求
> 2. 引用一旦引用一个实体后就不能引用其他实体，指针则可以改变其赋值
> 3. 有NULL指针没有空引用
> 4. 在sizeof()中，引用结果为引用实体的大小，指针则为地址空间所占的字节个数。
> 5. 引用自加1即引用的实体加1，指针加1是指针向后偏移一个指向类型的大小
> 6. 有多级指针，但是没有多级引用
> 7. 访问实现方式不同，指针需要显示解引用，引用由编译器自己处理（引用底层也是指针实现）
> 8. 引用比指针使用起来相对更安全



**内联函数**

> 以inline修饰的函数，编译器会在调用内联函数处展开，没有函数压栈的开销，可以提升程序运行的效率

```C++
int Add(int a, int b)
{
	return a + b;
}

int main()
{
	int ret = Add(1, 2);
	return 0;
}
```

![1547459108400](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547459108400.png)

>如果将上面Add函数加上inline修饰为内联函数，则不会主函数中调用它(call)，而是直接展开，执行

```C++
inline int Add(int a, int b)
{
	return a + b;
}

int main()
{
	int ret = Add(1, 2);
	return 0;
}
```

![1547459185023](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547459185023.png)

**inline特性**

> 1. inline是一种**以空间换时间**的做法，因此代码很长或者包含递归或循环的函数不适宜作为内联函数
> 2. **inline对编译器而言只是一个建议，**编译器会自动优化，对于一些用inline修饰的的复杂函数，编译器会忽略掉内联
> 3. 内联函数不建议生命和建议分离，因为内联函数被展开，没有函数地址，链接时就会找不到。

> **面试题：宏的优缺点**
>
> 优点：
>
> 1. 增强代码的复用性
> 2. 提高性能
>
> 缺点：
>
> 1. 宏不方便调试（在预编译阶段进行了替换）
> 2. 导致代码的可读性差，可维护性差，容易误用
> 3. 没有类型安全检查
>
> C++中有哪些技术替换宏？
>
> 1. 常量定义：使用const
> 2. 函数定义：换用inline函数



**auto关键字(C++11)**

> C++11中，auto作为一个新的类型指示符来指示编译器，auto声明的变量必须在编译时期推导而得

```C++
int main()
{
	int a = 1;
	auto b = a;
	auto c = 'c';
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;

	return 0;
}
/*auto定义变量时必须进行初始化*/
```

![1547460317629](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547460317629.png)

> **auto并不是一种类型，而是一个类型声明时的占位符，编译器会在编译时将auto替换为变量实际的类型**



**auto使用细则**

>1. **auto与指针和引用结合起来使用**
>
>   用auto声明指针类型时，auto和auto*没有任何区别，但用auto声明引用类型时必须加&，否则不是引用类型
>
>   ```c++
>   int main()
>   {
>   	int a = 1;
>   	auto b = &a;
>   	auto* c = &a;
>   	auto& d = a;
>   	cout << typeid(b).name() << endl;
>   	cout << typeid(c).name() << endl;
>   	cout << typeid(d).name() << endl;
>   
>   	return 0;
>   }
>   ```
>
>   ![1547460944914](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547460944914.png)
>
>2. **在同一行定义多个变量**
>
>   当在同一行声明多个变量时，这些变量必须是同一类型的，编译器只会对第一个的类型进行推导，然后用推到出的类型声明其他变量
>
>   ```c++
>   int main()
>   {
>   	auto a = 1, b = 2;
>   	auto c = 3, d = 4.0;  //报错：在声明符列表中，“auto”必须始终推导为同一类型
>   	return 0;
>   }
>   ```
>
>3. **auto不能推导的场景**
>
>   1. **auto不能作为函数参数的类型**
>
>      ```c++
>      void autoTest(auto a)  //参数不能为包含“auto”的类型,编译器无法对a的实际类型进行推导
>      {
>      
>      }
>      ```
>
>   2. **auto不能直接用来声明数组**
>
>      ```C++
>      int main()
>      {
>      	int a[] = { 1, 2, 3 };
>      	auto b[3] = a;  //报错：数组的元素类型不能是包含“auto”的类型
>      	return 0;
>      }
>      ```
>
>   3. C++ 11只保留了auto作为类型指示符的用法
>
>   4. auto实际中最常用在：基于范围的for循环、lambda表达式



**基于范围的for循环(C++11)**

> C++98中遍历一个数组会这样写：
>
> ```C++
> void TestFor()
> {
>     int arr[] = {1,2,3,4,5,6};
>     for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
>         arr[i] = 0;
>     for(int *p = arr; p<arr+sizeof(arr)/sizeof(arr[0]); ++p)
>         *p = 1;
> }
> ```
>
> 对于有范围的集合，有程序员来限定集合可访问的范围是多余的，而且很容易犯错
>
> C++11中引入基于范围的for循环，for(用于迭代的变量 : 被迭代的范围)
>
> ```C++
> void TestFor()
> {
> 	int arr[] = { 1, 2, 3, 4, 5, 6 };
> 	for (auto& x : arr)
> 		x *= 2;
> 
> 	for (auto x : arr)
> 		cout << x << endl;
> }
> ```
>
> **与普通for循环相同，可以用continue来结束本次循环，也可以使用break来跳出整个循环**

**范围for的使用条件**

> 1. **for循环迭代的范围必须是确定的**
>
>    ```C++
>    void TestFor(int arr[])
>    {
>    	for (auto x : arr)  /*报错：未找到类型“int []”的可调用“begin”函数;未找到类型“int []”的可调用“end”函数;数组作为参数传递时已经退化为指针，无法确定范围*/
>    		//...
>    }
>    ```
>
> 2. **迭代的对象要实现++和==操作**



**指针空值nullptr（C++11）**

> NULL实际是一个宏，在stddef.h有如下定义：
>
> ```C++
> #ifndef NULL
> #ifdef __cplusplus
> #define NULL 0
> #else
> #define NULL ((void *)0)
> #endif
> #endif
> ```
>
> 可以看到，NULL可能被定义为字面常量0，也可能被定义为无类型的(void *)常量，在使用空指针时，不可避免的会遇到一些麻烦，例如：
>
> ```C++
> void F(int)
> {
> 	cout << "F(int)" << endl;
> }
> void F(int *)
> {
> 	cout << "F(int *)" << endl;
> }
> int main()
> {
> 	F(0);
> 	F(NULL);
> 	F((int*)(NULL));
> 	return 0;
> }
> ```
>
> ![1547463803200](C:\Users\QIYU\AppData\Roaming\Typora\typora-user-images\1547463803200.png)
>
> NULL被定义为0
>
> 而nullptr代表一个指针空值常量
>
> nullptr是有类型的，其类型为nullptr_t