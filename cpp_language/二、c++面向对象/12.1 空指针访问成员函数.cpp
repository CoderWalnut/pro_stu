/*
1.如果成员函数中没有用到this指针, 可以用空指针调用成员函数;
2.如果成员函数中用到this指针, 不可以用空指针调用成员函数, 会出问题, 可在函数最开始对this进行判断，防止程序崩溃
*/

#include <iostream>
using namespace std;

class Person
{
public:

void showClass()
{
	cout << "class Name is Person" << endl;
}

void showAge()
{

	// if (this == NULL)
	// {
	// 	return;
	// }

	//m_Age = 0;
	cout << "age = " << this->m_Age << endl;
}

	int m_Age;
};

int main()
{
	Person * p = NULL;

	p->showClass(); //可以调用, 没有用到this指针

	// p->showAge(); //无法调用, this指针为NULL

	return EXIT_SUCCESS;
}