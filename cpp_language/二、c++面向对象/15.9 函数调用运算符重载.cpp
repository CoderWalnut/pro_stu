#include <iostream>
#include <string>
using namespace std;

class MyPrint{
public:
void operator()(string text)
{
    cout << text << endl;
}
};

void myPrint2(string str)
{
    cout << str << endl;
}

void test01()
{
    MyPrint myPrint;
    myPrint("hello world!");  //仿函数, 本质是一个对象, 也叫函数对象
    myPrint2("hello world!"); //普通函数
}

class MyAdd
{
public:
int operator()(int a, int b)
{
    return a + b;
}
};

void test02()
{
    MyAdd myAdd;
    cout << myAdd(1, 1) << endl;

    //MyAdd() 匿名对象; MyAdd()(1, 1)匿名函数对象, 当前行执行完立即释放
    //仿函数写法比较灵活, 不固定, 按需求来写
    cout << MyAdd()(1, 1) << endl;
}

int main()
{
    //test01();
    test02();

    return EXIT_SUCCESS;
}