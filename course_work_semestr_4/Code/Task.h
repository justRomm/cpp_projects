

#if !defined(TASK_H_)
#define TASK_H_
#include "Assignment.h"

class Task final: public Assignment
{
private:
    // Îïèñ çàâäàííÿ
	std::string taskDesc;
public:
    // Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
	Task();
    // Ïàðìåòðèçîâàíèé êîíñòðóêòîð
	Task(int _id, int _priority, std::string _component, std::string _taskDesc);
    // Äåñòðóêòîð
    ~Task() override;
    // Ñåòòåð îïèñó çàâäàííÿ
	void setTaskDesc(std::string _taskDesc);
    // Ãåòòåð îïèñó çàâäàííÿ
	std::string getTaskDesc() const;
    // Ïåðåâèçíà÷åíèé ìåòîä äëÿ ñòâîðåííÿ çàâäàííÿ ç êëàâ³àòóðè
	void createFromKeyboard() override;
    // Ïåðåâèçíà÷åíèé ìåòîä äëÿ âèâîäó çàâäàííÿ â ïîò³ê
	void show() const override;
    // Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ ñåð³àë³çàö³¿ îá'ºêòà çàâäàííÿ äî ïîòîêó
    friend std::ostream& operator<<(std::ostream& out, const Task& task);
    // Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ äåñåð³àë³çàö³¿ îá'ºêòà çàâäàííÿ ç âõ³äíîãî ïîòîêó
    friend std::ifstream& operator>>(std::ifstream& in, Task* task);
};

#endif

