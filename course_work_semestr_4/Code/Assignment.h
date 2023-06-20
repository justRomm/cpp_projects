/* БС-14 Романюк М.Д.
 * Визначення класу Assingment у файлі Assingment.h */

#if !defined(ASSIGNMENT_H_)
#define ASSIGNMENT_H_
#include <iostream>		// використовуєтсья для роботи з потоками вводу/виводу
#include <fstream>		// використовується для файлових потоків
#include <exception>	// використовується для роботи з винятками
#include <string>		// використовується для роботи з класом std::string
#include <ios>			// використовується для отримання розміру потоку
#include <limits>		// використовується для отримання числових обмежень
#include <sys/stat.h>	// використовується для перевірки існування файлу

// Абстрактний клас
class Assignment
{
protected:
	// ID завдання
	int id;
	// Пріоритет завдання
	int priority;
	// Назва компоненту проєкту
	std::string component;
public:
	// Конструктор за замовчуванням
	Assignment();
	// Парметризований конструктор
	Assignment(int _id, int _priority, std::string _component);
	// Віртуальний деструктор
	virtual ~Assignment();
	// Сеттер ID
	void setId(int _id);
	// Сеттер пріоритету
	void setPriority(int _priority);
	// Сеттер назви компоненту проєкту
	void setComponent(std::string _component);
	// Геттер ID
	int getId() const;
	// Геттер пріоритету
	int getPriority() const;
	// Геттер назви компоненту проєкту
	std::string getComponent() const;
	// Абстрактний метод для створення завдання з клавіатури
	virtual void createFromKeyboard() = 0;
	// Віртуальний метод виводу завдання в потік
	virtual void show() const;
};

#endif