#pragma once
template<typename T>
class UniqueVector1 {
private:
    std::vector<T> data;
    T min_range;
    T max_range;

public:
    UniqueVector1(T min_range, T max_range, std::initializer_list<T> list)
        : min_range(min_range), max_range(max_range) {
        for (const auto& item : list) {
            add(item);
        }
    }

    void add(T value) {
        if (value >= min_range && value <= max_range &&
            std::find(data.begin(), data.end(), value) == data.end()) {
            data.push_back(value);
        }
    }

    void add(std::initializer_list<T> list) {
        for (const auto& item : list) {
            add(item);
        }
    }

    void remove(T value) {
        data.erase(std::remove(data.begin(), data.end(), value), data.end());
    }

    void remove(std::initializer_list<T> list) {
        for (const auto& item : list) {
            remove(item);
        }
    }

    void set_range(T min_range, T max_range) {
        this->min_range = min_range;
        this->max_range = max_range;

         data.erase(std::remove_if(data.begin(), data.end(), [min_range, max_range](T value) {
            return value < min_range || value > max_range;
            }), data.end());
    }
    //Не использовать std::function<bool(T, T)> comparator
    //будет принимать лямбду или функциональный объект
    //Либо свой предикат либо шаблон, который принимает лямбда выражения
   // void sort(std::function<bool(T, T)> comparator) {
   //     std::sort(data.begin(), data.end(), comparator);
   // }
    template<typename Comparator>
    void sort(Comparator comparator) {
        std::sort(data.begin(), data.end(), comparator);
    }

    typename std::vector<T>::iterator begin() {
        return data.begin();
    }

    typename std::vector<T>::iterator end() {
        return data.end();
    }
};