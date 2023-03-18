#include <iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "Person无参构造函数调用" << endl;
	}

	Person(int a)
	{
		cout << "Person普通有参构造调用" << endl;
	}

	~Person()
	{
		cout << "Person析构函数调用" << endl;
	}
};

/*
malloc free 和 new delete区别: 
一、malloc free
	1.必须确定对象的大小
	2.返回 void* 要强转
	3.可能申请内存失败, 必须判断返回值来确保内存分配成功
	4.malloc不会调用构造函数, free不会调用析构函数; 用户必须自己操作
	5.malloc 和 free 属于库函数

二、new delete
	1.new 返回创建的对象的指针
	2.new操作符能确定在调用构造函数初始化之前内存分配是成功的, 不用确定内存分配是否成功
	3.new会调用构造函数, delete会调用析构函数
	4.new 和 delete 属于运算符
	5.不要用 void * 去接收 new 出来的对象, 用 void * 无法调用析构函数
	6.释放数组时候需要加 []
*/

void test01()
{
	Person * p = new Person;

	delete p;
}

// 不要用 void * 去接收 new 出来的对象, 用 void * 无法调用析构函数
void test02()
{
	void *p = new Person;

	delete p;
}

//利用new开辟数组
void test03()
{
	//int *pInt = new int[10];
	//double *pDouble = new double[10];

	//堆区开辟类数组，一定会调用相应数组大小数目的默认构造函数
	Person *pPerson = new Person[10];

	//释放类数组时候需要加 []
	delete [] pPerson;


	//栈上开辟类数组, 前三个调用有参构造，后面七个调用相应数目的默认构造函数
	Person pArray[10] = { Person(10), Person(20), Person(20) };
}

int main(){
	// test01();
	// test02();
	test03();

	return EXIT_SUCCESS;
}