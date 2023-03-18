#include<iostream>
#include <string>
using namespace std;

class Building
{
	//让 Relative 类作为 Building 类的友元, 可以访问Building类的私有成员数据
	friend class Relative;

public:
	Building();

	string m_SittingRoom;

private:
	string m_BedRoom;
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}


class Relative
{
public:

	Relative();
	
	~Relative();

	void visit();

	Building * m_building;
};

Relative::Relative()
{
	this->m_building =  new Building;
}

Relative::~Relative()
{
	delete this->m_building;
}

void Relative::visit()
{
	cout << "友元正在访问: " << this->m_building->m_SittingRoom << endl;
	cout << "友元正在访问: " << this->m_building->m_BedRoom << endl;
}

int main(){
	Relative rt;
	rt.visit();

	return EXIT_SUCCESS;
}