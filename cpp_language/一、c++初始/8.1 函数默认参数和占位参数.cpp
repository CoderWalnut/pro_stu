#include<iostream>
using namespace std;


//默认参数语法, 形参: 类型 变量  = 默认值
//注意事项, 如果有一个位置有了默认参数，那么从这个位置起，从左到右都必须有默认值
//没有给默认参数传参, 该参数使用默认值; 若给默认参数传参, 则该参数使用传入值
int func(int a, int b = 10 , int c = 10)
{
	return  a + b + c;
}

//函数的声明和定义只能有一个提供默认参数，不可以同时加默认参数
void myFunc(int a = 10, int b = 10);
void myFunc(int a , int b)
{
	
};

void test01()
{
	cout << func(20 , 10) << endl;

}


//占位参数  只写一个类型进行占位，调用时候必须要传入占位值
//占位参数可以有默认参数
//占位参数 用途？ 目前没用
void func2(int a, int)
{

}

void func3(int a, int = 1)
{
	
}

void test02()
{
	func2(10, 1);
	func3(10);
}

int main(){

	test01();

	return EXIT_SUCCESS;
}