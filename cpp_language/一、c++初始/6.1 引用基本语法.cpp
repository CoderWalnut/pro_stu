#include<iostream>
using namespace std;

//引用基本语法: 类型  &别名 = 原名
void test01()
{
	int a = 10;
	int &b = a;

	b = 100;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}


void test02()
{
	int a = 10;
	//int &b; //引用必须要初始化

	int &b = a;

	int c = 100;
	
	//引用一旦初始化后，就不可以引向其他变量
	//int &b = c;
	
	b = c; // 赋值

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//对数组建立引用
void test03()
{
	//1、直接建立引用
	int arr[10];
	int(&pArr)[10] = arr;

	for (int i = 0; i < 10; i++)
	{
		arr[i] = 100 + i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << pArr[i] << endl;
	}

	//2、先定义出数组类型，再通过类型 定义引用
	typedef int(ARRAY_TYPE)[10];
	//类型  &别名 = 原名
	ARRAY_TYPE & pArr2 = arr;

	for (int i = 0; i < 10; i++)
	{
		cout << pArr2[i] << endl;
	}
}

int main(){

	//test01();
	//test02();
	//test03();

	return EXIT_SUCCESS;
}