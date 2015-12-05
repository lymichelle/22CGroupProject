/*
--- HASHNODE CLASS ---
Header to store data for each node  of the hashtable.
*/

#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>

using namespace std;
template<class T>
class HashNode
{
    public:
        HashNode(){isEmpty = true;}
        HashNode(string key, T ptr);
        virtual ~HashNode();
        string key; //name of rock; primary key
        string crystalSystem; //secondary key
        float hardness;
        string cleavage;
        HashNode *next;
        HashNode *prev;

        string getKey() {return key;} //returns key.
        T getData(){ return _dataPtr; } //returns data.
        void displayNode(); //displays node contents.
        T _dataPtr;
    protected:
    private:
        bool isEmpty;

        bool _isEmpty(){return isEmpty;} //returns true if node is empty.
};

//constructor.
template<class T>
HashNode<T>::HashNode(string key, T ptr) //REPLACE WITH ROCK CLASS OBJECT
{
    isEmpty = false; //initialize isEmpty to false.
    _dataPtr = ptr; //assign data to node.
    this->key = key; //assign key to node.
}

//destructor.
template<class T>
HashNode<T>::~HashNode()
{
    //dtor
}

//function to display node.
template<class T>
void HashNode<T>::displayNode()
{
    cout << *_dataPtr << "x" << endl;
}

#endif // HASHNODE_H
