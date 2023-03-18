#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    一、string 类的构造函数
    string();                   // 无参构造函数 - 给定义的对象中的字符串成员变量赋空字符串
    string(const string& str);  // 拷贝构造函数 - str对象的字符串成员赋值给新定义的对象
    string(const char* s);      // 有参构造函数 - 字符串s赋值给string对象中的字符串成员
    string(int n, char c);      // 有参构造函数 - n个字符c赋值给string对象中的字符串成员
*/
void test01()
{
    string str1;
    cout << "str1 = " << str1 << endl;

    string str2(str1);
    cout << "str2 = " << str2 << endl;

    // string str3("hello world");
    // string str3 = string("hello world");
    string str3 = "hello world";
    cout << "str3 = " << str3 << endl;

    string str4(8, 'a');
    cout << "str4 = " << str4 << endl;
}

/*
    二、string 类中赋值成员函数
    string& operator=(const char* s);                       // 赋值字符串s
    string& operator=(const string& str)                    // 赋值str对象的字符串成员变量

    string& assign(size_t __n, char __c);                   // 赋值__n个字符__c
    string& assign(const char *__s);                        // 赋值字符串__s
    string& assign(const char *__s, size_t __n);            // 赋值字符串__s的前__n个字符
    string& assign(const string& __str);                    // 赋值__str对象的字符串成员
    string& assign(const string& __str, size_t __pos, size_t __n);  // 赋值__str对象的字符串成员从__pos开始__n个字符
*/
void test02()
{
    string str1;
    str1 = "hello-world";
    cout << "str1 = " << str1 << endl;

    string str2 = str1;
    cout << "str2 = " << str2 << endl;

    string str3;
    str3.assign(8, 'a');
    cout << "str3 = " << str3 << endl;

    string str4;
    str4.assign("hello-cpp");
    cout << "str4 = " << str4 << endl;

    string str5;
    str5.assign("hello-cpp", 6);
    cout << "str5 = " << str5 << endl;

    string str6;
    str6.assign(str4);
    cout << "str6 = " << str6 << endl;

    string str7;
    str7.assign(str4, 2, 5);
    cout << "str7 = " << str7 << endl;
}

/*
    三、string类中取字符成员函数
    char& operator[](size_t __pos);  // 获取__pos位置的字符
    char& at(size_t __n);           // 获取第n个字符
    []访问越界, 直接挂掉; at()访问越界, 会抛出out_of_range异常再挂

    为了修改string字符串的内容, 下标操作符[]和at()都会返回字符的引用, 
    但当字符串的内存被重新分配之后, 再通过引用操作原先的内存会发生错误
*/
void test03()
{
    string str1 = "hello-world";

    for(int i = 0; i < str1.size(); ++i){
        // cout << str1[i] << " ";
        cout << str1.at(i) << " ";
    }
    cout << endl;

    try{
        cout << str1[100] << endl;
        // cout << str1.at(100) << endl;
    }catch(out_of_range& e){
        cout << e.what() << endl;
    }catch(...){
        cout << "异常捕获" << endl;
    }


    string str2 = "abcdef";
	char& a = str2[2];
	char& b = str2[3];

	a = '1';
	b = '2';

	cout << str2 << endl;

	str2 = "opqrst";   // 重新分配内存

	// a = '1';     // 操作原先的内存, 出错
	// b = '2';     // 操作原先的内存, 出错
}

/*
    四、string类中字符串拼接函数
    string& operator+=(char __c);                   // 尾部拼接字符__c
    string& operator+=(const char *__s);            // 尾部拼接字符串__s
    string& operator+=(const string& __str);        // 尾部拼接__str对象的字符串成员

    string& append(size_t __n, char __c);           // 尾部追加__n个字符__c
    string& append(const char *__s);                // 尾部追加字符串__s
    string& append(const char *__s, size_t __n);    // 尾部追加字符串__s的前__n个字符
    string& append(const string& __str);            // 尾部追加__str对象的字符串成员
    string& append(const string& __str, size_t __pos, size_t __n);  // 尾部追加__str对象的字符串成员从__pos开始的__n个字符
*/
void test04()
{
    string str1 = "hello";
    string str2 = "world";

    str1+='-';
    cout << "str1 = " << str1 << endl;

    str1+="---";
    cout << "str1 = " << str1 << endl;


    str1 += str2;
    cout << "str1 = " << str1 << endl;

    string str3;
    str3+=str1;
    str3+=str2;
    cout << "str3 = " << str3 << endl;

    string str4;
    str4.append(8, 'a');
    cout << "str4 = " << str4 << endl;

    str4.append("bbbbbb");
    cout << "str4 = " << str4 << endl;

    str4.append("cccccc", 3);
    cout << "str4 = " << str4 << endl;

    str4.append(str2);
    cout << "str4 = " << str4 << endl;

    str4.append(str1, 0, 5);
    cout << "str4 = " << str4 << endl;
}

/*
    五、string类中的查找函数
    size_t find(char __c, size_t __pos) const;          // 查找字符__c第一次出现的位置, 从__pos开始查找, 返回第一次出现的位置, 该位置是下标不受__pos影响(下同)
    size_t find(const char *__s, size_t __pos) const;   // 查找字符串__s第一次出现的位置, 从__pos开始查找, 返回第一次出现的位置
    size_t find(const char *__s, size_t __pos, size_t __n) const;   // 查找字符串__s的前__n个字符第一次出现的位置, 从__pos开始查找, 返回第一次出现的位置
    size_t find(const string& __str, size_t __pos) const;   // 查找__str对象的字符串成员第一次出现的位置, 从__pos开始查找, 返回第一次出现的位置

    size_t rfind(char __c, size_t __pos) const;         // 从__pos位置开始逆序查找字符__c第一次出现的位置并返回(位置都是按顺序计算的)
    size_t rfind(const char *__s, size_t __pos) const;  // 从__pos位置开始逆序查找字符串__s第一次出现的位置并返回
    size_t rfind(const char *__s, size_t __pos, size_t __n) const;  // 从__pos位置开始逆序查找字符串__s的前__n个字符第一次出现的位置并返回
    size_t rfind(const string& __str, size_t __pos) const;      // 从__pos位置开始逆序查找__str对象的字符串成员第一次出现的位置并返回
*/
void test05()
{
    string str1 = "helldo-wllorld";
    string str2 = "ld";
    int loc;

    loc = str1.find('-', 2);
    cout << "char '-' find location is " << loc << endl;

    loc = str1.rfind('r', str1.size());
    cout << "char 'r' rfind location is " << loc << endl;


    loc = str1.find("ld", 1);
    cout << "substr \"ld\" find location is " << loc << endl;

    loc = str1.rfind("ld", 4);
    cout << "substr \"ld\" rfind location is " << loc << endl;

    loc = str1.find("llo-w", 1, 2);
    cout << "substr \"ll\" find location is " << loc << endl;

    loc = str1.rfind("llo-w", str1.size(), 2);
    cout << "substr \"ll\" rfind location is " << loc << endl;

    loc = str1.find(str2, 3);
    cout << "substr str2 find location is " << loc << endl;

    loc = str1.rfind(str2, 6);
    cout << "substr str2 rfind location is " << loc << endl;
}

/*
    六、string类中的替换函数
    string& replace(size_t __pos, size_t __n1, const char *__s);    // 从__pos位置开始的__n1个字符替换为字符串s
    string& replace(size_t __pos, size_t __n, const string& __str)  // 从__pos位置开始的__n个字符替换为__str对象的字符串成员
*/
void test06()
{
    string str1 = "aaabbbcccddd";
    str1.replace(3, 3, "^^^");
    cout << "str1 = " << str1 << endl;

    string str2 = "***";
    str1.replace(9, 3, str2);
    cout << "str1 = " << str1 << endl;
}

/*
    七、string类中的比较函数
    compare函数, >时返回大于0的数, <时返回小于0的数, ==时返回0
    按照ASCII码逐个字符进行比较, 出结果后, 后面的字符不再做比较

    int compare(const char *__s) const;         // 与字符串__s进行比较
    int compare(const string& __str) const;     // 与__str对象中的字符串成员进行比较
*/
void test07()
{
    string str1 = "aaabbbccc";
    string str2 = "aaabbbcccddd";
    int res;

    res = str1.compare("aaabbbccc");
    cout << "res = " << res << endl;

    res = str1.compare(str2);
    cout << "res = " << res << endl;
}

/*
    八、string类中的子串函数
    string substr(size_t __pos = 0UL, size_t __n = 18446744073709551615UL) const;    // 返回由__pos开始的__n个字符组成的字符串
    size_t size() const;    // 返回string对象的字符串成员的字节数, 不包括末尾0字符
*/
void test08()
{
    string str1 = "aaabbbccc";
    string str2 = str1.substr(0, 3);
    cout << "str2 = " << str2 << endl;
    size_t sz = str1.size();
    cout << "sz = " << sz << endl;
}

/*
    九、string类中的插入和删除操作
    string& insert(size_t __pos, size_t __n, char __c);     // 在__pos位置插入__n个字符__c
    string& insert(size_t __pos, const char *__s);          // 在__pos位置插入字符串s
    string& insert(size_t __pos1, const string &__str);     // 在__pos1位置插入str对象中的字符串成员
    string& erase(size_t __pos, size_t __n);                // 删除从__pos位置开始的__n个字符
*/
void test09()
{
    string str1 = "aaabbbcccddd";
    str1.insert(3, 3, 'e');
    cout << "str1 = " << str1 << endl;

    str1.insert(9, "fff");
    cout << "str1 = " << str1 << endl;

    string str2 = "ggg";
    str1.insert(18, str2);
    cout << "str1 = " << str1 << endl;

    str1.erase(3, 3);
    cout << "str1 = " << str1 << endl;
}

/*
    十、string类中的 string和c-style字符串转换
    const char* c_str() const;  // 以const char *类型返回string对象中的成员变量
*/
void test10()
{
    string str = "hello world";
    const char* s = str.c_str();
    cout << "s = " << s << endl;
}

/*
    十一、解析字符串
*/
void test11()
{
    string str = "www.hahaha.com.cn";

    vector<string> vec;
    string tmpStr;
    int start = 0;
    int pos = -1;

    while (true)
	{
		pos = str.find(".", start);

		if (pos == -1)
		{
			string tmpStr = str.substr(start, str.size() - start);
			vec.push_back(tmpStr);
			break;
		}

		string tmpStr = str.substr(start, pos - start);

		vec.push_back(tmpStr);

		start = pos + 1;
	}

	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << endl;
	}
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
    // test09();
    // test10();
    // test11();

    return 0;
}