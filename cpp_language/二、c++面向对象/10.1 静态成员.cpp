#include<iostream>
using namespace std;


class Person
{
public:
/*
一、静态成员变量
1. 静态数据成员不属于某一个对象, 编译阶段就分配了内存, 对象还未创建时就已经分配内存, 被所有同类的对象共享, 在为对象分配的空间中没有静态数据成员
2. 静态成员变量必须在类中声明, 在类外定义
3. 静态数据成员可以通过类名或对象名访问
4. 静态成员变量是有访问权限的
*/
	static int m_A; //要在类中声明

/*
二、静态成员函数
1. 所有对象都共享同一个静态成员函数
2. 只能在类中定义, 只能访问静态成员变量
3. 静态成员函数可以通过类名或对象名访问
4. 静态成员函数是有访问权限的
*/
	static void func()
	{
		//m_C = 100;  //不能访问非静态成员变量
		m_A = 100;
		cout << "static void func() 调用" << endl;
	}

	int m_C;

private:
	static int m_B; //要在类中声明

	static void func2()
	{
		
	}
};

//要在类外定义, 加类作用域, 否则是全局变量
int Person::m_A = 0;
int Person::m_B = 0;


void test01()
{
	//1. 通过对象进行访问
	Person p1;
	cout << p1.m_A << endl;

	Person p2;
	p2.m_A = 100;
	cout << p1.m_A << endl;

	//2. 通过类名进行访问
	cout << Person::m_A << endl;

	//3.静态成员变量是有访问权限的, 私有权限类外访问不到
	//cout << Person::m_B << endl;
}

void test02()
{
	//1. 通过对象进行访问
	Person p1;
	p1.func();
	
	//2. 通过类名进行访问
	Person::func();

	//3.静态成员函数是有访问权限的, 私有权限类外访问不到
	//Person::func2();
}

int main(){
	test01();
	test02();

	return EXIT_SUCCESS;
}