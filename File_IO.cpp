#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "RockDatabase.h"
using namespace std;

#define MAX 1000



void display(Mineral *anItem)
{
   cout << "\t" << *anItem << endl;
}

int main()
{

	RockDatabase rockBase("mineral.txt");
	//rockBase.deleteItem("Hexagonal", false);
    //rockBase.deleteItem("Ice", true);
    rockBase.print();
	cout << "\n" << string(50, '-') <<"\n" << endl;
    string temp = "Graphite";
    if(rockBase.deleteItem(temp, true)){
        cout << temp  << "Delete successful\n";
    }

	rockBase.print();
	cout << "\n" << string(50, '-') <<"\n" << endl;
	rockBase.undoDelete();
	rockBase.print();

	return 0;
}
