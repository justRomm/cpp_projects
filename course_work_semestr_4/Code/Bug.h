
#if !defined(bug_h_)
#define bug_h_
#include "Assignment.h"

class Bug final : public Assignment
{
private:
    // Î÷³êóâàí³ ðåçóëüòàòè
	std::string expRes;
    // Îòðèìàí³ ðåçóëüòàòè
    std::string obtRes;
public:
    // Êîíñòðóêòîð çà çàìîâ÷óâàííÿì
	Bug();
    // Ïàðìåòðèçîâàíèé êîíñòðóêòîð
	Bug(int _id, int _priority, std::string _component, std::string _expRes, std::string _obtRes);
    // Äåñòðóêòîð
    ~Bug() override;
    // Ñåòòåð î÷³êóâàíèõ ðåçóëüòàò³â
    void setExpRes(std::string _expRes);
    // Ñåòòåð îòðèìàíèõ ðåçóëüòàò³â
    void setObtRes(std::string _obtRes);
    // Ãåòòåð î÷³êóâàíèõ ðåçóëüòàò³â
    std::string getExpRes() const;
    // Ãåòòåð îòðèìàíèõ ðåçóëüòàò³â
    std::string getObtRes() const;
    // Ïåðåâèçíà÷åíèé ìåòîä äëÿ ñòâîðåííÿ äåôåêòó ç êëàâ³àòóðè
	void createFromKeyboard() override;
    // Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ ñåð³àë³çàö³¿ îá'ºêòà äåôåêòó äî ïîòîêó
	void show() const;
    // Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ ñåð³àë³çàö³¿ îá'ºêòà äåôåêòó äî ïîòîêó
    friend std::ostream& operator<<(std::ostream& out, const Bug& bug);
    // Ïåðåâàíòàæåíà äðóæíÿ ôóíêö³ÿ äëÿ äåñåð³àë³çàö³¿ îá'ºêòà äåôåêòó ç âõ³äíîãî ïîòîêó
    friend std::istream& operator>>(std::istream& in, Bug* bug);
};

#endif

