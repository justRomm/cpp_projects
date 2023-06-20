/* ��-14 ������� �.�.
 * ���������� ����� Task � ���� Task.h */

#if !defined(TASK_H_)
#define TASK_H_
#include "Assignment.h"

class Task final: public Assignment
{
private:
    // ���� ��������
	std::string taskDesc;
public:
    // ����������� �� �������������
	Task();
    // ��������������� �����������
	Task(int _id, int _priority, std::string _component, std::string _taskDesc);
    // ����������
    ~Task() override;
    // ������ ����� ��������
	void setTaskDesc(std::string _taskDesc);
    // ������ ����� ��������
	std::string getTaskDesc() const;
    // �������������� ����� ��� ��������� �������� � ���������
	void createFromKeyboard() override;
    // �������������� ����� ��� ������ �������� � ����
	void show() const override;
    // ������������� ������ ������� ��� ���������� ��'���� �������� �� ������
    friend std::ostream& operator<<(std::ostream& out, const Task& task);
    // ������������� ������ ������� ��� ������������ ��'���� �������� � �������� ������
    friend std::ifstream& operator>>(std::ifstream& in, Task* task);
};

#endif

