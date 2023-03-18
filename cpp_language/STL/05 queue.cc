#include <iostream>
#include <queue>
using namespace std;

/*
一、queue构造函数
queue<T> qe;                       // 默认构造函数
queue<T> qe(const queue& qe);      // 拷贝构造函数


二、queue大小操作

bool empty() const;
返回:
    Returns true if the %queue is empty.

size_t size() const;
返回:
    Returns the number of elements in the %queue.


三、queue赋值操作
queue<int>& operator=(const queue<int> &);

四、queue数据存取操作

往队尾添加元素
void push(int &&__x);

void pop();
Removes first element. 
This is a typical %queue operation. 
It shrinks the %queue by one. 
The time complexity of the operation depends on the underlying sequence. 
Note that no data is returned, and if the first element's data is needed, it should be retrieved before pop() is called.

int& front();
Returns a read/write reference to the data at the first element of the %queue.

int& back();
Returns a read/write reference to the data at the last element of the %queue.
*/

void test01()
{
    queue<int> qe1;
    cout << "qe1.empty() result = " << qe1.empty() << endl;

    qe1.push(10);
    qe1.push(20);
    qe1.push(30);
    qe1.push(40);
    qe1.push(50);
    cout << "qe1.size() = " << qe1.size() << endl;
    cout << "qe1 first element = " << qe1.front() << endl;
    cout << "qe1 last element = " << qe1.back() << endl;

    queue<int> qe2(qe1);
    cout << "qe2.size() = " << qe2.size() << endl;

    queue<int> qe3;
    qe3 = qe2;
    while(qe3.empty() == false){
        cout << "qe3.front() = " << qe3.front() << endl;
        qe3.pop();
    }

    cout << "qe3.size() = " << qe3.size() << endl; 
}


int main()
{
    test01();

    return 0;
}