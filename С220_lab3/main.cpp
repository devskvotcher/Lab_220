//������������ ������ �3
////initializer_list, move, default, delete, move ���������
//�������.������������ �����, ������� ��������� ���������������� ������� � ���������� ������ ����.
//������ ��������� ������� � ������������ �������, ��� ���� ������������ ������ ��� ����������� �����.���������: ��� ��� ������� � ��� ������������� ��������� ������, ��� ������� ����� ������ ���������� � �����, �  ������� ������ ��������� �� ������ ������� = > ���� ��������� ������� ������� ������������, �� ������ ������ ����� ��� ������������ = > ��������������� �����, ��������� ��������� � �������� ��������.
//�������� �� ��������� ������������� ����� ��������� ������, ����� ��������� ��������, ����� ������������ ������ push(), � ��������� ��������� � ������� �� �������� = > ��� ������������� ������ ������� �����������.
//��� ���������� ����� ���������� ����������� ������ � ������������ ������� = >
//�	������������� ������� ��������� ���������
//�	������ ��� ��������� ������������� �� ����������������
//��������!
//1.	������� ��������� ��� ������������� ������ ������!� ������������� ��������� �� ���� ������������� move - ���������
//2.	������� ������� �� ������ � ������� range - base - for
//��������� ������������� ����� �� ����������� ���� ���������.���������: ���� �� �� ������� �� ���������� ������ � �� ������������� ������������ � ������� ����� MyString, ������ �������� ��� �� std::string
//
//��������� �������� ������ �������� �� ������ ���������, �� � ���������� :
//
//MyQueue<MyString>  q1{ MyString(�AAA�), MyString(�qwerty�),<������_��������������> };
//
////������������� MyQueue � ����������� for:v
//for (const auto& el : q1) { std::cout << el << ' '; }
//
//MyString s(�abc�);
//q1.push(s);
//q1.push(MyString(�123�));
//MyString s1 = q1.pop();
//q1.push(�qqq�);
//MyQueue < MyString >  q2 = q1;
//MyQueue < MyString >  q22 = std::move(q1);
//
//MyQueue < MyString >  q3{ 10, MyString(�!�) }; //������� ������ ��������� 10 ��������� �� ������� �!� 
//q1 = q3;
//q2 = MyQueue < MyString >(5, MyString(� ? �));
//q1 = { MyString(�bbb�), MyString(�ssss�) };
//
//
#define _CRT_SECURE_NO_WARNINGS
#include "MyQueue.h"
#include "MyString.h"
#include <iostream>
int main()
{
	MyQueue<MyString>  q1{ MyString("AAA"), MyString("qwerty"), MyString("qwerwdqwdty"), MyString("davhvoe") };
	//������������� MyQueue � ����������� for:
	for (const auto& el : q1) 
	{ 
		std::cout << el << ' '; 
	}
	std::cout << std::endl;
	_asm nop
	MyString s("abc");
	q1.push(s);
	q1.push(MyString("123"));
	std::cout << s << std::endl;
	for (const auto& el : q1)
	{
		int i = 0;
		std::cout << el << ' ';		
	}
	std::cout << std::endl;
	_asm nop
	MyString s1 = q1.pop();
	std::cout << s1 << std::endl;
	_asm nop
	q1.push("qqq");
	for (const auto& el : q1)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	MyQueue <MyString>  q2 = q1; 
	for (const auto& el : q2)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	MyQueue <MyString>  q22 = std::move(q1);
	for (const auto& el : q22)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	MyQueue <MyString>  q3{ 10, MyString("!") }; //������� ������ ��������� 10 ��������� �� ������� �!� 
	for (const auto& el : q3)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	q1 = q3;
	for (const auto& el : q1)
	{
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	q2 = MyQueue < MyString >(5, MyString("?"));
	for (const auto& el : q2)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	q1 = { MyString("bbb"), MyString("ssss") };
	for (const auto& el : q1)
	{
		int i = 0;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	_asm nop
	//���-�� � ��������� ��������� capacity, �������� ������������� ������ �������������
	return 0;
}