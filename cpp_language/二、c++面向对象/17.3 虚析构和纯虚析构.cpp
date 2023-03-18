#include <iostream>
#include <string.h>
using namespace std;

class Animal{
    public:
        Animal()
        {
            cout << "Animal的构造函数的调用" << endl;
        }

        //如果子类中有指向堆区的成员变量, 那么要利用虚析构技术, 在delete的时候才能调用子类的析构函数
        virtual ~Animal()
        {
            cout << "Animal的析构函数的调用" << endl;
        }

        //纯虚析构需要有声明也需要有定义
        //如果一个类中有纯虚析构函数, 那么这个类属于抽象类, 无法实例化对象
        // virtual ~Animal() = 0;

        virtual void speak()
        {
            cout << "动物在说话" << endl;
        }
};

// 纯虚析构的定义
// Animal::~Animal()
// {
//     cout << "Animal的纯虚析构函数调用" << endl;
// }

class Cat : public Animal{
    public:
        Cat(char* name)
        {
            cout << "Cat的构造函数调用" << endl;
            m_Name = new char[strlen(name)+1];
            strcpy(m_Name, name);
        }

        ~Cat()
        {
            if(m_Name != NULL)
            {
                cout << "Cat的析构函数的调用" << endl;
                delete[] m_Name;
                m_Name = NULL;
            }
        }

        void speak()
        {
            cout << m_Name << "猫在说话" << endl;
        }

    public:
        char* m_Name;
};

void test01()
{
    Animal* animal = new Cat((char *)"Tom");
    animal->speak();

    delete animal;
}
/*
void test02()
{
    // 父转子: 向下类型转换, 不安全
    Animal *animal = new Animal;
    Cat *cat = (Cat *)animal;

    // 子转父: 向上类型转换, 安全
    Cat *cat = new Cat((char *)"Lucy");
    Animal *animal = (Animal *)cat;

    // 如果发生多态, 那么转换永远安全
}
*/
int main()
{
    test01();

    return EXIT_SUCCESS;
}