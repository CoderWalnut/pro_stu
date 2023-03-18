#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1、全局变量检测（未检测出问题）
int a;
int a = 10;

//2、函数检测；返回值没有检测、形参类型没有检测、函数调用参数个数没有检测
getRectS( w  , h)
{
	return w *h;
}
void test01()
{
	printf("%d\n", getRectS(10, 10, 10));
}


//3、类型转换检测（malloc()的返回值没有强制类型转换，未检测出问题（隐式转换））
void test02()
{
	char * p = malloc(64);
}


//4、struct（结构体中不可以有函数）；定义结构体变量，必须加关键字struct
struct Person
{
	int age;
	//void func();
};
void test03()
{
	struct Person p;
	p.age = 100;
}


//5、bool类型  没有此类型（要使用需要添加头文件 <stdbool.h>）
//bool a;


//6、三目运算符（返回的是值）
void test04()
{
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	*(a > b ? &a : &b) = 100;

	printf("a = %d\n", a);
	printf("b = %d\n", b);
}


//7、const
//全局const，通过变量名修改编译失败、保存地址再解引用修改，编译通过，运行段错误
const int m_A = 100;
void test05()
{
	//m_A = 200;
	//int * p = &m_A;
	//*p = 200;

	//局部const，通过变量名修改编译失败，保存地址再解引用修改，编译通过，修改成功
	const int m_B = 100;
	//m_B = 200;
	int * p = &m_B;
	*p = 200;

	printf("%d\n", m_B);

	//C语言下，const是伪常量，无论是全局还是局部都不可以用于数组长度，都编译失败
	//int arr[m_A] = {1};
	//int arr[m_B] = {1};
}


int main(){
	
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();

	return EXIT_SUCCESS;
}