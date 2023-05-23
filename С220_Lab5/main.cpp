#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include "Header.h"

int main()
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 1. unique_ptr
	{

		//1.а - обеспечьте корректное выполнение фрагмента
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			// Распечатайте все строки
			for (auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			__asm nop
			// Очистите память после использования
			for (auto& str_ptr : v) {
				delete str_ptr;
			}
			__asm nop
			// Не нужно очищать память вручную, unique_ptr сделает это автоматически
		} //???

		//1.b - модифицируйте задание 1.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			// Распечатайте все строки
			for (const auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			// Манипулирование
			// Допустим, мы хотим изменить первую строку
			if (!v.empty()) {
				*v[0] = "aa_modified";
			}
			// Распечатаем строки снова, чтобы увидеть изменения
			for (const auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			__asm nop
			// Нет необходимости вручную освобождать память, это делает unique_ptr
		} //???

		{//1.c - дополните задание 1.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  
			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("AAA"));
			vec.push_back(std::make_unique<std::string>("BBB"));
			vec.push_back(std::make_unique<std::string>("CCC"));

			for (auto& ptr : vec) {
				if (ptr != nullptr) {
					*ptr += "_1";
				}
			}

			// Вывод измененных строк
			for (const auto& ptr : vec) {
				if (ptr != nullptr) {
					std::cout << *ptr << '\n';
				}
			}
			__asm nop
		}

		{//1.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 // // Создание уникального указателя на динамический массив с 5 элементами
			std::unique_ptr<std::string[]> array_ptr(new std::string[5]);
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
// //С помощью оператора [] можно обращаться к элементам этого массива:
// // Заполнение массива
for (int i = 0; i < 5; ++i) {
	array_ptr[i] = "String " + std::to_string(i);
}

// Вывод содержимого массива
for (int i = 0; i < 5; ++i) {
	std::cout << array_ptr[i] << std::endl;
}
//Когда происходит освобождения памяти?
//Память, занимаемая динамическим массивом, будет автоматически освобождена, когда std::unique_ptr будет уничтожен.
//Это произойдет, когда уничтожится область видимости, в которой он определен, или явно будет вызван reset().
//Указатель std::unique_ptr автоматически удаляет объект, на который он указывает, при вызове своего деструктора.
__asm nop
		}

		{//1.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти
//Запаковать именно
			// Создаем массив указателей на динамически созданные строки
			std::string** arStrPtr = new std::string * [3];
			arStrPtr[0] = new std::string("aa");
			arStrPtr[1] = new std::string("bb");
			arStrPtr[2] = new std::string("cc");

			// Создаем unique_ptr с пользовательской delete-функцией
			std::unique_ptr<std::string* [], Deleter> ptr(arStrPtr);

			// Выводим значения строк для проверки
			for (int i = 0; i < 3; ++i) {
				std::cout << *ptr[i] << std::endl;
			}
			//В этом коде при уничтожении unique_ptr будет автоматически вызвана функция Deleter::operator(),
			//которая освободит память каждого динамически созданного объекта, а затем самостоятельно освободит память.
			__asm nop
		}

		{//1.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритма copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator
			 // Создаем и заполняем вектор, содержащий unique_ptr на std::string
			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("aa"));
			vec.push_back(std::make_unique<std::string>("bb"));
			vec.push_back(std::make_unique<std::string>("cc"));

			// Создаем пустой список с элементами того же типа
			std::list<std::unique_ptr<std::string>> lst;

			// Используем std::make_move_iterator для перемещения элементов вектора в список
			std::copy(std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.end()), std::back_inserter(lst));

			// Обнуляем вектор, чтобы убедиться, что мы корректно переместили элементы
			vec.clear();

			// Проверяем список, выводя его содержимое
			for (const auto& ptr : lst) {
				std::cout << *ptr << std::endl;
			}
			__asm nop

		}
		__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 2.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же объектом потока вывода =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()
	/*
	{

	//"писатели":
	//Создать writer1, writer2




	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку


	__asm nop
	}//закрытие файла???

	*/
	{
	// Создаем shared_ptr с пользовательской функцией-делитером
	std::shared_ptr<std::ofstream> ofs(new std::ofstream("output.txt"), file_closer);

	if (!ofs->is_open()) {
		std::cerr << "Couldn't open the file\n";
		return 1;
	}

	Writer writer1(ofs, "writer1");
	Writer writer2(ofs, "writer2");

	srand(time(0));  // Инициализация генератора случайных чисел

	// Заданное число итераций случайным образом позволяет одному из "писателей" записать в файл свою строчку
	for (int i = 0; i < 10; ++i) {
		if (rand() % 2 + 1 == 1) {
			writer1.write();
		}
		else {
			writer2.write();
		}
	}
	}
/***************************************************************/
//Задание 3.
	{
		//Дан массив элементов типа string
		std::string strings[] = {"abc", "123", "qwerty", "#$%"};
		auto noop_deleter = [](std::string*) {};

		// Определяем сравнивающую функцию для умных указателей
		auto compare = [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) { return *a < *b; };
		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
		//элементов в массиве!
		// Создаем множество и векторы для хранения умных указателей на строки
		std::set<std::shared_ptr<std::string>, decltype(compare)> letterStrings(compare);
		std::vector<std::shared_ptr<std::string>> digitStrings;
		std::vector<std::shared_ptr<std::string>> nonAlphanumericStrings;
		//В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы 
		
		for (std::string& s : strings) {
			bool onlyDigits = true;
			bool onlyLetters = true;
			for (char c : s) {
				if (!std::isdigit(c)) {
					onlyDigits = false;
				}
				if (!std::isalpha(c)) {
					onlyLetters = false;
				}
			}

			if (onlyLetters) {
				letterStrings.insert(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else if (onlyDigits) {
				digitStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
			else {
				nonAlphanumericStrings.push_back(std::shared_ptr<std::string>(&s, noop_deleter));
			}
		}

		// Выводим строки на экран и вычисляем их сумму
		int sum = 0;
		for (const auto& ptr : digitStrings) {
			std::cout << *ptr << "\n";
			sum += std::atoi(ptr->c_str());
		}

		std::cout << "Сумма: " << sum << "\n";

		// Выводим строки без букв и цифр на экран
		for (const auto& ptr : nonAlphanumericStrings) {
			std::cout << *ptr << "\n";
		}

		// Выводим строки с буквами на экран
		for (const auto& ptr : letterStrings) {
			std::cout << *ptr << "\n";
		}
		__asm nop
		/******************************************************************************************/

		//В std::vector "складываем" обертки для строк, которые содержат только цифры 
		//Выводим на экран
		//Находим сумму
		
		//std::vector<std::shared_ptr < std::string>>

		/******************************************************************************************/
		//сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
		//и просто выводим


	}

	
/******************************************************************************************/
//Задание 4. 
	{
		//Дано
		std::string ar[] = { "my", "Hello", "World" };
		std::vector<std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };

		// Определяем функцию-делитер, которая ничего не делает
		auto noop_deleter = [](std::string*) {};

		// а) Добавление оберток для элементов массива в вектор
		for (std::string& element : ar) {
			v.push_back(std::shared_ptr<std::string>(&element, noop_deleter));
		}

		// б) Сортировка вектора по алфавиту
		std::sort(v.begin(), v.end(), [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) {
			return *a < *b;
			});

		// в) Вывод отсортированного вектора на экран
		for (const auto& element : v) {
			std::cout << *element << " ";
		}
		std::cout << std::endl;

		// Освобождение памяти произойдет автоматически, так как используется std::shared_ptr

		__asm nop
	}
	/***************************************************************/
		//Задание 5. shared_ptr и weak_ptr
		//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
		//имя - string
		//возможно признак: жив или уже нет...
		//родители - shared_ptr (родители не всегда известны...)
		//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

		//Методы класса human:
		//конструктор - для инициализации имени и признака
		//конструктор копирования, оператор присваивания, move ???
		//статический метод child() - 
		//				должен создать создать и вернуть обертку для родившегося человека
		//				+ сформировать все связи ребенка с родителями и наоборот

		//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...
	}

	{
		std::shared_ptr<Human> grandM1(new Human("Eva"));
		std::shared_ptr<Human> grandF1(new Human("Adam"));
		//Все связи в create
		std::string child1_name = "Alice";
		std::shared_ptr<Human> child1 = Human::create_child(grandM1, grandF1, child1_name);

		//Все связи в create
		std::string child2_name = "Bob";
		std::shared_ptr<Human> child2 = Human::create_child(grandM1, grandF1, child2_name);

		std::string grandchild1_name = "Charlie";
		std::shared_ptr<Human> grandchild1 = Human::create_child(child1, child2, grandchild1_name);
		//Все связи в create
		std::string grandchild2_name = "Dave";
		std::shared_ptr<Human> grandchild2 = Human::create_child(child1, child2, grandchild2_name);

		grandF1->print_family_tree(grandF1);
		child2->print_family_tree(child2);
		__asm nop
	}
	__asm nop
	return 0;
}
