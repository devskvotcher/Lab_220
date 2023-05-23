#pragma once
class Human
{
	std::string name;
	std::shared_ptr<Human> mother;
	std::shared_ptr<Human> father;
	std::vector<std::weak_ptr<Human>> children;
public:
	Human(const std::string& name) : name(name) {}
	static std::shared_ptr<Human> create_child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father, std::string& name)
	{
		//��������� Human
		std::shared_ptr<Human> child = std::make_shared<Human>(name);
		child->mother = mother;
		child->father = father;
		mother->children.push_back(child);
		father->children.push_back(child);
		return child;
		//���������� Human
	}
	//� ������ ��������� ��� �����������, �����������, ������������ = delete;
	void print_family_tree(const std::shared_ptr<Human>& person, int depth = 0) {
		// ������� ������
		std::string indent(15 * depth, ' ');

		//if (depth == 0) { // ������������� ���������� � ��������� ������ ��� "���������" ��������
		//	if (person->mother) {
		//		std::cout << indent << "Mother: " << person->mother->name << std::endl;
		//	}
		//	if (person->father) {
		//		std::cout << indent << "Father: " << person->father->name << std::endl;
		//	}
		//}
		// ������� ���������� � ������� ��������
		std::cout << indent << person->name << std::endl;

		// ������� ���������� � �����
		for (auto& child : person->children) {
			if (auto child_ptr = child.lock()) { // ���������, ��� ������ ��� �������
				print_family_tree(child_ptr, depth + 1);
			}
		}
	}
	//��������� ����������� � ������������
	Human(const Human&) = delete;
	Human& operator=(const Human&) = delete;

	//��������� �����������
	Human(Human&&) = delete;
	Human& operator=(Human&&) = delete;
	~Human() { std::cout << "Deleting: " << name << std::endl; }
};
// ������� ��� ������������ ������
struct Deleter {
	void operator()(std::string** ptr) const {
		// ������� �� ���� ��������� ������� � ��������� ������
		for (int i = 0; i < 3; ++i) {
			delete ptr[i];
		}
		// �� ������� ���������� ������, ���������� ��� ������ ����������
		delete[] ptr; // ����� ������ �� �����, ��� ��� unique_ptr ������� ��� �������������
	}
};
class Writer {
public:
	Writer(std::shared_ptr<std::ofstream> ptr, std::string name) : stream_ptr(ptr), name(std::move(name)) {}

	void write() {
		*stream_ptr << "String from " << name << "\n";
	}

private:
	std::shared_ptr<std::ofstream> stream_ptr;
	std::string name;
};
// �������-�������, ������� ��������� ����
auto file_closer = [](std::ofstream* ofs) {
	ofs->close();
	delete ofs;
};