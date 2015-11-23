#include "Menu.h"

/************************************************

*************************************************/
void Menu::mainMenu()
{
	char choice;
	bool quit = false;
	cout << "Insert welcome message here." << endl;

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
			<< "Q - Quit\n";

		cin >> choice;
		choice = toupper(choice);
		cout << endl;

		switch (choice)
		{
		case 'A': // add
			caseAdd();
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
			caseStatistic();
			break;
		case 'N': // undo delete
			caseUndo();
			break;
		case 'Q': // quit
			quit = true;
			break;
		default:
			cout << "Invalid input.\n";
		}
		cout << endl;
	}

	cout << "Insert \"thank you\" message here." << endl;
}

/*************************************************
*************************************************/
void Menu::caseAdd()
{
}

void Menu::caseUndo()
{
}

/*************************************************
*************************************************/
void Menu::caseDelete()
{
}

/*************************************************
*************************************************/
void Menu::caseStatistic()
{
}

/*************************************************
*************************************************/
void Menu::caseWriteFile()
{

}

/*bool outFileValid(ofstream &outFile)
{
	outFile.open("file_name.txt");
	if (!outFile.is_open())
	{
		cout << "Error opening out put file!" << endl;
		return false;
	}
	return true;

}*/

/*************************************************
*************************************************/
void Menu::caseSearch()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select a search type from the options below:\n" << endl
			<< "P - Primary Search\n" // change names later
			<< "S - Secondary Search\n"
			<< "R - Return to previous menu\n" << endl;
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'P': // primary key
			break;
		case 'S': // secondary key
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
*************************************************/
void Menu::caseList()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select how to display the website data from the options below.\n" << endl;
		cout << "U - display unsorted\n"
			<< "P - display by domain name\n"
			<< "O - display by countries\n"
			<< "I - display special\n"
			<< "R - Return to previous menu\n" << endl;
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'U':
			cout << "Unsorted List as Followed:" << endl;
			break;
		case 'P':

			break;

		case 'O':
			break;

		case 'I':

			break;

		case 'R':
			break;

		default:
			cout << "Invalid input." << endl;
			break;
		}
	}
}