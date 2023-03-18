#include <iostream>
#include <string>
using namespace std;

class Phone
{
public:

	Phone(string pName)
	{
		cout << "phone 的普通有参构造调用" << endl;
		m_PhoneName = pName;
	}

	~Phone()
	{
		cout << "phone 的析构函数调用" << endl;
	}

	string m_PhoneName;
};

class Game
{
public:

	Game(string gName)
	{
		cout << "Game 的普通有参构造调用" << endl;
		m_GameName = gName;
	}
	
	~Game()
	{
		cout << "Game 的析构函数调用" << endl;
	}

	string m_GameName;
};


class Person
{
public:

	Person(string name, string pName, string gName) : m_Name(name), m_Phone(pName), m_Game(gName)
	{
		cout << "Person 的普通有参构造调用" << endl;
	}

	void PlayGame()
	{
		cout << m_Name << "拿着 << " << m_Phone.m_PhoneName << " >> 牌手机，玩着 :" << m_Game.m_GameName << endl;
	}

	~Person()
	{
		cout << "Person 的析构函数调用" << endl;
	}

	string m_Name;
	Phone m_Phone;
	Game  m_Game;
};


void test01()
{
	//当其他类对象作为本类成员, 按照构造顺序, 先构造其他类对象再构造自身, 析构的顺序和构造相反
	Person p("张三", "苹果", "王者荣耀");
	p.PlayGame();

	Person p2("李四", "三星", "消消乐");
	p2.PlayGame();
}



int main(){
	test01();
	
	return EXIT_SUCCESS;
}