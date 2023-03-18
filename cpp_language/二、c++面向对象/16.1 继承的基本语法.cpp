/*
继承机制可以利用已有的数据类型来定义新的数据类型, 新的类不仅拥有旧类的成员, 还拥有新定义的成员;
一个 B 类继承于 A 类, 或称从类 A 派生类 B, 这样的话, 类 A 成为基类(父类), 类 B 成为派生类(子类);
派生类中的成员, 包含两大部分: 一类是从基类继承过来的, 一类是自己增加的成员, 从基类继承过过来的表现其共性, 而新增的成员体现了其个性.

派生类定义格式：
class 派生类名 : 继承方式 基类名{
    //派生类新增的成员变量和成员函数
}

三种继承方式:
    public 公有继承; protected 保护继承; private 私有继承;

从继承源上分:
    单继承: 指每个派生类只直接继承了一个基类的特征
    多继承: 指多个基类派生出一个派生类的继承关系, 多继承的派生类直接继承了不止一个基类的特征

派生类继承基类, 派生类拥有基类中全部成员变量和成员函数(除了构造和析构), 
但是在派生类中, 继承的成员并不一定能直接访问，不同的继承方式会导致不同的访问权限, 派生类的访问权限规则如下:

公有派生:
    基类属性          公有   保护  私有
    派生类对基类权限  公有   保护  不能访问     

保护派生:
    基类属性         公有   保护  私有
    派生类对基类权限  保护   保护  不能访问

私有有派生:
    基类属性         公有   保护  私有
    派生类对基类权限  私有   私有  不能访问

不是所有的函数都能自动从基类继承到派生类中: 
    构造函数和析构函数不能被继承，必须为每一个特定的派生类分别创建;
    operator= 不能被继承;
    在继承的过程中, 如果没有创建这些函数, 编译器会自动生成它们.
*/
#include <iostream>
using namespace std;

class A{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};

//可切换不同的继承方式来验证继承特性
class B : public A{
public:
void PrintB()
{
    cout << m_A << endl;
    cout << m_B << endl;
    cout << m_C << endl;
}
};

class SubB : public B{
public:
void PrintSubB()
{
    cout << m_A << endl;
    cout << m_B << endl;
    cout << m_C << endl;
}
};

int main()
{
    B b;
    b.PrintB()
    cout << b.m_A << endl;
    cout << b.m_B << endl;
    cout << b.m_C << endl;

    SubB subb;
    subb.PrintSubB();
    cout << subb.m_A << endl;
    cout << subb.m_B << endl;
    cout << subb.m_C << endl;

    return EXIT_SUCCESS;
}