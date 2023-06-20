/* БС-14 Романюк М.Д.
 * Реалізація методів класу QueueP у файлі QueueP.cpp */

#include "QueueP.h"
// -------------------------------------------------------------------------------------------------
// Конструктор за замовченням 
QueueP::QueueP() 
	: size(0)
	, head(nullptr)
{}
// -------------------------------------------------------------------------------------------------
// Деструктор 
QueueP::~QueueP() { clear(); }
// -------------------------------------------------------------------------------------------------
// Геттер розміру черги з пріоритетом
int QueueP::getSize() const { return size; }
// -------------------------------------------------------------------------------------------------
// Геттер посилання на голову черги з пріоритетом
Node* QueueP::getHead() const { return head; }
// -------------------------------------------------------------------------------------------------
// Метод додавання елементу за пріоритетом
void QueueP::push(Assignment* _el, int _priority)
{
	// Створення тимчасових посилань на вузли
	Node* new_node, *tmp;
	// Створення вузла, що буде доданий в клас-контейнер
	new_node = new Node;
	new_node->el = _el;
	new_node->priority = _priority;
	// Перевірка пріоритетності задля вірного розташування
	if (head == nullptr || _priority < head->priority)
	{
		new_node->next = head;
		head = new_node;
	}
	else
	{
		tmp = head;
		while (tmp->next != nullptr && tmp->next->priority <= _priority)
		{
			tmp = tmp->next;
		}
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
	// Збільшення розміру
	size++;
}
// -------------------------------------------------------------------------------------------------
// Метод видалення одного елемента з голови черги з пріоритетом
void QueueP::pop()
{
	// Перевірка на порожність
	if (head == nullptr)
		return;
	// Створення тимчасового вузла
	Node* tmp = head;
	// Видалення елемента, завдяки тимчасовому вузлу.
	head = head->next;
	delete tmp;
	size--;
}
// -------------------------------------------------------------------------------------------------
// Метод очищення черги з пріоритетом
void QueueP::clear()
{
	while (!empty())
		pop();
}
// -------------------------------------------------------------------------------------------------
// Метод перевірки черги з пріоритетом на порожність
bool QueueP::empty() const { return (size == 0); }
// -------------------------------------------------------------------------------------------------
// Метод виводу черги з пріоритетом в потік
void QueueP::show() const
{
	// Перевірка на порожність
	if (head == nullptr)
	{
		std::cout << "Queue is empty\n";
		return;
	}
	// Створення тимчасового вузла
	Node* tmp;
	tmp = head;
	// Поелементний прохід по черзі
	while (tmp != nullptr)
	{
		std::cout << "\nElement: ";
		// Перевірка типу елемента
		if (typeid(*tmp->el) == typeid(Task))
		    std::cout << "Task\n";
		else
		    std::cout << "Bug\n";
		// Виведення sajhvfws] елемента d gjnsr
		tmp->el->show();
		tmp = tmp->next;
	}
}
// -------------------------------------------------------------------------------------------------
// Метод сортування черги з пріоритетом
void QueueP::sort()
{
	if (!size)
	{
		std::cout << "Queue is empty.\n";
		return;
	}
	int i;
	std::string s;
	// Створення тимчасової черги з пріоритетом
	QueueP* new_q = new QueueP();
	// Виведення меню
	do
	{
		system("cls");
		std::cout
			<< "+--------------MENU--------------+\n"
			<< "| <1>. By priority ascending     |\n"
			<< "| <2>. By priority descending    |\n"
			<< "| <3>. By ID ascending           |\n"
			<< "| <4>. By ID descending          |\n"
			<< "| <5>. Leave sorting page        |\n"
			<< "+--------------------------------+\n"
			<< "\n>> ";
		std::getline(std::cin, s, '\n');
		i = atoi(s.c_str());
		// Створення тимчасовго вузла
		Node* tmp = head;
		// Обробка варіантів сортування
		switch (i)
		{
		// За пріоритетом по зростанню
		case 1:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority);
				tmp = tmp->next;
			}

			*this = *new_q;
			// Видалення тимчасової черги з пріоритетом
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// За пріоритетом по спаданню
		case 2:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// Видалення тимчасової черги з пріоритетом
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// За індексом по зростанню
		case 3:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId());
				tmp = tmp->next;
			}
			*this = *new_q;
			// Видалення тимчасової черги з пріоритетом
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// За індексом по спаданню
		case 4:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId()*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// Видалення тимчасової черги з пріоритетом
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		case 5:
		{
			// Видалення тимчасової черги з пріоритетом
			new_q->clear();
			delete new_q;
			return;
		}
		default:
		{
			system("cls");
			std::cout << "Your choice is not correct...\n";
		}
		}
		
	} while (1);
}
// -------------------------------------------------------------------------------------------------
// Перевантаження оператора привласнення
QueueP* QueueP::operator=(const QueueP& _queue)
{
	// Перевірка на самоприсвоєння
	if (this == &_queue) 
		return this;
	// Очищення поточої черги з пріоритетом
	clear(); 
	Node* curr = _queue.head;
	// Додавання копій елементів з _queue до поточої черги з пріоритетом
	while (curr != nullptr) {
		push(curr->el, curr->priority); 
		curr = curr->next;
	}
	// Повернення поточної черги з пріоритетом
	return this;
}
// -------------------------------------------------------------------------------------------------
// Функція для отримання розширення файлу
std::string GetFileExtension(const std::string& fileName)
{
	if (fileName.find_last_of(".") != std::string::npos)
		return fileName.substr(fileName.find_last_of(".") + 1);
	return "";
}
// -------------------------------------------------------------------------------------------------
// Метод для зчитування елементів з файлу у чергу з пріоритетом
void QueueP::readFromFile()
{
	// Взяття у користувача назви файлу
	std::cout << "Enter filename(with .dat or .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// Перевірка на правильність розширення файлу
	std::string fileExt = GetFileExtension(filename);
	if (!(fileExt == "dat" || fileExt == "txt"))
	{
		std::cout << "Wrong file extenion.\n";
		return;
	}
	std::ifstream in;
	in.open(filename, std::ios::binary);
	// Перевірка на успішність відкриття файлу
	if (!in.is_open())
	{
		std::cout << "Error opening file!\n";
		return;
	}
	// Поелементне виведення об'єктів з файлу
	int k, count = 0;
	while (in >> k)
	{
		// Перевірка типу об'єкта
		if (k == 1)
		{
			// Десеріалізація об'єкту тупи завдання з потоку
			Task* task = new Task();
			// Перевірка на успішність зчитування
			if (!(in >> task))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// Додавання об'єкту до черги з пріоритетом
			push(task, task->getPriority());
		}
		else if (k == 2)
		{
			// Десеріалізація об'єкту тупи дефект з потоку
			Bug* bug = new Bug();
			// Перевірка на успішність зчитування
			if (!(in >> bug))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// Додавання об'єкту до черги з пріоритетом
			push(bug, bug->getPriority());
		}
		else
		{
			// Обробка випадку, коли у файлі записаний не передбачений специфікатор об'єкту
			std::cout << "Error while reading file. Unknown type specifier.\n";
			in.close();
			return;
		}
	} // кінець while (in >> k)
	std::cout << "Loaded...\n";
	in.close();
}
// -------------------------------------------------------------------------------------------------
// Функція перевірки існування файлу
bool chechExistance(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
// -------------------------------------------------------------------------------------------------
// Метод для запису черги з пріоритетом у файл 
void QueueP::writeToFile() const
{
	// Взяття у користувача назви файлу
	std::cout << "Enter filename where you want to save data (with .dat ot .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// Перевірка на правильність розширення файлу
	std::string fileExt = GetFileExtension(filename);
	if (!(fileExt == "dat" || fileExt == "txt"))
	{
		std::cout << "Wrong file extenion.\n";
		return;
	}
	while (chechExistance(filename))
	{
		std::string ch;
		std::cout
			<< "File with this name already exists.\n"
			<< "Do you want to overwrite?(y/n)\n";
		std::getline(std::cin, ch, '\n');
		while (!(ch == "y" || ch == "n"))
		{
			std::cout << "Incorrect choice. Try again: ";
			std::getline(std::cin, ch, '\n');
		}
		if (ch == "n")
		{
			std::cout << "Enter new name: ";
			std::getline(std::cin, filename, '\n');
		}
		else
			break;
	}
	std::ofstream out;
	out.open(filename, std::ios::binary);
	// Перевірка на успішність відкриття файлу
	if (!out.is_open())
	{
		std::cout << "Error opening file!\n";
		out.close();
		return;
	}
	// Поелементний вивід об'єктів у файл
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		if (typeid(*(tmp->el)) == typeid(Task))
		{
			// Перевірка на успішність виводу об'єкта завдання
			if (!(out << 1 << (*((Task*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		else if (typeid(*(tmp->el)) == typeid(Bug))
		{
			// Перевірка на успішність виводу об'єкта дефекту
			if (!(out << 2 << (*((Bug*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		tmp = tmp->next;
	}
	std::cout << "Saved...\n";
	out.close();
}
// -------------------------------------------------------------------------------------------------
// Функція переводу строки в нижній регістр
std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	// Прохід по елементам строки
	for (char& c : result)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c += 'a' - 'A';
		}
	}
	return result;
}
// -------------------------------------------------------------------------------------------------
// Метод для отримання кількості елементів типу дефект з черги з пріоритетом,
// що знаходиться в певному компоненті
void QueueP::doReq() const
{
	std::string component, tmp_str;
	// Взяття у користувача назви компоненту
	std::cout << "Enter component's name where you want to count bugs: ";
	std::getline(std::cin, component, '\n');
	// Перевірка вводу
	if (component.empty())
	{
		std::cout << "String can not be empty.\n";
		return;
	}
	// Переведення назви в нижній регістр задля запобігання проблеми різниці регістрів
	component = toLowerCase(component);
	int count = 0;
	int len = getSize();
	// Поелементний прохід по черзі
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		// Перевірка типу об'єкта в черзі
		if (typeid(*(tmp->el)) == typeid(Bug))
		{
			tmp_str = tmp->el->getComponent();
			tmp_str = toLowerCase(tmp_str);
			// Перевірка на однаковість
			if (tmp_str == component)
				count++;
		}
		tmp = tmp->next;
	}
	if (count)
	{
		std::cout << "There is " << count << " bug(s) in this component.\n";
	}
	else
		std::cout << "There is no bugs in this component.\n";

}