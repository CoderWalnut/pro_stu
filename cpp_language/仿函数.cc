#include <iostream>

class MyPrint {
public:
    int m_num = 0;

    void operator()(int val) {
        std::cout << val << std::endl;
        m_num++;
    }
};

void doBussiness(MyPrint print, int num) {
    print(num);
}

void test01() {
    MyPrint mp;
    mp(20);
    mp(30);
    mp(40);
    std::cout << mp.m_num << std::endl;
}

void test02() {
    //参数1：匿名函数对象
    doBussiness(MyPrint(), 100);
}

int main()
{
    //test01();

    test02();
}