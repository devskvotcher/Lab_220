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
		//Формируем Human
		std::shared_ptr<Human> child = std::make_shared<Human>(name);
		child->mother = mother;
		child->father = father;
		mother->children.push_back(child);
		father->children.push_back(child);
		return child;
		//Возвращаем Human
	}
	//В классе запретить все копирования, перемещения, присваивания = delete;
	void print_family_tree(const std::shared_ptr<Human>& person, int depth = 0) {
		// Создаем отступ
		std::string indent(15 * depth, ' ');

		//if (depth == 0) { // Распечатываем информацию о родителях только для "корневого" человека
		//	if (person->mother) {
		//		std::cout << indent << "Mother: " << person->mother->name << std::endl;
		//	}
		//	if (person->father) {
		//		std::cout << indent << "Father: " << person->father->name << std::endl;
		//	}
		//}
		// Выводим информацию о текущем человеке
		std::cout << indent << person->name << std::endl;

		// Выводим информацию о детях
		for (auto& child : person->children) {
			if (auto child_ptr = child.lock()) { // Проверяем, что ссылка еще валидна
				print_family_tree(child_ptr, depth + 1);
			}
		}
	}
	//Запрещаем копирование и присваивание
	Human(const Human&) = delete;
	Human& operator=(const Human&) = delete;

	//Запрещаем перемещение
	Human(Human&&) = delete;
	Human& operator=(Human&&) = delete;
	~Human() { std::cout << "Deleting: " << name << std::endl; }
};
// Функтор для освобождения памяти
struct Deleter {
	void operator()(std::string** ptr) const {
		// Пройдем по всем элементам массива и освободим память
		for (int i = 0; i < 3; ++i) {
			delete ptr[i];
		}
		// Не забудем освободить память, выделенную под массив указателей
		delete[] ptr; // Этого делать не нужно, так как unique_ptr сделает это автоматически
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
// Функция-делитер, которая закрывает файл
auto file_closer = [](std::ofstream* ofs) {
	ofs->close();
	delete ofs;
};