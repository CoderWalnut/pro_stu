/*
    一、类的主要特点之一是数据隐藏, 即类的私有成员无法在类的外部(作用域之外)访问;
但有时候需要在类的外部访问类的私有成员, 解决方法是使用友元函数, 友元函数是一种特权函数，c++允许这个特权函数访问私有成员.

    二、friend 关键字只出现在声明处, 类、类成员函数、全局函数都可声明为友元,
友元函数不是类的成员, 不带 this 指针; 友元函数可访问对象中任意成员数据，包括私有成员数据.

	三、友元关系不能被继承; 
		友元关系是单向的, 类 A 是类 B 的友元, 但类 B 不一定是类 A 的友元; 
		友元关系不具有传递性, 类 C 是类 B 的友元, 类 B 是类 A 的友元, 但类 C 不一定是类 A 的友元.
*/

#include <iostream>
#include <string>
using namespace std;

class Building
{
	//利用friend关键字让全局函数 relative(); 作为本类友元, 可以访问类中的私有成员
	friend void relative(Building * buliding);

public:
Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

public:
	string m_SittingRoom;

private:
	string m_BedRoom;
};

//友元全局函数, 可以访问Building的私有成员数据
void relative(Building *buliding)
{
	cout << "友元正在访问: " << buliding->m_SittingRoom << endl;
	cout << "友元正在访问: " << buliding->m_BedRoom << endl;
}


int main(){
	Building buliding;
	relative(&buliding);

	return EXIT_SUCCESS;
}