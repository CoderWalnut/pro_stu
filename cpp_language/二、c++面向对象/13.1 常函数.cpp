/*
一、const修饰成员函数
	用 const 修饰成员函数时, const 修饰 this 指针指向的内存区域, 
	const成员函数体内可以访问但不可以修改本类中的任何成员变量, 成员变量类型符前用 mutable 修饰时, 才可以修改.
*/

#include <iostream>
using namespace std;

class Person{
public:
Person()
{
	this->mAge = 0;
	this->mID = 0;
}

//在函数括号后面加上 const 修饰, 不可修改成员变量, 除了 mutable 变量
void someOperate() const
{
	//this->mAge = 200; //mAge 不可修改
	this->mID = 10;

	cout << "ID: " << mID << " mAge: " << mAge << endl;
}

private:
	int mAge;
	mutable int mID;
};

int main(){
	Person person;
	person.someOperate();

	return EXIT_SUCCESS;
}