/*
    如果一个类的成员, 既要实现共享, 又要实现不可改变, 那就用 static const 修饰;
    定义 static const 成员数据时, 最好在类内部初始化.
*/

#include <iostream>
using namespace std;

class Person{
public:
// static const int mShare = 10;  //只读, 不可修改
const static int mShare = 10;    //只读, 不可修改
};

int main()
{
    cout << Person::mShare << endl;
    // Person::mShare = 20;

    return EXIT_SUCCESS;
}