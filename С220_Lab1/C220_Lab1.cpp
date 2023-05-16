//�������� 1:
// enum class
// initializer_list � ������������� ������ �������������
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
	//������� 1. 
	{
		enum class months: uint8_t { January, February, March, April, June, July, August, September, October, November, December };
		enum class weekDays:uint8_t { Monday, Tuesday, Wednesday, Thuesday, Friday, Saturday, Sunday };

		//months m = January;
	    months m = months::January;
		//�) ������� �������� (��� ������, ��� ���������� ��
		//������ ��������� ������������ ������������ �������
		//���������!)

		//if (m == weekDays::Monday) { // ������ ���������� }
		
		//�) ������������� ������������� ������

		// ���������� std::array ��� ����������� ������������� ������
			std::array<months, 3> year = { months::January, months::February, months::March };
			size_t n = sizeof(year); // ������ ������� � ������

			std::cout << "Size of year array: " << n << " bytes" << std::endl;
		
		//���������� 3 �����, ����� �������������� ��� � ������ ��������� 
		__asm nop
	}


	/**********************************************************/
		//������� 2. �������� � � ������� ������ �������������
		//��������� ���������� ������ � ���������� - string
		//� ������� range-based for ������������ ��� ����� � 	
		//������� ������� � ��������� ������� ������ ��������
		//�����������
	{
		std::vector<std::string> words = { "Hello", "world!", "C++", "Forever" };

		// �������������� ���� ���� � ������� ������� � �������������� range-based for
		for (std::string& word : words) {
			for (char& c : word) {
				c = std::toupper(static_cast<unsigned char>(c));
			}
		}

		// ����� ��������������� ����� �� �����
		for (const std::string& word : words) {
			std::cout << word << std::endl;
		}
		__asm nop
	}


	/**********************************************************/
		///������� 3. �������� � ��������� ����������
		//map ����� ��������� (3� � 3�) ����� �������, ����� �� �������� 
		//� �������� ����� �����, � � �������� �������� 
		//��������������� �� �������� ������������ ���� (string), 
		//������������ � ���� �����

		//3�. ������������������ map "�������" ����������� ������ �������������
		//� ������� range-based for � structured binding
		//������������ ����������, ��������: A: any, apple, away
	{
		// 3�. ������������������ map "�������" ����������� ������ �������������
		std::map<char, std::set<std::string>> words =
		{
			{'A', {"any", "apple", "away"}},
			{'B', {"banana", "blue", "boat"} },
			{'C', {"cat", "cloud", "coat"}}
		};

		// � ������� range-based for � structured binding ������������ ����������
		//std::cout << key << ": " << value << std::endl;
			//����������� ���, ����������� �� value
			for (const auto& [key, value] : words) {
				std::cout << key << ": ";
				for (const auto& word : value) {
					std::cout << word << ", ";
				}
				std::cout << std::endl;
			}
		


		__asm nop
	}

	//3�. �������� ������ map � ����������� �������� ������
	//��� ���������� �������.
	//� ������� range-based for � structured binding
	//������������ ����������, ��������: A: any, apple, away
	{
		// �������� ������� map � ������� �������
		std::map<char, std::set<std::string>> words;
		const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };

		// ���������� map � �������������� �������
		for (const char* word : s) {
			char firstLetter = std::toupper(word[0]);
			words[firstLetter].insert(word);
		}

		// ���������� ����������� map � �������������� range-based for � structured binding
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
		//������� 4. ������� ������� ��� ������ �� ������
		//��������� �������������������, �������� ����:
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
		///������� 5. 	
		//C������ ������� ��� "���������" ��������, ��������:
		//����: {1, -2, 5}, �����: {-1, 2, -5})
		//��������� �������� ���� std::string ����� ��������� "aBc1" -> "AbC1"
		//��������� �������������������, �������� ����:
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
		//������� 6. ����������� ������� ���������� �� ������
		//��������� �������������������, �������� ����
		//���������� ��� ���������� ����� ������������ ����������
		//�������� sort(), � ��� ������� ������� - ������-�������
	{
		std::vector<double> vd = { -3.3, 2.2, -1.1 };
		absSort(vd);
		for (const auto& e : vd) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		int ar[] = { -3, 2, -1 };
		absSort(ar); //������������� begin � end ������� � ������
		for (const auto& e : ar) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;


		__asm nop
	}


	/********************************************************/
		//������� 7.
		//�������� �������, ������� ����� ����������� �
		//���������� ������, ������ ������� 
		//�������� �������� ������ ��������� ���� 
		//������������������� ������ �����
		//� � ���������� ������� ����.

		//��������� 1: ��� ��� ������������������ ����� ����
		//������ �����, ������� ������� ������ ���������������
		//������� ������������ �� ����

		//��������� 2: ��������� � ����������� �������������
		//���������� copy() � transform(), � ������� 
		//���������������� �������� ������ � ���� �������
		//�������� ������-��������

		//��������:
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

	//	// ��� ������ �� �������� ��������� ����� ���������� �� ����������
	//	// ��-�� ����, ��� �������� + ��� ����� ��������� ������������
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
		//������� 8. ���������� �������, ������� ��������� ��������� ���������:	
		//�������������� ������������������ ������ ���� � ���������� ������ ����, 
		//��� (������) ���������� ������ ���� �� vector, list, deque, set 
		//� ���������� ���� �� ����, ��� � � �������������� ������������������ 

		//������� ������ "���������" �������� �������� ������������������ � ��� ������ ���������� 
		//�������� ��������� �������. ������� ������ ������-��������
		//�������� ������������������ ��� ���� �� ��������
	{
		//�������� 1:
		std::vector<int> v{ 1, 2, 3, 4, 5 };
		std::list<int> l; // ���� ������
		std::deque<int> d; // � ���� ��������

		Separate(v, l, d, [](const auto& e) { return e % 2 == 0; });

		std::cout << "������ ��������: ";
		for (const auto& e : l) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::cout << "�������� ��������: ";
		for (const auto& e : d) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop
	}
	{
		//2.
		//��������� �������� �������: �� ��������, ������� �������� � �������� ��������, � ���� //���������, ��������� - � ������
		double ar[] = { 0.8, 1.1, 33.3, -4.1, 5.5 };
		std::set<double> s; // ���� ��, ������� �������� � [0, 6]
		std::vector<double> v; // ���� ���������

		Separate(ar, s, v, [](const auto& e) { return e >= 0 && e <= 6; });

		std::cout << "�������� � ��������� [0, 6]: ";
		for (const auto& e : s) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		std::cout << "��������� ��������: ";
		for (const auto& e : v) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;

		__asm nop
	}


	/********************************************************/
		//������� 9. C ������� ��������� for_each()!!! 
		//(� �� count_if()) ��������� ������� ���� � �������
		//��������.
		//  ������������ ������ �������
	{
		
		char s[] = "Hello World!";
		int upperCaseCount = 0;

		std::for_each(std::begin(s), std::end(s) - 1, [&upperCaseCount](const auto& c) {
			if (std::isupper(c))
			{
				++upperCaseCount;
			}
			});

		std::cout << "���������� ���� � ������� ��������: " << upperCaseCount << std::endl;

		__asm nop
		
	}


	/********************************************************/
		//������� 10. ����������� ����������� enum � ��������� �������������  - enumToString
		// � �������� - stringToEnum

		//���������: 
		//***********
		//1. ��������������� ����������� ���������� ������ ��� ����� ����� ���-�� ������� =>
		//1.1 ����������� ��������� � ������������ ������ ���� ����������� => ��������������� ������
		//���� ������ ���� �����������, => ���������� ������ ����� ���� ������������ � ��������
		//����� � std::map

		//1.2 � ��� �������� (��������������� ���������� ����������)
		//����� ���� ������ � ���� ����� ����������� (�������� ������, ������, ��� �������� �� �����������) 
		//=> �������� ��������� std::map<string,<��������> >

		//1.3 �������� ��������� �++11 ���������� ������������� ���� ����� ���� ������� ������� � ����,
		//� �������� �� ���������� ������������� ����������� 

		//***********
		//2.1 ��� ��� ���� ������������ ������, �� enumToString � stringToEnum ������ ���� ����������
		//2.2 ������������ ����� ��������� ��� ������������ �������� � ������� ��������, �������
		//   ������ �� ������������� => ������!


		//***********
		//3. ����� �������� � map<string, <��������> > �� �������� �� ���� ������������, ��������� ��� ��������������
		//��������� ���������� (� ��������� ��������� � ����������� ������������� ��������� ����������)


		//***********

	{
		//��������:
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
		//����� ��������� ������������� ���������� enumMap ��� ������������ COLORS � ����������� ������� enumToString � stringToEnum � �������������� �������. 
		//� �������� ����������� ����� ���������������� �������� ��� ������ � � ������ ������ ������������ ���������� std::runtime_error.
	}

	return 0;
}
