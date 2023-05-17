#pragma once
//������ �������
//�������� ����� constexpr ���������, ��� ������� ����� ���� ��������� �� ����� ����������, 
//���� ��������� ������� �������� ������������ �����������.
//������� constexpr ����� ���� ������� � ���������, ����� ��� ����� ��������� �������� �� ����� ����������, 
//����� �������� ��������� �������� �������
constexpr unsigned int factorial(int n) {
	return (n <= 1) ? 1 : (n * factorial(n - 1));
}
//������(�) �������
/*  �������� ����� constexpr ���������, ��� ������� ����� ���� ��������� �� ����� ����������, 
	���� ��������� ������� �������� ������������ �����������.
    ���� for ����������� �� ��� ���, ���� ������ � binary[i] �� ����� �������� ������� '\0', ��� �������� ����� ������.
    ������ ����� ���������� ���������� �������� ��������� �������������. 
	��� ������ �������� ����������� ����� result �� ���� ��� ����� (result << 1), 
	����� ���������� ����� ��� ������ ����. 
	����� � ���������� ������������ �������� �������� ����, ����������� ��� �������� binary[i] - '0'. 
	����� ������ '0' ���������� �� binary[i], ����� ������������� ������ � �����.
	*/
	constexpr int binaryLiteralToValue(const char* binary)
{
	int result = 0;
	
	// ���������� �������� ��������� �������������
	for (int i = 0; binary[i] != '\0'; i++)
	{
		result = (result << 1) + (binary[i] - '0');
	}

	return result;
}
//����������� ����������������� ��������
constexpr int operator"" _b(const char* binary)
{
	return binaryLiteralToValue(binary);
}
//������(�) �������
//std::bitset<sizeof(int)* CHAR_BIT>(value), ������� ������������ ������������� �������� value � ���� �������� ������.
//������ �������� ������ ������������ ��� sizeof(int)* CHAR_BIT, ��� sizeof(int) - ������ ������ ����� � ������, 
//� CHAR_BIT - ���������� ��� � �����.
std::string operator"" _toBinStr(unsigned long long value)
{
	/*std::string binaryString = "0b" + std::bitset<sizeof(int)* CHAR_BIT>(value).to_string();
	return binaryString;*/
	std::bitset<sizeof(unsigned long long)* CHAR_BIT> binaryBits(value);
	std::string binaryString = binaryBits.to_string();
	size_t firstOne = binaryString.find('1');
	if (firstOne != std::string::npos) {
		binaryString = binaryString.substr(firstOne);
	}
	return "0b" + binaryString;
}
//������ �������
//��������� ����� Range.
//����� ����� ��������� �������: T (��� ������), MinValue (����������� �������� ���������) 
//� MaxValue (������������ �������� ���������).
//����� clamp() ��������� �������� value � ������������ ��� � �������� ���������. 
//���� ��� T �������� ��������������, ����� ���������, ��������� �� value ��� ���������, 
//� ���������� ��������� ��������� �������� (MinValue ��� MaxValue), ���� value ������� �� �������. 
//���� ��� T �� �������� ��������������, ��������� ��������� �� ������ � ����� ���������� �������� ���� T, 
//���������� ��� ��������������� ������� T.
template <typename T, T MinValue, T MaxValue>
class Range
{
public:
	T getMin() const { return MinValue; }
	T getMax() const { return MaxValue; }

	bool isInRange(T value) const
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			return value >= MinValue && value <= MaxValue;
		}
		else
		{
			std::cerr << "Range class can only be used with arithmetic types." << std::endl;
			return false;
		}
	}

	T clamp(T value) const
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			if (value < MinValue)
				return MinValue;
			else if (value > MaxValue)
				return MaxValue;
			else
				return value;
		}
		else
		{
			std::cerr << "Range class can only be used with arithmetic types." << std::endl;
			return T();
		}
	}
};
//��������� �������
template<typename T>
void printValue(const T& value) {
	if constexpr (std::is_pointer_v<T>)
		std::cout << *value << ' ';  // ������������� �������� �� ������, ���� T - ���������
	else
		std::cout << value << ' ';   // ����� ������������� �������� ��������
}
//������� print �������� ��������� � ��������� ��� ��������� �������: Container - ������ ����������,
//Value - ��� ��������� ����������, � Args... - �������������� ��������� ������� ����������.
template<template<typename, typename...> class Container, typename Value, typename... Args>
void print(const Container<Value, Args...>& c) 
{
	for (const auto& v : c) {
		printValue(v);
	}
	std::cout << '\n';
}
//������� print �������� ��������� � ��������� ��� ��������� �������:
//T - ��� ��������� �������, � N - ������ �������.
//�������� arr �������� ������� �� ����������� ������ ���� T � ������� N, 
//������� �������� ��������, ������� ����� �������.
template<typename T, std::size_t N>
void print(const T(&arr)[N]) {
	for (const auto& v : arr) {
		printValue(v);
	}
	std::cout << '\n';
}

template<typename T, typename U>
auto add(T a, U b) {
	if constexpr (std::is_same_v<T, std::vector<U>> && !std::is_same_v<U, std::vector<T>>) {
		for (auto& element : a) {
			element += b;
		}
		return a;
	}
	else if constexpr (std::is_same_v<U, std::vector<T>> && !std::is_same_v<T, std::vector<U>>) {
		for (auto& element : b) {
			element += a;
		}
		return b;
	}
	else if constexpr (std::is_same_v<T, U>) {
		return a + b;
	}
}
/*������ ������� if constexpr ���������, �������� �� T �������� ���� U, � ��� ���� U �� �������� �������� ���� T.
���� ������� �����������, �� ���������� ����������� �������� ������� �������� ������� a � ��������� b, � ������������ ���������� ������ a.
������ ������� else if constexpr ���������, �������� �� U �������� ���� T, � ��� ���� T �� �������� �������� ���� U. ���� ������� �����������, �� ���������� ����������� �������� ������� �������� ������� b � ��������� a, � ������������ ���������� ������ b.
������ ������� else if constexpr ���������, �������� �� ���� T � U �����������. ���� ������� �����������, �� ������������ ��������� �������� a + b.
��� ������� if constexpr ��������������� �� ����� ����������, � ������ ���� �� ��� ����� ������� ��� ���������� � ����������� �� ����� T � U.*/
template <typename T>
void printAdapter(T& adapter) {
	if constexpr (std::is_same_v<T, std::stack<typename T::value_type>> || std::is_same_v<T, std::priority_queue<typename T::value_type>>) {
		while (!adapter.empty()) {
			if constexpr (std::is_pointer_v<typename T::value_type>) {
				std::cout << *(adapter.top()) << " ";
			}
			else {
				std::cout << adapter.top() << " ";
			}
			adapter.pop();
		}
	}
	else if constexpr (std::is_same_v<T, std::queue<typename T::value_type>>) {
		while (!adapter.empty()) {
			if constexpr (std::is_pointer_v<typename T::value_type>) {
				std::cout << *(adapter.front()) << " ";
			}
			else {
				std::cout << adapter.front() << " ";
			}
			adapter.pop();
		}
	}
	std::cout << '\n';
}
template <typename T>
constexpr auto Smth() {
	if constexpr (std::is_same_v<T, int>) {
		return 1;
	}
	else if constexpr (std::is_same_v<T, double>) {
		return 2.2;
	}
	else if constexpr (std::is_same_v<T, const char*>) {
		return "abc";
	}
}
/*  ����� MyArray �������� ��������� � ����� ��� ��������� �������: T - ��� ��������� �������, � size - ������ �������.
    ��������� ���� ar ������������ ������ ��������� ���� T �������� size.
    ����������� �� ��������� constexpr MyArray() = default; �������� ������������� �� ��������� � ���������� �������� �� ��������� ��� ������������� ��������� ������� ar.
    ����������� constexpr MyArray(const T* data) ��������� ��������� data �� ������� ������ ��������� ���� T � �������������� �������� ������� ar ���������� �� data.*/
template<typename T, size_t size>
class MyArray
{
	T ar[size]{};

public:
	constexpr MyArray() = default;

	constexpr MyArray(const T* data) {
		for (size_t i = 0; i < size; ++i) {
			ar[i] = data[i];
		}
	}
};
//��� ������� �������� ���������� ���������, ������������� � �������������� deduction guide (����������� �� ������ �����) ��� ������ MyArray.
//������ ������������� ��������� ��������� ������ MyArray<T, size> �� ������ �� ������� ������ ���� T �������� size.
template<typename T, size_t size>
MyArray(T(&)[size])->MyArray<T, size>;
//������ ������������� ��������� ��������� ������ MyArray<T, size> �� ����������� ������ �� ������� ������ ���� T �������� size.
template<typename T, size_t size>
MyArray(const T(&)[size])->MyArray<T, size>;