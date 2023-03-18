#include <iostream>
#include <string>
using namespace std;

class Person{

public:
Person(string name, int age)
{
    m_Name = name;
    m_Age = age;
}

bool operator==(Person &p)
{
    if((m_Name == p.m_Name) && (m_Age == p.m_Age))
    {
        return true;
    }
    return false;
}

bool operator!=(Person &p)
{
    if((m_Name != p.m_Name) || (m_Age != p.m_Age))
    {
        return true;
    }
    return false;
}

string m_Name;
int m_Age;
};

void test01()
{
    /* int a = 10;
    int b = 20;
    if(a == 20)
    {
        cout << "a == b" << endl;
    }
    else
    {
        cout << "a != b" << endl;
    } */

    Person p1("Tom", 18);
    Person p2("Tom", 19);
    if(p1 == p2)
    {
        cout << "p1 == p2" << endl;
    }
    else
    {
        cout << "p1 != p2" << endl;
    }

    if(p1 != p2)
    {
        cout << "p1 != p2" << endl;
    }
    else
    {
        cout << "p1 == p2" << endl;
    }
}

int main()
{
    test01();

    return EXIT_SUCCESS;
}