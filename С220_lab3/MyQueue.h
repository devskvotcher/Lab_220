#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
template <typename T>
class MyQueue {
public:
    MyQueue() : head(0), tail(0), count(0), capacity(2), data(new T[capacity]) {}

    MyQueue(std::initializer_list<T> init_list) : MyQueue() {
        for (const auto& element : init_list) {
            push(element);
        }
    }

    MyQueue(const MyQueue& other) : head(0), tail(other.count), count(other.count), capacity(other.count), data(new T[capacity]) {
        std::copy(other.data + other.head, other.data + other.tail, data);
    }

    MyQueue(MyQueue&& other) noexcept : head(other.head), tail(other.tail), count(other.count), capacity(other.capacity), data(other.data) {
        other.data = nullptr;
        other.count = 0;
    }

    MyQueue(int n, const T& val) : head(0), tail(n), count(n), capacity(n), data(new T[capacity]) {
        std::fill(data, data + count, val);
    }

    MyQueue& operator=(MyQueue other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~MyQueue() {
        delete[] data;
    }

    void push(T value) {
        if (count == capacity) {
            resize(capacity * 2);
        }
        data[tail] = std::move(value);
        tail = (tail + 1) % capacity;
        ++count;
    }

    T pop() {
        if (count == 0) {
            throw std::out_of_range("Queue is empty");
        }
        T result = std::move(data[head]);
        head = (head + 1) % capacity;
        --count;
        if (count < capacity / 4) {
            resize(capacity / 2);
        }
        return result;
    }

    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;
        iterator() : ptr(nullptr), first(nullptr), last(nullptr), real_last(nullptr) {}
        iterator(const T* ptr, const T* first, const T* last, const T* real_last) : ptr(ptr), first(first), last(last), real_last(real_last) {}

        iterator& operator++() {
            if (ptr == real_last - 1 && first <= last) {
                ptr = first;
            }
            else {
                ++ptr;
            }
            return *this;
        }

        pointer operator->() const {
            return ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        reference operator*() const {
            return *ptr;
        }

    private:
        const T* ptr;
        const T* first;
        const T* last;
        const T* real_last;
    };
    
    iterator begin() const {
        return iterator(data + head, data, data + capacity, data + tail);
    }

    iterator end() const {
        return iterator(data + tail, data, data + capacity, data + tail);
    }

private:
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