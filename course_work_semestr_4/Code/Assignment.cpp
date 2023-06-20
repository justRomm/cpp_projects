/* БС-14 Романюк М.Д.
 * Реалізація методів класу Assingment у файлі Assingment.cpp */

#include "Assignment.h"
// Конструктор за замовчуванням
Assignment::Assignment()
	: id(0)
	, priority(0)
	, component("")
{}
// Парметризований конструктор
Assignment::Assignment(int _id, int _priority, std::string _component)
	: id(_id)
	, priority(_priority)
	, component(_component)
{}
// Сеттер ID
void Assignment::setId(int _id) { id = _id; }
// Сеттер пріоритету
void Assignment::setPriority(int _priority) { priority = _priority; }
// Сеттер назви компоненту проєкту
void Assignment::setComponent(std::string _component) { component = _component; }
// Геттер ID
int Assignment::getId() const { return id; }
// Геттер пріоритету
int Assignment::getPriority() const { return priority; }
// Геттер назви компоненту проєкту
std::string Assignment::getComponent() const { return component; }
// Віртуальний метод виводу завдання в потік
void Assignment::show() const
{
	std::cout	<< "Project ID: " << id
				<< "\nPriority: " << priority
				<< "\nComponent: " << component << "\n";
}
// Віртуальний деструктор
Assignment::~Assignment()
{}
