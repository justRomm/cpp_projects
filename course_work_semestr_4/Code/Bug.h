/* ��-14 ������� �.�.
 * ���������� ����� Bug � ���� Bug.h */

#if !defined(bug_h_)
#define bug_h_
#include "Assignment.h"

class Bug final : public Assignment
{
private:
    // �������� ����������
	std::string expRes;
    // ������� ����������
    std::string obtRes;
public:
    // ����������� �� �������������
	Bug();
    // ��������������� �����������
	Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _obtRes);
    // ����������
    ~Bug() override;
    // ������ ���������� ����������
    void setExpRes(std::string _expRes);
    // ������ ��������� ����������
    void setObtRes(std::string _obtRes);
    // ������ ���������� ����������
    std::string getExpRes() const;
    // ������ ��������� ����������
    std::string getObtRes() const;
    // �������������� ����� ��� ��������� ������� � ���������
	void createFromKeyboard() override;
    // ������������� ������ ������� ��� ���������� ��'���� ������� �� ������
	void show() const;
    // ������������� ������ ������� ��� ���������� ��'���� ������� �� ������
    friend std::ostream& operator<<(std::ostream& out, const Bug& bug);
    // ������������� ������ ������� ��� ������������ ��'���� ������� � �������� ������
    friend std::istream& operator>>(std::istream& in, Bug* bug);
};

#endif

