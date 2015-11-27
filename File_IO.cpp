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
/*
	ifstream inFile;
	string name, formula, color, crys_system, cleavage;
	double hardness;
	char ch = ' ';
	int count = 0, i = 0;
	inFile.open("mineral.txt");
	if (inFile.fail())
	{
		cout << "No such file!" << endl;
		exit(100);
	}
	BinarySearchTree<Mineral*> tree;
	BinarySearchTree<Mineral*> secondTree;
	while (!inFile.eof())
	{
		getline(inFile, name);
		getline(inFile, formula);
		getline(inFile, color);
		inFile >> hardness;
		inFile.get(ch);
		getline(inFile, crys_system);
		getline(inFile, cleavage);
		inFile.get(ch);
		Mineral* mineral;
		mineral = new Mineral(name,
                        crys_system,
                        cleavage,
                        color,
                        formula,
                        hardness);
		tree.insert(mineral, mineral->getName());
		secondTree.insert(mineral, mineral->getCystalSystem());
		count++;
	}




	//tree.breadth(display);
	cout << "Primary Tree: " << endl;
	tree.inOrder(display);
	cout << "Secondary Tree: " << endl;
	secondTree.inOrder(display);
	cout << "Deleting Ice from primary tree..." << endl;
	cout << "Deleting Hexagonal from secondary tree..." << endl;
	tree.remove("Ice");
	secondTree.remove("Hexagonal");
	cout << "Primary Tree: " << endl;
	tree.inOrder(display);
	cout << "Secondary Tree: " << endl;
	secondTree.inOrder(display);
	//tree.indented();
	//system("pause");
	*/
	RockDatabase rockBase("mineral.txt");
	rockBase.search("Idfwu");
	cout << "Deleting Ice\n" << endl;
	rockBase.deleteItem("Ice");
	rockBase.print();
	cout << "\nUndo delete Ice\n" << endl;
	rockBase.undoDelete();
	rockBase.print();

	return 0;
}
