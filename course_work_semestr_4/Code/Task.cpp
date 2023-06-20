/* БС-14 Романюк М.Д.
 * Реалізація методів класу Task у файлі Task.cpp*/

#include "Task.h"
// -------------------------------------------------------------------------------------------------
// Конструктор за замовчуванням
Task::Task()
	: Assignment()
	, taskDesc("")
{}
// -------------------------------------------------------------------------------------------------
// Парметризований конструктор
Task::Task(int _id, int _priority, std::string _component, std::string _taskDesc)
	: Assignment(_id, _priority, _component)
	, taskDesc(_taskDesc)
{}
// -------------------------------------------------------------------------------------------------
// Сеттер опису завдання
void Task::setTaskDesc(std::string _taskDesc) { taskDesc = _taskDesc; }
// -------------------------------------------------------------------------------------------------
// Геттер опису завдання
std::string Task::getTaskDesc() const { return taskDesc; }
// -------------------------------------------------------------------------------------------------
// Перевизначений метод для створення завдання з клавіатури
void Task::createFromKeyboard()
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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	// Взяття значення опису завдання з вводу користувача
	std::cout << "Enter desc: ";
	std::getline(std::cin, taskDesc, '\n');
	// Перевірка на коректність вводу
	while (taskDesc.empty())
	{
		std::cout << "Task description can not be an empty string.\nEnter again: ";
		std::getline(std::cin, taskDesc, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// Перевизначений метод для виводу завдання в потік
void Task::show() const 
{
	Assignment::show();
	std::cout << "Task description: " << taskDesc << "\n\n";
}
// -------------------------------------------------------------------------------------------------
// Перевантажена дружня функція для серіалізації об'єкта завдання до потоку
std::ostream& operator<<(std::ostream& out, const Task& task)
{
	// Запис ID та пріоритет до вихідного файлового потоку
	out.write((char*)&task.id, sizeof(task.id));
	out.write((char*)&task.priority, sizeof(task.priority));
	// Запис розміру рядка назви компоненту та сам рядок до вихідного потоку
	size_t componentSize = task.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(task.component.data(), componentSize);
	// Запис розміру рядка опису завдання та сам рядок до вихідного потоку
	size_t taskDescSize = task.taskDesc.size();
	out.write((char*)&taskDescSize, sizeof(taskDescSize));
	out.write(task.taskDesc.data(), taskDescSize);
	// Повернення вихідного потоку
	return out;
}
// -------------------------------------------------------------------------------------------------
// Перевантажена дружня функція для десеріалізації об'єкта завдання з вхідного потоку
std::ifstream& operator>>(std::ifstream& in, Task* task)
{
	try {
		// Зчитування ID з вхідного потоку
		in.read((char*)&task->id, sizeof(task->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading task ID");
		}
		// Зчитування пріоритету з вхідного потоку
		in.read((char*)&task->priority, sizeof(task->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading task priority");
		}
		// Зчитування розміру рядка назви компонента
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// Зчитування рядка назви компонента
		task->component.resize(componentSize);
		in.read((char*)task->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component's name data");
		}
		// Зчитування розміру рядка опису завдання
		size_t taskDescSize;
		in.read((char*)&taskDescSize, sizeof(taskDescSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading task description size");
		}
		// Зчитування рядка опису завдання
		task->taskDesc.resize(taskDescSize);
		in.read((char*)task->taskDesc.data(), taskDescSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading task description data");
		}
	} // кінець try
	// Обробка усіх можливих винятків під час десеріалізації об'єкта з вхідного потоку
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// Повернення вхідного потоку
	return in;
} // кінець friend std::ifstream& operator>>(std::ifstream& in, Task* task)
// -------------------------------------------------------------------------------------------------
// Деструктор
Task::~Task()
{}
