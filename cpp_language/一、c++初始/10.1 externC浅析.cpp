#include<iostream>
using namespace std;
#include "test.h"


//方法一: 告诉编译器show();函数用C语言方式做链接, 若用此种方法就不能在包含该函数的头文件
//不推荐此方法
//extern "C" void show();


void test01()
{
	show();//在C++中有函数重载会修饰函数名, 但是show();是c语言文件, 因此链接失败
}


int main(){
	test01();

	return EXIT_SUCCESS;
}