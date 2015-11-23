	#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Menu
{
private:

public:
	void mainMenu();
	void caseSearch();
	void caseList();
	void caseAdd();
	void caseDelete();
	void caseUndo();
	void caseWriteFile();
	void caseStatistic();
};

#endif