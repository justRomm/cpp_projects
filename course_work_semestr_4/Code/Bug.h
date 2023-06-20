/* БС-14 Романюк М.Д.
 * Визначення класу Bug у файлі Bug.h */

#if !defined(bug_h_)
#define bug_h_
#include "Assignment.h"

class Bug final : public Assignment
{
private:
    // Очікувані результати
	std::string expRes;
    // Отримані результати
    std::string obtRes;
public:
    // Конструктор за замовчуванням
	Bug();
    // Парметризований конструктор
	Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _obtRes);
    // Деструктор
    ~Bug() override;
    // Сеттер очікуваних результатів
    void setExpRes(std::string _expRes);
    // Сеттер отриманих результатів
    void setObtRes(std::string _obtRes);
    // Геттер очікуваних результатів
    std::string getExpRes() const;
    // Геттер отриманих результатів
    std::string getObtRes() const;
    // Перевизначений метод для створення дефекту з клавіатури
	void createFromKeyboard() override;
    // Перевантажена дружня функція для серіалізації об'єкта дефекту до потоку
	void show() const;
    // Перевантажена дружня функція для серіалізації об'єкта дефекту до потоку
    friend std::ostream& operator<<(std::ostream& out, const Bug& bug);
    // Перевантажена дружня функція для десеріалізації об'єкта дефекту з вхідного потоку
    friend std::istream& operator>>(std::istream& in, Bug* bug);
};

#endif

