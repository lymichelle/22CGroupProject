// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Jose Sepulveda

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { destroyTree(rootPtr); }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType )) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType )) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType )) const{_postorder(visit, rootPtr);}
	void preOrder(ostream& out){ _preorder(out, rootPtr); }
	void inOrder(ostream& out){ _inorder(out, rootPtr); }
	void postOrder(ostream& out){ _postorder(out, rootPtr);}


	// functions added by Jose Sepulveda
	void indented() const{_indented(rootPtr);}
	int getLevel(BinaryNode<ItemType>* nodePtr, string data) const{return _getLevel(rootPtr, data, 1);}
	bool deleteLeaves();
	void breadth(void visit(ItemType )) const{_breadth(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	//virtual bool insert(const ItemType & newData) = 0;
	//virtual bool remove(const ItemType & data) = 0;
	//virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;

	void _preorder(ostream& out, BinaryNode<ItemType>* nodePtr);
	void _inorder(ostream& out, BinaryNode<ItemType>* nodePtr);
	void _postorder(ostream& out, BinaryNode<ItemType>* nodePtr);

	// internal functions added by Jose Sepulveda
	void _indented(BinaryNode<ItemType>* nodePtr) const;
	int _getLevel(BinaryNode<ItemType>* nodePtr, string data, int level) const;
	BinaryNode<ItemType>* _deleteLeaves(BinaryNode<ItemType>* nodePtr);
	void _breadth(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////
template<class ItemType>
bool BinaryTree<ItemType>::deleteLeaves(){
	if(rootPtr->getRightPtr() != nullptr && rootPtr->getLeftPtr() != nullptr)
		if(_deleteLeaves(rootPtr))
			return true;
		else
			return false;
}

//Added by Jose Sepulveda
//This iterative function utilizes a queue to print the breadth first traversal of the tree
template<class ItemType>
void BinaryTree<ItemType>::_breadth(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr == nullptr)
		return;
	Queue<BinaryNode<ItemType>*> q;
	q.enqueue(nodePtr);
	while(!q.isEmpty()){
		BinaryNode<ItemType>* node;
		q.dequeue(node);
		ItemType item = node->getItem();
		//cout << "\t" << node->getItem() << endl;
		visit(item);
		if(node->getLeftPtr() != nullptr)
			q.enqueue(node->getLeftPtr());
		if(node->getRightPtr() != nullptr)
			q.enqueue(node->getRightPtr());
	}



}

//Added by Jose Sepulveda
//This recursive function deletes all the leaves of the tree

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_deleteLeaves(BinaryNode<ItemType>* nodePtr){
	if(nodePtr != nullptr && count > 0){
		if(nodePtr->getLeftPtr() == nullptr && nodePtr->getRightPtr() == nullptr){
			delete nodePtr;
			count--;
			return nullptr;
		}else{
			nodePtr->setLeftPtr(_deleteLeaves(nodePtr->getLeftPtr()));
			nodePtr->setRightPtr(_deleteLeaves(nodePtr->getRightPtr()));
		}
	}
	return nodePtr;

}

//Added by Jose Sepulveda
//_getLevel function is an internal function that counts down to the number of levels of the data given
template<class ItemType>
int BinaryTree<ItemType>::_getLevel(BinaryNode<ItemType>* nodePtr, string data, int level) const{
	if(nodePtr == nullptr)
		return 0;
	if(nodePtr->getKey() == data)
		return level;
	int i = _getLevel(nodePtr->getLeftPtr(), data, level+1);
	if(i != 0)
		return i;
	i = _getLevel(nodePtr->getRightPtr(), data, level+1);
	return i;
}



template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;


    return newNodePtr;
}

//Added by Jose Sepulveda
//This function is a post-order traversed delete, it calls itself until everything is deleted.
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if(nodePtr){
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
	return;
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(ostream& out, BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		out << *item << "\n";
		_preorder(out, nodePtr->getLeftPtr());
		_preorder(out, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
		if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(ostream& out, BinaryNode<ItemType>* nodePtr){
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(out, nodePtr->getLeftPtr());
		out << *item << "\n";
		_inorder(out, nodePtr->getRightPtr());
	}
}

//Added by Jose Sepulveda
//This functions is a reverse inorder traversal that uses the getLevel function in order to find
//the number of tabs to place so it results in an indented tree list.
template<class ItemType>
void BinaryTree<ItemType>::_indented(BinaryNode<ItemType>* nodePtr) const
{
		if (nodePtr)
	{
		string item = nodePtr->getKey();
		_indented(nodePtr->getRightPtr());
		int i = getLevel(rootPtr, item);
		cout << string(i, '\t') << "(" << i << ")" << item << endl << endl;
		_indented(nodePtr->getLeftPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
		if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(ostream& out, BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(out, nodePtr->getLeftPtr());
		_postorder(out, nodePtr->getRightPtr());
		out << *item << "\n";
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}


#endif

