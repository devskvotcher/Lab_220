/*Лабораторная работа №2
initializer_list, move, default, delete, move итераторы
Задание 1. Создайте класс, который должен предоставлять функциональность вектора с УНИКАЛЬНЫМИ значениями любого типа в заданном диапазоне.
Например:
В нашей структуре хранятся целые с уникальными значениями и данных задан диапазон[1, 10].Пользователь хочет добавить в наш вектор{ 2,-1,3,33, 5,2 }. В результате в нашем векторе должны храниться значения{ 2,3,5 }
Внимание: при инициализации или присваивании НЕ нужно менять порядок значений, заданный пользователем!При наличии повторяющихся значений нужно оставить первое!
•	Для хранения элементов используйте std::vector.
o	Вариант 1 : использовать std::vector в качестве внедренного объекта
o	Вариант 2 : наследовать свой класс от std::vector – при этом важно каким должен быть спецификатор наследования
Реализовать оба варианта!
•	Реализуйте конструктор, который может принимать любое количество значений(значения могут повторяться)
•	Реализуйте метод добавления любого количества значений(значения могут повторяться)
•	Реализуйте метод удаления любого количества значений(значения могут повторяться)
•	Предусмотрите возможность изменения диапазона хранимых значений
•	Реализуйте метод сортировки, который будет принимать в качестве параметра условие сортировки(по возрастанию / по убыванию / по модулю…)
•	и другие(полезные на Ваш взгляд) методы
•	явно обозначьте – какие методы вы делегируете сгенерировать компилятору автоматически
•	реализуйте возможность копирования из нашей структуры данных значения в другое хранилище, например:
vector<int> v;
std::copy(my.begin(), my.end(), …);

Задание 2. Реализуйте шаблон класса MyUniquePTR, который является оберткой для указателя на объект любого типа.
Задача – класс должен обеспечивать единоличное владение динамически создаваемым объектом.Проверить функционирование шаблона на примере MyString :
{
	MyUniquePTR<MyString> p1(new MyString(“abc”));
	std::cout << p1->GetString();
	p1->SetNewString(“qwerty”);
	MyString  s2 = *p1;
	//MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку => 
	Исправьте!
		If(p1) { std::cout << ”No object!” } //а это должно работать
	MyUniquePTR< MyString > p3(new MyString(“vvv”));
	//p3 = p2; //и здесь компилятор должен выдавать ошибку
	vector< MyUniquePTR< MyString >> v; //как проинициализировать???
	list< MyUniquePTR< MyString >> l;
	//как скопировать из v в l ???
}
*/
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <functional>
#include "UniqueVector1.h"
#include "UniqueVector2.h"
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <cstring>
#include "MyString.h"
#include "MyUniquePtr.h"
int main()
{
	//--------Первая работа------------Вариант 1---------------------------------
	UniqueVector1<int> uvec(1, 10, { 2, -1, 3, 33, 5, 2 });
	uvec.add({ 7, 8, 2, 10 });
	uvec.remove({ 2, 5 });
	uvec.set_range(1, 15);
	UniqueVector1<int> uv(0, 10, { 1, 5, 3, 7, 9 });
	uv.sort([](int a, int b) { return a > b; }); // сортировка по убыванию
	uvec.sort([](int a, int b) { return a < b; }); // По возрастанию
	std::vector<int> vec;
	std::copy(uvec.begin(), uvec.end(), std::back_inserter(vec));
	for (const auto& value : vec) {
		std::cout << value << ' ';
	}std::cout << std::endl;
	//--------Первая работа------------Вариант 2---------------------------------
	UniqueVector2<int> uvec2(1, 10, { 2, -1, 3, 33, 5, 2 });
	uvec2.add({ 7, 8, 2, 10 });
	uvec2.remove({ 2, 5 });
	uvec2.set_range(1, 15);
	UniqueVector2<int> uv2(0, 10, { 1, 5, 3, 7, 9 });
	uv2.sort([](int a, int b) { return a > b; }); // сортировка по убыванию
	uvec2.sort([](int a, int b) { return a < b; }); // По возрастанию
	std::vector<int> vec2;
	std::copy(uvec2.begin(), uvec2.end(), std::back_inserter(vec2));
	for (const auto& value : vec2) {
		std::cout << value << ' ';
	}
	//-------Вторая работа------------------------------------------------
	MyUniquePtr<MyString> p1(new MyString("abc"));
	std::cout << p1->GetString() << std::endl;
	p1->SetNewString("qwerty");
	MyString s2 = *p1;
	// MyUniquePtr<MyString> p2 = p1; // Компилятор выдаст ошибку
	MyUniquePtr<MyString> p2(std::move(p1));
	
	if (!p1) {
		std::cout << "No object!" << std::endl;
	}
	MyUniquePtr<MyString> p3(new MyString("vvv"));
	// p3 = p2; // Компилятор выдаст ошибку
	std::vector<MyUniquePtr<MyString>> v;
	v.push_back(MyUniquePtr<MyString>(new MyString("abc")));
	v.push_back(MyUniquePtr<MyString>(new MyString("def")));
	v.push_back(MyUniquePtr<MyString>(new MyString("ghi")));
	for (const auto& ptr : v) {
		std::cout << ptr << std::endl;
	}
	std::list<MyUniquePtr<MyString>> l;
	for (auto& ptr : v) {
		l.push_back(std::move(ptr));
	}
	for (const auto& ptr : l) {
		std::cout << ptr << std::endl;
	}
	// Копирование из v в l не возможно, потому что MyUniquePtr не поддерживает копирование
	// Можно воспользоваться std::move для перемещения объектов
	return 0;
}