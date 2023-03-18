/*
二、const 修饰对象(常对象)
    1.常对象只能调用 常函数;
    2.常对象可访问 const 或 非const 成员变量但不能修改, 若成员变量用 mutable 修饰则可修改.
*/

#include <iostream>
#include <string>
using namespace std;

class Person{
public:
Person()
{
    this->mAge = 0;
    this->mID = 0;
}

void ChangePerson() const
{
    //mAge = 100;
    mID = 100;

    cout << "Age: " << mAge << " ID: " << mID << endl;
}

void ShowPerson()
{
    this->mAge = 1000;

    cout << "ID:" << this->mID << " Age:" << this->mAge << endl;
}

public:
    int mAge;
    mutable int mID;
};

int main()
{
    const Person person;

    //1. 可访问数据成员
    cout << "Age: " << person.mAge << " ID: " << person.mID << endl;

    // person.mAge = 300; //不可修改
    person.mID = 1001; //但是可以修改 mutable 修饰的成员变量

    //2. 只能访问 const 修饰的函数
    // person.ShowPerson();
    person.ChangePerson();

    return EXIT_SUCCESS;
}