//Практика 1:
// enum class
// initializer_list и универсальные списки инициализации
// auto
// decltype
// lambda 
// template variable


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <array>
#include <algorithm>
#include <iterator>
#include "Header.h"



int main()
{
	setlocale(0, "Rus");
	//Задание 1. 
	{
		enum class months: uint8_t { January, February, March, April, June, July, August, September, October, November, December };
		enum class weekDays:uint8_t { Monday, Tuesday, Wednesday, Thuesday, Friday, Saturday, Sunday };

		//months m = January;
	    months m = months::January;
		//а) уберите проблемы (это значит, что КОМПИЛЯТОР не
		//должен позволять программисту осуществлять опасные
		//сравнения!)

		//if (m == weekDays::Monday) { // Ошибка компиляции }
		
		//б) оптимизируйте использование памяти

		// Используем std::array для оптимизации использования памяти
			std::array<months, 3> year = { months::January, months::February, months::March };
			size_t n = sizeof(year); // Размер массива в байтах

			std::cout << "Size of year array: " << n << " bytes" << std::endl;
		
		//Получилось 3 байта, нужно оптимизировать что б размер получился 
		__asm nop
	}


	/**********************************************************/
		//Задание 2. Создайте и с помощью списка инициализации
		//заполните значениями вектор с элементами - string
		//С помощью range-based for преобразуйте все буквы в 	
		//верхний регистр а остальные символы должны остаться
		//неизменными
	{
		std::vector<std::string> words = { "Hello", "world!", "C++", "Forever" };

		// Преобразование всех букв в верхний регистр с использованием range-based for
		for (std::string& word : words) {
			for (char& c : word) {
				c = std::toupper(static_cast<unsigned char>(c));
			}
		}

		// Вывод преобразованных строк на экран
		for (const std::string& word : words) {
			std::cout << word << std::endl;
		}
		__asm nop
	}


	/**********************************************************/
		///Задание 3. Создайте и заполните значениями
		//map двумя способами (3а и 3б) таким образом, чтобы он содержал 
		//в качестве ключа букву, а в качестве значения 
		//отсортированную по алфавиту совокупность слов (string), 
		//начинающихся с этой буквы

		//3а. Проинициализируйте map "вручную" посредством списка инициализации
		//С помощью range-based for и structured binding
		//распечатайте содержимое, например: A: any, apple, away
	{
		// 3а. Проинициализируйте map "вручную" посредством списка инициализации
		std::map<char, std::set<std::string>> words =
		{
			{'A', {"any", "apple", "away"}},
			{'B', {"banana", "blue", "boat"} },
			{'C', {"cat", "cloud", "coat"}}
		};

		// С помощью range-based for и structured binding распечатайте содержимое
		//std::cout << key << ": " << value << std::endl;
			//Диапазонный фор, распечатать по value
			for (const auto& [key, value] : words) {
				std::cout << key << ": ";
				for (const auto& word : value) {
					std::cout << word << ", ";
				}
				std::cout << std::endl;
			}
		


		__asm nop
	}

	//3б. Создайте пустой map и используйте заданный массив
	//для выполнения задания.
	//С помощью range-based for и structured binding
	//распечатайте содержимое, например: A: any, apple, away
	{
		// Создание пустого map и задание массива
		std::map<char, std::set<std::string>> words;
		const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };

		// Заполнение map с использованием массива
		for (const char* word : s) {
			char firstLetter = std::toupper(word[0]);
			words[firstLetter].insert(word);
		}

		// Распечатка содержимого map с использованием range-based for и structured binding
		for (const auto& [key, value] : words) {
			std::cout << key << ": ";
			for (const auto& word : value) {
				std::cout << word << ", ";
			}
			std::cout << std::endl;
		}
		__asm nop
	}


	/*********************************************************/
		//Задание 4. создать функцию для вывода на печать
		//элементов последовательностей, заданных ниже:
	{
		std::vector<double> vd = { 1.1, 2.2, 3.3 };
		PrintAnyCont(vd);

		std::string s("abc");
		PrintAnyCont(s);

		int ar[] = { 1, 2, 3 };
		PrintAnyCont(ar);

		std::initializer_list<int> il{ 3, 4, 5 };
		PrintAnyCont(il);


		__asm nop
	}


	/********************************************************/
		///Задание 5. 	
		//Cоздать функцию для "отрицания" значений, например:
		//было: {1, -2, 5}, стало: {-1, 2, -5})
		//изменение объектов типа std::string может выглядеть "aBc1" -> "AbC1"
		//элементов последовательностей, заданных ниже:
	{
		std::vector<double> vd{ 1.1, 2.2, 3.3 };
		NegateAll(vd);
		for (const auto& e : vd) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::list<std::string> ls{ "aBc", "Qwerty", "n12" };
		NegateAll(ls);
		for (const auto& e : ls) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		int ar[]{ 1, 2, 3 };
		NegateAll(ar);
		for (const auto& e : ar) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop

	}


	/********************************************************/
		//Задание 6. Реализовать функцию сортировки по модулю
		//элементов последовательностей, заданных ниже
		//Собственно для сортировки можно использовать обобщенный
		//алгоритм sort(), а для задания условия - лямбда-функцию
	{
		std::vector<double> vd = { -3.3, 2.2, -1.1 };
		absSort(vd);
		for (const auto& e : vd) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		int ar[] = { -3, 2, -1 };
		absSort(ar); //Универсальный begin и end глянуть в лекции
		for (const auto& e : ar) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;


		__asm nop
	}


	/********************************************************/
		//Задание 7.
		//Напишите функцию, которая будет формировать и
		//возвращать вектор, каждый элемент 
		//которого является суммой элементов двух 
		//последовательностей РАЗНОЙ длины
		//и с элементами РАЗНОГО типа.

		//Подсказка 1: так как последовательности могут быть
		//разной длины, логично сделать размер результирующего
		//вектора максимальным из двух

		//Подсказка 2: подумайте о возможности использования
		//алгоритмов copy() и transform(), в котором 
		//трансформирующее действие удобно в свою очередь
		//задавать лямбда-функцией

		//например:
	{
		std::vector<int> v{ 1, 2, 3, 4 };
		std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };

		auto res1 = SumCont(v, l);
		for (const auto& e : res1) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		auto res2 = SumCont(ar, ll);
		for (const auto& e : res2) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

	//	// При работе со строками результат будет отличаться от ожидаемого
	//	// из-за того, что оператор + для строк выполняет конкатенацию
		std::set<std::string> s{ "abc", "qwerty", "my" };
		std::deque<const char*> d{ "111", "22" };

		auto res3 = SumCont(s, d);
		for (const auto& e : res3) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop
	}


	/********************************************************/
		//Задание 8. Реализуйте функцию, которая принимает следующие параметры:	
		//сформированную последовательность любого типа с элементами любого типа, 
		//два (пустых) контейнера любого типа из vector, list, deque, set 
		//с элементами того же типа, что и у сформированной последовательности 

		//Функция должна "разложить" значения заданной последовательности в два пустых контейнера 
		//согласно заданному условию. Условие задать лямбда-функцией
		//Исходная последовательность при этом не меняется
	{
		//Например 1:
		std::vector<int> v{ 1, 2, 3, 4, 5 };
		std::list<int> l; // сюда четные
		std::deque<int> d; // а сюда нечетные

		Separate(v, l, d, [](const auto& e) { return e % 2 == 0; });

		std::cout << "Четные элементы: ";
		for (const auto& e : l) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::cout << "Нечетные элементы: ";
		for (const auto& e : d) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop
	}
	{
		//2.
		//Разложить согласно условию: те значения, которые попадают в заданный диапазон, в один //контейнер, остальные - в другой
		double ar[] = { 0.8, 1.1, 33.3, -4.1, 5.5 };
		std::set<double> s; // сюда те, которые попадают в [0, 6]
		std::vector<double> v; // сюда остальные

		Separate(ar, s, v, [](const auto& e) { return e >= 0 && e <= 6; });

		std::cout << "Значения в диапазоне [0, 6]: ";
		for (const auto& e : s) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::cout << "Остальные значения: ";
		for (const auto& e : v) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop
	}


	/********************************************************/
		//Задание 9. C помощью алгоритма for_each()!!! 
		//(а не count_if()) посчитать сколько букв в верхнем
		//регистре.
		//  Использовать лямбда функцию
	{
		
		char s[] = "Hello World!";
		int upperCaseCount = 0;

		std::for_each(std::begin(s), std::end(s) - 1, [&upperCaseCount](const auto& c) {
			if (std::isupper(c))
			{
				++upperCaseCount;
			}
			});

		std::cout << "Количество букв в верхнем регистре: " << upperCaseCount << std::endl;

		__asm nop
		
	}


	/********************************************************/
		//Задание 10. Реализовать конвертацию enum в строковое представление  - enumToString
		// и наоборот - stringToEnum

		//Подсказки: 
		//***********
		//1. Соответствующие именованным константам строки все равно нужно где-то хранить =>
		//1.1 Именованные константы в перечислении должны быть уникальными => соответствующие строки
		//тоже должны быть уникальными, => уникальные строки могут быть использованы в качестве
		//ключа в std::map

		//1.2 а вот значения (соответствующие именованым константам)
		//могут быть любыми и даже могут повторяться (упрощаем задачу, считая, что значения НЕ повторяются) 
		//=> подходит контейнер std::map<string,<значение> >

		//1.3 Согласно стандарту С++11 переменные перечислимого типа могут быть разного размера и типа,
		//а хотелось бы обеспечить универсальную конвертацию 

		//***********
		//2.1 Так как типы перечислений разные, то enumToString и stringToEnum должны быть шаблонными
		//2.2 Пользователь может ошибиться или злонамеренно передать в функции значения, которым
		//   ничего не соответствует => защита!


		//***********
		//3. Чтобы действия с map<string, <значение> > не зависили от типа перечисления, подумайте над использованием
		//шаблонной переменной (в частности вспомните о возможности специялизации шаблонной переменной)


		//***********

	{
		//Например:
	/*
			COLORS c1;
			try {
				c1 = stringToEnum<COLORS>("blue");
			}
			catch (...)
			{
			//...
			}


			auto Str = enumToString(c1);
	*/
		try {
			auto c1 = stringToEnum<COLORS>("blue");
			std::cout << "COLORS value: " << c1 << std::endl;
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		try {
			auto str = enumToString(RED);
			std::cout << "COLORS string: " << str << std::endl;
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		__asm nop
		//Здесь создается специализация переменной enumMap для перечисления COLORS и реализуются функции enumToString и stringToEnum с использованием шаблона. 
		//В функциях выполняется поиск соответствующего значения или строки и в случае ошибки генерируется исключение std::runtime_error.
	}

	return 0;
}
