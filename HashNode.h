#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>

using namespace std;
template<class T>
class HashNode
{
    public:
        //HashNode(string, string, float, string);
        HashNode(){isEmpty = true;}
        HashNode(string key, T ptr);
        virtual ~HashNode();
        string key; //name of rock; primary key

        string crystalSystem; //secondary key
        float hardness;
        string cleavage;
        HashNode *next;
        HashNode *prev;
        bool _isEmpty(){return isEmpty;}
        string getKey() {return key;}
        T getData(){ return _dataPtr; }
        void displayNode();
        T _dataPtr;
        //RockClass RockObject
    protected:
    private:
        bool isEmpty;
        //T _dataPtr;
};

/*
HashNode::HashNode(string key, string crystalSystem, float hardness, string cleavage) //REPLACE WITH ROCK CLASS OBJECT
{/*
    this->key = key;
    this->crystalSystem = crystalSystem;
    this->hardness = hardness;
    this->cleavage = cleavage;}*/
template<class T>
HashNode<T>::HashNode(string key, T ptr) //REPLACE WITH ROCK CLASS OBJECT
{
 //ctor
    isEmpty = false;
    _dataPtr = ptr;
    this->key = key;
}

template<class T>
HashNode<T>::~HashNode()
{
    //dtor
}
template<class T>
void HashNode<T>::displayNode()
{
    cout << *_dataPtr << "x" << endl;
}

#endif // HASHNODE_H
