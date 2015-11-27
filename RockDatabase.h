#ifndef ROCKDATABASE_H_INCLUDED
#define ROCKDATABASE_H_INCLUDED

#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "BST/Stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class RockDatabase{
    private:
        ifstream _inFile;
        BinarySearchTree<Mineral*> _primaryTree;
        BinarySearchTree<Mineral*> _secondaryTree;
        Stack<Mineral*> _undoStack;
        int _count;

    public:
        RockDatabase(){};
        RockDatabase(string filePath){_count = 0; loadFromFile(filePath);}
        void print(){_primaryTree.inOrder(display);}
        bool loadFromFile(string filePath);
        bool search(string target);
        bool deleteItem(string target);
        bool undoDelete();

        static void display(Mineral *anItem)
        {
            cout << "\t" << *anItem << endl;
        }


};

bool RockDatabase::loadFromFile(string filePath){
   	string name, formula, color, crys_system, cleavage;
	double hardness;
	char ch = ' ';
	_inFile.open(filePath);
	if (_inFile.fail())
	{
		cout << "No such file!" << endl;
		return false;
	}
    while (!_inFile.eof())
	{
		getline(_inFile, name);
		getline(_inFile, formula);
		getline(_inFile, color);
		_inFile >> hardness;
		_inFile.get(ch);
		getline(_inFile, crys_system);
		getline(_inFile, cleavage);
		_inFile.get(ch);
		Mineral* mineral;
		mineral = new Mineral(name,
                        crys_system,
                        cleavage,
                        color,
                        formula,
                        hardness);
		_primaryTree.insert(mineral, mineral->getName());
		_secondaryTree.insert(mineral, mineral->getCystalSystem());
		_count++;
	}
	_inFile.close();
	return true;

}

bool RockDatabase::search(string target){
    Mineral* mineral;
    if(_primaryTree.getEntry(target, mineral)){
        cout << "FOUND!";
        display(mineral);
        return true;
    }
    cout << "Sorry, '" << target << "' not found." << endl;
    return false;
}

bool RockDatabase::deleteItem(string target){
    Mineral* mineral;
    if(_primaryTree.getEntry(target, mineral)){
        _undoStack.push(mineral);
        _primaryTree.remove(target);
        return true;
    }
    return false;

}

bool RockDatabase::undoDelete(){
    Mineral* mineral;
    if(_undoStack.pop(mineral)){
        _primaryTree.insert(mineral, mineral->getName());
        return true;
    }
    return false;

}
#endif // ROCKDATABASE_H_INCLUDED
