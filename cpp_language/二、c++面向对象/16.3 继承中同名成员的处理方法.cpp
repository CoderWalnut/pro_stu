/*
当子类成员和父类成员同名时, 子类依然从父类继承同名成员;
子类访问同名成员默认访问子类的成员(本作用域，就近原则);
在子类通过作用域::进行同名成员区分, 成员前加 父类:: 使用父类的同名成员
*/

#include <iostream>
using namespace std;

class Base{
public:
int m_Param;

public:
Base() : m_Param(0)
{}
};

class Derived : public Base{
public:
int m_Param;

public:
Derived() : m_Param(10)
{}

int &getBaseParam()
{
    return Base::m_Param;
}
};

int main()
{
    Derived der;
    cout << der.m_Param << endl;

    der.getBaseParam() = 100;
    cout << "Base::m_Param: " << der.getBaseParam() << endl;

    return EXIT_SUCCESS;
}