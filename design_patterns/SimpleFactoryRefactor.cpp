#include <iostream>
#include <string>
using namespace std;

class Api {
public:
    virtual void test(string s) = 0;

protected:
    Api() {}    // 屏蔽构造函数，体现接口
};

class ImplOne : public Api {
public:
    void test(string s) {
        cout << "现在是One在执行" << s << endl;
    }
};

class ImplTwo : public Api {
public:
    void test(string s) {
        cout << "现在是Two在执行" << s << endl;
    }
};

class Factory {
public:
    static Api* createApi(int type) {
        Api* pApi = nullptr;
        if (type == 1) {
            pApi = new ImplOne();
        }
        if (type == 2) {
            pApi = new ImplTwo();
        }
        
        return pApi;
    }

    static Api* createApi() {
        
    }

};
// 实现了客户端调用和implOne, implTwo的解耦合


int main(void) {
    Api* pApi = Factory::createApi(2);
    pApi->test("现在是使用简单工厂方法重构");

    Api* pApiEx = Factory::createApi();

    return 0;
}