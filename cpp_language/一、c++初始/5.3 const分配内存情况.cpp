#include<iostream>
using namespace std;
#include <string>

//1、对const变量取地址，会分配临时内存，地址指向临时的内存，而不是const变量
void test01()
{
	const int a = 10;
	int * p = (int *)&a;
}

//2、使用普通变量初始化const变量，会分配内存，对const变量取地址，地址指向const变量
void test02()
{
	int a = 10;
	const int b = a;

	int *p = (int *)&b;
	*p = 1000;

	cout << "b = " << b << endl;
}

//3、对于自定义数据类型，无法直接修改其中的变量；可通过取地址间接修改
struct Person
{
	string m_Name;
	int m_Age;
};
void test03()
{
	const Person p;
	//p.m_Age = 10;

	Person * pp = (Person *)&p;
	(*pp).m_Name = "Tom";
	pp->m_Age = 10;

	cout << "姓名: " << p.m_Name << " 年龄: " << p.m_Age << endl;
}


int main(){

	//test02();
	test03();

	return EXIT_SUCCESS;
}