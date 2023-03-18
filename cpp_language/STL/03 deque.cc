#include <iostream>
#include <deque>
using namespace std;

void dequePrint(const deque<int>& dq)
{
    // iterator 普通迭代器
    // reverse_iterator 反转迭代器
    // const_iterator 只读迭代器
    for(deque<int>::const_iterator it = dq.begin(); it != dq.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

/*
    一、deque构造函数
    deque<T> dq;                // 默认构造
    deque(begin, end);          // 有参构造, 将[begin, end)区间中的元素拷贝给自身
    deque(n, elem);             // 有参构造, 将n个elem拷贝给自身
    deque(const deque& dq);     // 拷贝构造
*/
void test01()
{
    deque<int> dq1;
    dequePrint(dq1);

    deque<int> dq2;
    dq2.push_back(10);
    dq2.push_back(20);
    dq2.push_back(30);
    dq2.push_back(40);

    deque<int> dq3(dq2.begin(), dq2.end());
    dequePrint(dq3);

    deque<int> dq4(6, 8);
    dequePrint(dq4);

    deque<int> dq5(dq2);
    dequePrint(dq5);
}

/*
    二、deque的双端插入和删除
    void push_back(int &&__x);      // 在尾部添加数据__x
    void push_front(int &&__x);     // 在头部添加数据__X
    void pop_back();                // 删除最后一个元素
    void pop_front();               // 删除第一个元素
*/
void test02()
{
    deque<int> dq1;
    dq1.push_back(10);
    dq1.push_back(20);
    dq1.push_back(30);
    dq1.push_front(100);
    dq1.push_front(200);
    dq1.push_front(300);
    dequePrint(dq1);

    dq1.pop_back();
    dq1.pop_front();
    dequePrint(dq1);
}

/*
三、deque数据存取

Provides access to the data contained in the %deque.
int& at(size_t __n);
参数:
    __n – The index of the element for which data should be accessed.
返回:
    Read/write reference to data.
异常:
std::out_of_range If __n is an invalid index. 
This function provides for safer data access. 
The parameter is first checked that it is in the range of the deque. 
The function throws out_of_range if the check fails.

Subscript access to the data contained in the %deque.
int& operator[](size_t __n);
参数:
    __n – The index of the element for which data should be accessed.
返回:
    Read/write reference to data. This operator allows for easy, array-style, data access. 
    Note that data access with this operator is unchecked and out_of_range lookups are not defined. 
    (For checked lookups see at().)

int& front();
返回:
    Returns a read/write reference to the data at the first element of the %deque.

int& back();
返回:
    Returns a read/write reference to the data at the last element of the %deque.
*/
void test03()
{
    deque<int> dq1;
    dq1.push_back(10);
    dq1.push_back(20);
    dq1.push_back(30);
    dq1.push_back(40);
    dequePrint(dq1);

    cout << dq1.at(1) << endl;
    cout << dq1[2] << endl;
    cout << dq1.front() << endl;
    cout << dq1.back() << endl;
}

/*
四、deque插入和删除操作

Inserts given rvalue into %deque before specified iterator.
iterator insert(const_iterator __position, int&& __x);
参数:
__position – A const_iterator into the %deque.
__x – Data to be inserted.
返回:
An iterator that points to the inserted data. 
This function will insert a copy of the given rvalue before the specified location.


Inserts a number of copies of given data into the %deque.
iterator insert(const_iterator __position, size_t __n, const int& __x);
参数:
    __position – A const_iterator into the %deque.
    __n – Number of elements to be inserted.
    __x – Data to be inserted.
返回:
    An iterator that points to the inserted data. 
    This function will insert a specified number of copies of the given data before the location specified by __position.


Inserts a range into the %deque.
iterator insert(const_iterator __position, iterator __first, iterator __last);
参数:
    __position – A const_iterator into the %deque.
    __first – An input iterator.
    __last – An input iterator.
返回:
An iterator that points to the inserted data. 
This function will insert copies of the data in the range [__first,__last) into the %deque before the location specified by __position. 
This is known as <em>range insert</em>.

删除__position位置的数据, 返回指向下一元素的迭代器
iterator erase(const_iterator __position);


删除[__first, __last)区间的数据, 返回指向下一元素的迭代器
iterator erase(const_iterator __first, const_iterator __last);


void clear();
Erases all the elements. 
Note that this function only erases the elements, 
and that if the elements themselves are pointers, 
the pointed-to memory is not touched in any way. 
Managing the pointer is the user's responsibility.
*/
void test04()
{
    deque<int> dq1;
    dq1.push_back(10);
    dq1.push_back(20);
    dq1.push_back(30);
    dq1.push_back(40);
    dequePrint(dq1);

    deque<int>::const_iterator it = dq1.begin();
    dq1.insert(it + 2, 100);
    dequePrint(dq1);

    dq1.insert(it + 3, 1, 200);
    dequePrint(dq1);

    deque<int> dq2;
    dq2.insert(dq2.begin(), dq1.begin(), dq1.end());
    dequePrint(dq2);

    dq2.erase(dq2.begin());
    dequePrint(dq2);

    dq2.erase(dq2.begin(), dq2.begin() + 3);
    dequePrint(dq2);

    dq2.clear();
    dequePrint(dq2);
}

/*
五、deque元素排序
Sort the elements of a sequence using a predicate for comparison.
inline void std::sort<std::deque<int>::iterator, bool (*)(int v1, int v2)>(std::deque<int>::iterator, std::deque<int>::iterator, bool (*)(int v1, int v2))
参数:
__first – An iterator.
__last – Another iterator.
__comp – A comparison functor.
返回:
Nothing. 
Sorts the elements in the range [__first,__last) in ascending order, 
such that __comp(*(i+1),*i) is false for every iterator i in the range [__first,__last-1). 
The relative ordering of equivalent elements is not preserved, 
use stable_sort() if this is needed.
*/
void test05()
{

}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    test05();

    return 0;
}