/*
静态成员函数和非静态成员函数的共同点:
    1. 都可以被继承到派生类中;
    2. 如果派生类重定义一个静态成员函数, 所有在基类中的其他重载函数会被隐藏, 可加作用于调用;
    3. 如果派生类重定义基类中一个函数, 所有使用该函数名的基类版本都会被隐藏, 可加作用于调用.
*/

#include <iostream>
using namespace std;

class Base{
public:
static void func()
{
    cout << "Base::static void func()" << endl;
    cout << "Base::m_A = " << Base::m_A << endl;
}

static void func(int a)
{
    cout << "Base::static void func(int a)" << endl;
}

static int m_A;
};

int Base::m_A = 10;


class Son : public Base{
public:
static void func()
{
    cout << "Son::static void func()" << endl;
    cout << "Son::m_A = " << Son::m_A << endl;

}

static int m_A;
};

int Son::m_A = 20;

void test01()
{
    //1. 通过对象访问静态成员数据
    Son s;
    cout << "Son中的m_A = " << s.m_A << endl;
    cout << "Base中的m_A = " << s.Base::m_A << endl;

    //2. 通过类名访问静态成员数据
    cout << "Son中的m_A = " << Son::m_A << endl;
    cout << "Base中的m_A= " << Son::Base::m_A << endl;
}

void test02()
{
    //1. 通过对象访问静态成员函数
    Son s;
    s.func();
    s.Base::func();

    //2. 通过类名访问静态成员函数
    Son::func();
    //当子类重定义父类中同名成员函数, 子类的成员函数会隐藏掉父类中所有的版本, 需要加作用域调用
    Son::Base::func(1);
}

int main()
{
    test01();
    test02();

    return EXIT_SUCCESS;
}