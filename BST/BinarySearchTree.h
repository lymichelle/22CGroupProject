// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Jose Sepulveda

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"


template<class ItemType>
class BinarySearchTree : virtual public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const string target, bool & success);
	BinaryNode<ItemType>* _removeByData(BinaryNode<ItemType>* nodePtr,
		ItemType target,
		bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor, string & key);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const string target) const;

public:
	// insert a node at the correct location
    bool insert(const ItemType & newEntry, string key);
	// remove a node if found
	bool remove(const string target);
    bool remove(const ItemType target);
	// find a target node
	bool getEntry(const string target, ItemType & returnedItem) const;

};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry, string key)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry , key);
	BinaryTree<ItemType>::rootPtr = _insert(BinaryTree<ItemType>::rootPtr, newNodePtr);
	BinaryTree<ItemType>::count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const string target)
{
	bool isSuccessful = false;
	BinaryTree<ItemType>::rootPtr = _remove(BinaryTree<ItemType>::rootPtr, target, isSuccessful);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove( ItemType target)
{
	bool isSuccessful = false;
	BinaryTree<ItemType>::rootPtr = _removeByData(BinaryTree<ItemType>::rootPtr, target, isSuccessful);
	return isSuccessful;
}

//Modified by Jose Sepulveda
//This member function calls the recursive findNode function. If an item is found it saves
//its contents into the returnedItem variable and returns true, otherwise it returns false.

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const string anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* node = findNode(BinaryTree<ItemType>::rootPtr, anEntry);
	if(node != nullptr){
		returnedItem = node->getItem();
		return true;
	}
	return false;

}



//////////////////////////// private functions ////////////////////////////////////////////


//Modified by Jose Sepulveda
//This recursive function calls itself until the correct place to store the data is found.
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{

	if(nodePtr == nullptr){
		return newNodePtr;
	}else{
		if(newNodePtr->getKey() < nodePtr->getKey()){
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr() , newNodePtr));
		}else{
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const string target,
                                                          bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getKey() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getKey() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeByData(BinaryNode<ItemType>* nodePtr,
                                                          ItemType target,
                                                          bool & success)

{



	if (nodePtr == 0)
	{
		success = false;
		return nullptr;
	}
	nodePtr->setLeftPtr(_removeByData(nodePtr->getLeftPtr(), target, success));
	nodePtr->setRightPtr(_removeByData(nodePtr->getRightPtr(), target, success));
	if (target == nodePtr->getItem())
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		string newNodeKey;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue, newNodeKey));
		nodePtr->setItem(newNodeValue);
		nodePtr->setKey(newNodeKey);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor,
                                                                     string & key)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		key = nodePtr->getKey();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor, key));
		return nodePtr;
	}
}


//Modified by Jose Sepulveda
//This member function calls itself until it either finds the data or doesn't

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const string target) const
{
	if(nodePtr == nullptr)
		return nullptr;
	else if (nodePtr->getKey() == target)
		return nodePtr;
	else{
		BinaryNode<ItemType>* left = findNode(nodePtr->getLeftPtr(), target);
		return left ? left : findNode(nodePtr->getRightPtr(), target);
	}
}


#endif
