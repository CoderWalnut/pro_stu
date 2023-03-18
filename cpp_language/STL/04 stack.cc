#include <iostream>
#include <stack>
using namespace std;

/*
一、stack构造函数

stack<T> sk;                // 默认构造函数, 空stack
stack(const stack& sk);     // 拷贝构造函数


二、stack大小操作

bool empty() const;
返回:
    Returns true if the %stack is empty.

size_t size() const;
返回:
    Returns the number of elements in the %stack.


三、stack赋值操作
stack<int>& operator=(stack<int> &);

四、stack数据存取操作

向栈顶添加元素
void push(int&& __x);

int& top();
返回:
    Returns a read/write reference to the data at the first element of the %stack.

void pop();
Removes first element. 
This is a typical %stack operation. 
It shrinks the %stack by one. 
The time complexity of the operation depends on the underlying sequence. 
Note that no data is returned, and if the first element's data is needed, it should be retrieved before pop() is called.

*/

void test01()
{
    stack<int> sk1;
    cout << "sk1.empty() result = " << sk1.empty() << endl;

    sk1.push(10);
    sk1.push(20);
    sk1.push(30);
    sk1.push(40);
    sk1.push(50);
    cout << "sk1.size() = " << sk1.size() << endl;

    stack<int> sk2(sk1);
    cout << "sk2.size() = " << sk2.size() << endl;

    stack<int> sk3;
    sk3 = sk2;
    while(sk3.empty() == false){
        cout << "sk3.top() = " << sk3.top() << endl;
        sk3.pop();
    }

    cout << "sk3.size() = " << sk3.size() << endl; 
}


int main()
{
    test01();

    return 0;
}