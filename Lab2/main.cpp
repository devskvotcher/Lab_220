/*������������ ������ �2
initializer_list, move, default, delete, move ���������
������� 1. �������� �����, ������� ������ ������������� ���������������� ������� � ����������� ���������� ������ ���� � �������� ���������.
��������:
� ����� ��������� �������� ����� � ����������� ���������� � ������ ����� ��������[1, 10].������������ ����� �������� � ��� ������{ 2,-1,3,33, 5,2 }. � ���������� � ����� ������� ������ ��������� ��������{ 2,3,5 }
��������: ��� ������������� ��� ������������ �� ����� ������ ������� ��������, �������� �������������!��� ������� ������������� �������� ����� �������� ������!
�	��� �������� ��������� ����������� std::vector.
o	������� 1 : ������������ std::vector � �������� ����������� �������
o	������� 2 : ����������� ���� ����� �� std::vector � ��� ���� ����� ����� ������ ���� ������������ ������������
����������� ��� ��������!
�	���������� �����������, ������� ����� ��������� ����� ���������� ��������(�������� ����� �����������)
�	���������� ����� ���������� ������ ���������� ��������(�������� ����� �����������)
�	���������� ����� �������� ������ ���������� ��������(�������� ����� �����������)
�	������������� ����������� ��������� ��������� �������� ��������
�	���������� ����� ����������, ������� ����� ��������� � �������� ��������� ������� ����������(�� ����������� / �� �������� / �� �������)
�	� ������(�������� �� ��� ������) ������
�	���� ���������� � ����� ������ �� ����������� ������������� ����������� �������������
�	���������� ����������� ����������� �� ����� ��������� ������ �������� � ������ ���������, ��������:
vector<int> v;
std::copy(my.begin(), my.end(), �);

������� 2. ���������� ������ ������ MyUniquePTR, ������� �������� �������� ��� ��������� �� ������ ������ ����.
������ � ����� ������ ������������ ����������� �������� ����������� ����������� ��������.��������� ���������������� ������� �� ������� MyString :
{
	MyUniquePTR<MyString> p1(new MyString(�abc�));
	std::cout << p1->GetString();
	p1->SetNewString(�qwerty�);
	MyString  s2 = *p1;
	//MyUniquePTR< MyString > p2=p1; //����� ���������� ������ �������� ������ => 
	���������!
		If(p1) { std::cout << �No object!� } //� ��� ������ ��������
	MyUniquePTR< MyString > p3(new MyString(�vvv�));
	//p3 = p2; //� ����� ���������� ������ �������� ������
	vector< MyUniquePTR< MyString >> v; //��� �������������������???
	list< MyUniquePTR< MyString >> l;
	//��� ����������� �� v � l ???
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
	//--------������ ������------------������� 1---------------------------------
	UniqueVector1<int> uvec(1, 10, { 2, -1, 3, 33, 5, 2 });
	uvec.add({ 7, 8, 2, 10 });
	uvec.remove({ 2, 5 });
	uvec.set_range(1, 15);
	UniqueVector1<int> uv(0, 10, { 1, 5, 3, 7, 9 });
	uv.sort([](int a, int b) { return a > b; }); // ���������� �� ��������
	uvec.sort([](int a, int b) { return a < b; }); // �� �����������
	std::vector<int> vec;
	std::copy(uvec.begin(), uvec.end(), std::back_inserter(vec));
	for (const auto& value : vec) {
		std::cout << value << ' ';
	}std::cout << std::endl;
	//--------������ ������------------������� 2---------------------------------
	UniqueVector2<int> uvec2(1, 10, { 2, -1, 3, 33, 5, 2 });
	uvec2.add({ 7, 8, 2, 10 });
	uvec2.remove({ 2, 5 });
	uvec2.set_range(1, 15);
	UniqueVector2<int> uv2(0, 10, { 1, 5, 3, 7, 9 });
	uv2.sort([](int a, int b) { return a > b; }); // ���������� �� ��������
	uvec2.sort([](int a, int b) { return a < b; }); // �� �����������
	std::vector<int> vec2;
	std::copy(uvec2.begin(), uvec2.end(), std::back_inserter(vec2));
	for (const auto& value : vec2) {
		std::cout << value << ' ';
	}
	//-------������ ������------------------------------------------------
	MyUniquePtr<MyString> p1(new MyString("abc"));
	std::cout << p1->GetString() << std::endl;
	p1->SetNewString("qwerty");
	MyString s2 = *p1;
	// MyUniquePtr<MyString> p2 = p1; // ���������� ������ ������
	MyUniquePtr<MyString> p2(std::move(p1));
	
	if (!p1) {
		std::cout << "No object!" << std::endl;
	}
	MyUniquePtr<MyString> p3(new MyString("vvv"));
	// p3 = p2; // ���������� ������ ������
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
	// ����������� �� v � l �� ��������, ������ ��� MyUniquePtr �� ������������ �����������
	// ����� ��������������� std::move ��� ����������� ��������
	return 0;
}