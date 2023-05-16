#define _CRT_SECURE_NO_WARNINGS
#pragma once
class MyString {
private:
    char* str;

public:
    MyString() : str(new char[1] {'\0'}) {} // Конструктор по умолчанию
    MyString(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    MyString(const MyString& other) {
        if (other.str) {
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        else {
            str = nullptr;
        }
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) 
        {
            delete[] str;
            if (other.str) {
                str = new char[strlen(other.str) + 1];
                strcpy(str, other.str);
            }
            else {
                str = nullptr;
            }
        }
        return *this;
    }

    MyString(MyString&& other) noexcept : str(other.str) {
        other.str = nullptr;
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            other.str = nullptr;
        }
        return *this;
    }

    ~MyString() {
        delete[] str;
    }

    const char* GetString() const {
        return str;
    }

    void SetNewString(const char* s) {
        delete[] str;
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    bool operator==(const MyString& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }
};

std::ostream& operator<<(std::ostream& os, const MyString& Mystr) {
    os << Mystr.GetString();
    return os;
}