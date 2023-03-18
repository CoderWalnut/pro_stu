#include <iostream>
#include <vector>
using namespace std;

/*
    一、vector的未雨绸缪机制
    // Returns the total number of elements that the %vector can hold before needing to allocate more memory.
    size_t capacity() const;

    void push_back(const int& __x)  // Add data to the end of the %vector.
*/
void test01()
{
    vector<int> vInt;
    for(int i = 0; i < 10; ++i){
        vInt.push_back(i);
        cout << "vInt capacity = " << vInt.capacity() << endl;
    }
}


/*
    二、vector 构造函数
    vector<T> v;                    // 采用模板实现类实现，默认构造函数, 空容器
    vector(v.begin(), v.end());     // 有参构造函数, 将[v.begin(), v.end())区间中的元素赋值给自身
    vector(n, elem);                // 有参构造函数, 将n个elem赋值给自身
    vector(const vector& vec);      // 拷贝构造函数, 将vec容器的内容赋值自身

    // Returns a read/write iterator that points to the first element in the %vector. Iteration is done in ordinary element order.
    iterator begin();

    // Returns a read/write iterator that points one past the last element in the %vector. Iteration is done in ordinary element order.
    iterator end();
*/
void vectorPrint(vector<int>& v)
{
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }

    cout << endl;
}

void test02()
{
    vector<int> vec1;
    vectorPrint(vec1);

    int arr[] = {1, 2, 3, 4, 5, 6};
    vector<int> vec2(arr, arr + sizeof(arr)/sizeof(int));
    vectorPrint(vec2);

    vector<int> vec3(8, 8);
    vectorPrint(vec3);

    vector<int> vec4(vec2);
    vectorPrint(vec4);
}

/*
    三、vector 常用的赋值操作
    void assign(iterator __first, iterator __last);  // 赋值[__first, __last)区间的元素
    void assign(size_t __n, const int& __val);       // 赋值n个__val
    vector<int>& operator=(const vector<int>& __x);  // 赋值__x中的元素

    void swap(vector<int> &__x);  // 自身容器元素替换为__x容器中的元素
*/
void test03()
{
    vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50);
    vec1.push_back(60);

    vector<int> vec2;
    vec2.assign(vec1.begin(), vec1.end());
    vectorPrint(vec2);

    vector<int> vec3;
    vec3.assign(6,6);
    vectorPrint(vec3);

    vector<int> vec4;
    vec4 = vec2;
    vectorPrint(vec4);

    vec4.swap(vec3);
    vectorPrint(vec4);
}

/*
    四、vector 大小操作
    size_t size() const;    // Returns the number of elements in the %vector.

    // __new_size – Number of elements the %vector should contain.
    // This function will %resize the %vector to the specified number of elements. 
    // If the number is smaller than the %vector's current size the %vector is truncated, otherwise default constructed elements are appended.
    void resize(size_t __new_size);

    // __new_size – Number of elements the %vector should contain.
    // __x – Data with which new elements should be populated.
    // This function will %resize the %vector to the specified number of elements.
    // If the number is smaller than the %vector's current size the %vector is truncated, otherwise the %vector is extended and new elements are populated with given data.
    void resize(size_t __new_size, const int& __x);

    // Returns true if the %vector is empty. (Thus begin() would equal end().)
    bool empty() const;

    // This function attempts to reserve enough memory for the %vector to hold the specified number of elements.
    // If the number requested is more than max_size(), length_error is thrown.
    // The advantage of this function is that if optimal code is a necessity and the user can determine the number of elements that will be required, 
    // the user can reserve the memory in %advance, and thus prevent a possible reallocation of memory and copying of %vector data.
    void reserve(size_t __n);
*/
void test04()
{
    vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50);
    vec1.push_back(60);

    cout << "vec1.size() = " << vec1.size() << endl;

    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    vec1.resize(4);
    vectorPrint(vec1);
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    vec1.resize(10);
    vectorPrint(vec1);
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    vec1.resize(6, 1);
    vectorPrint(vec1);
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    vec1.resize(20, 1);
    vectorPrint(vec1);
    cout << "vec1.capacity() = " << vec1.capacity() << endl;

    if(vec1.empty() == true)
        cout << "vec1 is empty." << endl;
    else
        cout << "vec1 is not empty." << endl;
}

/*
    五、vector 数据存取操作
    int& operator[](size_t __n);    // 获取第n个元素
    int& at(size_t __n);            // 获取第n个元素

    []访问越界, 直接挂掉; at()访问越界, 会抛出out_of_range异常再挂
    为了修改vector的内容, 下标操作符[]和at()都会返回元素的引用, 
    但当vector的内存被重新分配之后, 再通过引用操作原先的内存会发生错误


    // Returns a read/write reference to the data at the first element of the %vector.
    int& front();

    // Returns a read/write reference to the data at the last element of the %vector.
    int& back();
*/
void test05()
{
    vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50);
    vec1.push_back(60);

    for(int i = 0; i < vec1.size(); ++i){
        cout << vec1[i] << " ";
        // cout << vec1.at(i) << " ";
    }
    cout << endl;

    cout << vec1.front() << endl;
    cout << vec1.back() << endl;
}

/*
    六、vector 插入和删除操作
    Inserts a number of copies of given data into the %vector.
    This function will insert a specified number of copies of the given data before the location specified by position. 
    Note that this kind of operation could be expensive for a %vector and if it is frequently used the user should consider using std::list.
    参数:
        __position – A const_iterator into the %vector.
        __n – Number of elements to be inserted.
        __x – Data to be inserted.
    返回:
        An iterator that points to the inserted data. 
    iterator insert(const_iterator __position, size_t __n, const int &__x);

    Removes last element.
    This is a typical stack operation. 
    It shrinks the %vector by one. 
    Note that no data is returned, and if the last element's data is needed, it should be retrieved before pop_back() is called.
    void pop_back();

    Remove element at given position.
    This function will erase the element at the given position and thus shorten the %vector by one. 
    Note This operation could be expensive and if it is frequently used the user should consider using std::list. 
    The user is also cautioned that this function only erases the element, and that if the element is itself a pointer, the pointed-to memory is not touched in any way. 
    Managing the pointer is the user's responsibility.
    参数:
    __position – Iterator pointing to element to be erased.
    返回:
        An iterator pointing to the next element (or end()).
    iterator erase(const_iterator __position);

    Remove a range of elements.
    This function will erase the elements in the range [__first,__last) and shorten the %vector accordingly. 
    Note This operation could be expensive and if it is frequently used the user should consider using std::list. 
    The user is also cautioned that this function only erases the elements, and that if the elements themselves are pointers, the pointed-to memory is not touched in any way. 
    Managing the pointer is the user's responsibility.
    参数:
        __first – Iterator pointing to the first element to be erased.
        __last – Iterator pointing to one past the last element to be erased.
    返回:
        An iterator pointing to the element pointed to by __last prior to erasing (or end()).
    iterator erase(const_iterator __first, const_iterator __last);

    Erases all the elements. 
    Note that this function only erases the elements, and that if the elements themselves are pointers, the pointed-to memory is not touched in any way. 
    Managing the pointer is the user's responsibility.
    void clear();
*/
void test06()
{
    vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);

    vector<int>::iterator it = vec1.begin() + 1;
    vec1.insert(it, 1, 100);
    vectorPrint(vec1);

    vec1.pop_back();
    vectorPrint(vec1);

    vec1.erase(vec1.begin());
    vectorPrint(vec1);

    vec1.clear();

    // 和 vec1.clear(); 效果相互等价
    // vec1.erase(vec1.begin(), vec1.end());
    vectorPrint(vec1);
}

/*
    七、巧用reserve预留空间
*/
void test07()
{
    vector<int> vec1;
    int* p = nullptr;
    int num = 0;

    vec1.reserve(100000);   // 一次预留好内存大大减少重新分配内存的次数
    for(int i = 0; i < 100000; ++i){
        vec1.push_back(i);
        if(p != &vec1[0]){  // 用于计算重新分配内存的次数
            p = &vec1[0];
            ++num;
        }
    }

    cout << "num = " << num << endl;
}

/*
    八、巧用swap收缩内存
*/
void test08()
{
    vector<int> vec1;
    for(int i = 0; i < 100000; ++i){
        vec1.push_back(i);
    }
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    cout << "vec1.size() = " << vec1.size() << endl;

    vec1.resize(3);
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    cout << "vec1.size() = " << vec1.size() << endl;

    vector<int> (vec1).swap(vec1);  // 匿名对象
    cout << "vec1.capacity() = " << vec1.capacity() << endl;
    cout << "vec1.size() = " << vec1.size() << endl;
}


/*
reverse_iterator iterator> rbegin();
返回:
Returns a read/write reverse iterator that points to the last element in the %vector. 
Iteration is done in reverse element order.

reverse_iterator rend();
返回:
Returns a read/write reverse iterator that points to one before the first element in the %vector. 
Iteration is done in reverse element order.
*/
void test09()
{
    vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50);

    // 逆序遍历
    for(vector<int>::reverse_iterator it = vec1.rbegin(); it != vec1.rend(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    // vector的迭代器时随机访问迭代器, 支持跳跃访问
    vector<int>::iterator itBegin = vec1.begin();
    itBegin = itBegin + 3;
    cout << *itBegin << endl;
}


int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test07();
    // test08();
    test09();


    return 0;
}