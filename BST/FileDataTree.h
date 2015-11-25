#ifndef FILEDATATREE_H
#define FILEDATATREE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>



template<class T>
class FileDataTree
{
private:
		ifstream inFile;
		 BinarySearchTree<T> tree;
	public:
		FileDataTree(){};
		FileDataTree(string filename);
		void display(T & anItem)
		{
			 cout << "\t" << anItem << endl;
		}  
		void print(){tree.indented();}
		void breadth(){cout << "\nBreadth First Traversal:\n"; tree.breadth();}
		void inOrder(){cout << "\nIn-Order Traversal:\n"; tree.inOrder(display);}
		void preOrder(){cout << "\nPre-Order Traversal:\n"; tree.preOrder(display);}
		void postOrder(){cout << "\nPost-Order Traversal:\n"; tree.postOrder(display);}
		void deleteLeaves(){cout << "\nDeleting all leaves..."; 
			(tree.deleteLeaves()) ? (cout << "success!\n") : (cout << "failed, only root remains.\n");}

		bool search(int num){
			T target(num, "null");
			Employee result;
			if(empTree.getEntry(target, result)){
				cout << "\nFound!: " << result << "\n";
				return true;
			}
			cout << "\nNot found.\n";
			return false;
			
		}



};
#endif
