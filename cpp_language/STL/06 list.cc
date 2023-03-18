#include <iostream>
#include <list>
using namespace std;

void listPrint(const list<int>& ls)
{
    for(list<int>::const_iterator it = ls.begin(); it != ls.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}



/*
一、list构造函数
    list<T> ls;             // 默认构造函数, 空列表
    list(n, elem);          // 有参构造函数, 将n个elem赋值给自身
    list(begin, end);       // 有参构造函数, 将[begin, end)区间中的元素赋值给自身
    list(const list& ls);   // 拷贝构造函数
*/
void test01()
{
    list<int> ls1;
    listPrint(ls1);

    list<int> ls2(6, 8);
    listPrint(ls2);

    list<int> ls3(ls2.begin(), ls2.end());
    listPrint(ls3);

    list<int> ls4(ls2);
    listPrint(ls4);
}

/*
二、list插入和删除操作

void push_back(int&& __x);      // 在容器尾部加入一个元素
void pop_back();                // 删除容器最后一个元素
void push_front(int&& __x);     // 在容器开头插入一个元素
void pop_front();               // 删除容器第一个元素

Inserts given rvalue into %list before specified iterator.
iterator insert(const_iterator __position, int &&__x);
参数:
__position – A const_iterator into the %list.
__x – Data to be inserted.
返回:
An iterator that points to the inserted data. 
This function will insert a copy of the given rvalue before the specified location. 
Due to the nature of a %list this operation can be done in constant time, and does not invalidate iterators and references.

iterator insert(const_iterator __position, size_t __n, const int &__x);

Inserts a range into the %list.
iterator insert(const_iterator __position, iterator __first, iterator __last);
参数:
__position – A const_iterator into the %list.
__first – An input iterator.
__last – An input iterator.

返回:
An iterator pointing to the first element inserted (or __position). 
This function will insert copies of the data in the range [ * first,last) into the %list before the location specified by position. 
This operation is linear in the number of elements inserted and does not invalidate iterators and references.


iterator erase(const_iterator __position);  // 删除__position位置的数据，返回下一个数据的位置。

iterator erase(const_iterator __first, const_iterator __last);  // 删除[beg, end)区间的数据，返回下一个数据的位置。

Remove all elements equal to value.
void remove(const int &__value);
参数:
__value – The value to remove. Removes every element in the list equal to value. 
Remaining elements stay in list order. 
Note that this function only erases the elements, and that if the elements themselves are pointers, the pointed-to memory is not touched in any way. 
Managing the pointer is the user's responsibility.

Erases all the elements. 
void clear();
Note that this function only erases the elements, 
and that if the elements themselves are pointers, the pointed-to memory is not touched in any way.
Managing the pointer is the user's responsibility.
*/

void test02()
{
    list<int> ls1;
    ls1.push_back(10);
    ls1.push_back(20);
    ls1.push_back(30);
    ls1.push_back(40);
    ls1.push_back(50);
    listPrint(ls1);

    ls1.pop_back();
    listPrint(ls1);

    ls1.push_front(1);
    ls1.push_front(2);
    ls1.push_front(3);
    listPrint(ls1);

    ls1.pop_front();
    listPrint(ls1);

    ls1.insert(ls1.begin(), 100);
    ls1.insert(++ls1.begin(), 1, 200);
    listPrint(ls1);
    ls1.clear();

    list<int> ls2;
    ls2.insert(ls2.begin(), ls1.begin(), ls1.end());
    listPrint(ls2);
    ls2.erase(ls2.begin(), ls2.end());
    listPrint(ls2);

}


int main()
{
    // test01();
    test02();

    return 0;
}