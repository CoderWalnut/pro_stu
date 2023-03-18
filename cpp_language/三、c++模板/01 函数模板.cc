#include <iostream>
using namespace std;

void swapInt(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swapDouble(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

// 用函数模板实现通用交换函数
template<typename T>    // T代表一个通用的数据类型, 告诉编译器如果下面紧跟着的函数或类中出现T不要报错
void swapData(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 模板不能单独使用, 必须指定出T才能使用
template<typename T>
void swapTest()
{

}

void test01()
{
    int a = 10;
    int b = 20;
    char c1 = 'c';

    // 1. 自动类型推导, 必须推导出一致的T数据类型, 才可以正常的使用模板
    swapData(a, b);
    cout << "a = " << a << ", b = " << b << endl;
    // 1. 自动类型推导, 推导不出一致的T数据类型, 无法调用
    // swapData(a, c);

    // 2. 显示指定类型
    swapData<int>(a, b);
    cout << "a = " << a << ", b = " << b << endl;

    // 3. 模板不能单独使用, 必须指定出T才能使用
    // swapTest();
    swapTest<int>();

    double d = 3.14;
    double e = 4.26;
    swapData<double>(d, e);
    cout << "d = " << d << ", e = " << e << endl;
}

int main()
{
    test01();

    return 0;
}
