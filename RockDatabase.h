//This class is a database that uses 2 BST's and a HashTable to store minerals
//Edited by: Michelle Ly, Jose Sepulveda

#ifndef ROCKDATABASE_H_INCLUDED
#define ROCKDATABASE_H_INCLUDED

#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "HashTable.h"
#include "BST/Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
class RockDatabase{
private:
	ifstream _inFile;
	ofstream _outFile;

	//BST's
	BinarySearchTree<Mineral*> _primaryTree;
	BinarySearchTree<Mineral*> _secondaryTree;

	//HashTable
	Hash<Mineral*> _hashTable;

	// Stack that holds the the pointers to deleted data
	Stack<Mineral*> _undoStackData;

	// Stack that holds information on which tree it was
	// deleted from; True = Primary, False = Secondary.
	int _count;


public:
	// Constructors
	RockDatabase(){};
	RockDatabase(string filePath){ _count = 0; loadFromFile(filePath); }

	// All the display functions
	void showHashStats(){ _hashTable.showStatistics(); }
	void indented(){ _primaryTree.indented(); }
	void printDatabase();
	void printHash(){
		_hashTable.traverseHashTable(displayHash);
	}
	void printPrimarySorted(){
		cout << "Primary Tree, Key = Name\n";
		_primaryTree.inOrder(display);
	}
	void printSecondarySorted(){
		cout << "Secondary Tree, Key = Crystal System\n";
		_secondaryTree.inOrder(display);
	}


	// All the mutators for the database
	void addMineral();
	void insertMineral(Mineral* min);
	bool deleteItem(string target);
	bool undoDelete();


	// Search functions
	bool search(string target);
	bool secondarySearch(string target);

	// File I/O functins
	void saveToFile(string fileName);
	bool loadFromFile(string filePath);

	// Helper functions
	bool stringToDouble(string str, double & dub);
	bool isStrNum(string str);

	// Display functions passed into structures
	static void display(Mineral *anItem)
	{
		cout << "" << *anItem << endl;
	}
	static void displayHash(HashNode<Mineral*> *aHashNode)
	{
		cout << "" << *(aHashNode->_dataPtr) << endl;
	}

};

// Inserts mineral to all structures
void RockDatabase::insertMineral(Mineral* min){
	_hashTable.insert(min->getName(), min);
	_primaryTree.insert(min, min->getName());
	_secondaryTree.insert(min, min->getCystalSystem());
	_count++;
}


// Prompts user to enter a mineral
void RockDatabase::addMineral(){
	string name, crystSyst, form, cleav, col;
	string hard;
	double hardness = 0.0;
	cin.ignore();
	cout << "Enter the mineral name: ";
	getline(cin, name);
	cout << "\nEnter the crystal system: ";
	getline(cin, crystSyst);
	cout << "\nEnter the color: ";
	getline(cin, col);
	cout << "\nEnter the formula: ";
	getline(cin, form);
	cout << "\nEnter the hardness: ";
	getline(cin, hard);
	while (!stringToDouble(hard, hardness)){
		cout << "\nPlease enter a valid hardness (floating Point #): ";
		cin >> hard;
	}
	cout << "\nEnter the cleavage: ";
	cin >> cleav;
	cout << endl;
	Mineral * mineral;
	mineral = new Mineral(name, crystSyst, cleav, col, form, hardness);
	insertMineral(mineral);

}

//Prints all contents of the database
void RockDatabase::printDatabase(){
	cout << "Primary Tree, Key = Mineral Name\n";
	_primaryTree.inOrder(display);
	cout << string(50, '-') << endl;
	cout << "Secondary Tree, Key = Crystal System\n";
	_secondaryTree.inOrder(display);
	cout << string(50, '-') << endl;
	cout << "Hash Table\n";
	_hashTable.traverseHashTable(displayHash);
	cout << string(50, '-') << endl;


}

// Saves contents of the HashTable to "fileName"
void RockDatabase::saveToFile(string fileName){
	_outFile.open(fileName);
	_hashTable.traverseHashTable(_outFile);
	_outFile.close();
}

//Reading file into Mineral class
bool RockDatabase::loadFromFile(string filePath){
	string name, formula, color, crys_system, cleavage, hardness;
	string temp;
	double hard;
	char ch = ' ';
	_inFile.open(filePath);
	if (_inFile.fail())
	{
		cout << "No such file: " << filePath << endl;
		return false;
	}
	char c;
	while (!_inFile.eof())
	{
		getline(_inFile, temp, ' ');
		getline(_inFile, name);
		getline(_inFile, temp, ' ');
		getline(_inFile, crys_system);
		getline(_inFile, temp, ' ');
		getline(_inFile, formula);
		getline(_inFile, temp, ' ');
		getline(_inFile, cleavage);
		getline(_inFile, temp, ' ');
		getline(_inFile, color);
		getline(_inFile, temp, ' ');
		getline(_inFile, hardness);
		stringToDouble(hardness, hard);
		_inFile >> c;
		Mineral* mineral;
		mineral = new Mineral(name,
			crys_system,
			cleavage,
			color,
			formula,
			hard);
		insertMineral(mineral);
		_count++;
	}
	_inFile.close();
	return true;

}

//Converting "hardness" to a double
bool RockDatabase::stringToDouble(string str, double & dub){
	size_t pos = str.find('.');
	if (pos != string::npos){
		string wholeNum = str.substr(0, pos);
		string deciNum = str.substr(pos + 1);
		if (isStrNum(wholeNum) && isStrNum(deciNum)){
			dub = stod(wholeNum + "." + deciNum);
			return true;
		}

	}
	return false;
}

//Confirming if string is a decimal digit
bool RockDatabase::isStrNum(string str){
	for (int i = 0; i < str.length(); i++)
		if (!isdigit(str[i]))
			return false;
	return true;

}
//Searching via primary key using getEntry
bool RockDatabase::search(string target){
	Mineral* mineral;
	if (_hashTable.getEntry(target, mineral)){
		display(mineral);
		return true;
	}
	return false;
}

//Searching via secondary key using findEntries
bool RockDatabase::secondarySearch(string target){
	Mineral* mineral;
	if (_secondaryTree.findEntries(display, target)){
		return true;
	}
	return false;
}

//Deleting data by searching for target, pushing it into
//_undoStackData, and deleting it from hash and BSTs
bool RockDatabase::deleteItem(string target){
	Mineral* mineral;
	if (_hashTable.getEntry(target, mineral)){
		_undoStackData.push(mineral);
		_hashTable.remove(target);
		_primaryTree.remove(target);
		_secondaryTree.remove(mineral);
		_count--;
		return true;
	}
	return false;

}
//Undo-ing the last deletion by popping the last
//item from _undoStackData and inserting it into
//hash and BSTs
bool RockDatabase::undoDelete(){
	Mineral* mineral;
	if (_undoStackData.pop(mineral)){
		_hashTable.insert(mineral->getName(), mineral);
		_primaryTree.insert(mineral, mineral->getName());
		_secondaryTree.insert(mineral, mineral->getCystalSystem());
		_count++;
		return true;
	}
	return false;

}


#endif // ROCKDATABASE_H_INCLUiDED
