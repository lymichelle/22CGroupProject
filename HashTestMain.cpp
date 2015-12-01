#include <iostream>
#include "HashTable.h"


//note: printHashTable is actually just a traversal of the hash table.

void displayHash (HashNode<int> *aHashNode)
{
    cout << aHashNode->key << endl;
}

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    Hash<int> hashy;

    cout << hashy.hashFunc("43") << endl;
    cout << hashy.hashFunc("60343") << endl;

    hashy.insert("43", 43);
    hashy.insert("60343", 60343);
    hashy.insert("7", 7);
    hashy.Search("6");
    hashy.Search("7");
    hashy.Search("5");
    hashy.Search("43");
    hashy.Search("60343");

    cout << "Printing hash table..." << endl;
    hashy.traverseHashTable(display);

    hashy.remove("7");

    cout << "printing hash table after deletion..." << endl;
    hashy.traverseHashTable(display);

    return 0;
}
