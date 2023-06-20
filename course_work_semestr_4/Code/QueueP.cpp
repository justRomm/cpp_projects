/* ��-14 ������� �.�.
 * ��������� ������ ����� QueueP � ���� QueueP.cpp */

#include "QueueP.h"
// -------------------------------------------------------------------------------------------------
// ����������� �� ����������� 
QueueP::QueueP() 
	: size(0)
	, head(nullptr)
{}
// -------------------------------------------------------------------------------------------------
// ���������� 
QueueP::~QueueP() { clear(); }
// -------------------------------------------------------------------------------------------------
// ������ ������ ����� � ����������
int QueueP::getSize() const { return size; }
// -------------------------------------------------------------------------------------------------
// ������ ��������� �� ������ ����� � ����������
Node* QueueP::getHead() const { return head; }
// -------------------------------------------------------------------------------------------------
// ����� ��������� �������� �� ����������
void QueueP::push(Assignment* _el, int _priority)
{
	// ��������� ���������� �������� �� �����
	Node* new_node, *tmp;
	// ��������� �����, �� ���� ������� � ����-���������
	new_node = new Node;
	new_node->el = _el;
	new_node->priority = _priority;
	// �������� ������������ ����� ������ ������������
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
	// ��������� ������
	size++;
}
// -------------------------------------------------------------------------------------------------
// ����� ��������� ������ �������� � ������ ����� � ����������
void QueueP::pop()
{
	// �������� �� ���������
	if (head == nullptr)
		return;
	// ��������� ����������� �����
	Node* tmp = head;
	// ��������� ��������, ������� ����������� �����.
	head = head->next;
	delete tmp;
	size--;
}
// -------------------------------------------------------------------------------------------------
// ����� �������� ����� � ����������
void QueueP::clear()
{
	while (!empty())
		pop();
}
// -------------------------------------------------------------------------------------------------
// ����� �������� ����� � ���������� �� ���������
bool QueueP::empty() const { return (size == 0); }
// -------------------------------------------------------------------------------------------------
// ����� ������ ����� � ���������� � ����
void QueueP::show() const
{
	// �������� �� ���������
	if (head == nullptr)
	{
		std::cout << "Queue is empty\n";
		return;
	}
	// ��������� ����������� �����
	Node* tmp;
	tmp = head;
	// ������������ ������ �� ����
	while (tmp != nullptr)
	{
		std::cout << "\nElement: ";
		// �������� ���� ��������
		if (typeid(*tmp->el) == typeid(Task))
		    std::cout << "Task\n";
		else
		    std::cout << "Bug\n";
		// ��������� sajhvfws] �������� d gjnsr
		tmp->el->show();
		tmp = tmp->next;
	}
}
// -------------------------------------------------------------------------------------------------
// ����� ���������� ����� � ����������
void QueueP::sort()
{
	if (!size)
	{
		std::cout << "Queue is empty.\n";
		return;
	}
	int i;
	std::string s;
	// ��������� ��������� ����� � ����������
	QueueP* new_q = new QueueP();
	// ��������� ����
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
		// ��������� ���������� �����
		Node* tmp = head;
		// ������� ������� ����������
		switch (i)
		{
		// �� ���������� �� ���������
		case 1:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority);
				tmp = tmp->next;
			}

			*this = *new_q;
			// ��������� ��������� ����� � ����������
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// �� ���������� �� ��������
		case 2:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// ��������� ��������� ����� � ����������
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// �� �������� �� ���������
		case 3:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId());
				tmp = tmp->next;
			}
			*this = *new_q;
			// ��������� ��������� ����� � ����������
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// �� �������� �� ��������
		case 4:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId()*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// ��������� ��������� ����� � ����������
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		case 5:
		{
			// ��������� ��������� ����� � ����������
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
// �������������� ��������� ������������
QueueP* QueueP::operator=(const QueueP& _queue)
{
	// �������� �� �������������
	if (this == &_queue) 
		return this;
	// �������� ������ ����� � ����������
	clear(); 
	Node* curr = _queue.head;
	// ��������� ���� �������� � _queue �� ������ ����� � ����������
	while (curr != nullptr) {
		push(curr->el, curr->priority); 
		curr = curr->next;
	}
	// ���������� ������� ����� � ����������
	return this;
}
// -------------------------------------------------------------------------------------------------
// ������� ��� ��������� ���������� �����
std::string GetFileExtension(const std::string& fileName)
{
	if (fileName.find_last_of(".") != std::string::npos)
		return fileName.substr(fileName.find_last_of(".") + 1);
	return "";
}
// -------------------------------------------------------------------------------------------------
// ����� ��� ���������� �������� � ����� � ����� � ����������
void QueueP::readFromFile()
{
	// ������ � ����������� ����� �����
	std::cout << "Enter filename(with .dat or .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// �������� �� ����������� ���������� �����
	std::string fileExt = GetFileExtension(filename);
	if (!(fileExt == "dat" || fileExt == "txt"))
	{
		std::cout << "Wrong file extenion.\n";
		return;
	}
	std::ifstream in;
	in.open(filename, std::ios::binary);
	// �������� �� �������� �������� �����
	if (!in.is_open())
	{
		std::cout << "Error opening file!\n";
		return;
	}
	// ����������� ��������� ��'���� � �����
	int k, count = 0;
	while (in >> k)
	{
		// �������� ���� ��'����
		if (k == 1)
		{
			// ������������ ��'���� ���� �������� � ������
			Task* task = new Task();
			// �������� �� �������� ����������
			if (!(in >> task))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// ��������� ��'���� �� ����� � ����������
			push(task, task->getPriority());
		}
		else if (k == 2)
		{
			// ������������ ��'���� ���� ������ � ������
			Bug* bug = new Bug();
			// �������� �� �������� ����������
			if (!(in >> bug))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// ��������� ��'���� �� ����� � ����������
			push(bug, bug->getPriority());
		}
		else
		{
			// ������� �������, ���� � ���� ��������� �� ������������ ������������ ��'����
			std::cout << "Error while reading file. Unknown type specifier.\n";
			in.close();
			return;
		}
	} // ����� while (in >> k)
	std::cout << "Loaded...\n";
	in.close();
}
// -------------------------------------------------------------------------------------------------
// ������� �������� ��������� �����
bool chechExistance(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
// -------------------------------------------------------------------------------------------------
// ����� ��� ������ ����� � ���������� � ���� 
void QueueP::writeToFile() const
{
	// ������ � ����������� ����� �����
	std::cout << "Enter filename where you want to save data (with .dat ot .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// �������� �� ����������� ���������� �����
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
	// �������� �� �������� �������� �����
	if (!out.is_open())
	{
		std::cout << "Error opening file!\n";
		out.close();
		return;
	}
	// ������������ ���� ��'���� � ����
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		if (typeid(*(tmp->el)) == typeid(Task))
		{
			// �������� �� �������� ������ ��'���� ��������
			if (!(out << 1 << (*((Task*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		else if (typeid(*(tmp->el)) == typeid(Bug))
		{
			// �������� �� �������� ������ ��'���� �������
			if (!(out << 2 << (*((Bug*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		tmp = tmp->next;
	}
	std::cout << "Saved...\n";
	out.close();
}
// -------------------------------------------------------------------------------------------------
// ������� �������� ������ � ����� ������
std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	// ������ �� ��������� ������
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
// ����� ��� ��������� ������� �������� ���� ������ � ����� � ����������,
// �� ����������� � ������� ���������
void QueueP::doReq() const
{
	std::string component, tmp_str;
	// ������ � ����������� ����� ����������
	std::cout << "Enter component's name where you want to count bugs: ";
	std::getline(std::cin, component, '\n');
	// �������� �����
	if (component.empty())
	{
		std::cout << "String can not be empty.\n";
		return;
	}
	// ����������� ����� � ����� ������ ����� ���������� �������� ������ �������
	component = toLowerCase(component);
	int count = 0;
	int len = getSize();
	// ������������ ������ �� ����
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		// �������� ���� ��'���� � ����
		if (typeid(*(tmp->el)) == typeid(Bug))
		{
			tmp_str = tmp->el->getComponent();
			tmp_str = toLowerCase(tmp_str);
			// �������� �� ����������
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