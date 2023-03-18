#include<iostream>
using namespace std;
#include <fstream>
#include <string>

void test01()
{
	//写文件  o --  输出    
	ofstream  ofs("./test.txt", ios::out | ios::trunc);

	//ofs.open("./test.txt", ios::out | ios::trunc);  设置打开方式 以及路径

	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	ofs << "姓名：孙悟空" << endl;
	ofs << "年龄：999" << endl;
	ofs << "性别：男" << endl;

	//关闭文件
	ofs.close();

}


void test02()
{
	//读文件   i  -- 输入
	ifstream  ifs;
	ifs.open("./test.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };

	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}


	//第二种方式
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

	//第三种方式
	//string buf;
	//while ( getline(ifs,buf) )
	//{
	//	cout << buf << endl;
	//}


	//第四种方式
	char  c;
	while ( (c = ifs.get()) != EOF )
	{
		cout << c;
	}

	ifs.close();
}

int main(){

	//test01();
	test02();

	return EXIT_SUCCESS;
}