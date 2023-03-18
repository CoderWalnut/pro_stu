#include<iostream>
using namespace std;
/*
1. 编译器会给一个类 至少添加3个函数: 无参构造(空实现); 析构函数(空实现); 
	拷贝构造(同一种类, 将旧对象中所有的值拷贝赋值给新的对象); 
	普通有参构造函数只有自己提供, 编译器不会提供

2. 无参构造、析构、拷贝构造，只要自己提供了，编译器就不会再提供

3. 提供了 无参构造 会屏蔽 编译器提供的无参构造, 无法屏蔽编译器提供的拷贝构造
	
4. 提供了 普通有参构造 会屏蔽 编译器提供的无参构造函数, 无法屏蔽编译器提供的拷贝构造
	此时若没有提供无参构造函数, 再调用无参构造会报错
	
5. 提供了 拷贝构造 会屏蔽 编译器提供的无参构造和拷贝构造 
	此时若没有提供无参构造函数, 再调用无参构造会报错
*/

class Person
{
public:
/*
	Person()
	{
		cout << "无参构造函数调用" << endl;
	}
*/
/*
	Person(int age)
	{
		m_Age = age;
		cout << "普通有参构造函数调用" << endl;
	}
*/
/*
	Person(const Person &p)
	{
		m_Age = p.m_Age;
		cout << "拷贝构造函数调用" << endl;
	}
*/
	~Person()
	{
		cout << "析构函数调用" << endl;
	}

	int m_Age = 20;
	int m_Num = 5527;
	char name[50] = "hahaha"
};

void test01()
{
	//Person p1;
	
	//Person p1(30);

	//Person p2(p1);

	cout << "p2的年龄为: " << p2.m_Age << endl;
	cout << "p2的学号为: " << p2.m_Num << endl;
	cout << "p2的姓名为: " << p2.name << endl;
}


int main()
{
	test01();

	return EXIT_SUCCESS;
}