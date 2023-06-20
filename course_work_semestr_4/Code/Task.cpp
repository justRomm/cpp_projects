

#include "Task.h"
// -------------------------------------------------------------------------------------------------
// Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
Task::Task()
	: Assignment()
	, taskDesc("")
{}
// -------------------------------------------------------------------------------------------------
// Ïàðìåòðèçîâàíèé êîíñòðóêòîð
Task::Task(int _id, int _priority, std::string _component, std::string _taskDesc)
	: Assignment(_id, _priority, _component)
	, taskDesc(_taskDesc)
{}
// -------------------------------------------------------------------------------------------------
// Ñåòòåð îïèñó çàâäàííÿ
void Task::setTaskDesc(std::string _taskDesc) { taskDesc = _taskDesc; }
// -------------------------------------------------------------------------------------------------
// Ãåòòåð îïèñó çàâäàííÿ
std::string Task::getTaskDesc() const { return taskDesc; }
// -------------------------------------------------------------------------------------------------
// Ïåðåâèçíà÷åíèé ìåòîä äëÿ ñòâîðåííÿ çàâäàííÿ ç êëàâ³àòóðè
void Task::createFromKeyboard()
{
	// Âçÿòòÿ çíà÷åííÿ ID ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter ID: ";
	std::string inp;
	std::cin >> inp;
	id = atoi(inp.c_str());
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (id < 1) 
	{
		std::cout << "ID must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		id = atoi(inp.c_str());
	}
	// Âçÿòòÿ çíà÷åííÿ ïð³îðèòåòó ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter priority: ";
	std::cin >> inp;
	priority = atoi(inp.c_str());
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (priority < 1)
	{
		std::cout << "Priority must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		priority = atoi(inp.c_str());
	}
	// Âçÿòòÿ çíà÷åííÿ íàçâè êîìïîíåíòó ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter component: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, component, '\n');
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (component.empty())
	{
		std::cout << "Component's name can not be an empty string.\nEnter again: ";
		std::getline(std::cin, component, '\n');
	}
	// Âçÿòòÿ çíà÷åííÿ îïèñó çàâäàííÿ ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter desc: ";
	std::getline(std::cin, taskDesc, '\n');
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (taskDesc.empty())
	{
		std::cout << "Task description can not be an empty string.\nEnter again: ";
		std::getline(std::cin, taskDesc, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// Ïåðåâèçíà÷åíèé ìåòîä äëÿ âèâîäó çàâäàííÿ â ïîò³ê
void Task::show() const 
{
	Assignment::show();
	std::cout << "Task description: " << taskDesc << "\n\n";
}
// -------------------------------------------------------------------------------------------------
// Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ ñåð³àë³çàö³¿ îá'ºêòà çàâäàííÿ äî ïîòîêó
std::ostream& operator<<(std::ostream& out, const Task& task)
{
	// Çàïèñ ID òà ïð³îðèòåò äî âèõ³äíîãî ôàéëîâîãî ïîòîêó
	out.write((char*)&task.id, sizeof(task.id));
	out.write((char*)&task.priority, sizeof(task.priority));
	// Çàïèñ ðîçì³ðó ðÿäêà íàçâè êîìïîíåíòó òà ñàì ðÿäîê äî âèõ³äíîãî ïîòîêó
	size_t componentSize = task.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(task.component.data(), componentSize);
	// Çàïèñ ðîçì³ðó ðÿäêà îïèñó çàâäàííÿ òà ñàì ðÿäîê äî âèõ³äíîãî ïîòîêó
	size_t taskDescSize = task.taskDesc.size();
	out.write((char*)&taskDescSize, sizeof(taskDescSize));
	out.write(task.taskDesc.data(), taskDescSize);
	// Ïîâåðíåííÿ âèõ³äíîãî ïîòîêó
	return out;
}
// -------------------------------------------------------------------------------------------------
// Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ äåñåð³àë³çàö³¿ îá'ºêòà çàâäàííÿ ç âõ³äíîãî ïîòîêó
std::ifstream& operator>>(std::ifstream& in, Task* task)
{
	try {
		// Ç÷èòóâàííÿ ID ç âõ³äíîãî ïîòîêó
		in.read((char*)&task->id, sizeof(task->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading task ID");
		}
		// Ç÷èòóâàííÿ ïð³îðèòåòó ç âõ³äíîãî ïîòîêó
		in.read((char*)&task->priority, sizeof(task->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading task priority");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà íàçâè êîìïîíåíòà
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// Ç÷èòóâàííÿ ðÿäêà íàçâè êîìïîíåíòà
		task->component.resize(componentSize);
		in.read((char*)task->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component's name data");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà îïèñó çàâäàííÿ
		size_t taskDescSize;
		in.read((char*)&taskDescSize, sizeof(taskDescSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading task description size");
		}
		// Ç÷èòóâàííÿ ðÿäêà îïèñó çàâäàííÿ
		task->taskDesc.resize(taskDescSize);
		in.read((char*)task->taskDesc.data(), taskDescSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading task description data");
		}
	} // ê³íåöü try
	// Îáðîáêà óñ³õ ìîæëèâèõ âèíÿòê³â ï³ä ÷àñ äåñåð³àë³çàö³¿ îá'ºêòà ç âõ³äíîãî ïîòîêó
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// Ïîâåðíåííÿ âõ³äíîãî ïîòîêó
	return in;
} // ê³íåöü friend std::ifstream& operator>>(std::ifstream& in, Task* task)
// -------------------------------------------------------------------------------------------------
// Äåñòðóêòîð
Task::~Task()
{}
