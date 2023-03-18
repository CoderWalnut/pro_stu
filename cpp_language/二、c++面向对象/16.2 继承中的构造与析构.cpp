/*
1 继承中的对象模型
    子类是由父类成员叠加子类新成员而成

2 继承中构造和析构的调用原则
    子类对象在创建时会首先调用父类的构造函数, 父类构造函数执行完毕后, 才会调用子类的构造函数;
    ??? 当父类构造函数有参数时，需要在子类初始化列表(参数列表)中显示调用父类构造函数;
    析构函数调用顺序和构造函数相反, 先调用子类析构，再调用父类析构.

3 类中既有继承又定义了类, 构造和析构的调用为:
构造函数 ==>
            父类  对象成员  子类
                                <==析构函数 
*/

#include <iostream>
using namespace std;

class A{
public:
    int m_A;
    int m_B;
};

class B : public A{
public:
    int m_C;
};

class C : public B{
public:
    int m_D;
};

void test01()
{
    cout << "test01() start" << endl;
    cout << "calss A size: " << sizeof(A) << endl;  //calss A size: 8
    cout << "calss B size: " << sizeof(B) << endl;  //calss B size: 12
    cout << "calss C size: " << sizeof(C) << endl;  //calss C size: 16
    cout << "test01() end" << endl;
}


class D{
public:
D()
{
    cout << "D类构造函数" << endl;
}
~D()
{
    cout << "D类析构函数" << endl;
}
};

class E : public D{
public:
E()
{
    cout << "E类构造函数" << endl;
}
~E()
{
    cout << "E类析构函数" << endl;
}
};

class F : public E{
public:
F()
{
    cout << "F类构造函数" << endl;
}
~F()
{
    cout << "F类析构函数" << endl;
}
};

void test02()
{
    cout << "test02() start" << endl;
    F f;
    cout << "test02() end" << endl;
}

class G : public E{
public:
G()
{
    cout << "G类构造函数" << endl;
}
~G()
{
    cout << "G类析构函数" << endl;
}

public:
    F f;
};

void test03()
{
    cout << "test03() start" << endl;
    G g;
    cout << "test03() end" << endl;
}

int main()
{
    test01();
    test02();
    test03();

    return EXIT_SUCCESS;
}