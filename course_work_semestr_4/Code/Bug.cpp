
#include "Bug.h"
 // -------------------------------------------------------------------------------------------------
// Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
Bug::Bug()
	: Assignment()
	, expRes("")
	, obtRes("")
{
}
// -------------------------------------------------------------------------------------------------
// Ïàðìåòðèçîâàíèé êîíñòðóêòîð
Bug::Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _givenRes)
	: Assignment(_id, _priority, _component)
	, expRes(_expRes)
	, obtRes(_givenRes)
{
}
// -------------------------------------------------------------------------------------------------
// Ñåòòåð î÷³êóâàíèõ ðåçóëüòàò³â 
void Bug::setExpRes(std::string _expRes) { expRes = _expRes; }
// -------------------------------------------------------------------------------------------------
// Ñåòòåð îòðèìàíèõ ðåçóëüòàò³â 
void Bug::setObtRes(std::string _givenRes) { obtRes = _givenRes; }
// -------------------------------------------------------------------------------------------------
// Ãåòòåðî÷³êóâàíèõ ðåçóëüòàò³â
std::string Bug::getExpRes() const { return expRes; }
// -------------------------------------------------------------------------------------------------
// Ãåòòåð îòðèìàíèõ ðåçóëüòàò³â
std::string Bug::getObtRes() const { return obtRes; }
// -------------------------------------------------------------------------------------------------
// Ïåðåâèçíà÷åíèé ìåòîä äëÿ ñòâîðåííÿ äåôåêòó ç êëàâ³àòóðè
void Bug::createFromKeyboard()
{
	// Âçÿòòÿ çíà÷åííÿ ID ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter ID: ";
	std::string inp;
	std::cin >> inp;
	id = atoi(inp.c_str());
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (id < 1)
	{
		std::cout << "ID must be a number greater then 0.\nEnter again: ";
		std::cin >> inp;
		id = atoi(inp.c_str());
	}
	// Âçÿòòÿ çíà÷åííÿ ïð³îðèòåòó ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter priority: ";
	std::cin >> inp;
	priority = atoi(inp.c_str());
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (priority < 1)
	{
		std::cout << "Priority must be a number greater then 0.\nEnter again: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inp;
		priority = atoi(inp.c_str());
	}
	// Âçÿòòÿ çíà÷åííÿ íàçâè êîìïîíåíòó ç ââîäó êîðèñòóâà÷à
	std::cout << "Enter component: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, component, '\n');
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (component.empty())
	{
		std::cout << "Component's name can not be an empty string.\nEnter again: ";
		std::getline(std::cin, component, '\n');
	}
	// Âçÿòòÿ çíà÷åííÿ î÷³êóâàíèõ ðåçóëüòàò³â
	std::cout << "Enter expected result: ";
	std::getline(std::cin, expRes, '\n');
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (expRes.empty())
	{
		std::cout << "Expected result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, expRes, '\n');
	}
	// Âçÿòòÿ çíà÷åííÿ îòðèìàíèõ ðåçóëüòàò³â
	std::cout << "Enter obtained result: ";
	std::getline(std::cin, obtRes, '\n');
	// Ïåðåâ³ðêà íà êîðåêòí³ñòü ââîäó
	while (obtRes.empty())
	{
		std::cout << "Obtained result can not be an empty string.\nEnter again: ";
		std::getline(std::cin, obtRes, '\n');
	}
}
// -------------------------------------------------------------------------------------------------
// Ïåðåâèçíà÷åíèé ìåòîä äëÿ âèâîäó çàâäàííÿ â ïîò³ê
void Bug::show() const
{
	Assignment::show();
	std::cout << "Expected result: " << expRes 
			  << "\nObtained results: " << obtRes << "\n\n";
}
// Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ ñåð³àë³çàö³¿ îá'ºêòà äåôåêòó äî ïîòîêó
std::ostream& operator<<(std::ostream& out, const Bug& bug)
{
	// Çàïèñ ID òà ïð³îðèòåò äî âèõ³äíîãî ôàéëîâîãî ïîòîêó
	out.write((char*)&bug.id, sizeof(bug.id));
	out.write((char*)&bug.priority, sizeof(bug.priority));
	// Çàïèñ ðîçì³ðó ðÿäêà íàçâè êîìïîíåíòó òà ñàì ðÿäîê íàçâè êîìïîíåíòó äî âèõ³äíîãî ïîòîêó
	size_t componentSize = bug.component.size();
	out.write((char*)&componentSize, sizeof(componentSize));
	out.write(bug.component.data(), componentSize);
	// Çàïèñ ðîçì³ðó ðÿäêà î÷³êóâàíèõ ðåçóëüòàò³â òà ñàì ðÿäîê äî âèõ³äíîãî ïîòîêó
	size_t expResSize = bug.expRes.size();
	out.write((char*)&expResSize, sizeof(expResSize));
	out.write(bug.expRes.data(), expResSize);
	// Çàïèñ ðîçì³ðó ðÿäêà îòðèìàíèõ ðåçóëüòàò³â òà ñàì ðÿäîê äî âèõ³äíîãî ïîòîêó
	size_t obtResSize = bug.obtRes.size();
	out.write((char*)&obtResSize, sizeof(obtResSize));
	out.write(bug.obtRes.data(), obtResSize);
	// Ïîâåðíåííÿ âèõ³äíîãî ïîòîêó
	return out;
}
// -------------------------------------------------------------------------------------------------
// Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ äåñåð³àë³çàö³¿ îá'ºêòà äåôåêòó ç âõ³äíîãî ïîòîêó
std::istream& operator>>(std::istream& in, Bug* bug)
{
	try {
		// Ç÷èòóâàííÿ ID ç âõ³äíîãî ïîòîêó
		in.read((char*)&bug->id, sizeof(bug->id));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug ID");
		}
		// Ç÷èòóâàííÿ ïð³îðèòåòó ç âõ³äíîãî ïîòîêó
		in.read((char*)&bug->priority, sizeof(bug->priority));
		if (in.fail()) {
			throw std::runtime_error("Error reading bug priority");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà íàçâè êîìïîíåíòà
		size_t componentSize;
		in.read((char*)&componentSize, sizeof(componentSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading component size");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà î÷³êóâàíîãî ðåçóëüòàòó íàçâè êîìïîíåíòà
		bug->component.resize(componentSize);
		in.read((char*)bug->component.data(), componentSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading component data");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà î÷³êóâàíîãî ðåçóëüòàòó
		size_t expResSize;
		in.read((char*)&expResSize, sizeof(expResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result size");
		}
		// Ç÷èòóâàííÿ ðÿäêà î÷³êóâàíîãî ðåçóëüòàòó
		bug->expRes.resize(expResSize);
		in.read((char*)bug->expRes.data(), expResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading expected result data");
		}
		// Ç÷èòóâàííÿ ðîçì³ðó ðÿäêà îòðèìàíîãî ðåçóëüòàòó
		size_t obtResSize = 0;
		in.read((char*)&obtResSize, sizeof(obtResSize));
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result size");
		}
		// Ç÷èòóâàííÿ ðÿäêà îòðèìàíîãî ðåçóëüòàòó
		bug->obtRes.resize(obtResSize);
		in.read((char*)bug->obtRes.data(), obtResSize);
		if (in.fail()) {
			throw std::runtime_error("Error reading obtained result data");
		}
	} // ê³íåöü try
	// Îáðîáêà óñ³õ ìîæëèâèõ âèíÿòê³â ï³ä ÷àñ äåñåð³àë³çàö³¿ îá'ºêòà ç âõ³äíîãî ïîòîêó
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		in.setstate(std::ios::failbit);
	}
	// Ïîâåðíåííÿ âõ³äíîãî ïîòîêó
	return in;
} // ê³íåöü friend std::istream& operator>>(std::istream& in, Bug* bug)
// -------------------------------------------------------------------------------------------------
// Äåñòðóêòîð
Bug::~Bug()
{
}
