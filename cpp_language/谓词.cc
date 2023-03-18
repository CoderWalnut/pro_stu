#include <iostream>
#include <vector>
#include <algorithm>

// 一元谓词
class GreaterThanFive {
public:
	bool operator()(int num) {
		return num > 5;
	}
};

void test01() {
	std::vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}

	std::vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterThanFive());
	if (it == v.end()) {
		std::cout << "没有找到" << std::endl;
	}
	else {
		std::cout << "找到了" << *it << std::endl;
	}
}

//二元谓词
class MyCompare {
public:
    bool operator()(int num1, int num2) {
        return num1 > num2;
    }
};

void test02() {
    std::vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(90);
    v.push_back(60);

    //默认从小到大
    sort(v.begin(), v.end());
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    //使用函数对象改变算法策略，排序从大到小
    sort(v.begin(), v.end(), MyCompare());
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
	// test01();

    test02();

	return 0;
}