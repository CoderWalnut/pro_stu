#include <iostream>
using namespace std;

class Person{
//全局函数做友元
friend ostream &operator<<(ostream &cout, Person &person);

private:
    int m_id;
    int m_age;

public:
    Person(int id, int age) : m_id(id), m_age(age){};
/*
    void operator<<(ostream &cout)  //p.operator<<(cout)  p<<cout
    {

    }
*/
};

//全局函数实现左移运算符的重载; 
//不建议使用成员函数实现左移运算符重载, 无法实现让cout在左侧
ostream &operator<<(ostream &cout, Person &person)
{
    cout << "ID: " << person.m_id << " Age: " << person.m_age;

    return cout;
}

int main()
{
    Person person(110, 25);

    cout << person << endl;

    return EXIT_SUCCESS;
}