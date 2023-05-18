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
	//������� 1. ���������� ���������� ���������� � ������� constexpr-�������.
	//
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>; (����!)
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������, � ��������� �����������
	//		  ����� 
	//		- ���� �������� ����������� constexpr- ������� - ��� ���������, ���������� �������� ���������
	//		  �� ����� ����������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ���������� (���� � ��������
	//				��������� ������������ ���������, ��������� ����������� �� ����� ����������).
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-�������:

	{	//��������:
		int ar[factorial(3)];

		//���
		constexpr int n = factorial(5);
		int ar1[n];

		//����������:
		/*int m = 7;
		constexpr int n1 = factorial(m);
		int ar1[n1];*/
		constexpr int m = 7;
		constexpr int n1 = factorial(m);
		int ar2[n1];

		//� ���?
		/*int n2 = factorial(m);*/
		constexpr int n2 = factorial(m);
		//��������, ��� ������ �������� ������������� ���������� ��������, ������������ �� ����� ����������.
		std::cout << "Size of ar: " << sizeof(ar) / sizeof(int) << std::endl;
		std::cout << "Size of ar1: " << sizeof(ar1) / sizeof(int) << std::endl;
		std::cout << "Size of ar2: " << sizeof(ar2) / sizeof(int) << std::endl;
		__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 2a. ������� � ������� ����������������� �������� �� ��������� ������������� ����������
	//� ��������, ��������: ������ "100000000" -> � �������� 256
	//��������� ��������� ����������� �������� 0b
	//����� ����� ����������������� �������� �������� ������ � �������, ��������: 100000000_b
	//������� ������������ ���������������� ������� � ������������ ���������� - const char*

	//��� ��� ���� ���� � ���������, ������� ��������� �������� �� ����� ����������
	// => ���������� ���������������� ������� ����������� constexpr - �������
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>;
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������,
	//		- ������� ����� ���� ����������� (���� �������� ����� ������� - ��� ���������,
	//		  ���������� �������� ��������� ������ ����������� ������� �� ����� ����������)

	{
		// ������ ������������� ����������������� ��������
		int value = 100000000_b;
		std::cout << "Value: " << value << std::endl; // �����: Value: 256
		value = 1001_b;
		std::cout << "Value: " << value << std::endl; // �����: Value: 256
		__asm nop

	}

	//������� 2b. ������� � ��������� �������� �������������, ��������: 256 -> "0b100000000"
	//��� ��� ������ ����� ���� ����� �����, �������� � ����� ���������� ������ std::string
	//=> ������������ �������� �� ����� ���� constexpr!
	//���������: ������������ std::bin ���� ��� => �������������� � �������� ������
	//�������� ������ �������
	//���������: ���������� �������� � ����� ���������� ��������� CHAR_BIT - <cstdint>

	{
		std::string sBin= 9_toBinStr;
		std::cout << "Binary=" << sBin << std::endl;
		__asm nop
	}


	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 3. constexpr - ������� 
	//������� ����� (������ ������?) ��� �������� � ��������������� ���������� ��������.
	//� ������ ������ ����:
	//	���������� ��� �������� ������������ � ������������� ��������,
	//	������ ��� ��������� ������� �� ��������
	//	����� ��� �������� - �������� �� ��������� �������� � ��������
	//	�����, ������� �������� ����� �������� ������� ���� � ��������� �������������� ��������:
	//							���� ����������� ���������, �� ��� � ����������
	//							���� ������ ������������ ��������, ���������� �����������
	//							���� ������ ������������� ��������, ���������� ������������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ����������. 

	{
		constexpr Range<int, 3, 10> range;
		int value = 12;

		std::cout << "Min Value: " << range.getMin() << std::endl;
		std::cout << "Max Value: " << range.getMax() << std::endl;
		std::cout << "Is " << value << " in range? " << (range.isInRange(value) ? "Yes" : "No") << std::endl;
		std::cout << "Clamped value: " << range.clamp(value) << std::endl;
		
		int arr[range.getMin()]; //������ �������, ����� ��� � ����� ���������� �� ��
		__asm nop
	}
	/***************************************************************/
//������� 4.
	/*
	���������� ������ ������� ��� ������ ����� ������������������� (vector, list, deque, set � ����������� �������), ������� ����� ���������:
	�	��� ������� ������ ����,
	�	��� � ��������� �� ������� ������ ���� (��������� ������������� ����������� => � ���� ������ ������� �������� �������� �� ������)
	���������: if constexpr
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
	//������� 5.
		/* ���������� ������ ������� �������� ���� ��������.
		���� ������ ��������� �������� ��������, �� ��� �������� ������� ����� ��������� �� �������� ������� ���������. ��� ���� �������� ������� � ������ �������� ������ ���� ������ � ���� �� ����.
		���������: if constexpr, is_same
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
//������� 6.
	/* 	���������� ������ ������� ������ �� ������ �������� ��������� ������ �������� (stack, queue, priority_queue)
	���������: if constexpr, is_same
	������������� ����� ��������, ���� � �������� �������� ���������.
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
//������� 7.
	/* 	���������� ������ constexpr ������� Smth(), ������� ������ ���������� �������� ������� ����
	���������: constexpr, if constexpr
	*/
	//constexpr int res1 = /*<����� Smth()>;*/ //res1 = 1
	//constexpr double res2 = /*<����� Smth()>; */ //res2 = 2.2
	//  /*constexpr???*/ std::string res3 = /*<����� Smth()>; */ //res3 = "abc"
	{
		constexpr auto res1 = Smth<int>(); // res1 = 1
		constexpr auto res2 = Smth<double>(); // res2 = 2.2
		auto res3 = Smth<const char*>(); // res3 = "abc"
	}

	//***************************************************************/
	//������� 8.

		/*���������������� deduction guide � ��� ������ ����� ���������� �������
		����� ������ ������, ������� ������������� ���������� ������������ ������ ���������
		����������� � ���������� ������ ����. */
		/*
		template<typename T, size_t size> class MyArray
			{
				T ar[size]; //��� ���������� ������������� ��������� �������� ���� �� ��������� �����?
				�
				public:
				MyArray(const T*[, �������� ������ ���������]);


			};

		*/
		/*
		//��������� ���������� ����������������� ����������� �������� �������������.
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
