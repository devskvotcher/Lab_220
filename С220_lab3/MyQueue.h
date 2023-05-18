#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
template <typename T>
class MyQueue {
public:
//����������� �� ���������. �������������� ��������� �������� ������ ������: head (��������� ������), tail (�������� ������), count (���������� ���������), capacity (������� �������) � �������� ������ ��� ������ data �������� capacity.
    MyQueue() : head(0), tail(0), count(0), capacity(2), data(new T[capacity]) {}
//�����������, ����������� ������ �������������.������� �������, ������������� �� ���������� �� init_list.
    MyQueue(std::initializer_list<T> init_list) : MyQueue() {
        for (const auto& element : init_list) {
            push(element);
        }
    }
//����������� �����������. ������� ����� �������, ������� �������� �� other.
    MyQueue(const MyQueue& other)
        : head(0), tail(other.count), count(other.count), capacity(other.capacity), data(new T[other.capacity]) {
        for (std::size_t i = 0; i < count; ++i) {
            data[i] = other.data[(other.head + i) % other.capacity];
        }
    }
//����������� �����������. ������� ����� �������, ���������� ������� �� other.
    MyQueue(MyQueue&& other) noexcept : head(other.head), tail(other.tail), count(other.count), capacity(other.capacity), data(other.data) {
        other.data = nullptr;
        other.count = 0;
    }
//�����������, ��������� ������� �������� n � ����������� ��� �������� ��������� val.
    MyQueue(int n, const T& val) : head(0), tail(n), count(n), capacity(n), data(new T[capacity]) {
        std::fill(data, data + count, val);
    }

    //MyQueue& operator=(MyQueue&& other) noexcept {
    //    if (this != &other) {
    //        delete[] data;        
    //        swap(*this, other);
    //        other.data = nullptr;
    //        other.count = 0;
    //    }        
    //    return *this;
    //}
    MyQueue& operator=(MyQueue other) noexcept {
        swap(*this, other);
        return *this;
    }
    ~MyQueue() {
        delete[] data;
    }
//��������� ������� value � ����� �������. ���� ���������� ��������� ����� �������, ������ ������� ����������� � ������� ������ resize().
    void push(T value) {
        if (count == capacity - 1) {
            resize(capacity + 1); //*2
        }
        data[tail] = std::move(value);
        tail = (tail + 1) % capacity;
        ++count;
    }
//������� � ���������� ������� �� ������ �������. ���� ������� �����, ������������� ���������� std::out_of_range. ���� ���������� ��������� ���������� ������ �������� �������, ������ ������� ����������� ����� � ������� ������ resize().
    T pop() {
        if (count == 0) {
            throw std::out_of_range("Queue is empty");
        }
        T result = std::move(data[head]);
        head = (head + 1) % capacity;
        --count;
       // if (count < capacity / 4) {
       //     resize(capacity / 2);
       // }
        return result;
    }

    class iterator {
    public:
        iterator() : m_pQ(nullptr), m_i(0) {}
        iterator(const MyQueue* pQ, int i) : m_pQ(pQ), m_i(i) {}

        iterator& operator++() {
            if (m_pQ != nullptr) 
            {
        //        m_i = (m_i + 1) % m_pQ->capacity;
                m_i++;
            }
            return *this;
        }

        /*T& operator*() {
            if (m_pQ != nullptr) {
                return m_pQ->data[(m_pQ->head + m_i) % m_pQ->capacity];
            }
            throw std::out_of_range("Iterator out of range");
        }*/
        T operator*() {
            if (m_pQ != nullptr) {
                //return m_pQ->data[(m_pQ->head + m_i) % m_pQ->capacity];
                return m_pQ->data[m_i % m_pQ->capacity];
            }
            throw std::out_of_range("Iterator out of range");
        }

        bool operator!=(const iterator& other) const {
           // return m_pQ != other.m_pQ || m_i != other.m_i;
            return m_i != other.m_i;
        }

    private:
        const MyQueue* m_pQ;
        int m_i;
    };
    iterator begin() const {
        return iterator(this, head);
    }

    iterator end() const {
        return iterator(this, head + count);
    }
private:
    //���������������� ������ �� �������� ������� � �����. �������� ������� ������� � data �� new_capacity
    void resize(std::size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < count; ++i) {
            new_data[i] = std::move(data[(head + i) % capacity]);
        }
        delete[] data;
        data = new_data;
        head = 0;
        tail = count;
        capacity = new_capacity;
    }
//����������� �����, ����������� ����� ���������� ����� ����� ��������� ������ MyQueue.
//������������ ��� ���������� ���������� �������� ������ ����� ����� ��������� ��� 
//���������� �������� ������������.
//����������� ������ ��� �� ������� �������� ������� � ����� ���� ������ ��� ������������� 
//�������� ���������� ������
    static void swap(MyQueue& first, MyQueue& second) noexcept {
        using std::swap;
        swap(first.head, second.head);
        swap(first.tail, second.tail);
        swap(first.count, second.count);
        swap(first.capacity, second.capacity);
        swap(first.data, second.data);
    }

    std::size_t head;
    std::size_t tail;
    std::size_t count;
    std::size_t capacity;
    T* data;
};