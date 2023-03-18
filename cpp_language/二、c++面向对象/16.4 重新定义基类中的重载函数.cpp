/*
Derived1 重定义 Base 类的myfunc函数, der1可访问func1及func1重载版本的函数, 加 Base:: 作用域可访问Base类中的myfunc函数;
Derived2 通过改变函数参数列表的方式重定义了基类的func1函数, 则从基类中继承来的func1函数其他重载版本被隐藏, 可用作用域显示的调用;
Derived3 通过改变函数返回类型的方式重定义了基类的func1函数, 从基类继承来的func1及func1重载版本将被隐藏, 可用作用域显示的调用.
*/

#include <iostream>
using namespace std;

class Base{
public:
void func1()
{
    cout << "Base::void func1()" << endl;
}

void func1(int param)
{
    cout << "Base::void fun1(int param)" << endl;
}

void myfunc()
{
    cout << "Base::void myfunc()" << endl;
}
};

class Derived1 : public Base{
public:
void myfunc()
{
    cout << "Derived1::void myfunc()" << endl;
}
};

class Derived2 : public Base{
public:
void func1(int param1, int param2)
{
    cout << "Derived2::void func1(int param1, int param2)" << endl;
}
};

class Derived3 : public Base{
public:
int func1(int param)
{
    cout << "Derived3::int func1(int param)" << endl;
    return 0;
}
};

int main()
{
    // Derived1 der1;
    // der1.func1();
    // der1.func1(20);
    // der1.myfunc();
    // der1.Base::myfunc();
    // cout << "=======================" << endl;

    // Derived2 der2;
    // der2.Base::func1();
    // der2.Base::func1(20);
    // der2.func1(10,20);
    // der2.myfunc();
    // cout << "=======================" << endl;

    // Derived3 der3;
    // der3.Base::func1();
    // der3.Base::func1(10);
    // der3.func1(20);
    // der3.myfunc();

    return EXIT_SUCCESS;
}