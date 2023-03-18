#include<iostream>
using namespace std;

/*
函数重载条件:
	1.在同一个作用域
	2.函数名称相同
	3.参数个数、类型、顺序不同, const也可作为重载条件
*/
/*
class Person
{
public:
	void func()   成员函数 而不是全局函数
	{
	}
};
*/

void func()
{
	cout << "func()调用" << endl;
}

void func(int a)
{
	cout << "func(int a)调用" << endl;
}

void func(double a)
{
	cout << "func(double a)调用" << endl;
}

void func(int a, double b)
{
	cout << "func(int a ,double b)调用" << endl;
}

void func(double a, int b)
{
	cout << "func(double a, int b)调用" << endl;
}

/*
//函数返回值不可以作为函数重载的条件
int func(int a, double b)
{
	cout << "func(int a ,double b)调用" << endl;
}
*/

void test01()
{
	func(1,3.14);
}



//函数重载遇到引用需要避免二义性出现
void myFunc(int a)
{
	cout << "myfunc(int a )调用" << endl; 
}

void myFunc(int &a) // int & a  = 10;
{
	cout << "myfunc(int &a )调用" << endl;
}

void myFunc(const int &a) // const int &a = 10;
{
	cout << "myfunc( const int &a )调用" << endl;
}

void test02()
{
	int a = 10;
	
	//此时void myFunc(int a)和 void myFunc(int &a)会产生二义性
	//myFunc(a);

	//此时void myFunc(int a)和void myFunc(const int &a)会产生二义性
	//myFunc(10);
}



//函数重载遇到默认参数需要避免二义性出现
void func2(int a , int b = 10)
{

}

void func2(int a)
{

}

void test03()
{
	//此时void func2(int a , int b = 10)和void func2(int a)会产生二义性
	//func2(10);
}


int main(){
	//test01();
	//test02();
	//test03();

	return EXIT_SUCCESS;
}