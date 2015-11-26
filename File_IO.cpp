#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Mineral.h"
#include "BST/BinarySearchTree.h"
using namespace std;

#define MAX 1000

void displayOLD(Mineral & anItem)
{
   cout << "\t" << anItem << endl;
}

void display(Mineral *anItem)
{
   cout << "\t" << *anItem << endl;
}

int main()
{
    vector<Mineral> minVec;
	ifstream inFile;
	string name[MAX], formula[MAX], color[MAX], crys_system[MAX], cleavage[MAX];
	double hardness[MAX];
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
		getline(inFile, name[count]);
		getline(inFile, formula[count]);
		getline(inFile, color[count]);
		inFile >> hardness[count];
		inFile.get(ch);
		getline(inFile, crys_system[count]);
		getline(inFile, cleavage[count]);
		inFile.get(ch);
		Mineral* mineral;
		mineral = new Mineral(name[count],
                        crys_system[count],
                        cleavage[count],
                        color[count],
                        formula[count],
                        hardness[count]);
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
	return 0;
}
