#include <iostream>
#include <string>
using namespace std;
/*
class Calculator{
public:
    int m_A;
    int m_B;

public:
int getResult(string oper)
{
    if(oper == "+"){
        return m_A + m_B;
    }
    else if(oper == "-"){
        return m_A - m_B;
    }
    else if(oper == "*"){
        return m_A * m_B;
    }
}
};

void test01()
{
    Calculator c;
    c.m_A = 10;
    c.m_B = 10;
    cout << c.getResult("+") << endl;
}
*/

//设计原则: 开闭原则
//对扩展进行开放, 对修改进行关闭

//利用多态来实现计算器
class AbstractCalculator{
public:
    int m_A;
    int m_B;

public:
//纯虚函数
//如果一个类中包含了纯虚函数, 那么这个类就无法实例化对象, 这个类通常称为 抽象类
//抽象类的子类 必须要重写 父类中的纯虚函数, 否则也属于抽象类
virtual int getResult() = 0;

/*
virtual int getResult()
{
    return 0;
}
*/
};

//加法计算器
class AddCalculator : public AbstractCalculator{
public:
int getResult()
{
    return m_A + m_B;
}
};

//减法计算器
class SubCalculator : public AbstractCalculator{
public:
int getResult()
{
    return m_A - m_B;
}
};

//乘法计算器
class MulCalculator : public AbstractCalculator{
public:
int getResult()
{
    return m_A * m_B;
}
};

class Test : public AbstractCalculator{

};

void test02()
{
    AbstractCalculator* calculator = new AddCalculator;
    calculator->m_A = 100;
    calculator->m_B = 200;
    cout << calculator->getResult() << endl;

    delete calculator;

    calculator = new SubCalculator;
    calculator->m_A = 100;
    calculator->m_B = 200;
    cout << calculator->getResult() << endl;
}

int main()
{
    test02();

    //Test test; //无法使用抽象类实例化对象

    return EXIT_SUCCESS;
}