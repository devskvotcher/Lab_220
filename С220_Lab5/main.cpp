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
	//������� 1. unique_ptr
	{

		//1.� - ���������� ���������� ���������� ���������
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			// ������������ ��� ������
			for (auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			__asm nop
			// �������� ������ ����� �������������
			for (auto& str_ptr : v) {
				delete str_ptr;
			}
			__asm nop
			// �� ����� ������� ������ �������, unique_ptr ������� ��� �������������
		} //???

		//1.b - ������������� ������� 1.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,
		 //� ������������ ��������
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			// ������������ ��� ������
			for (const auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			// ���������������
			// ��������, �� ����� �������� ������ ������
			if (!v.empty()) {
				*v[0] = "aa_modified";
			}
			// ����������� ������ �����, ����� ������� ���������
			for (const auto& str_ptr : v) {
				std::cout << *str_ptr << std::endl;
			}
			__asm nop
			// ��� ������������� ������� ����������� ������, ��� ������ unique_ptr
		} //???

		{//1.c - ��������� ������� 1.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  
			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("AAA"));
			vec.push_back(std::make_unique<std::string>("BBB"));
			vec.push_back(std::make_unique<std::string>("CCC"));

			for (auto& ptr : vec) {
				if (ptr != nullptr) {
					*ptr += "_1";
				}
			}

			// ����� ���������� �����
			for (const auto& ptr : vec) {
				if (ptr != nullptr) {
					std::cout << *ptr << '\n';
				}
			}
			__asm nop
		}

		{//1.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string
		 // // �������� ����������� ��������� �� ������������ ������ � 5 ����������
			std::unique_ptr<std::string[]> array_ptr(new std::string[5]);
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
// //� ������� ��������� [] ����� ���������� � ��������� ����� �������:
// // ���������� �������
for (int i = 0; i < 5; ++i) {
	array_ptr[i] = "String " + std::to_string(i);
}

// ����� ����������� �������
for (int i = 0; i < 5; ++i) {
	std::cout << array_ptr[i] << std::endl;
}
//����� ���������� ������������ ������?
//������, ���������� ������������ ��������, ����� ������������� �����������, ����� std::unique_ptr ����� ���������.
//��� ����������, ����� ����������� ������� ���������, � ������� �� ���������, ��� ���� ����� ������ reset().
//��������� std::unique_ptr ������������� ������� ������, �� ������� �� ���������, ��� ������ ������ �����������.
__asm nop
		}

		{//1.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������
//���������� ������
			// ������� ������ ���������� �� ����������� ��������� ������
			std::string** arStrPtr = new std::string * [3];
			arStrPtr[0] = new std::string("aa");
			arStrPtr[1] = new std::string("bb");
			arStrPtr[2] = new std::string("cc");

			// ������� unique_ptr � ���������������� delete-��������
			std::unique_ptr<std::string* [], Deleter> ptr(arStrPtr);

			// ������� �������� ����� ��� ��������
			for (int i = 0; i < 3; ++i) {
				std::cout << *ptr[i] << std::endl;
			}
			//� ���� ���� ��� ����������� unique_ptr ����� ������������� ������� ������� Deleter::operator(),
			//������� ��������� ������ ������� ����������� ���������� �������, � ����� �������������� ��������� ������.
			__asm nop
		}

		{//1.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator
			 // ������� � ��������� ������, ���������� unique_ptr �� std::string
			std::vector<std::unique_ptr<std::string>> vec;
			vec.push_back(std::make_unique<std::string>("aa"));
			vec.push_back(std::make_unique<std::string>("bb"));
			vec.push_back(std::make_unique<std::string>("cc"));

			// ������� ������ ������ � ���������� ���� �� ����
			std::list<std::unique_ptr<std::string>> lst;

			// ���������� std::make_move_iterator ��� ����������� ��������� ������� � ������
			std::copy(std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.end()), std::back_inserter(lst));

			// �������� ������, ����� ���������, ��� �� ��������� ����������� ��������
			vec.clear();

			// ��������� ������, ������ ��� ����������
			for (const auto& ptr : lst) {
				std::cout << *ptr << std::endl;
			}
			__asm nop

		}
		__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//������� 2.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� �������� ������ ������ =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()
	/*
	{

	//"��������":
	//������� writer1, writer2




	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������


	__asm nop
	}//�������� �����???

	*/
	{
	// ������� shared_ptr � ���������������� ��������-���������
	std::shared_ptr<std::ofstream> ofs(new std::ofstream("output.txt"), file_closer);

	if (!ofs->is_open()) {
		std::cerr << "Couldn't open the file\n";
		return 1;
	}

	Writer writer1(ofs, "writer1");
	Writer writer2(ofs, "writer2");

	srand(time(0));  // ������������� ���������� ��������� �����

	// �������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ���� ���� �������
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
//������� 3.
	{
		//��� ������ ��������� ���� string
		std::string strings[] = {"abc", "123", "qwerty", "#$%"};
		auto noop_deleter = [](std::string*) {};

		// ���������� ������������ ������� ��� ����� ����������
		auto compare = [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) { return *a < *b; };
		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� �) ��� ����������� � �) ��� ��������� �������
		//��������� � �������!
		// ������� ��������� � ������� ��� �������� ����� ���������� �� ������
		std::set<std::shared_ptr<std::string>, decltype(compare)> letterStrings(compare);
		std::vector<std::shared_ptr<std::string>> digitStrings;
		std::vector<std::shared_ptr<std::string>> nonAlphanumericStrings;
		//� std::set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 
		
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

		// ������� ������ �� ����� � ��������� �� �����
		int sum = 0;
		for (const auto& ptr : digitStrings) {
			std::cout << *ptr << "\n";
			sum += std::atoi(ptr->c_str());
		}

		std::cout << "�����: " << sum << "\n";

		// ������� ������ ��� ���� � ���� �� �����
		for (const auto& ptr : nonAlphanumericStrings) {
			std::cout << *ptr << "\n";
		}

		// ������� ������ � ������� �� �����
		for (const auto& ptr : letterStrings) {
			std::cout << *ptr << "\n";
		}
		__asm nop
		/******************************************************************************************/

		//� std::vector "����������" ������� ��� �����, ������� �������� ������ ����� 
		//������� �� �����
		//������� �����
		
		//std::vector<std::shared_ptr < std::string>>

		/******************************************************************************************/
		//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, �� �������� ����
		//� ������ �������


	}

	
/******************************************************************************************/
//������� 4. 
	{
		//����
		std::string ar[] = { "my", "Hello", "World" };
		std::vector<std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };

		// ���������� �������-�������, ������� ������ �� ������
		auto noop_deleter = [](std::string*) {};

		// �) ���������� ������� ��� ��������� ������� � ������
		for (std::string& element : ar) {
			v.push_back(std::shared_ptr<std::string>(&element, noop_deleter));
		}

		// �) ���������� ������� �� ��������
		std::sort(v.begin(), v.end(), [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) {
			return *a < *b;
			});

		// �) ����� ���������������� ������� �� �����
		for (const auto& element : v) {
			std::cout << *element << " ";
		}
		std::cout << std::endl;

		// ������������ ������ ���������� �������������, ��� ��� ������������ std::shared_ptr

		__asm nop
	}
	/***************************************************************/
		//������� 5. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - string
		//�������� �������: ��� ��� ��� ���...
		//�������� - shared_ptr (�������� �� ������ ��������...)
		//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

		//������ ������ human:
		//����������� - ��� ������������� ����� � ��������
		//����������� �����������, �������� ������������, move ???
		//����������� ����� child() - 
		//				������ ������� ������� � ������� ������� ��� ����������� ��������
		//				+ ������������ ��� ����� ������� � ���������� � ��������

		//������ ����������� ����������� ��������������� ������ ��� ���������� ����������

	{
		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//� ��� ��������� ���� - child():


		//� � ����� � ���� ������� ���� ����:


		//...
	}

	{
		std::shared_ptr<Human> grandM1(new Human("Eva"));
		std::shared_ptr<Human> grandF1(new Human("Adam"));
		//��� ����� � create
		std::string child1_name = "Alice";
		std::shared_ptr<Human> child1 = Human::create_child(grandM1, grandF1, child1_name);

		//��� ����� � create
		std::string child2_name = "Bob";
		std::shared_ptr<Human> child2 = Human::create_child(grandM1, grandF1, child2_name);

		std::string grandchild1_name = "Charlie";
		std::shared_ptr<Human> grandchild1 = Human::create_child(child1, child2, grandchild1_name);
		//��� ����� � create
		std::string grandchild2_name = "Dave";
		std::shared_ptr<Human> grandchild2 = Human::create_child(child1, child2, grandchild2_name);

		grandF1->print_family_tree(grandF1);
		child2->print_family_tree(child2);
		__asm nop
	}
	__asm nop
	return 0;
}
