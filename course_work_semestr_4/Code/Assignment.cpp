

#include "Assignment.h"
// Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
Assignment::Assignment()
	: id(0)
	, priority(0)
	, component("")
{}
// Ïàðìåòðèçîâàíèé êîíñòðóêòîð
Assignment::Assignment(int _id, int _priority, std::string _component)
	: id(_id)
	, priority(_priority)
	, component(_component)
{}
// Ñåòòåð ID
void Assignment::setId(int _id) { id = _id; }
// Ñåòòåð ïð³îðèòåòó
void Assignment::setPriority(int _priority) { priority = _priority; }
// Ñåòòåð íàçâè êîìïîíåíòó ïðîºêòó
void Assignment::setComponent(std::string _component) { component = _component; }
// Ãåòòåð ID
int Assignment::getId() const { return id; }
// Ãåòòåð ïð³îðèòåòó
int Assignment::getPriority() const { return priority; }
// Ãåòòåð íàçâè êîìïîíåíòó ïðîºêòó
std::string Assignment::getComponent() const { return component; }
// Â³ðòóàëüíèé ìåòîä âèâîäó çàâäàííÿ â ïîò³ê
void Assignment::show() const
{
	std::cout	<< "Project ID: " << id
				<< "\nPriority: " << priority
				<< "\nComponent: " << component << "\n";
}
// Â³ðòóàëüíèé äåñòðóêòîð
Assignment::~Assignment()
{}
