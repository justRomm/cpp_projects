/* БС-14 Романюк М.Д.
 * Визначення класу Task у файлі Task.h */

#if !defined(TASK_H_)
#define TASK_H_
#include "Assignment.h"

class Task final: public Assignment
{
private:
    // Опис завдання
	std::string taskDesc;
public:
    // Конструктор за замовчуванням
	Task();
    // Парметризований конструктор
	Task(int _id, int _priority, std::string _component, std::string _taskDesc);
    // Деструктор
    ~Task() override;
    // Сеттер опису завдання
	void setTaskDesc(std::string _taskDesc);
    // Геттер опису завдання
	std::string getTaskDesc() const;
    // Перевизначений метод для створення завдання з клавіатури
	void createFromKeyboard() override;
    // Перевизначений метод для виводу завдання в потік
	void show() const override;
    // Перевантажена дружня функція для серіалізації об'єкта завдання до потоку
    friend std::ostream& operator<<(std::ostream& out, const Task& task);
    // Перевантажена дружня функція для десеріалізації об'єкта завдання з вхідного потоку
    friend std::ifstream& operator>>(std::ifstream& in, Task* task);
};

#endif

