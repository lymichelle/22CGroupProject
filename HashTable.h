/* HASHTABLE CLASS
Program to implement hash table to store, traverse, and edit template ADT data.
*/

//Header files.
#ifndef HASH_H
#define HASH_H
#include "HashNode.h"
#include "Mineral.h"
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

template<class T>
class Hash
{
    public:
        Hash();
        virtual ~Hash();
        HashNode<T> **htable;
        int tableSize = 49;
        void insert(string key, T data);
        bool remove(string key);
        int Search(string key);
        bool getEntry(string key, T & data);
        void traverseHashTable(void visit(HashNode<T>*));
        void traverseHashTable(ostream& out);
        void showStatistics();
        float getLoadFactor();

    protected:
    private:
        int numOfBlocksInHashFilled = 0;
        int numElements;
        int numOfCollisions = 0;
        int getNumOfLinkedLists();
        float getAvgNumOfNodes();
        int getNumOfBlocksFilled();
        int hashFunc(string key);
        int rehashFunc(string key);
};

//constructor.
template<class T>
Hash<T>::Hash()
{
    htable = new HashNode<T>*[tableSize]; //allocating memory for htable.
    for (int i = 0; i < tableSize; i++)
        {
            htable[i] = NULL; //initialize contents of htable to null.
        }
    numElements = 0; //number of total elements is initialized to 0.
}


//destructor.
template<class T>
Hash<T>::~Hash()
{
    delete [] htable;
}

//hash function.
template<class T>
int Hash<T>::hashFunc(string key)
{
    //first takes the sum of the ASCII values of all the characters in the key
    //and then raises it to the power of the sum of the ASCII values of all the
    //characters of another string.
    int sum = 0;
    for (int i = 0; i < key.length(); i++){
        sum += (int)key[i];
    }
    string power = "Hello Delia!";
    int powerSum = 0;
    for (int i = 0; i < power.length(); i++){
        powerSum += (int)power[i];
    }

    //mod the value with tableSize to get hash index.
    return (sum^(powerSum)) % tableSize;
}

//insert key into hash table.
template<class T>
void Hash<T>::insert (string key, T data)
{
    int hashIndex = hashFunc(key);
    HashNode<T> *entry = htable[hashIndex];
    //if index in htable is empty
    //insert into the table.
    if (entry == NULL)
        {
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = NULL;
            htable[hashIndex] = entry;
            numOfBlocksInHashFilled++; //increment number of blocks filled in the hash table.
            cout << (htable[hashIndex])->getKey() << " inserted" << endl;
        }
    //linked list collision resolution.
    //if index in htable is not empty
    //create a new node and link it to the index.
    else
        {
            HashNode<T> *pPrev = entry;
            while (entry != NULL){
                pPrev = entry;
                entry = entry->next;

                }
            entry = new HashNode<T>(key, data);
           // entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = pPrev;
            pPrev->next = entry;
            numOfCollisions++; //increment numOfCollisions whenever there is a collision.
            cout << key << " inserted" << endl;
    }
    numElements++; //increment number of elements after insertion.
}

//this function removes an entry from hashtable by its key.
template<class T>
bool Hash<T>::remove(string key)
{
    bool flag = false; //set flag to false.
    int hashIndex = hashFunc(key);
    HashNode<T> *entry = new HashNode<T>;
    entry = htable[hashIndex];

    //walk through the hash table
    while (entry != nullptr){
        if (entry->key == key){
            //check if entry is in a linked list.
            if(entry->prev != nullptr){
                HashNode<T> *pCurr;
                pCurr = entry->prev;
                pCurr->next = entry->next;
                numOfCollisions--;
            }
            if(entry->next != nullptr){
                HashNode<T> *pNext;
                pNext = entry->next;
                pNext->prev = entry->prev;
                numOfCollisions--;
            }
            //check if entry is in the hash table
            //with no nodes linked to it.
            if(entry->next == nullptr && entry->prev == nullptr){
                htable[hashIndex] = nullptr;
                entry->_dataPtr = nullptr;
                numOfBlocksInHashFilled--; //decrement if node to be deleted resides in the hashtable.
            }

            //check if entry is last node in linked list.
            if(entry->next != nullptr && entry->prev == nullptr)
            {
                htable[hashIndex] = entry->next;
                entry->_dataPtr = nullptr;
                numOfCollisions--; //decrement number of collisions if part of a linked list.
            }
            numElements--; //decrement number of elements upon deletion

            flag = true; //set flag to true.
            return true;
        }
        entry = entry->next;
    }

    //if key cannot be found return false.
    if (!flag){
        return false;
    }
}

//this function searches for a key in the hashtable.
template<class T>
int Hash<T>::Search(string key)
 {
            bool flag = false; //set flag to false.
            int hashIndex = hashFunc(key);
            HashNode<T>* entry = htable[hashIndex];

            while (entry != NULL){
                if (entry->key == key)
                {
                    cout << entry->key << " found!" << endl;
                    flag = true; //set flag to true once entry is found.
                    cout << flag << endl;
                }
                entry = entry->next; //walk through the linked list.
            }

            //if not found
            //return -1.
            if (!flag){
                cout << key << " not found." << endl;
                return -1;
            }
}

//this function is a private search function for the hashtable.
template<class T>
bool Hash<T>::getEntry(string key, T & data)
 {
            bool flag = false; //set flag to false.
            int hashIndex = hashFunc(key);
            HashNode<T>* entry = htable[hashIndex];
            while (entry != NULL){
                if (entry->key == key)
                {
                   // cout << entry->key << " found!" << endl;
                    flag = true; //set
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

template<class T>
void Hash<T>::traverseHashTable(ostream& out)
{
    HashNode<T>* traverser = new HashNode<T>;

    for (int i = 0; i < tableSize; i++){
        traverser = htable[i];

        //if hash block is not null
        //visit it.
        if (htable[i]!=NULL){
            int j = 0;
            //cout << "Stored @ index: " << i << ", " << j << endl;
            out << *htable[i]->getData() << endl;

            while (traverser->next!=NULL){
                j++;
                traverser = traverser->next;
              //  cout << "Stored @ index: " << i << ", " << j << endl;
                out << *traverser->getData() << endl;
                }
        }
    }
}
template <class T>
void Hash<T>::showStatistics()
{
    std::cout << "Load Factor: " << numOfBlocksInHashFilled << "/" << tableSize<< setprecision(2) << "=" << (float)numOfBlocksInHashFilled/(float)tableSize * 100 << "%" << std::endl;
    std::cout << "Number of collisions: " << numOfCollisions << std::endl;
    std::cout << "Number of linked lists: " << getNumOfLinkedLists() << std::endl;
    std::cout << "Average number of nodes in linked lists: " << (float)numOfCollisions/(float)getNumOfLinkedLists() << std::endl;
   // std::cout << "Average number of nodes: " << getAvgNumOfNodes() << std::endl;
}


template <class T>
float Hash<T>::getLoadFactor()
{
    float loadFactor;
    loadFactor = (float)(numOfBlocksInHashFilled)/(float)(tableSize);
    return loadFactor;
}

//count average number of nodes in the linked lists.

template <class T>
float Hash<T>::getAvgNumOfNodes()
{
    int nodeCount = 0; //Linked list counter.
    HashNode<T>* traverser = new HashNode<T>; //traverses the array.
    //for the length of the array
    for (int i = 0; i < tableSize; i++){
        traverser = htable[i]; //traverse the array
        if (htable[i]!=NULL){ //if a spot in the array is not null
            while (traverser->next!=NULL){ //check entry->next.
                nodeCount++; //if entry->next is not null, increment LL counter.
            }
        }
    }
    float temp = nodeCount;
    float temp2 = getNumOfLinkedLists();
    return (temp/temp2);
}

template <class T>
int Hash<T>::getNumOfBlocksFilled()
{
    return numOfBlocksInHashFilled;
}


//count number of linked lists.
template <class T>
int Hash<T>::getNumOfLinkedLists()
{
    int numOfLL = 0; //Linked list counter.
    HashNode<T>* traverser = new HashNode<T>; //traverses the array.
    //for the length of the array
    for (int i = 0; i < tableSize; i++){
        traverser = htable[i]; //traverse the array
        if (htable[i]!=NULL){ //if a spot in the array is not null
            if (traverser->next!=NULL){ //check entry->next.
                numOfLL++; //if entry->next is not null, increment LL counter.
            }
        }
    }
    return numOfLL;
}

template <class T>
int Hash<T>::rehashFunc(string key){
    cout << "What's your favorite ice cream flavor?" << endl;
    string response;
    cin >> response;

    int sum = 0;
    for (int i = 0; i < key.length(); i++){
        sum += (int)key[i];
    }
    int powerSum = 0;
    for (int i = 0; i < response.length(); i++){
        powerSum += (int)response[i];
    }

    return (sum^powerSum % tableSize);
}

#endif // HASH_H
