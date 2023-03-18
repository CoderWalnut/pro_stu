#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Person
{
public:

	Person( char * name ,int age )
	{
		m_Name = (char *) malloc(strlen(name) + 1);

		strcpy(m_Name, name);

		m_Age = age;
	}
	
	//如果有成员变量内存开辟在堆区, 不提供该拷贝构造函数, 使用编译器提供的拷贝构造函数, 会出现 double free
	//编译器提供的拷贝构造函数做的是浅拷贝
	//提供拷贝构造函数在堆区申请内存做的是深拷贝
	//用深拷贝来解决浅拷贝出现的问题
	Person(const Person &p)
	{
	   m_Name =(char*)malloc(strlen(p.m_Name) + 1);
	   strcpy(m_Name, p.m_Name);
	   m_Age = p.m_Age;
	}

	~Person()
	{
		if (m_Name != NULL)
		{
			cout << "Person析构调用" << endl;
			free(m_Name);
			m_Name = NULL;
		}
	}

	char *m_Name;
	int m_Age;
};


void test01()
{
	Person p((char *)"德玛西亚", 18);
	std::cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;

	Person p2(p);
	std::cout << "姓名： " << p2.m_Name << " 年龄： " << p2.m_Age << endl;
}

int main(){

	test01();

	return EXIT_SUCCESS;
}