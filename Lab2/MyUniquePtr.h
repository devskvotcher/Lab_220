#pragma once
template<typename T>
class MyUniquePtr {
private:
    T* ptr;
public:
    MyUniquePtr(T* ptr = nullptr) : ptr(ptr) {}
    ~MyUniquePtr() 
    {
        delete ptr;
    }
    MyUniquePtr(const MyUniquePtr&) = delete; // Запрет копирования
    MyUniquePtr& operator=(const MyUniquePtr&) = delete; // Запрет присваивания
    MyUniquePtr(MyUniquePtr&& other) : ptr(other.ptr) 
    {
        other.ptr = nullptr;
    }
    MyUniquePtr& operator=(MyUniquePtr&& other) 
    {
        if (this != &other) 
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    T& operator*() 
    {
        return *ptr;
    }
    T* operator->() 
    {
        return ptr;
    }
    explicit operator bool() const 
    {
        return ptr != nullptr;
    }  
    T* get() const 
    {
        return ptr;
    }
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const MyUniquePtr<T>& ptr) {
    if (ptr) {
        os << *ptr.get();
    }
    else {
        os << "nullptr";
    }
    return os;
}