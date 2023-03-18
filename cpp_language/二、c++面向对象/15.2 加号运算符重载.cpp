#include <iostream>
using namespace std;

class Person{

//friend Person operator+(Person &p1, Person &p2);
//friend Person operator+(Person &p, int num);

//private:
public:
    int m_A; int m_B;

public:
Person() {}
Person(int a, int b) : m_A(a), m_B(b){}
/*
//一、成员函数实现加号运算符重载
Person operator+(Person &p)
{
    Person tmp;
    tmp.m_A = this->m_A + p.m_A;
    tmp.m_B = this->m_B + p.m_B;
    return tmp;
}
*/
};

//二、全局函数实现加号运算符重载
Person operator+(Person &p1, Person &p2)
{
    Person tmp;
    tmp.m_A = p1.m_A + p2.m_A;
    tmp.m_B = p1.m_B + p2.m_B;
    return tmp;
}

//三、运算符重载可以发生函数重载
Person operator+(Person &p, int num)
{
    Person tmp;
    tmp.m_A = p.m_A + num;
    tmp.m_B = p.m_B + num;
    return tmp;
}

int main()
{
    Person p1(10, 10);
    Person p2(20, 20);

    //Person p3 = p1.operator+(p2);       //成员运算符重载调用本质
    //Person p3 = operator+(p1, p2);      //全局运算符重载调用本质
    Person p3 = p1 + p2;                //两者都可简写

    //p3 = p3 + 10;

    cout << "p3.m_A = " << p3.m_A << " p3.m_B = " << p3.m_B << endl;

    return EXIT_SUCCESS;
}