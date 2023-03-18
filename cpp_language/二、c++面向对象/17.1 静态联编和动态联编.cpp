#include <iostream>
using namespace std;

class Animal{
public:
//加 virtual 后变为虚函数
virtual void speak()
{
    cout << "动物在说话" << endl;
} 
};

class Cat : public Animal{
public:
void speak()
{
    cout << "小猫在说话" << endl;
}
};

class Dog : public Animal{
public:
void speak()
{
    cout << "小狗在说话" << endl;
}
};

/*
静态多态:
    函数重载; 运算符重载

动态多态产生的条件:
    先有继承关系
    父类中有虚函数, 子类重写父类中的虚函数
    父类的指针或引用 指向子类的对象
*/

//对于有父子关系的两个类 指针或引用 是可以直接转换的
void doSpeak(Animal& animal)  //Animal& animal = cat
{
    //如果地址早就绑定好了, 地址早绑定, 属于静态联编
    //如果想调用小猫说话, 这个时候函数的地址就不能早就绑定好, 而是在运行阶段再去绑定函数地址, 属于地址晚绑定, 叫动态联编
    animal.speak();
}

void test01()
{
    Cat cat;
    doSpeak(cat);

    Dog dog;
    doSpeak(dog);
}


int main()
{
    test01();

    return EXIT_SUCCESS;
}