/*
c++中的 数据 和 处理数据的操作(函数) 是分开存储的:
1.成员变量保存在对象中, 静态成员变量不保存在对象中;
2.成员函数虽然在类声明之内, 却不在对象中; 每一个非内联成员函数只会诞生一份函数实例;
3.成员函数不保存在对象中, 静态成员函数不保存在对象中

总结: 只有成员变量会保存在对象中, 静态成员变量、成员函数、静态成员函数都不在对象中,
    静态成员变量、成员函数、静态成员函数都只有一份
*/

#include <iostream>
using namespace std;

class MyClass01{
public:
    int mA;
};

class MyClass02{
public:
    int mA;
    static int sB;
};

class MyClass03{
public:
void printMyClass()
{
    cout << "hello world!" << endl;
}

public:
    int mA;
    static int sB;
};

class MyClass04{
public:
void printMyClass()
{
    cout << "hello world!" << endl;
}

static void ShowMyClass()
{
    cout << "hello world!" << endl;
}

public:
    int mA;
    static int sB;
};

int main()
{
    MyClass01 mclass01;
    MyClass02 mclass02;
    MyClass03 mclass03;
    MyClass04 mclass04;

    cout << "对象 mclass01: " << sizeof(mclass01) << endl; //4

    cout << "对象 mclass02: " << sizeof(mclass02) << endl; //4

    cout << "对象 mclass03: " << sizeof(mclass03) << endl; //4

    cout << "对象 mclass04: " << sizeof(mclass04) << endl; //4

    return EXIT_SUCCESS;
}