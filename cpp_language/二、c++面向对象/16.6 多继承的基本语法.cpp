#include <iostream>
using namespace std;

class Base1{
public:
    Base1()
    {
        m_A = 10;
    }

public:
    int m_A;
};

class Base2{
public:
    Base2()
    {
        m_A = 20;
    }

public:
    int m_A;
};

//多继承
class Son : public Base1, public Base2{
public:
    int m_C;
    int m_D;
};

void test01()
{
    cout << "sizeof(Son) = " << sizeof(Son) << endl;

    Son s;
    //当多继承的两个父类有同名成员，需要加作用域区分
    cout << s.Base1::m_A << endl;
    cout << s.Base2::m_A << endl;
}

int main()
{
    test01();

    return EXIT_SUCCESS;
}