#ifndef HASH_H
#define HASH_H
#include "HashNode.h"

using namespace std;

class Hash
{
    public:
        Hash();
        virtual ~Hash();
        HashNode **htable, **top;
        int tableSize = 25;

        int hashFunc(int);
        void insert(int key);
        void remove(int key);
        int Search(int key);
        void traverseHashTable(void visit(HashNode*));
    protected:
    private:
};

//constructor.
Hash::Hash()
{
    htable = new HashNode*[tableSize];
    top = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; i++)
        {
            htable[i] = NULL;
            top[i] = NULL;
        }
}


//destructor.
Hash::~Hash()
{
    delete [] htable;
}

/*
int Hash::hashFunc(string key)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++){
        sum += (int)key[i];
    }
    return sum % tableSize;
}*/

//assigns index to key.
int Hash::hashFunc(int key)
{
    return key % tableSize;
}

//insert key into hash table.
void Hash::insert (int key)
{
    int hashIndex = hashFunc(key);
    HashNode *entry = htable[hashIndex];
    if (entry == NULL)
        {
            entry = new HashNode(key);
            entry->key = key;
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
            entry = new HashNode(key);
            entry->key = key;
            entry->next = NULL;
            entry->prev = top[hashIndex];
            top[hashIndex]->next = entry;
            top[hashIndex] = entry;
    }
}

//remove key from hashtable.
void Hash::remove(int key)
{
    bool flag = false;
    int hashIndex = hashFunc(key);
    HashNode *entry = new HashNode;
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
int Hash::Search(int key)
 {
            bool flag = false;
            int hashIndex = hashFunc(key);
            HashNode* entry = htable[hashIndex];
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
void Hash::traverseHashTable(void visit(HashNode*))
{
    HashNode* traverser = new HashNode;

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
