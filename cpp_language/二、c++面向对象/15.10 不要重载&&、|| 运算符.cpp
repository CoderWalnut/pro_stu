/* 
    不能重载 operator&& 和 operator|| 的原因是无法在这两种情况下实现内置操作
符的完整语义.
内置版本的 && 和 || 首先计算左边的表达式, 如果能够决定结果, 就不计算右边的表达式了;
运算符重载其实是另一种形式的函数调用而已, 对于函数调用总是在函数执行之前对所有参数进
行求值.
*/

#include <iostream>
using namespace std;

class Complex{
public:
Complex(int flag)
{
    m_flag = flag;
}

Complex &operator+=(Complex &complex)
{
    m_flag += complex.m_flag;
    return *this;
}

bool operator&&(Complex &complex)
{
    return (m_flag && complex.m_flag);
}

    int m_flag;
};

int main()
{
    Complex complex1(0);
    Complex complex2(1);

    //&& 结合性从左到右, 函数调用总是在函数执行之前对所有参数进行求值
    //(complex1 += complex2)运算导致complex1中的m_flag为1, 结果为真
    if(complex1 && (complex1 += complex2))
    {
        cout << "真" << endl;
    }
    else
    {
        cout << "假" << endl;
    }

    return EXIT_SUCCESS;
}