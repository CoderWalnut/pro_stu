#include<iostream>
using namespace std;

class Person
{
public: //构造和析构必须要声明在全局作用域
	//构造函数: 
	//没有返回值, 不用写void
	//函数名 与 类名 相同
	//可以有参数, 可以发生重载
	//由编译器自动调用一次, 无须手动调用
	Person()
	{
		cout << "Person的构造函数调用" << endl;
	}
	
	//析构函数: 
	//没有返回值, 不用写void
	//函数名 与 类名相同, 函数名前加 ~
	//不可以有参数, 不可以发生重载
	//析构函数也是由编译器自动调用一次, 无须手动调用
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

};

void test01()
{
	Person p;
}

int main(){
	
	test01();

	return EXIT_SUCCESS;
}