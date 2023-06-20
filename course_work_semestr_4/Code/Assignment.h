

#if !defined(ASSIGNMENT_H_)
#define ASSIGNMENT_H_
#include <iostream>		// âèêîðèñòîâóºòñüÿ äëÿ ðîáîòè ç ïîòîêàìè ââîäó/âèâîäó
#include <fstream>		// âèêîðèñòîâóºòüñÿ äëÿ ôàéëîâèõ ïîòîê³â
#include <exception>	// âèêîðèñòîâóºòüñÿ äëÿ ðîáîòè ç âèíÿòêàìè
#include <string>		// âèêîðèñòîâóºòüñÿ äëÿ ðîáîòè ç êëàñîì std::string
#include <ios>			// âèêîðèñòîâóºòüñÿ äëÿ îòðèìàííÿ ðîçì³ðó ïîòîêó
#include <limits>		// âèêîðèñòîâóºòüñÿ äëÿ îòðèìàííÿ ÷èñëîâèõ îáìåæåíü
#include <sys/stat.h>	// âèêîðèñòîâóºòüñÿ äëÿ ïåðåâ³ðêè ³ñíóâàííÿ ôàéëó

// Àáñòðàêòíèé êëàñ
class Assignment
{
protected:
	// ID çàâäàííÿ
	int id;
	// Ïð³îðèòåò çàâäàííÿ
	int priority;
	// Íàçâà êîìïîíåíòó ïðîºêòó
	std::string component;
public:
	// Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
	Assignment();
	// Ïàðìåòðèçîâàíèé êîíñòðóêòîð
	Assignment(int _id, int _priority, std::string _component);
	// Â³ðòóàëüíèé äåñòðóêòîð
	virtual ~Assignment();
	// Ñåòòåð ID
	void setId(int _id);
	// Ñåòòåð ïð³îðèòåòó
	void setPriority(int _priority);
	// Ñåòòåð íàçâè êîìïîíåíòó ïðîºêòó
	void setComponent(std::string _component);
	// Ãåòòåð ID
	int getId() const;
	// Ãåòòåð ïð³îðèòåòó
	int getPriority() const;
	// Ãåòòåð íàçâè êîìïîíåíòó ïðîºêòó
	std::string getComponent() const;
	// Àáñòðàêòíèé ìåòîä äëÿ ñòâîðåííÿ çàâäàííÿ ç êëàâ³àòóðè
	virtual void createFromKeyboard() = 0;
	// Â³ðòóàëüíèé ìåòîä âèâîäó çàâäàííÿ â ïîò³ê
	virtual void show() const;
};

#endif
