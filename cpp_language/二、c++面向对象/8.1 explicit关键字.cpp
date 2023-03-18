#include<iostream>
using namespace std;

class MyString
{
public:
	MyString(char * str)
	{
	
	}
	
	/*
	explicit用途: 
		1.禁止用隐式方式来构造对象, 只能使用括号法和显示构造
		2.是针对单参数的构造函数(或者除了第一个参数外其余参数都有默认值的多参构造)
	*/
	explicit MyString(int len)
	{
		
	}
};

void test01()
{
	MyString str1(10);

	MyString str2(100);

	//MyString str3 = 10; // 可能让人误解为 "10"
}


int main(){
	test01();

	return EXIT_SUCCESS;
}