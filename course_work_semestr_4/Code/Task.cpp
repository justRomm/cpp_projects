/* ��-14 ������� �.�.
 * ��������� ������ ����� Task � ���� Task.cpp*/

#include "Task.h"
// -------------------------------------------------------------------------------------------------
// ����������� �� �������������
Task::Task()
	: Assignment()
	, taskDesc("")
{}
// -------------------------------------------------------------------------------------------------
// ��������������� �����������
Task::Task(int _id, int _priority, std::string _component, std::string _taskDesc)
	: Assignment(_id, _priority, _component)
	, taskDesc(_taskDesc)
{}
// -------------------------------------------------------------------------------------------------
// ������ ����� ��������
void Task::setTaskDesc(std::string _taskDesc) { taskDesc = _taskDesc; }
// -------------------------------------------------------------------------------------------------
// ������ ����� ��������
std::string Task::getTaskDesc() const { return taskDesc; }
// -------------------------------------------------------------------------------------------------
// �������������� ����� ��� ��������� �������� � ���������
void Task::createFromKeyboard()
{
	// ������ �������� ID � ����� �����������
	std::cout << "Enter ID: ";
	std::string inp;
	std::cin >> inp;
	id = atoi(inp.c_str());
	// �������� �� ���������� �����
	while (id < 1) 
	{
		std::cout << "ID must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		id = atoi(inp.c_str());
	}
	// ������ �������� ��������� � ����� �����������
	std::cout << "Enter priority: ";
	std::cin >> inp;
	priority = atoi(inp.c_str());
	// �������� �� ���������� �����
	while (priority < 1)
	{
		std::cout << "Priority must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		priority = atoi(inp.c_str());
	}
	// ������ �������� ����� ���������� � ����� �����������
	std::cout << "Enter component: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, component, '\n');
	// �������� �� ���������� �����
	while (component.empty())
	{
		std::cout << "Component's name can not be an empty string.\nEnter again: ";
		std::getline(std::cin, component, '\n');
	}
	// ������ �������� ����� �������� � ����� �����������
	std::cout << "Enter desc: ";
	std::getline(std::cin, taskDesc, '\n');
	// �������� �� ���������� �����
	while (taskDesc.empty())
	{
		std::cout << "Task description can not be an empty string.\nEnter again: ";
		std::getline(std::cin, taskDesc, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// �������������� ����� ��� ������ �������� � ����
void Task::show() const 
{
	Assignment::show();
	std::cout << "Task description: " << taskDesc << "\n\n";
}
// -------------------------------------------------------------------------------------------------
// ������������� ������ ������� ��� ���������� ��'���� �������� �� ������
std::ostream& operator<<(std::ostream& out, const Task& task)
{
	// ����� ID �� �������� �� ��������� ��������� ������
	out.write((char*)&task.id, sizeof(task.id));
	out.write((char*)&task.priority, sizeof(task.priority));
	// ����� ������ ����� ����� ���������� �� ��� ����� �� ��������� ������
	size_t componentSize = task.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(task.component.data(), componentSize);
	// ����� ������ ����� ����� �������� �� ��� ����� �� ��������� ������
	size_t taskDescSize = task.taskDesc.size();
	out.write((char*)&taskDescSize, sizeof(taskDescSize));
	out.write(task.taskDesc.data(), taskDescSize);
	// ���������� ��������� ������
	return out;
}
// -------------------------------------------------------------------------------------------------
// ������������� ������ ������� ��� ������������ ��'���� �������� � �������� ������
std::ifstream& operator>>(std::ifstream& in, Task* task)
{
	try {
		// ���������� ID � �������� ������
		in.read((char*)&task->id, sizeof(task->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading task ID");
		}
		// ���������� ��������� � �������� ������
		in.read((char*)&task->priority, sizeof(task->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading task priority");
		}
		// ���������� ������ ����� ����� ����������
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// ���������� ����� ����� ����������
		task->component.resize(componentSize);
		in.read((char*)task->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component's name data");
		}
		// ���������� ������ ����� ����� ��������
		size_t taskDescSize;
		in.read((char*)&taskDescSize, sizeof(taskDescSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading task description size");
		}
		// ���������� ����� ����� ��������
		task->taskDesc.resize(taskDescSize);
		in.read((char*)task->taskDesc.data(), taskDescSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading task description data");
		}
	} // ����� try
	// ������� ��� �������� ������� �� ��� ������������ ��'���� � �������� ������
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// ���������� �������� ������
	return in;
} // ����� friend std::ifstream& operator>>(std::ifstream& in, Task* task)
// -------------------------------------------------------------------------------------------------
// ����������
Task::~Task()
{}
