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
        bool remove(string key);
        int Search(string key);
        bool getEntry(string key, T & data);
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
			HashNode<T> *pPrev;
			while (entry != NULL){
				pPrev = entry;
				entry = entry->next;
			}
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = pPrev;
            pPrev->next = entry;
            //top[hashIndex] = entry;
            cout << key << " inserted" << endl;
    }
}

//remove key from hashtable.
template<class T>
bool Hash<T>::remove(string key)
{
    bool flag = false;
    int hashIndex = hashFunc(key);
    HashNode<T> *entry = new HashNode<T>;
    entry = htable[hashIndex];
    while (entry != nullptr){

        if (entry->key == key){
            if(entry->prev != nullptr){
                HashNode<T> *pCurr;
                pCurr = entry->prev;
                pCurr->next = entry->next;
            }
            if(entry->next != nullptr){
                HashNode<T> *pNext;
                pNext = entry->next;
                pNext->prev = entry->prev;
            }
            if(entry->next == nullptr && entry->prev == nullptr){
                htable[hashIndex] = nullptr;
                top[hashIndex] = nullptr;
            }

            flag = true;
            return true;
        }else if (entry->key != key)
            entry = entry->next;
    }

    if (!flag){
        //cout << key << " does not exist in the table. Nothing has been deleted." << endl;
        return false;
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

template<class T>
bool Hash<T>::getEntry(string key, T & data)
 {
            bool flag = false;
            int hashIndex = hashFunc(key);
            HashNode<T>* entry = htable[hashIndex];
            while (entry != NULL){
                if (entry->key == key)
                {
                   // cout << entry->key << " found!" << endl;
                    flag = true;
                    data = entry->getData();
                    //cout << flag << endl;
                    return true;
                }
                entry = entry->next;
            }
            if (!flag){
               // cout << key << " not found." << endl;
                return false;
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
            int j = 0;
            //cout << "Stored @ index: " << i << ", " << j << endl;
            visit(htable[i]);

            while (traverser->next!=NULL){
                j++;
                traverser = traverser->next;
                //cout << "Stored @ index: " << i << ", " << j << endl;
                visit(traverser);
                }
        }
    }
}

#endif // HASH_H
