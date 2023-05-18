#pragma once
//Первое задание
//Ключевое слово constexpr указывает, что функция может быть вычислена на этапе компиляции, 
//если аргументы функции являются константными выражениями.
//Функция constexpr может быть полезна в ситуациях, когда нам нужно вычислить значение на этапе компиляции, 
//чтобы избежать накладных расходов времени
constexpr unsigned int factorial(int n) {
	return (n <= 1) ? 1 : (n * factorial(n - 1));
}
//Второе(а) задание
/*  Ключевое слово constexpr указывает, что функция может быть вычислена на этапе компиляции, 
	если аргументы функции являются константными выражениями.
    Цикл for выполняется до тех пор, пока символ в binary[i] не равен нулевому символу '\0', что означает конец строки.
    Внутри цикла происходит вычисление значения двоичного представления. 
	При каждой итерации выполняется сдвиг result на один бит влево (result << 1), 
	чтобы освободить место для нового бита. 
	Затем к результату прибавляется значение текущего бита, вычисленное как разность binary[i] - '0'. 
	Здесь символ '0' вычитается из binary[i], чтобы преобразовать символ в цифру.
	*/
	constexpr int binaryLiteralToValue(const char* binary)
{
	int result = 0;
	
	// Вычисление значения двоичного представления
	for (int i = 0; binary[i] != '\0'; i++)
	{
		result = (result << 1) + (binary[i] - '0');
	}

	return result;
}
//Определение пользовательского литерала
constexpr int operator"" _b(const char* binary)
{
	return binaryLiteralToValue(binary);
}
//Второе(б) задание
//std::bitset<sizeof(int)* CHAR_BIT>(value), который представляет целочисленное значение value в виде битового набора.
//Размер битового набора определяется как sizeof(int)* CHAR_BIT, где sizeof(int) - размер целого числа в байтах, 
//а CHAR_BIT - количество бит в байте.
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
//Третье задание
//шаблонный класс Range.
//Класс имеет параметры шаблона: T (тип данных), MinValue (минимальное значение диапазона) 
//и MaxValue (максимальное значение диапазона).
//Метод clamp() принимает значение value и ограничивает его в пределах диапазона. 
//Если тип T является арифметическим, метод проверяет, находится ли value вне диапазона, 
//и возвращает ближайшее граничное значение (MinValue или MaxValue), если value выходит за пределы. 
//Если тип T не является арифметическим, выводится сообщение об ошибке и метод возвращает значение типа T, 
//полученное при конструировании объекта T.
//template <typename T, T MinValue, T MaxValue>
//class Range
//{
//public:
//	T getMin() const { return MinValue; }
//	T getMax() const { return MaxValue; }
//
//	isInRange(T value) const
//	{
//		if constexpr (std::is_arithmetic_v<T>)
//		{
//			return value >= MinValue && value <= MaxValue;
//		}
//		else
//		{
//			std::cerr << "Range class can only be used with arithmetic types." << std::endl;
//			return false;
//		}
//	}
//
//	T clamp(T value) const
//	{
//		if constexpr (std::is_arithmetic_v<T>)
//		{
//			if (value < MinValue)
//				return MinValue;
//			else if (value > MaxValue)
//				return MaxValue;
//			else
//				return value;
//		}
//		else
//		{
//			std::cerr << "Range class can only be used with arithmetic types." << std::endl;
//			return T();
//		}
//	}
//};
template <typename T, T MinValue, T MaxValue>
class Range
{
public:
	constexpr T getMin() const { return MinValue; }
	constexpr T getMax() const { return MaxValue; }

	constexpr bool isInRange(T value) const
	{
		return value >= MinValue && value <= MaxValue;
	}

	constexpr T clamp(T value) const
	{
		if (value < MinValue)
			return MinValue;
		else if (value > MaxValue)
			return MaxValue;
		else
			return value;
	}
};
//Четвертое задание
template<typename T>
void printValue(const T& value) {
	if constexpr (std::is_pointer_v<T>)
		std::cout << *value << ' ';  // распечатываем значение по адресу, если T - указатель
	else
		std::cout << value << ' ';   // иначе распечатываем значение напрямую
}
//Функция print является шаблонной и принимает три параметра шаблона: Container - шаблон контейнера,
//Value - тип элементов контейнера, и Args... - дополнительные аргументы шаблона контейнера.
template<template<typename, typename...> class Container, typename Value, typename... Args>
void print(const Container<Value, Args...>& c) 
{
	for (const auto& v : c) {
		printValue(v);
	}
	std::cout << '\n';
}
//Функция print является шаблонной и принимает два параметра шаблона:
//T - тип элементов массива, и N - размер массива.
//Параметр arr является ссылкой на статический массив типа T и размера N, 
//который содержит элементы, которые нужно вывести.
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
/*Первое условие if constexpr проверяет, является ли T вектором типа U, и при этом U не является вектором типа T.
Если условие выполняется, то происходит циклическое сложение каждого элемента вектора a с значением b, и возвращается измененный вектор a.
Второе условие else if constexpr проверяет, является ли U вектором типа T, и при этом T не является вектором типа U. Если условие выполняется, то происходит циклическое сложение каждого элемента вектора b с значением a, и возвращается измененный вектор b.
Третье условие else if constexpr проверяет, являются ли типы T и U одинаковыми. Если условие выполняется, то возвращается результат сложения a + b.
Все условия if constexpr рассматриваются на этапе компиляции, и только одно из них будет выбрано для выполнения в зависимости от типов T и U.*/
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
	else
	{
		return T{};
	}
}
/*  Класс MyArray является шаблонным и имеет два параметра шаблона: T - тип элементов массива, и size - размер массива.
    Приватное поле ar представляет массив элементов типа T размером size.
    Конструктор по умолчанию constexpr MyArray() = default; является конструктором по умолчанию и использует значение по умолчанию для инициализации элементов массива ar.
    Конструктор constexpr MyArray(const T* data) принимает указатель data на обычный массив элементов типа T и инициализирует элементы массива ar значениями из data.*/
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
//Эти функции являются шаблонными функциями, определенными с использованием deduction guide (руководства по выводу типов) для класса MyArray.
//Первая специализация позволяет создавать объект MyArray<T, size> из ссылки на обычный массив типа T размером size.
template<typename T, size_t size>
MyArray(T(&)[size])->MyArray<T, size>;
//Вторая специализация позволяет создавать объект MyArray<T, size> из константной ссылки на обычный массив типа T размером size.
template<typename T, size_t size>
MyArray(const T(&)[size])->MyArray<T, size>;