#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>

using namespace std;

class HashNode
{
    public:
        //HashNode(string, string, float, string);
        HashNode(){isEmpty = true;}
        HashNode(int key);
        virtual ~HashNode();
        int key; //name of rock; primary key
        string crystalSystem; //secondary key
        float hardness;
        string cleavage;
        HashNode *next;
        HashNode *prev;
        bool _isEmpty(){return isEmpty;}
        int getKey() {return key;}
        void displayNode();

        //RockClass RockObject
    protected:
    private:
        bool isEmpty;
};

/*
HashNode::HashNode(string key, string crystalSystem, float hardness, string cleavage) //REPLACE WITH ROCK CLASS OBJECT
{/*
    this->key = key;
    this->crystalSystem = crystalSystem;
    this->hardness = hardness;
    this->cleavage = cleavage;}*/

HashNode::HashNode(int key) //REPLACE WITH ROCK CLASS OBJECT
{
 //ctor
    isEmpty = false;
    this->key = key;
}


HashNode::~HashNode()
{
    //dtor
}

void HashNode::displayNode()
{
    cout << key << endl;
}

#endif // HASHNODE_H
