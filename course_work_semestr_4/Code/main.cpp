
#define _CRT_SECURE_NO_WARNINGS
#include "QueueP.h"
// -------------------------------------------------------------------------------------------------
// Ôóíêö³ÿ ìåíþ êîðèñòóâà÷à
void Run()
{
	// Ñòâîðåííÿ îá'ºêòó òèïó ÷åðãè ç ïð³îðèòåòîì
	QueueP* queue = new QueueP();
	int i;
	std::string s;
	// Âèâåäåííÿ ìåíþ
	do
	{
		system("cls");
		std::cout
			<< "+--------------MENU--------------+\n"
			<< "| <1>. Create task object        |\n"
			<< "| <2>. Create bug object         |\n"
			<< "| <3>. Show assignments          |\n"
			<< "| <4>. Remove the project        |\n"
			<< "| <5>. Save to the file          |\n"
			<< "| <6>. Load from the file        |\n"
			<< "| <7>. Do request                |\n"
			<< "| <8>. Sort                      |\n"
			<< "| <9>. Leave the program         |\n"
			<< "+--------------------------------+\n"
			<< "\n>> ";
		std::getline(std::cin, s, '\n');
		i = atoi(s.c_str());
		// Îáðîáêà âàð³àíò³â ìåíþ
		switch (i)
		{
		case 1:
		{
			system("cls");
			// Ñòâîðåííÿ íîâîãî îá'ºêòó
			Assignment* ptr = new Task();
			ptr->createFromKeyboard();
			// Äîäàâàííÿ îá'ºêòó äî ÷åðãè ç ïð³îðèòåòîì
			queue->push(ptr, ptr->getPriority());
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			// Ñòâîðåííÿ íîâîãî îá'ºêòó
			Assignment* ptr = new Bug();
			ptr->createFromKeyboard();
			// Äîäàâàííÿ îá'ºêòó äî ÷åðãè ç ïð³îðèòåòîì
			queue->push(ptr, ptr->getPriority());
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			std::cout << "Queue elements: \n";
			queue->show();
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			queue->clear();
			std::cout << "Cleared...\n";
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			queue->writeToFile();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			queue->readFromFile();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			queue->doReq();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			queue->sort();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");
			std::cout << "\n\nBye-bye\n\n\n";
			system("pause");
			return;
		}
		default:
		{
			system("cls");
			std::cout << "Your choice is not correct...\n";
			system("pause");
			break;
		} 
		} // ê³íåöü switch (i)
	} while (1);
} // ê³íåöü void Run()
// -------------------------------------------------------------------------------------------------
// Îñíîâíà ôóíêö³ÿ
int main()
{
	Run(); 
	return 0;
}
