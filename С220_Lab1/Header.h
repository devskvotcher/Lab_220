#pragma once
template<typename T>
void PrintAnyCont(const T& container) {
	for (const auto& elem : container) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}
template<typename T>
void NegateAllImpl(T& container, std::true_type) 
{
	for (auto& e : container) {
		e = -e;
	}
}

template<typename T>
void NegateAllImpl(T& container, std::false_type) 
{
	for (auto& e : container) {
		for (auto& ch : e) {
			if (std::isupper(ch)) {
				ch = std::tolower(ch);
			}
			else if (std::islower(ch)) {
				ch = std::toupper(ch);
			}
		}
	}
}

template<typename T>
void NegateAll(T& container) 
{
	using ValueType = typename std::remove_reference<decltype(*std::begin(container))>::type;
	NegateAllImpl(container, std::is_arithmetic<ValueType>());
}
template<typename T>
void absSort(T& container)
{
	std::sort(std::begin(container), std::end(container),
		[](const auto& a, const auto& b) {
			return std::abs(a) < std::abs(b);
		});
}
/*template<typename T1, typename T2>
auto SumCont(const T1& container1, const T2& container2)
{
    using ValueType = decltype(*std::begin(container1) + *std::begin(container2));
    size_t size1 = std::distance(std::begin(container1), std::end(container1));
    size_t size2 = std::distance(std::begin(container2), std::end(container2));
    std::vector<ValueType> result(std::max(size1, size2));
    
    auto it1 = std::begin(container1);
    auto it2 = std::begin(container2);
    for (auto& elem : result) {
        elem = (it1 != std::end(container1) ? *it1 : ValueType{}) + (it2 != std::end(container2) ? *it2 : ValueType{});
        if (it1 != std::end(container1)) ++it1;
        if (it2 != std::end(container2)) ++it2;
    }

    return result;
}*/
// D куыгде копируем первый контейнер copy();
	// tramsform() второй контейнер трансформируем с result и резульатат суммы записываем в result
	//Передать итератор на начало, и передать итератор на начало суммирующего контейнера
template<typename T1, typename T2>
auto SumCont(const T1& container1, const T2& container2)
{
	//определяется тип элементов, хранящихся в контейнерах container1 и container2
	using ValueType = decltype(*std::begin(container1) + *std::begin(container2));
	//Затем вычисляется количество элементов в каждом контейнере с помощью std::distance.
	size_t size1 = std::distance(std::begin(container1), std::end(container1));
	size_t size2 = std::distance(std::begin(container2), std::end(container2));
	//Создается новый вектор result размера, равного максимальному размеру из двух контейнеров. 
	//Это необходимо для того, чтобы иметь достаточное количество места для хранения результата.
	std::vector<ValueType> result(std::max(size1, size2));
	//С помощью std::copy копируются элементы из container1 в result.
	std::copy(std::begin(container1), std::end(container1), result.begin());
	//Затем с помощью std::transform складываются соответствующие элементы из container2 и result, и результат записывается в result.
	std::transform(std::begin(container2), std::end(container2), result.begin(), result.begin(),
		[](const auto& e1, const auto& e2) { return e1 + e2; });

	return result;
}
template<typename InCont, typename OutCont1, typename OutCont2, typename Predicate>
void Separate(const InCont& input, OutCont1& output1, OutCont2& output2, Predicate condition) {
	for (const auto& e : input) {
		if (condition(e)) {
			output1.insert(output1.end(), e);
		}
		else {
			output2.insert(output2.end(), e);
		}
	}
}
enum COLORS {
	RED,
	GREEN,
	BLUE,
};
template <typename T>
std::map<std::string, T> enumMap;

template <>
inline std::map<std::string, COLORS> enumMap<COLORS> = {
	{"red", RED},
	{"green", GREEN},
	{"blue", BLUE},
};

template <typename T>
std::string enumToString(T value) {
	for (const auto& [key, val] : enumMap<T>) {
		if (val == value) {
			return key;
		}
	}
	throw std::runtime_error("Unknown enum value");
}

template <typename T>
T stringToEnum(const std::string& str) {
	auto it = enumMap<T>.find(str);
	if (it != enumMap<T>.end()) {
		return it->second;
	}
	throw std::runtime_error("Unknown enum string");
}