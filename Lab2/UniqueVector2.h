#pragma once
template<typename T>
class UniqueVector2 : private std::vector<T> {
	T min_range;
	T max_range;
public:
	UniqueVector2(T min_range, T max_range, std::initializer_list<T> list)
		: min_range(min_range), max_range(max_range)
	{
		add(list);
	}
	// using std::vector<T>::begin;
	typename std::vector<T>::iterator begin()
	{
		return std::vector<T>::begin();
	}
	//using std::vector<T>::end;
	typename std::vector<T>::iterator end()
	{
		return std::vector<T>::end();
	}
	//using std::vector<T>::erase;
	typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator position)
	{
		return std::vector<T>::erase(position);
	}

	void add(std::initializer_list<T> list)
	{
		for (const auto& item : list)
		{
			add(item);
		}
	}
	void add(T value)
	{
		if (value >= min_range && value <= max_range &&
			std::find(begin(), end(), value) == end())
		{
			this->push_back(value);
		}
	}

	void remove(std::initializer_list<T> list) {
		for (const auto& item : list) {
			remove(item);
		}
	}
	void remove(T value) {
		std::vector<T>::erase(std::remove(std::vector<T>::begin(), std::vector<T>::end(), value), std::vector<T>::end());
	}


	void set_range(T min_range, T max_range)
	{
		this->min_range = min_range;
		this->max_range = max_range;

		std::vector<T>::erase(std::remove_if(this->begin(), this->end(), [this](T value) {
			return value < this->min_range || value > this->max_range;
			}), this->end());
	}

	template<typename Comparator>
	void sort(Comparator comparator) {
		std::sort(begin(), end(), comparator);
	}
};