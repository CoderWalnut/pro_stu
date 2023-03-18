#include <iostream>
#include <string.h>
using namespace std; 


class Person{

public:
    char *m_Name; int m_Age;

Person() {}

Person(const char *name, int age)
{
    m_Name = new char[strlen(name) + 1];
    strcpy(m_Name, name);
    m_Age = age;
}

//提供拷贝构造函数
Person(const Person &p)
{
    m_Name = new char[strlen(p.m_Name) + 1];
    strcpy(m_Name, p.m_Name);
    m_Age = p.m_Age;
}


//重载 = 运算符
Person &operator=(const Person &p)
{
    //先判断原来堆区是否有内容, 如果有先释放
    if(m_Name != NULL)
    {
        delete [] m_Name;
        m_Name = NULL;
    }

    m_Name = new char[strlen(p.m_Name) + 1];
    strcpy(m_Name, p.m_Name);
    m_Age = p.m_Age;

    return *this; 
}

~Person()
{
    if(m_Name != NULL)
    {
        delete [] m_Name;
        m_Name = NULL;
    }
}

};

//一、编译器默认给一个类 4 个函数: 默认构造、析构、拷贝构造(值拷贝)、operator=(值拷贝)
//二、使用编译器默认的 operator=(值拷贝), 会出现double free
//三、重载 = 运算符解决此问题
//四、提供拷贝构造函数解决拷贝构造带来的double free问题
void test01()
{
    Person p1("Tom", 18);
    Person p2("Jerry", 19);
    Person p3("Lucy", 20);

    p3 = p2 = p1;

    Person p4 = p3;

    cout << "p1.m_Age = " << p1.m_Age << " p1.m_Name = " << p1.m_Name << endl;
    cout << "p2.m_Age = " << p2.m_Age << " p2.m_Name = " << p2.m_Name << endl;
    cout << "p3.m_Age = " << p3.m_Age << " p3.m_Name = " << p3.m_Name << endl;
    cout << "p4.m_Age = " << p4.m_Age << " p4.m_Name = " << p4.m_Name << endl;
}

int main()
{
    test01();

    return EXIT_SUCCESS;
}