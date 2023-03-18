#include<iostream>
using namespace std;

class Person
{
public:

	//未使用初始化列表
	// Person(int a, int b, int c)
	// {
	// 	m_A = a;
	// 	m_B = b;
	// 	m_C = c;
	// }


	//构造函数名称后 ：成员变量(值), 成员变量（值）...


	//使用初始化列表, 方法一: 
	Person() : m_A(10), m_B(20), m_C(30)
	{
	}



	//使用初始化列表, 方法二: 
	// Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c)
	// {
	// }


	int m_A;
	int m_B;
	int m_C;
};

void test01()
{
	//未使用初始化列表
	// Person p(1, 2, 3);
	
	//使用初始化列表, 方法一:
	// Person p;

	//使用初始化列表, 方法二:
	// Person p(10, 20, 30);
	
	cout << "m_A = " << p.m_A << endl;
	cout << "m_B = " << p.m_B << endl;
	cout << "m_C = " << p.m_C << endl;
}

int main(){

	test01();

	return EXIT_SUCCESS;
}