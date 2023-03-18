#include<iostream>
#include <string>
using namespace std;

class Building;

class Relative
{
public:
	Relative();

	void visit();

	void visit2();

	Building * m_building;
};

class Building
{
   friend void Relative::visit();

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



Relative::Relative()
{
	this->m_building = new Building;
}

void Relative::visit()
{
	cout << "友元正在访问: " << this->m_building->m_SittingRoom << endl;
	cout << "友元正在访问: " << this->m_building->m_BedRoom << endl;
}

void Relative::visit2()
{
	cout << "友元正在访问: " << this->m_building->m_SittingRoom << endl;
	cout << "友元正在访问: " << this->m_building->m_BedRoom << endl;
}



int main(){
	Relative rt;
	rt.visit();
	rt.visit2();

	return EXIT_SUCCESS;
}