/* ��-14 ������� �.�.
 * ���������� ����� Assingment � ���� Assingment.h */

#if !defined(ASSIGNMENT_H_)
#define ASSIGNMENT_H_
#include <iostream>		// ��������������� ��� ������ � �������� �����/������
#include <fstream>		// ��������������� ��� �������� ������
#include <exception>	// ��������������� ��� ������ � ���������
#include <string>		// ��������������� ��� ������ � ������ std::string
#include <ios>			// ��������������� ��� ��������� ������ ������
#include <limits>		// ��������������� ��� ��������� �������� ��������
#include <sys/stat.h>	// ��������������� ��� �������� ��������� �����

// ����������� ����
class Assignment
{
protected:
	// ID ��������
	int id;
	// �������� ��������
	int priority;
	// ����� ���������� ������
	std::string component;
public:
	// ����������� �� �������������
	Assignment();
	// ��������������� �����������
	Assignment(int _id, int _priority, std::string _component);
	// ³��������� ����������
	virtual ~Assignment();
	// ������ ID
	void setId(int _id);
	// ������ ���������
	void setPriority(int _priority);
	// ������ ����� ���������� ������
	void setComponent(std::string _component);
	// ������ ID
	int getId() const;
	// ������ ���������
	int getPriority() const;
	// ������ ����� ���������� ������
	std::string getComponent() const;
	// ����������� ����� ��� ��������� �������� � ���������
	virtual void createFromKeyboard() = 0;
	// ³��������� ����� ������ �������� � ����
	virtual void show() const;
};

#endif