#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include <bitset>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <stack>
#include <queue>
#include "Header.h"

int main()
{


	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 1. Реализуйте вычисление факториала с помощью constexpr-функции.
	//
	//Подсказки/напоминания: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>; (пока!)
	//		- но это выражение может включать вызов другой constexpr – функции, в частности рекурсивный
	//		  вызов 
	//		- если параметр рекурсивной constexpr- функции - это константа, компилятор вычислит результат
	//		  на этапе компиляции

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции (если в качестве
	//				параметра используется константа, известная компилятору на этапе компиляции).
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-функции:

	{	//Например:
		int ar[factorial(3)];

		//или
		constexpr int n = factorial(5);
		int ar1[n];

		//попробуйте:
		/*int m = 7;
		constexpr int n1 = factorial(m);
		int ar1[n1];*/
		constexpr int m = 7;
		constexpr int n1 = factorial(m);
		int ar2[n1];

		//а так?
		/*int n2 = factorial(m);*/
		constexpr int n2 = factorial(m);
		//Проверка, что размер массивов соответствует ожидаемому значению, вычисленному на этапе компиляции.
		std::cout << "Size of ar: " << sizeof(ar) / sizeof(int) << std::endl;
		std::cout << "Size of ar1: " << sizeof(ar1) / sizeof(int) << std::endl;
		std::cout << "Size of ar2: " << sizeof(ar2) / sizeof(int) << std::endl;
		__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 2a. Перевод с помощью пользовательского литерала из двоичного представления строкового
	//в значение, например: строку "100000000" -> в значение 256
	//Проверить результат посредством префикса 0b
	//Чтобы вызов пользовательского литерала выглядел просто и читаемо, например: 100000000_b
	//логично использовать пользовательский литерал с единственным параметром - const char*

	//Так как речь идет о литералах, логично вычислять значения на этапе компиляции
	// => реализуйте пользовательский литерал посредством constexpr - функций
	//Подсказка/напоминание: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>;
	//		- но это выражение может включать вызов другой constexpr – функции,
	//		- которая может быть рекурсивной (если параметр такой функции - это константа,
	//		  компилятор вычислит результат вызова рекурсивной функции на этапе компиляции)

	{
		// Пример использования пользовательского литерала
		int value = 100000000_b;
		std::cout << "Value: " << value << std::endl; // Вывод: Value: 256
		value = 0_b;
		std::cout << "Value: " << value << std::endl; // Вывод: Value: 256
		__asm nop

	}

	//Задание 2b. Перевод в строковое двоичное представление, например: 256 -> "0b100000000"
	//Так как строка может быть любой длины, логичнее и проще возвращать объект std::string
	//=> возвращаемое значение не может быть constexpr!
	//Подсказка: манипулятора std::bin пока нет => преобразование в двоичную строку
	//придется делать вручную
	//Подсказка: количество разрядов в байте определяет константа CHAR_BIT - <cstdint>

	{
		std::string sBin= 256_toBinStr;
		std::cout << "Binary=" << sBin << std::endl;
		__asm nop
	}


	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 3. constexpr - объекты 
	//Создать класс (шаблон класса?) для хранения и манипулирования диапазоном значений.
	//В классе должны быть:
	//	переменные для хранения минимального и максимального значений,
	//	методы для получения каждого из значений
	//	метод для проверки - попадает ли указанное значение в диапазон
	//	метод, который получает любое значение данного типа и формирует результирующее значение:
	//							если принадлежит диапазону, то его и возвращаем
	//							если меньше минимального значения, возвращаем минимальное
	//							если больше максимального значения, возвращаем максимальное

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции. 

	{
		Range<int, 0, 10> range;
		int value = -1;

		std::cout << "Min Value: " << range.getMin() << std::endl;
		std::cout << "Max Value: " << range.getMax() << std::endl;
		std::cout << "Is " << value << " in range? " << (range.isInRange(value) ? "Yes" : "No") << std::endl;
		std::cout << "Clamped value: " << range.clamp(value) << std::endl;
		__asm nop
	}
	/***************************************************************/
//Задание 4.
	/*
	Реализуйте шаблон функции для печати любых последовательностей (vector, list, deque, set и встроенного массива), которые могут содержать:
	•	как объекты любого типа,
	•	так и указатели на объекты любого типа (указатели распечатывать неинтересно => в этом случае следует получать значение по адресу)
	Подсказки: if constexpr
	*/
	{
		std::vector<int> vec{ 1, 2, 3, 4, 5 };
		std::list<std::string> list{ "Hello", "World" };
		std::deque<double> deq{ 1.1, 2.2, 3.3, 4.4 };
		std::set<char> set{ 'a', 'b', 'c', 'd' };
		int arr[] = { 6, 7, 8, 9, 10 };

		// pointers
		int a = 1;
		int* ptr_a = &a;
		std::vector<int*> vec_ptrs{ ptr_a, ptr_a, ptr_a };

		print(vec);
		print(list);
		print(deq);
		print(set);
		print(arr);
		print(vec_ptrs);
	}

	/***************************************************************/
	//Задание 5.
		/* Реализуйте шаблон функции сложения двух значений.
		Если первое слагаемое является вектором, то все элементы вектора нужно увеличить на значение второго параметра. При этом элементы вектора и второй параметр должны быть одного и того же типа.
		Подсказки: if constexpr, is_same
		*/
	{
		int a = 2;
		int b = 3;
		auto val = add(a, b);
		std::cout << "Result (5 expected): " << val << std::endl; // Output: 5

		int c = 4;
		std::vector<int> vec = { 1, 2, 3 };
		auto val2 = add(c, vec);
		std::cout << "Result (5, 6, 7 expected): ";
		for (const auto& v : val2) {
			std::cout << v << " "; // Output: 5 6 7
		}
		std::cout << std::endl;

		std::vector<int> vec2 = { 1, 2, 3 };
		int d = 3;
		auto val3 = add(vec2, d);
		std::cout << "Result (4, 5, 6 expected): ";
		for (const auto& v : val3) {
			std::cout << v << " "; // Output: 4 5 6
		}
		std::cout << std::endl;

	}


	/***************************************************************/
//Задание 6.
	/* 	Реализуйте шаблон функции вывода на печать значений элементов любого адаптера (stack, queue, priority_queue)
	Подсказки: if constexpr, is_same
	Предусмотрите вывод значений, если в адаптере хранятся указатели.
	*/
	{
		std::stack<int> stack;
		stack.push(1);
		stack.push(2);
		stack.push(3);
		std::cout << "Stack: ";
		printAdapter(stack); // Output: 3 2 1

		std::queue<int> queue;
		queue.push(1);
		queue.push(2);
		queue.push(3);
		std::cout << "Queue: ";
		printAdapter(queue); // Output: 1 2 3

		std::priority_queue<int> pQueue;
		pQueue.push(1);
		pQueue.push(2);
		pQueue.push(3);
		std::cout << "Priority Queue: ";
		printAdapter(pQueue); // Output: 3 2 1

		int a = 1, b = 2, c = 3;
		std::stack<int*> stackPtr;
		stackPtr.push(&a);
		stackPtr.push(&b);
		stackPtr.push(&c);
		std::cout << "Stack (pointers): ";
		printAdapter(stackPtr); // Output: 3 2 1

		__asm nop
	}

	/***************************************************************/
//Задание 7.
	/* 	Реализуйте шаблон constexpr функции Smth(), которая должна возвращать значения разного типа
	Подсказки: constexpr, if constexpr
	*/
	//constexpr int res1 = /*<вызов Smth()>;*/ //res1 = 1
	//constexpr double res2 = /*<вызов Smth()>; */ //res2 = 2.2
	//  /*constexpr???*/ std::string res3 = /*<вызов Smth()>; */ //res3 = "abc"
	{
		constexpr auto res1 = Smth<int>(); // res1 = 1
		constexpr auto res2 = Smth<double>(); // res2 = 2.2
		auto res3 = Smth<const char*>(); // res3 = "abc"
	}

	//***************************************************************/
	//Задание 8.

		/*Пользовательский deduction guide – для вывода типов параметров шаблона
		Задан шаблон класса, который инкапсулирует внедренный ограниченный массив известной
		размерности с элементами любого типа. */
		/*
		template<typename T, size_t size> class MyArray
			{
				T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
				…
				public:
				MyArray(const T*[, возможно другие параметры]);


			};

		*/
		/*
		//Требуется обеспечить работоспособность приведенных примеров использования.
			{
				MyArray<int, 5> ar1;//MyArray<int,5>
MyArray<char, 5> ar2{"ABCqwerty"};//MyArray<char,5>

				MyArray ar3{"ABC"}; //MyArray<char,4>

int ar[] = { 1,2,3 };
				MyArray ar4{ ar };

			}

			*/
			{
				MyArray<int, 5> ar1;//MyArray<int,5>
MyArray<char, 5> ar2{"ABCqwerty"};//MyArray<char,5>

				MyArray ar3{"ABC"}; //MyArray<char,4>

			int ar[] = { 1,2,3 };
				MyArray ar4{ ar };

			}
		


}
