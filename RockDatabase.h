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
        BinarySearchTree<Mineral*> _primaryTree;
        BinarySearchTree<Mineral*> _secondaryTree;
        Hash<Mineral*> _hashTable;
        // Stack that holds the the pointers to deleted data
        Stack<Mineral*> _undoStackData;
	void toRehash();
        // Stack that holds information on which tree it was
        // deleted from; True = Primary, False = Secondary.
       // Stack<int> _undoStackBool;
        int _count;


    public:
        void indented(){
            _primaryTree.indented();
        }
        void saveToFile(string fileName){
			_outFile.open(fileName);
			_hashTable.traverseHashTable(_outFile);
			_outFile.close();
		}
		bool stringToDouble(string str, double & dub);
		bool isStrNum(string str);
		bool secondarySearch(string target);

        RockDatabase(){};
        RockDatabase(string filePath){_count = 0; loadFromFile(filePath);}
        void printPrimarySorted(){
            cout<<"Primary Tree, Key = Name\n";
            _primaryTree.inOrder(display);
            //cout<<string(50, '-') << "\nHash Table\n";
            //_hashTable.traverseHashTable(displayHash);
            //_primaryTree.breadth(display);
            //_secondaryTree.indented();
        }
		void printDatabase(){
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
        void printSecondarySorted(){
            cout<<string(50, '-') << "\nSecondary Tree, Key = Crystal System\n";
            _secondaryTree.inOrder(display);
        }
        void printHash(){
            _hashTable.traverseHashTable(displayHash);
        }

        void addMineral(){
            string name, crystSyst, form, cleav, col;
            string hard;
            double hardness = 0.0;
            cin.ignore();
            cout << "Enter the mineral name: ";
            getline(cin, name);
            cout << "\nEnter the crystal system: ";
            cin >> crystSyst;
			cout << "\nEnter the color: ";
			cin >> col;
            cout <<"\nEnter the formula: ";
            cin >> form;
            //do{
                cout <<"\nEnter the hardness: ";
                cin >> hard;
                while(!stringToDouble(hard, hardness)){
                    cout << "\nPlease enter a valid hardness(0.0-10.0): ";
                    cin >> hard;
                }
            //}while()
            cout << "\nEnter the cleavage: ";
            cin >> cleav;
            cout << endl;
            Mineral * mineral;
            mineral = new Mineral(name, crystSyst, cleav, col, form, hardness);
            insertMineral(mineral);

        }
        void insertMineral(Mineral* min){
            _hashTable.insert(min->getName(), min);
            _primaryTree.insert(min, min->getName());
            _secondaryTree.insert(min, min->getCystalSystem());
        }
        void showHashStats(){_hashTable.showStatistics();}
        bool loadFromFile(string filePath);
        bool search(string target);
        bool secondarySearch(string target) const;
        bool deleteItem(string target);
        bool undoDelete();
        static void display(Mineral *anItem)
        {
            cout << "" << *anItem << endl;
        }

        static void displayHash (HashNode<Mineral*> *aHashNode)
        {
            cout << "" << *(aHashNode->_dataPtr) << endl;
        }

};

bool RockDatabase::loadFromFile(string filePath){
   	string name, formula, color, crys_system, cleavage, hardness;
	string temp;
	double hard;
	char ch = ' ';
	_inFile.open(filePath);
	if (_inFile.fail())
	{
		cout << "No such file!" << endl;
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
		//getline(_inFile, temp, '\n');
		//_inFile.get(ch);

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
//"9.6"
bool RockDatabase::stringToDouble(string str, double & dub){
    size_t pos = str.find('.');
    //cout << str << endl;
    if(pos!=string::npos){
        string wholeNum = str.substr(0, pos);

        string deciNum = str.substr(pos+1);
       // cout << wholeNum << " . " << deciNum << endl;
        if(isStrNum(wholeNum) && isStrNum(deciNum)){
            dub = stod(wholeNum + "." + deciNum);
            //cout << "asdfas";
            return true;
        }

    }
    return false;
}

bool RockDatabase::isStrNum(string str){
    for(int i = 0; i < str.length(); i++)
        if(!isdigit(str[i]))
            return false;
    return true;

}

bool RockDatabase::search(string target){
    Mineral* mineral;
    if(_hashTable.getEntry(target, mineral)){
        //cout << "FOUND!";
        display(mineral);
        return true;
    }
    //cout << "Sorry, '" << target << "' not found." << endl;
    return false;
}

bool RockDatabase::secondarySearch(string target){
    Mineral* mineral;
    if(_secondaryTree.findEntries(display, target)){
        return true;
    }
    return false;
}
/*
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
*/

bool RockDatabase::deleteItem(string target){
    Mineral* mineral;
    if(_hashTable.getEntry(target, mineral)){
        _undoStackData.push(mineral);
        _hashTable.remove(target);
        _primaryTree.remove(target);
        _secondaryTree.remove(mineral);
        return true;
    }
    return false;

}

bool RockDatabase::undoDelete(){
    Mineral* mineral;
    if(_undoStackData.pop(mineral)){
         _hashTable.insert(mineral->getName(), mineral);
         _primaryTree.insert(mineral, mineral->getName());
         _secondaryTree.insert(mineral, mineral->getCystalSystem());
        return true;
    }
    return false;

}

void RockDatabase::toRehash()
{
    Mineral* mineral;
    mineral = new Mineral("ruby", "alsdkf", "asdf", "asdf", "sdaf", 1.2);
    if (_hashTable.getLoadFactor() > 0.5)
    {
        _hashTable.rehashInsert("Hello Jose", mineral);
    }
}

#endif // ROCKDATABASE_H_INCLUiDED
