#ifndef ROCKDATABASE_H_INCLUDED
#define ROCKDATABASE_H_INCLUDED

#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "HashTable.h"
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
        Hash<Mineral*> _hashTable;
        // Stack that holds the the pointers to deleted data
        Stack<Mineral*> _undoStackData;

        // Stack that holds information on which tree it was
        // deleted from; True = Primary, False = Secondary.
        Stack<int> _undoStackBool;
        int _count;


    public:
        RockDatabase(){};
        RockDatabase(string filePath){_count = 0; loadFromFile(filePath);}
        void print(){
            //cout<<"Primary Tree, Key = Name\n";
            //_primaryTree.inOrder(display);
            //cout<<string(50, '-') << "\nSecondary Tree, Key = Crystal System\n";
            //_secondaryTree.inOrder(display);
            cout<<string(50, '-') << "\nHash Table\n";
            _hashTable.traverseHashTable(displayHash);
            //_primaryTree.breadth(display);
            //_secondaryTree.indented();
        }
        bool loadFromFile(string filePath);
        bool search(string target);

        //Takes two arguments, the target to delete
        //and a bool representing which tree to delete from
        //True = Primary Tree, False = Secondary Tree.
        bool deleteItem(string target, int structureId);
        bool undoDelete();

        static void display(Mineral *anItem)
        {
            cout << "\t" << *anItem << endl;
        }

        static void displayHash (HashNode<Mineral*> *aHashNode)
        {
            cout << *(aHashNode->_dataPtr) << endl;
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
		_hashTable.insert(mineral->getName(), mineral);
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

bool RockDatabase::deleteItem(string target, int structureId){
    Mineral* mineral;
    if(structureId == 0){
        if(_hashTable.getEntry(target, mineral)){
            _undoStackData.push(mineral);
            _undoStackBool.push(structureId);
            _hashTable.remove(target);
        }
    }else if(structureId == 1){
        if(_primaryTree.getEntry(target, mineral)){
            _undoStackData.push(mineral);
            _undoStackBool.push(structureId);
            _primaryTree.remove(target);
            return true;
        }
    }else if(structureId == 2){
        if(_secondaryTree.getEntry(target, mineral)){
            _undoStackData.push(mineral);
            _undoStackBool.push(structureId);
            _secondaryTree.remove(target);
            return true;
        }
    }
    return false;

}

bool RockDatabase::undoDelete(){
    Mineral* mineral;
    int structureId;
    if(_undoStackData.pop(mineral) && _undoStackBool.pop(structureId)){
        if(structureId == 0){
            _hashTable.insert(mineral->getName(), mineral);
        }else if(structureId == 1){
            _primaryTree.insert(mineral, mineral->getName());
        }else if(structureId == 2){
            _secondaryTree.insert(mineral, mineral->getCystalSystem());
        }

        return true;
    }
    return false;

}

#endif // ROCKDATABASE_H_INCLUDED
