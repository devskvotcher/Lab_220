#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ostream>
class MyString 
{
private:
    char* str;

public:
    MyString(const char* s) 
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    MyString(const MyString& other) 
    {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    MyString& operator=(const MyString& other) 
    {
        if (this != &other) {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    ~MyString() 
    {
        delete[] str;
    }

    const char* GetString() const 
    {
        return str;
    }

    void SetNewString(const char* s) 
    {
        delete[] str;
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
};
std::ostream& operator<<(std::ostream& os, const MyString &Mystr)
{
    os << Mystr.GetString();
    return os;
}