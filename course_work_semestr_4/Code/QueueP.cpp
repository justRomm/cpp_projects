

#include "QueueP.h"
// -------------------------------------------------------------------------------------------------
// Êîíñòðóêòîð çà çàìîâ÷åííÿì 
QueueP::QueueP() 
	: size(0)
	, head(nullptr)
{}
// -------------------------------------------------------------------------------------------------
// Äåñòðóêòîð 
QueueP::~QueueP() { clear(); }
// -------------------------------------------------------------------------------------------------
// Ãåòòåð ðîçì³ðó ÷åðãè ç ïð³îðèòåòîì
int QueueP::getSize() const { return size; }
// -------------------------------------------------------------------------------------------------
// Ãåòòåð ïîñèëàííÿ íà ãîëîâó ÷åðãè ç ïð³îðèòåòîì
Node* QueueP::getHead() const { return head; }
// -------------------------------------------------------------------------------------------------
// Ìåòîä äîäàâàííÿ åëåìåíòó çà ïð³îðèòåòîì
void QueueP::push(Assignment* _el, int _priority)
{
	// Ñòâîðåííÿ òèì÷àñîâèõ ïîñèëàíü íà âóçëè
	Node* new_node, *tmp;
	// Ñòâîðåííÿ âóçëà, ùî áóäå äîäàíèé â êëàñ-êîíòåéíåð
	new_node = new Node;
	new_node->el = _el;
	new_node->priority = _priority;
	// Ïåðåâ³ðêà ïð³îðèòåòíîñò³ çàäëÿ â³ðíîãî ðîçòàøóâàííÿ
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
	// Çá³ëüøåííÿ ðîçì³ðó
	size++;
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä âèäàëåííÿ îäíîãî åëåìåíòà ç ãîëîâè ÷åðãè ç ïð³îðèòåòîì
void QueueP::pop()
{
	// Ïåðåâ³ðêà íà ïîðîæí³ñòü
	if (head == nullptr)
		return;
	// Ñòâîðåííÿ òèì÷àñîâîãî âóçëà
	Node* tmp = head;
	// Âèäàëåííÿ åëåìåíòà, çàâäÿêè òèì÷àñîâîìó âóçëó.
	head = head->next;
	delete tmp;
	size--;
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä î÷èùåííÿ ÷åðãè ç ïð³îðèòåòîì
void QueueP::clear()
{
	while (!empty())
		pop();
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä ïåðåâ³ðêè ÷åðãè ç ïð³îðèòåòîì íà ïîðîæí³ñòü
bool QueueP::empty() const { return (size == 0); }
// -------------------------------------------------------------------------------------------------
// Ìåòîä âèâîäó ÷åðãè ç ïð³îðèòåòîì â ïîò³ê
void QueueP::show() const
{
	// Ïåðåâ³ðêà íà ïîðîæí³ñòü
	if (head == nullptr)
	{
		std::cout << "Queue is empty\n";
		return;
	}
	// Ñòâîðåííÿ òèì÷àñîâîãî âóçëà
	Node* tmp;
	tmp = head;
	// Ïîåëåìåíòíèé ïðîõ³ä ïî ÷åðç³
	while (tmp != nullptr)
	{
		std::cout << "\nElement: ";
		// Ïåðåâ³ðêà òèïó åëåìåíòà
		if (typeid(*tmp->el) == typeid(Task))
		    std::cout << "Task\n";
		else
		    std::cout << "Bug\n";
		// Âèâåäåííÿ sajhvfws] åëåìåíòà d gjnsr
		tmp->el->show();
		tmp = tmp->next;
	}
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä ñîðòóâàííÿ ÷åðãè ç ïð³îðèòåòîì
void QueueP::sort()
{
	if (!size)
	{
		std::cout << "Queue is empty.\n";
		return;
	}
	int i;
	std::string s;
	// Ñòâîðåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
	QueueP* new_q = new QueueP();
	// Âèâåäåííÿ ìåíþ
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
		// Ñòâîðåííÿ òèì÷àñîâãî âóçëà
		Node* tmp = head;
		// Îáðîáêà âàð³àíò³â ñîðòóâàííÿ
		switch (i)
		{
		// Çà ïð³îðèòåòîì ïî çðîñòàííþ
		case 1:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority);
				tmp = tmp->next;
			}

			*this = *new_q;
			// Âèäàëåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// Çà ïð³îðèòåòîì ïî ñïàäàííþ
		case 2:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->priority*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// Âèäàëåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// Çà ³íäåêñîì ïî çðîñòàííþ
		case 3:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId());
				tmp = tmp->next;
			}
			*this = *new_q;
			// Âèäàëåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		// Çà ³íäåêñîì ïî ñïàäàííþ
		case 4:
		{
			while (tmp != nullptr)
			{
				new_q->push(tmp->el, tmp->el->getId()*(-1));
				tmp = tmp->next;
			}
			*this = *new_q;
			// Âèäàëåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
			new_q->clear();
			delete new_q;
			std::cout << "Sorted...\n";
			return;
		}
		case 5:
		{
			// Âèäàëåííÿ òèì÷àñîâî¿ ÷åðãè ç ïð³îðèòåòîì
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
// Ïåðåâàíòàæåííÿ îïåðàòîðà ïðèâëàñíåííÿ
QueueP* QueueP::operator=(const QueueP& _queue)
{
	// Ïåðåâ³ðêà íà ñàìîïðèñâîºííÿ
	if (this == &_queue) 
		return this;
	// Î÷èùåííÿ ïîòî÷î¿ ÷åðãè ç ïð³îðèòåòîì
	clear(); 
	Node* curr = _queue.head;
	// Äîäàâàííÿ êîï³é åëåìåíò³â ç _queue äî ïîòî÷î¿ ÷åðãè ç ïð³îðèòåòîì
	while (curr != nullptr) {
		push(curr->el, curr->priority); 
		curr = curr->next;
	}
	// Ïîâåðíåííÿ ïîòî÷íî¿ ÷åðãè ç ïð³îðèòåòîì
	return this;
}
// -------------------------------------------------------------------------------------------------
// Ôóíêö³ÿ äëÿ îòðèìàííÿ ðîçøèðåííÿ ôàéëó
std::string GetFileExtension(const std::string& fileName)
{
	if (fileName.find_last_of(".") != std::string::npos)
		return fileName.substr(fileName.find_last_of(".") + 1);
	return "";
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä äëÿ ç÷èòóâàííÿ åëåìåíò³â ç ôàéëó ó ÷åðãó ç ïð³îðèòåòîì
void QueueP::readFromFile()
{
	// Âçÿòòÿ ó êîðèñòóâà÷à íàçâè ôàéëó
	std::cout << "Enter filename(with .dat or .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// Ïåðåâ³ðêà íà ïðàâèëüí³ñòü ðîçøèðåííÿ ôàéëó
	std::string fileExt = GetFileExtension(filename);
	if (!(fileExt == "dat" || fileExt == "txt"))
	{
		std::cout << "Wrong file extenion.\n";
		return;
	}
	std::ifstream in;
	in.open(filename, std::ios::binary);
	// Ïåðåâ³ðêà íà óñï³øí³ñòü â³äêðèòòÿ ôàéëó
	if (!in.is_open())
	{
		std::cout << "Error opening file!\n";
		return;
	}
	// Ïîåëåìåíòíå âèâåäåííÿ îá'ºêò³â ç ôàéëó
	int k, count = 0;
	while (in >> k)
	{
		// Ïåðåâ³ðêà òèïó îá'ºêòà
		if (k == 1)
		{
			// Äåñåð³àë³çàö³ÿ îá'ºêòó òóïè çàâäàííÿ ç ïîòîêó
			Task* task = new Task();
			// Ïåðåâ³ðêà íà óñï³øí³ñòü ç÷èòóâàííÿ
			if (!(in >> task))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// Äîäàâàííÿ îá'ºêòó äî ÷åðãè ç ïð³îðèòåòîì
			push(task, task->getPriority());
		}
		else if (k == 2)
		{
			// Äåñåð³àë³çàö³ÿ îá'ºêòó òóïè äåôåêò ç ïîòîêó
			Bug* bug = new Bug();
			// Ïåðåâ³ðêà íà óñï³øí³ñòü ç÷èòóâàííÿ
			if (!(in >> bug))
			{
				std::cout << "Error while reading file.\n";
				in.close();
				return;
			}
			// Äîäàâàííÿ îá'ºêòó äî ÷åðãè ç ïð³îðèòåòîì
			push(bug, bug->getPriority());
		}
		else
		{
			// Îáðîáêà âèïàäêó, êîëè ó ôàéë³ çàïèñàíèé íå ïåðåäáà÷åíèé ñïåöèô³êàòîð îá'ºêòó
			std::cout << "Error while reading file. Unknown type specifier.\n";
			in.close();
			return;
		}
	} // ê³íåöü while (in >> k)
	std::cout << "Loaded...\n";
	in.close();
}
// -------------------------------------------------------------------------------------------------
// Ôóíêö³ÿ ïåðåâ³ðêè ³ñíóâàííÿ ôàéëó
bool chechExistance(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
// -------------------------------------------------------------------------------------------------
// Ìåòîä äëÿ çàïèñó ÷åðãè ç ïð³îðèòåòîì ó ôàéë 
void QueueP::writeToFile() const
{
	// Âçÿòòÿ ó êîðèñòóâà÷à íàçâè ôàéëó
	std::cout << "Enter filename where you want to save data (with .dat ot .txt extension): ";
	std::string filename;
	std::getline(std::cin, filename, '\n');
	// Ïåðåâ³ðêà íà ïðàâèëüí³ñòü ðîçøèðåííÿ ôàéëó
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
	// Ïåðåâ³ðêà íà óñï³øí³ñòü â³äêðèòòÿ ôàéëó
	if (!out.is_open())
	{
		std::cout << "Error opening file!\n";
		out.close();
		return;
	}
	// Ïîåëåìåíòíèé âèâ³ä îá'ºêò³â ó ôàéë
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		if (typeid(*(tmp->el)) == typeid(Task))
		{
			// Ïåðåâ³ðêà íà óñï³øí³ñòü âèâîäó îá'ºêòà çàâäàííÿ
			if (!(out << 1 << (*((Task*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		else if (typeid(*(tmp->el)) == typeid(Bug))
		{
			// Ïåðåâ³ðêà íà óñï³øí³ñòü âèâîäó îá'ºêòà äåôåêòó
			if (!(out << 2 << (*((Bug*)(tmp->el)))))
				std::cout << "Error writing data to the file.\n";
		}
		tmp = tmp->next;
	}
	std::cout << "Saved...\n";
	out.close();
}
// -------------------------------------------------------------------------------------------------
// Ôóíêö³ÿ ïåðåâîäó ñòðîêè â íèæí³é ðåã³ñòð
std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	// Ïðîõ³ä ïî åëåìåíòàì ñòðîêè
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
// Ìåòîä äëÿ îòðèìàííÿ ê³ëüêîñò³ åëåìåíò³â òèïó äåôåêò ç ÷åðãè ç ïð³îðèòåòîì,
// ùî çíàõîäèòüñÿ â ïåâíîìó êîìïîíåíò³
void QueueP::doReq() const
{
	std::string component, tmp_str;
	// Âçÿòòÿ ó êîðèñòóâà÷à íàçâè êîìïîíåíòó
	std::cout << "Enter component's name where you want to count bugs: ";
	std::getline(std::cin, component, '\n');
	// Ïåðåâ³ðêà ââîäó
	if (component.empty())
	{
		std::cout << "String can not be empty.\n";
		return;
	}
	// Ïåðåâåäåííÿ íàçâè â íèæí³é ðåã³ñòð çàäëÿ çàïîá³ãàííÿ ïðîáëåìè ð³çíèö³ ðåã³ñòð³â
	component = toLowerCase(component);
	int count = 0;
	int len = getSize();
	// Ïîåëåìåíòíèé ïðîõ³ä ïî ÷åðç³
	Node* tmp;
	tmp = head;
	while (tmp != nullptr)
	{
		// Ïåðåâ³ðêà òèïó îá'ºêòà â ÷åðç³
		if (typeid(*(tmp->el)) == typeid(Bug))
		{
			tmp_str = tmp->el->getComponent();
			tmp_str = toLowerCase(tmp_str);
			// Ïåðåâ³ðêà íà îäíàêîâ³ñòü
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
