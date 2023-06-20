/* ��-14 ������� �.�.
 * ��������� ������ ����� Assingment � ���� Assingment.cpp */

#include "Assignment.h"
// ����������� �� �������������
Assignment::Assignment()
	: id(0)
	, priority(0)
	, component("")
{}
// ��������������� �����������
Assignment::Assignment(int _id, int _priority, std::string _component)
	: id(_id)
	, priority(_priority)
	, component(_component)
{}
// ������ ID
void Assignment::setId(int _id) { id = _id; }
// ������ ���������
void Assignment::setPriority(int _priority) { priority = _priority; }
// ������ ����� ���������� ������
void Assignment::setComponent(std::string _component) { component = _component; }
// ������ ID
int Assignment::getId() const { return id; }
// ������ ���������
int Assignment::getPriority() const { return priority; }
// ������ ����� ���������� ������
std::string Assignment::getComponent() const { return component; }
// ³��������� ����� ������ �������� � ����
void Assignment::show() const
{
	std::cout	<< "Project ID: " << id
				<< "\nPriority: " << priority
				<< "\nComponent: " << component << "\n";
}
// ³��������� ����������
Assignment::~Assignment()
{}
