#include <iostream>
using namespace std;

class MyInt{

friend ostream &operator<<(ostream &cout, MyInt &m);

private:
    int m_Num;

public:
MyInt() { m_Num = 0; }

//前置++运算符重载
MyInt &operator++()
{
    this->m_Num++;
    return *this;
}

//后置++运算符重载, 形参中写int占位参数, 编译器即可识别, 此时无需传参
//不能返回引用, 此函数结束后tmp被释放
MyInt operator++(int)
{
    MyInt tmp = *this;
    this->m_Num++;
    return tmp;
}
};

ostream &operator<<(ostream &cout, MyInt &m)
{
    cout << m.m_Num;
    return cout;
}

/*
    调用代码优先使用前缀形式, 除非确实需要后缀形式返回的原值, 前缀和后缀形式语义上是等价的, 
输入工作量也相当, 只是效率经常会略高一些, 由于前缀形式少创建了一个临时对象.
*/

int main()
{
    MyInt mi;

    //前置++可以一直加
    cout << ++(++mi) << endl;

    //后置++, linux下此操作无法实现
    //cout << mi++ << endl;

    mi++;
    cout << mi << endl;

    return EXIT_SUCCESS;
}