#ifndef HASH_H
#define HASH_H
#include "HashNode.h"
#include "Mineral.h"
#include <string>

using namespace std;
template<class T>
class Hash
{
    public:
        Hash();
        virtual ~Hash();
        HashNode<T> **htable, **top;
        int tableSize = 25;

        int hashFunc(string key);
        void insert(string key, T data);
        void remove(string key);
        int Search(string key);
        void traverseHashTable(void visit(HashNode<T>*));
    protected:
    private:
};

//constructor.
template<class T>
Hash<T>::Hash()
{
    htable = new HashNode<T>*[tableSize];
    top = new HashNode<T>*[tableSize];
    for (int i = 0; i < tableSize; i++)
        {
            htable[i] = NULL;
            top[i] = NULL;
        }
}


//destructor.
template<class T>
Hash<T>::~Hash()
{
    delete [] htable;
}

template<class T>
int Hash<T>::hashFunc(string key)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++){
        sum += (int)key[i];
    }
    cout << sum % tableSize << endl;
    return sum % tableSize;
}

/*
//assigns index to key.
template<class T>
int Hash<T>::hashFunc(string key)
{

    int n;
    for(int i = 0; key.length(); i++){
        n += key.at(i);
    }

    return stoi(key) % tableSize;
}
*/

//insert key into hash table.
template<class T>
void Hash<T>::insert (string key, T data)
{
    int hashIndex = hashFunc(key);
    HashNode<T> *entry = htable[hashIndex];
    if (entry == NULL)
        {
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = NULL;
            htable[hashIndex] = entry;
            top[hashIndex] = entry;

            cout << (htable[hashIndex])->getKey() << " inserted" << endl;
        }
    else
        {
            while (entry != NULL)
                entry = entry->next;
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = top[hashIndex];
            top[hashIndex]->next = entry;
            top[hashIndex] = entry;
    }
}

//remove key from hashtable.
template<class T>
void Hash<T>::remove(string key)
{
    bool flag = false;
    int hashIndex = hashFunc(key);
    HashNode<T> *entry = new HashNode<T>;
    entry = htable[hashIndex];
    while (entry != NULL){

        if (entry->key == key){
            flag = true;
            delete entry;
        }

        else if (entry->key != key)
            entry = entry->next;
    }

    if (!flag){
        cout << key << " does not exist in the table. Nothing has been deleted." << endl;
    }
}

//searches for a key in the hashtable.
template<class T>
int Hash<T>::Search(string key)
 {
            bool flag = false;
            int hashIndex = hashFunc(key);
            HashNode<T>* entry = htable[hashIndex];
            while (entry != NULL){
                if (entry->key == key)
                {
                    cout << entry->key << " found!" << endl;
                    flag = true;
                    cout << flag << endl;
                }
                entry = entry->next;
            }
            if (!flag){
                cout << key << " not found." << endl;
                return -1;
            }
}

//traverses hashtable.
template<class T>
void Hash<T>::traverseHashTable(void visit(HashNode<T>*))
{
    HashNode<T>* traverser = new HashNode<T>;

    for (int i = 0; i < tableSize; i++){
        traverser = htable[i];

        //if hash block is not null
        //visit it.
        if (htable[i]!=NULL){
            visit(htable[i]);
            while (traverser->next!=NULL){
                traverser = traverser->next;
                visit(traverser);
                }
        }
    }
}

#endif // HASH_H
