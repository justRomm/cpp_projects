/* ��-14 ������� �.�.
 * ���������� ����� QueueP � ���� QueueP.h */

#if !defined(QUEUEP_H_)
#define QUEUEP_H_

#include "Task.h"
#include "Bug.h"
// ���������, ����������� � ��������� ����� � ����������
struct Node
{
	// �������� ��������
	int priority;
	// �������
	Assignment* el;
	// ��������� �� ��������� �����
	Node* next;
};

class QueueP
{
private:
	// ����� ����� � ����������
	int size;
	// ������ ����� � ����������
	Node* head;
public:
	// ����������� �� �����������
	QueueP();
	// ����������
	~QueueP();
	// ������ ������ ����� � ����������
	int getSize() const;
	// ������ ��������� �� ������ ����� � ����������
	Node* getHead() const;
	// ����� ��������� �������� �� ����������
	void push(Assignment* elem, int priority);
	// ����� ��������� ������ �������� � ������ ����� � ����������
	void pop();
	// ����� �������� ����� � ����������
	void clear();
	// ����� �������� ����� � ���������� �� ���������
	bool empty() const;
	// ����� ������ ����� � ���������� � ����
	void show() const;
	// ����� ���������� ����� � ����������
	void sort();
	// �������������� ��������� ������������
	QueueP* operator=(const QueueP& _queue);
	// �����  ��� ���������� �������� � ����� � ����� � ����������
	void readFromFile();
	// �����  ��� ������ ����� � ���������� � ���� 
	void writeToFile() const;
	// �����  ��� ��������� ������� �������� ���� ������ � ����� � ����������, �� ����������� � ������� ���������
	void doReq() const;
};
#endif