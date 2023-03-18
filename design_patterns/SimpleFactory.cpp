#include <iostream>
#include <string>
using namespace std;

// 没有严格的进行h和cpp的分离
// 主要关注对象间的结构

class Api {
public:
    virtual void test(string s) = 0;

protected:
    Api() {}    // 屏蔽构造函数，体现接口
};


class Impl : public Api {
public:
    void test(string s) {
        cout << "现在是impl类, 正在执行功能方法 " << s << endl;
    }
};

// 测试用的客户端
int main(void) {
    Api* pApi = new Impl();
    pApi->test("测试运行"); 

    return 0;
}
