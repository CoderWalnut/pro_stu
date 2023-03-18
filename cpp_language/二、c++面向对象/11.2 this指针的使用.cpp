/*
c++的数据和操作也是分开存储, 并且每一个非内联成员函数只会诞生一份函数实例, 多个同类型的对象会共用一块代码;
那么问题是: 这一块代码是如何区分那个对象调用自己的呢?
	c++通过提供特殊的对象指针, this 指针, 解决上述问题; this 指针指向被调用的成员函数所属的对象;
	c++规定, this 指针是隐含在每个类的非静态成员函数中的一种指针; 当一个对象被创建后, 它的每一个非静态成员函数都含有一个系统自动生成的隐含指
针 this, 用以保存这个对象的地址, 虽然我们没有写上 this 指针, 编译器在编译的时候也是会加上的.
	因此 this 也称为"指向本对象的指针", this 指针并不是对象的一部分, 不会影响 sizeof(对象)的结果, 成员函数通过 this 指针即可知道操作的是那个对象的数据; 
	this 指针无需定义, 直接使用即可. 
	注意: 静态成员函数内部没有 this 指针, 静态成员函数不能操作非静态成员变量.

this指针的使用:
	当形参和成员变量同名时, 可用 this 指针来区分;
	在类的非静态成员函数中返回对象本身, 可使用 return *this;
*/

#include<iostream>
using namespace std;

class Person
{
public:
Person(int age)
{
	//age = age; //输出错误
	this->age = age;
}

bool compareAge(Person &p)
{
	if (this->age == p.age)
	{
		return true;
	}
	return false;
}

Person &personAddPerson(Person &p)
{
	this->age += p.age;
	return *this;
}

	int age;
};

int main(){
	Person p1(10);
	cout << "p1的年龄为: " << p1.age << endl;

	Person p2(10);
	bool ret = p1.compareAge(p2);
	if (ret)
		cout << "p1与p2年龄相等" << endl;

	//链式编程
	p1.personAddPerson(p2).personAddPerson(p2).personAddPerson(p2);
	cout << "p1的年龄为: " << p1.age << endl;

	return EXIT_SUCCESS;
}