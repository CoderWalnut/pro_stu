#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
friend ostream &operator<<(ostream &out, MyString &str);
friend istream &operator>>(istream &in, MyString &str);

public:
MyString(const char *);
MyString(const MyString &);
~MyString();

//重载[]运算符
char &operator[](int index);

//重载 = 号运算符
MyString &operator=(const MyString &str);
MyString &operator=(const char *str);

//字符串拼接, 重载加号运算符
MyString operator+(const MyString &str);
MyString operator+(const char *str);

//字符串比较，重载 == 运算符
bool operator==(const MyString &str);
bool operator==(const char *str);

private:
    char *pString;
    int m_Size;
};

MyString::MyString(const char *str)
{
    this->pString = new char[strlen(str) + 1];
    strcpy(this->pString, str);
    this->m_Size = strlen(str);
}

MyString::MyString(const MyString &str)
{
    this->pString = new char[strlen(str.pString) + 1];
    strcpy(this->pString, str.pString);
    this->m_Size = strlen(str.pString);
}

MyString::~MyString()
{
    if(this->pString != NULL)
    {
        delete [] this->pString;
        this->pString = NULL;
    }
}

char &MyString::operator[](int index)
{
    return this->pString[index];
}

MyString &MyString::operator=(const MyString &str)
{
    if(this->pString != NULL)
    {
        delete [] this->pString;
        this->pString = NULL;
    }

    this->pString = new char[strlen(str.pString) + 1];
    strcpy(this->pString, str.pString);
    this->m_Size = strlen(this->pString);

    return *this; 
}

MyString &MyString::operator=(const char *str)
{
    if(this->pString != NULL)
    {
        delete [] this->pString;
        this->pString = NULL;
    }

    this->pString = new char[strlen(str) + 1];
    strcpy(this->pString, str);
    this->m_Size = strlen(str);

    return *this;
}

MyString MyString::operator+(const MyString &str)
{
    int newSize = this->m_Size + str.m_Size + 1;
    char *tmp = new char[newSize];
    memset(tmp, 0, sizeof(tmp));
    strcat(tmp, this->pString);
    strcat(tmp, str.pString);
    MyString newstring(tmp);
    delete [] tmp;
    tmp = NULL;
    return newstring;
}

MyString MyString::operator+(const char *str)
{
    int newSize = this->m_Size + strlen(str) + 1;
    char *tmp = new char[newSize];
    memset(tmp, 0, sizeof(tmp));
    strcat(tmp, this->pString);
    strcat(tmp, str);
    MyString newstring(tmp);
    delete [] tmp;
    tmp = NULL;
    return newstring;
}

bool MyString::operator==(const MyString &str)
{
    if( (strcmp(this->pString, str.pString) == 0) && (this->m_Size == str.m_Size) )
        return true;
    return false;
}

bool MyString::operator==(const char *str)
{
    if( (strcmp(this->pString, str) == 0) && (this->m_Size == strlen(str)) )
        return true;
    return false;
}

ostream &operator<<(ostream &out, MyString &str)
{
    out << str.pString;
    return out;
}

istream &operator>>(istream &in, MyString &str)
{
    if(str.pString != NULL)
    {
        delete [] str.pString;
        str.pString = NULL;
    }

    char buf[1024] = {0};
    in >> buf;
    str.pString = new char[strlen(buf) + 1];
    strcpy(str.pString, buf);
    str.m_Size = strlen(str.pString);

    return in;
}