/*
两个派生类继承同一个基类而又有某个类同时继承者两个派生类, 这种继承被称为菱形继承, 或者钻石型继承.

                        动物
                          |
             |-------------------------|
            羊                         驼
            |--------------------------|
                          |
                        羊驼

菱形继承带来的问题:
1. 羊继承了动物的数据和函数, 鸵同样继承了动物的数据和函数, 当羊驼调用函数或者数据时, 就会产生二义性;
2. 羊驼继承自动物的函数和数据继承了两份，其实这份数据只需要一份就可以.

解决方法: 使用虚继承


*/

#include <iostream>
using namespace std;

//动物类
class Animal{
public:
	int m_Age;
};

//继承时加virtual继承, 那么Animal称为 虚基类
//羊类
class Sheep : virtual public Animal{

};

//驼类
class Tuo : virtual public Animal{

};

//羊驼
class SheepTuo : public Sheep, public Tuo{

};

void test01()
{
    SheepTuo st;
    st.Sheep::m_Age = 10;
    st.Tuo::m_Age = 20;

    cout << "Sheep::m_Age = " << st.Sheep::m_Age << endl;
    cout << "Tuo::m_Age = " << st.Tuo::m_Age << endl;
    cout << "SheepTuo::m_age = " << st.m_Age << endl;

    //当发生虚继承后, Sheep和Tuo类中继承了一个 vbptr指针(虚基类指针), 指向的是一个虚基类表vbtable
    //虚基类表中记录了偏移量, vbptr + 偏移量 可以找到唯一的一个 m_Age
}

int main()
{
    test01();

    return EXIT_SUCCESS;
}