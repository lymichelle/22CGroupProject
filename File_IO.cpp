#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Mineral.h"
#include "BST/BinarySearchTree.h"
using namespace std;

#define MAX 1000

void display(Mineral & anItem)
{
   cout << "\t" << anItem << endl;
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
	BinarySearchTree<Mineral> tree;
	BinarySearchTree<Mineral> secondTree;
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
		Mineral mineral(name[count],
                        crys_system[count],
                        cleavage[count],
                        color[count],
                        formula[count],
                        hardness[count]);
		minVec.push_back(mineral);
		tree.insert(mineral, mineral.getName());
		secondTree.insert(mineral, mineral.getCystalSystem());
		count++;
	}


	for(auto v: minVec){
        cout << v;
	}

	//tree.breadth(display);
	cout << "Primary Tree: " << endl;
	tree.inOrder(display);
	cout << "Secondary Tree: " << endl;
	secondTree.inOrder(display);
	//tree.indented();
	//system("pause");
	return 0;
}
