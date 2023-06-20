/* БС-14 Романюк М.Д.
 * Реалізація методів класу Bug у файлі Bug.cpp */

#include "Bug.h"
 // -------------------------------------------------------------------------------------------------
// Конструктор за замовчуванням
Bug::Bug()
	: Assignment()
	, expRes("")
	, obtRes("")
{
}
// -------------------------------------------------------------------------------------------------
// Парметризований конструктор
Bug::Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _givenRes)
	: Assignment(_id, _priority, _component)
	, expRes(_expRes)
	, obtRes(_givenRes)
{
}
// -------------------------------------------------------------------------------------------------
// Сеттер очікуваних результатів 
void Bug::setExpRes(std::string _expRes) { expRes = _expRes; }
// -------------------------------------------------------------------------------------------------
// Сеттер отриманих результатів 
void Bug::setObtRes(std::string _givenRes) { obtRes = _givenRes; }
// -------------------------------------------------------------------------------------------------
// Геттерочікуваних результатів
std::string Bug::getExpRes() const { return expRes; }
// -------------------------------------------------------------------------------------------------
// Геттер отриманих результатів
std::string Bug::getObtRes() const { return obtRes; }
// -------------------------------------------------------------------------------------------------
// Перевизначений метод для створення дефекту з клавіатури
void Bug::createFromKeyboard()
{
	// Взяття значення ID з вводу користувача
	std::cout << "Enter ID: ";
	std::string inp;
	std::cin >> inp;
	id = atoi(inp.c_str());
	// Перевірка на коректність вводу
	while (id < 1)
	{
		std::cout << "ID must be a number greater then 0.\nEnter again: ";
		std::cin >> inp;
		id = atoi(inp.c_str());
	}
	// Взяття значення пріоритету з вводу користувача
	std::cout << "Enter priority: ";
	std::cin >> inp;
	priority = atoi(inp.c_str());
	// Перевірка на коректність вводу
	while (priority < 1)
	{
		std::cout << "Priority must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		priority = atoi(inp.c_str());
	}
	// Взяття значення назви компоненту з вводу користувача
	std::cout << "Enter component: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, component, '\n');
	// Перевірка на коректність вводу
	while (component.empty())
	{
		std::cout << "Component's name can not be an empty string.\nEnter again: ";
		std::getline(std::cin, component, '\n');
	}
	// Взяття значення очікуваних результатів
	std::cout << "Enter expected result: ";
	std::getline(std::cin, expRes, '\n');
	// Перевірка на коректність вводу
	while (expRes.empty())
	{
		std::cout << "Expected result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, expRes, '\n');
	}
	// Взяття значення отриманих результатів
	std::cout << "Enter obtained result: ";
	std::getline(std::cin, obtRes, '\n');
	// Перевірка на коректність вводу
	while (obtRes.empty())
	{
		std::cout << "Obtained result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, obtRes, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// Перевизначений метод для виводу завдання в потік
void Bug::show() const
{
	Assignment::show();
	std::cout << "Expected result: " << expRes 
			  << "\nObtained results: " << obtRes << "\n\n";
}
// Перевантажена дружня функція для серіалізації об'єкта дефекту до потоку
std::ostream& operator<<(std::ostream& out, const Bug& bug)
{
	// Запис ID та пріоритет до вихідного файлового потоку
	out.write((char*)&bug.id, sizeof(bug.id));
	out.write((char*)&bug.priority, sizeof(bug.priority));
	// Запис розміру рядка назви компоненту та сам рядок назви компоненту до вихідного потоку
	size_t componentSize = bug.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(bug.component.data(), componentSize);
	// Запис розміру рядка очікуваних результатів та сам рядок до вихідного потоку
	size_t expResSize = bug.expRes.size();
	out.write((char*)&expResSize, sizeof(expResSize));
	out.write(bug.expRes.data(), expResSize);
	// Запис розміру рядка отриманих результатів та сам рядок до вихідного потоку
	size_t obtResSize = bug.obtRes.size();
	out.write((char*)&obtResSize, sizeof(obtResSize));
	out.write(bug.obtRes.data(), obtResSize);
	// Повернення вихідного потоку
	return out;
}
// -------------------------------------------------------------------------------------------------
// Перевантажена дружня функція для десеріалізації об'єкта дефекту з вхідного потоку
std::istream& operator>>(std::istream& in, Bug* bug)
{
	try {
		// Зчитування ID з вхідного потоку
		in.read((char*)&bug->id, sizeof(bug->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug ID");
		}
		// Зчитування пріоритету з вхідного потоку
		in.read((char*)&bug->priority, sizeof(bug->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug priority");
		}
		// Зчитування розміру рядка назви компонента
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// Зчитування розміру рядка очікуваного результату назви компонента
		bug->component.resize(componentSize);
		in.read((char*)bug->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component data");
		}
		// Зчитування розміру рядка очікуваного результату
		size_t expResSize;
		in.read((char*)&expResSize, sizeof(expResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result size");
		}
		// Зчитування рядка очікуваного результату
		bug->expRes.resize(expResSize);
		in.read((char*)bug->expRes.data(), expResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result data");
		}
		// Зчитування розміру рядка отриманого результату
		size_t obtResSize = 0;
		in.read((char*)&obtResSize, sizeof(obtResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result size");
		}
		// Зчитування рядка отриманого результату
		bug->obtRes.resize(obtResSize);
		in.read((char*)bug->obtRes.data(), obtResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result data");
		}
	} // кінець try
	// Обробка усіх можливих винятків під час десеріалізації об'єкта з вхідного потоку
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// Повернення вхідного потоку
	return in;
} // кінець friend std::istream& operator>>(std::istream& in, Bug* bug)
// -------------------------------------------------------------------------------------------------
// Деструктор
Bug::~Bug()
{
}