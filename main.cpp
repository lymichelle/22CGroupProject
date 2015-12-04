#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "RockDatabase.h"
using namespace std;

#define MAX 1000


class DatabaseMenu{
private:
	RockDatabase rockBase;

public:
	DatabaseMenu(){ rockBase.loadFromFile("mineral.txt"); mainMenu(); }
	void mainMenu();
	void caseSearch();
	void caseList();
	void caseDelete();
	void caseUndo();
	void caseWriteFile();
	void caseInfo();
	~DatabaseMenu(){rockBase.saveToFile("backup.txt");}
};


/*************************************************
* Definition of function display.
* This function takes a Mineral object and prints
* it, using the overloaded ostream operator.
*************************************************/
void display(Mineral *anItem)
{
   cout << "\t" << *anItem << endl;
}

/*************************************************
* main function									 *
*************************************************/
int main()
{
	DatabaseMenu menu;
	cin.get();
	return 0;
}

/*************************************************
* Definition of function mainMenu.
* This function displays a list of options and
* prompts the user to input a command and calls
* the corresponding function or submenu.  
*************************************************/
void DatabaseMenu::mainMenu()
{
	char choice;
	bool quit = false;
	cout << "Welcom to our mineral databse!" << endl;

	// add Jose's input validation thing

	while (!quit)
	{	// update below
		cout << "Please input the letter corresponding to the function you'd like to use from the list below." << endl
			 << "A - Add New \n"
			 << "D - Delete \n"
			 << "N - Undo Delete\n"
			 << "H - Statistics\n"
			 << "L - List \n"
			 << "S - Search for \n"
			 << "W - Write data into file\n"
		 	 << "I - Info about developers\n"
			 << "Q - Quit\n"
			 << "Input: ";

		cin >> choice;
		choice = toupper(choice);
		cout << endl;

		switch (choice)
		{
		case 'A': // add
			rockBase.addMineral();
			break;
		case 'D': // delete
			caseDelete();
			break;
		case 'S': // search
			caseSearch();
			break;
		case 'L': // list
			caseList();
			break;
		case 'W': // write to file
			caseWriteFile();
			break;
		case 'H': // Statistic
			rockBase.showHashStats();
			break;
		case 'N': // undo delete
			caseUndo();
			break;
        case 'I':
            caseInfo();
            break;
		case 'Q': // quit
			quit = true;
			break;
		default:
			cout << "Invalid input.\n"
				 << "Input: ";
		}
		cout << endl;
	}

	cout << "Goodbye." << endl;
}

/*************************************************
* Definition of function caseInfo
* This function displays the developers and their
* tasks.
*************************************************/
void DatabaseMenu::caseInfo(){
    cout << "Michelle Ly: File I/O" << endl;
    cout << "John Dwyer: Screen I/O" << endl;
    cout << "Nausheen Sujela: Hash Structure/Functions" << endl;
    cout << "Jose Sepulveda: BST, Integration" << endl;
}

/*************************************************
* Definition of function caseUndo.
* This function calls the rockBase undoDelete
* function to restore the last deleted object,
* and displays whether this was successful or not.
*************************************************/
void DatabaseMenu::caseUndo()
{
	if (rockBase.undoDelete()){
		cout << "Deletion was undone." << endl;
		return;
	}
	cout << "Nothing to undo." << endl;

}

/*************************************************
* Definition of function caseDelete.
* This function prompts the user to input the name
* of a mineral to be deleted, then calls the
* rockBase function to do so. This function will
* then display whether the deletion was successful
* or not.
*************************************************/
void DatabaseMenu::caseDelete()
{
	string mineralName;
	bool valid = true;
	cout << "Input the mineral would you like to delete:\n" << endl;
		cin.ignore();
		getline(cin, mineralName);

		if (rockBase.deleteItem(mineralName)){
			cout << "Successfully deleted, " << mineralName << endl;
			return;
		}
		cout << "Sorry, " << mineralName << " not found." << endl;

		return;
}

/*************************************************
* Definition of function caseWriteFile
* This function prompts the user to enter a file
* name to write to, then calls the rockBase
* function to write the data to the named file.
*************************************************/
void DatabaseMenu::caseWriteFile()
{
    string str;
    cout << "Enter a filename to write to: ";
    cin.ignore();
    getline(cin, str);
    rockBase.saveToFile(str);
}

/*************************************************
* Definition of function caseSearch.
* This function displays a list of options
* relating to searching for data and
* prompts the user to input a command which calls
* the corresponding function or submenu.
*************************************************/
void DatabaseMenu::caseSearch()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select a search type from the options below:\n" << endl
			<< "P - Search by Name\n"
			<< "S - Search by Crystal System\n"
			<< "R - Return to Previous Menu\n" 
			<< "Input: ";
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'P': // primary key
            string s;
            cout << "Enter a seach query: ";
            cin.ignore();
            getline(cin, s);// secondary key
            if(!rockBase.search(s)){
                cout << "Nothing found.\n";
            }
			break;
		case 'S':
            string s;
            cout << "Enter a seach query: ";
            cin.ignore();
            getline(cin, s);// secondary key
            if(!rockBase.secondarySearch(s)){
                cout << "Nothing found.\n";
            }
			break;
		case 'R': // previous
			valid = false;
			break;
		default:
			valid = false;
			cout << endl << "Invalid input. ";
			break;
		}
	}

	return;
}

/*************************************************
* Definition of function caseList.
* This function displays a list of options
* relating to displaying the data and
* prompts the user to input a command which calls
* the corresponding function or submenu.
*************************************************/
void DatabaseMenu::caseList()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select a display method.\n" << endl;
		cout << "U - Display Unsorted\n"
			 << "P - Display Sorted by Name\n"
			 << "S - Display Sorted by Crystal System\n"
			 << "I - Display Indented Tree Sorted by Name\n"
			 << "R - Return to Previous Menu\n"
			 << "Input: ";
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'U':
			cout << "Unsorted List as Followed:" << endl;
			rockBase.printHash();
			break;
		case 'P':
			rockBase.printPrimarySorted();
			break;
		case 'S':
			rockBase.printSecondarySorted();
			break;
        case 'I':
            rockBase.indented();
            break;
		case 'R':
			return;
			break;
		default:
			cout << "Invalid input." << endl;
			break;
		}
	}
}