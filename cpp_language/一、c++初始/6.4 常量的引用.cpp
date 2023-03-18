#include<iostream>
using namespace std;

void test01()
{
	//int &ref = 10;

	// 加了const之后，相当于 int temp = 10; const int &ref = temp; ref是temp的别名
	const int &ref = 10;

	int *p = (int *)&ref;  //p保存的是temp的地址
	*p = 10000;

	cout << ref << endl;
}

void showValue(const int &a)
{
	//a = 100000;  无法修改

	cout << "a = " << a << endl;
}
//常量引用的使用场景 修饰函数中的形参，防止误操作
void test02()
{
	int a = 100;
	showValue(a);
}

int main(){

	//test01();
	//test02();

	return EXIT_SUCCESS;
}