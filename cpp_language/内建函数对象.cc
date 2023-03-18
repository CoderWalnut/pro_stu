#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

//取反仿函数
void test01() {
    std::negate<int> n;
    std::cout << n(50) << std::endl;
}

//加法仿函数
void test02() {
    std::plus<int> p;
    std::cout << p(10, 20) << std::endl;
}

//大于仿函数
void test03() {
    std::vector<int> v;
    srand((unsigned int )time(NULL));
    for (int i = 0; i < 10; i++) {
        v.push_back(rand()%100);
    }

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    sort(v.begin(), v.end(), std::greater<int>());

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


int main() {
    // test01();
    // test02();
    test03();

    return 0;
}