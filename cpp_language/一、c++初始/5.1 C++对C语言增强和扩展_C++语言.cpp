#include<iostream>
using namespace std;

//1、全局变量检测增强（检测出重定义）
int a;
//int a = 10;

//2、函数检测增强：返回值检测、形参类型检测、函数调用参数个数检测
int getRectS(int w,int h)
{

	return w *h;
}
void test01()
{
	printf("%d\n", getRectS(10, 10));
}


//3、类型转换检测增强（malloc()的返回值必须进行强制类型转换）
void test02()
{
	char * p = (char *)malloc(64);
}


//4、struct增强（结构体中可以放函数）；定义结构体变量，可以不加关键字struct
struct Person
{
	int age;
	void func()
	{
		age++;
	}
};
void test03()
{
	Person p;
	p.age = 17;
	p.func();
	cout << "p的age = " << p.age << endl;
}


//5、bool类型扩展  有bool类型（bool类型代表真和假，true - 真(1)，false - 假(0)）
bool flag = true;
void test04()
{
	cout << sizeof(bool) << endl; //bool类型是1个字节
	//flag = false; //0
	//flag = true;  //1
	//flag = 100;   //将非0的数都转为1
	//flag = -100;  //将非0的数都转为1
	cout << flag << endl;
}

//6、三目运算符增强（返回的是变量）
void test05()
{
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	(a < b ? a : b )= 100;

	printf("a = %d\n", a);
	printf("b = %d\n", b);
}


//7、const增强
//全局const，通过变量名修改编译失败、保存地址再解引用修改，编译成功，运行段错误
const int m_A = 100;
void test06()
{
	//m_A = 200;
	
	//int * p = (int *)&m_A;
	//*p = 200;


	//局部const，通过变量名编译失败、保存地址再解引用修改，编译成功，运行成功，但修改失败，还是原来的值
	const int m_B = 100;
	//m_B = 200;
	
	//int * p = (int *)&m_B;
	//*p = 200;
	/*
		    符号表
	+----------------------+
	|	key   |   value    |     int temp = m_B; //当对const局部变量取地址的时候，编译器给变量分配临时的内存空间temp，p指针指向的是temp
	+----------------------+     int *p = &temp;
	|   m_B   |    100     |     *p = 200;       //实际修改的是temp的值
	|         |            |
	+----------------------+
	*/

	//C++下，const修饰的变量称为常量，全局和局部都可以用于数组长度
	int arr[m_A] = {1};
	int arr[m_B] = {1};
	
	cout << "m_A = " << m_A << endl;
	cout << "m_B = " << m_B << endl;
}


int main(){
	//test01();
	//test03();
	//test04();
	//test05();
	//test06();

	return EXIT_SUCCESS;
}