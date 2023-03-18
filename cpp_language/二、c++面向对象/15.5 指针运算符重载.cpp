#include <iostream>
using namespace std;

class Person{
public:
Person(int age)
{
    cout << "Person的有参构造调用" << endl;
    this->m_Age = age;
}

void showAge()
{
    cout << "年龄为: " << this->m_Age << endl;
}

~Person()
{
    cout << "Person的析构调用" << endl;
}

    int m_Age;
};


class SmartPoint{
private:
    Person *m_person;

public:
SmartPoint(Person *person)
{
    this->m_person = person;
}

//重载->运算符
Person *operator->()
{
    return this->m_person;
}

//重载 * 运算符
Person &operator*()
{
    return *m_person;
}

~SmartPoint()
{
    if(this->m_person)
    {
        delete this->m_person;
        this->m_person = NULL;
    }
}
};

int main()
{
/*
    Person *p = new Person(18);
    p->showAge();
    (*p).showAge();
    delete p;
*/

    SmartPoint sp(new Person(18));
    sp->showAge();         //本质sp->->showAge(); 编译器简化为 sp->showAge();
    (*sp).showAge();

    return EXIT_SUCCESS;
}