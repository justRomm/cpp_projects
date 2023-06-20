/* ��-14 ������� �.�.
 * ��������� ������ ����� Bug � ���� Bug.cpp */

#include "Bug.h"
 // -------------------------------------------------------------------------------------------------
// ����������� �� �������������
Bug::Bug()
	: Assignment()
	, expRes("")
	, obtRes("")
{
}
// -------------------------------------------------------------------------------------------------
// ��������������� �����������
Bug::Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _givenRes)
	: Assignment(_id, _priority, _component)
	, expRes(_expRes)
	, obtRes(_givenRes)
{
}
// -------------------------------------------------------------------------------------------------
// ������ ���������� ���������� 
void Bug::setExpRes(std::string _expRes) { expRes = _expRes; }
// -------------------------------------------------------------------------------------------------
// ������ ��������� ���������� 
void Bug::setObtRes(std::string _givenRes) { obtRes = _givenRes; }
// -------------------------------------------------------------------------------------------------
// ���������������� ����������
std::string Bug::getExpRes() const { return expRes; }
// -------------------------------------------------------------------------------------------------
// ������ ��������� ����������
std::string Bug::getObtRes() const { return obtRes; }
// -------------------------------------------------------------------------------------------------
// �������������� ����� ��� ��������� ������� � ���������
void Bug::createFromKeyboard()
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
	// ������ �������� ���������� ����������
	std::cout << "Enter expected result: ";
	std::getline(std::cin, expRes, '\n');
	// �������� �� ���������� �����
	while (expRes.empty())
	{
		std::cout << "Expected result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, expRes, '\n');
	}
	// ������ �������� ��������� ����������
	std::cout << "Enter obtained result: ";
	std::getline(std::cin, obtRes, '\n');
	// �������� �� ���������� �����
	while (obtRes.empty())
	{
		std::cout << "Obtained result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, obtRes, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// �������������� ����� ��� ������ �������� � ����
void Bug::show() const
{
	Assignment::show();
	std::cout << "Expected result: " << expRes 
			  << "\nObtained results: " << obtRes << "\n\n";
}
// ������������� ������ ������� ��� ���������� ��'���� ������� �� ������
std::ostream& operator<<(std::ostream& out, const Bug& bug)
{
	// ����� ID �� �������� �� ��������� ��������� ������
	out.write((char*)&bug.id, sizeof(bug.id));
	out.write((char*)&bug.priority, sizeof(bug.priority));
	// ����� ������ ����� ����� ���������� �� ��� ����� ����� ���������� �� ��������� ������
	size_t componentSize = bug.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(bug.component.data(), componentSize);
	// ����� ������ ����� ���������� ���������� �� ��� ����� �� ��������� ������
	size_t expResSize = bug.expRes.size();
	out.write((char*)&expResSize, sizeof(expResSize));
	out.write(bug.expRes.data(), expResSize);
	// ����� ������ ����� ��������� ���������� �� ��� ����� �� ��������� ������
	size_t obtResSize = bug.obtRes.size();
	out.write((char*)&obtResSize, sizeof(obtResSize));
	out.write(bug.obtRes.data(), obtResSize);
	// ���������� ��������� ������
	return out;
}
// -------------------------------------------------------------------------------------------------
// ������������� ������ ������� ��� ������������ ��'���� ������� � �������� ������
std::istream& operator>>(std::istream& in, Bug* bug)
{
	try {
		// ���������� ID � �������� ������
		in.read((char*)&bug->id, sizeof(bug->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug ID");
		}
		// ���������� ��������� � �������� ������
		in.read((char*)&bug->priority, sizeof(bug->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug priority");
		}
		// ���������� ������ ����� ����� ����������
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// ���������� ������ ����� ����������� ���������� ����� ����������
		bug->component.resize(componentSize);
		in.read((char*)bug->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component data");
		}
		// ���������� ������ ����� ����������� ����������
		size_t expResSize;
		in.read((char*)&expResSize, sizeof(expResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result size");
		}
		// ���������� ����� ����������� ����������
		bug->expRes.resize(expResSize);
		in.read((char*)bug->expRes.data(), expResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result data");
		}
		// ���������� ������ ����� ���������� ����������
		size_t obtResSize = 0;
		in.read((char*)&obtResSize, sizeof(obtResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result size");
		}
		// ���������� ����� ���������� ����������
		bug->obtRes.resize(obtResSize);
		in.read((char*)bug->obtRes.data(), obtResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result data");
		}
	} // ����� try
	// ������� ��� �������� ������� �� ��� ������������ ��'���� � �������� ������
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// ���������� �������� ������
	return in;
} // ����� friend std::istream& operator>>(std::istream& in, Bug* bug)
// -------------------------------------------------------------------------------------------------
// ����������
Bug::~Bug()
{
}