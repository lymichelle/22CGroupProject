// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Jose Sepulveda

//		Description: This program creates a modifyable BST with data from the employees.txt file
//				Windows 7 64-bit Visual Studio

#include "BinarySearchTree.h"  // BST ADT 
#include "Employee.h" //Employee Class

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

// display function to pass to BST traverse functions
void display(Employee & anItem)
{
   cout << "\t" << anItem << endl;
}  

//Added by Jose Sepulveda
//Class to make interacting with the BST simpler
class EmployeeTree{
	private:
		ifstream inFile;
		 BinarySearchTree<Employee> empTree;
	public:
		EmployeeTree(){};
		EmployeeTree(string filename);
		void print(){empTree.indented();}
		void breadth(){cout << "\nBreadth First Traversal:\n"; empTree.breadth(display);}
		void inOrder(){cout << "\nIn-Order Traversal:\n"; empTree.inOrder(display);}
		void preOrder(){cout << "\nPre-Order Traversal:\n"; empTree.preOrder(display);}
		void postOrder(){cout << "\nPost-Order Traversal:\n"; empTree.postOrder(display);}
		void deleteLeaves(){cout << "\nDeleting all leaves..."; 
			(empTree.deleteLeaves()) ? (cout << "success!\n") : (cout << "failed, only root remains.\n");}
		bool search(int num);
};



void check(bool success)
{
   if (success)
      cout << "Done." << endl;
   else
      cout << " Entry not in tree." << endl;
}  

//Added by Jose Sepulveda
//This function prints the menu
void printMenu(){
	cout << "\tS - Search by a unique key\n"
		 << "\tD - Recursive Depth-First Traversals\n"
		 << "\tB - Breadth-First Traversal\n"
		 << "\tT - Print tree as indented list\n"
		 << "\tG - Delete all leaves\n"
		 << "\tM - Show menu\n"
		 << "\tQ - Quit\n";


}

//Added by Jose Sepulveda
//This function is the main controller for the program
void bstController(EmployeeTree &tree){
	string commandList = "SDBTGAMQ";
    string command;
	printMenu();
    char choice;
    do{

        cout << "\nEnter a command: ";

        getline(cin, command);
        command[0] = toupper(command[0]);
        choice = command[0];
        if((commandList.find(choice) != string::npos)){
           if(choice == 'S'){
				int i;
			   cout << "Enter a key to search for: ";
			   cin >> i;
			   cin.ignore();
			   tree.search(i);
		   }
		   if(choice == 'D'){
			   tree.inOrder();
			   tree.preOrder();
			   tree.postOrder();		   
		   }
		   if(choice == 'B'){
			   tree.breadth();
		   }
		   if(choice == 'T'){
			   tree.print();
		   }
		   if(choice == 'G'){
			   tree.deleteLeaves();
		   }
		   if(choice == 'A'){
				cout << "\nProgrammed by Jose Sepulveda\n";
		   }
		   if(choice == 'M'){
			   printMenu();
		   }
		   
		}



    }while(choice != 'Q');
   
}

int main()
{
	EmployeeTree tree("employees.txt");
	bstController(tree);


   return 0;
}  

//Added by Jose Sepulveda
//This search simplifies it by printing the item if found.
bool EmployeeTree::search(int num){
			Employee target(num, "null");
			Employee result;
			if(empTree.getEntry(target, result)){
				cout << "\nFound!: " << result << "\n";
				return true;
			}
			cout << "\nNot found.\n";
			return false;
			
		}

//Added by Jose Sepulveda
//This constructor initiliazes the BST with the data from the file witht he fileName path
EmployeeTree::EmployeeTree(string filename){
	inFile.open(filename, fstream::in);
	string line;
	if(inFile){
		while(getline(inFile, line)){
			istringstream iss(line);
			vector<string> tokens;
			string temp;
			while(iss >> temp)
				tokens.push_back(temp);
			
			Employee emp(stoi(tokens[0]), tokens[1] + " " + tokens[2]);
			empTree.insert(emp);
		}
	}
	inFile.close();

}
