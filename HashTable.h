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
        //HashNode<T> **top;
        int tableSize = 5;
        int numOfBlocksInHashFilled = 0;
        int numOfCollisions = 0;
        int hashFunc(string key);
        int rehashFunc(string key);
        void rehashInsert(string key, T data);
        void insert(string key, T data);
        bool remove(string key);
        int Search(string key);
        bool getEntry(string key, T & data);
        void traverseHashTable(void visit(HashNode<T>*));
        void traverseHashTable(ostream& out);
        bool isPrime(int x);
        int resizeTable();
        float getLoadFactor();
        void showStatistics();
        int getNumOfLinkedLists();
        int getAvgNumOfNodes();
    protected:
    private:
};

//constructor.
template<class T>
Hash<T>::Hash()
{
    htable = new HashNode<T>*[tableSize];
    //top = new HashNode<T>*[tableSize];
    for (int i = 0; i < tableSize; i++)
        {
            htable[i] = NULL;
            //top[i] = NULL;
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
    string power = "Hello Delia!";
    int powerSum = 0;
    for (int i = 0; i < power.length(); i++){
        powerSum += (int)power[i];
    }

    return (sum^(powerSum)) % tableSize;
}

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
            //top[hashIndex] = entry;

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
               // top[hashIndex] = nullptr;
                entry->_dataPtr = nullptr;
            }
            if(entry->next != nullptr && entry->prev == nullptr) //it's thetop
            {
                htable[hashIndex] = entry->next;
                entry->_dataPtr = nullptr;
               // HashNode<T> *pCurr;
                //pCurr = entry->next;
                //pCurr->prev = entry->prev;




            }


            flag = true;
            return true;
        }
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
            cout << "Stored @ index: " << i << ", " << j << endl;
            visit(htable[i]);

            while (traverser->next!=NULL){
                j++;
                traverser = traverser->next;
                cout << "Stored @ index: " << i << ", " << j << endl;
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
                //cout << "Stored @ index: " << i << ", " << j << endl;
                out << *traverser->getData() << endl;
                }
        }
    }
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

//count average number of nodes in the linked lists.
//count number of linked lists.
template <class T>
int Hash<T>::getAvgNumOfNodes()
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
    return nodeCount;
}

//check if number is prime.
template <class T>
bool Hash<T>::isPrime(int x)
{
  bool prime;
  int numOfPrimes = 1;
  int *primeNumbers;
  int *temp;
  primeNumbers = new int;
  primeNumbers[0] = 2;

    for (int i = 3; i <= x; i++){
        prime = true;

        for (int j = 0; j < numOfPrimes; j++){
            if (i % primeNumbers[j] == 0){
                prime = false; //if divisible by a compound number or another prime number, it is not prime.
            }
        }
    if (prime){
        temp = new int;
        if (temp != primeNumbers) delete(primeNumbers);
        primeNumbers = temp;
        primeNumbers[numOfPrimes-1] = i;
    }
    }
    return prime;
}


//resizing function.
//This function increases size of table and creates new hashFunc.
template <class T>
int Hash<T>::resizeTable()
{
    int newTableSize = tableSize + 1;
    while (isPrime(newTableSize) == 0)
    {
        cout << "not prime" << endl;
        resizeTable();
    }
    tableSize = newTableSize;
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

template <class T>
void Hash<T>::rehashInsert(string key, T data){

    resizeTable();
 int hashIndex = rehashFunc(key);
    HashNode<T> *entry = htable[hashIndex];
    if (entry == NULL)
        {
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            entry->prev = NULL;
            htable[hashIndex] = entry;
           // top[hashIndex] = entry;

            cout << (htable[hashIndex])->getKey() << " inserted" << endl;
        }
    else
        {
            while (entry != NULL)
                entry = entry->next;
            entry = new HashNode<T>(key, data);
            entry->_dataPtr = data;
            entry->next = NULL;
            //entry->prev = top[hashIndex];
           // top[hashIndex]->next = entry;
           // top[hashIndex] = entry;
            cout << key << " inserted" << endl;
    }
}

template <class T>
float Hash<T>::getLoadFactor()
{
    return static_cast<float>(numOfBlocksInHashFilled/tableSize);
}

template <class T>
void Hash<T>::showStatistics()
{
    std::cout << "Load Factor: " << numOfBlocksInHashFilled << "/" << tableSize << std::endl;
    std::cout << "Number of collisions: " << numOfCollisions << std::endl;
    std::cout << "Number of linked lists: " << getNumOfLinkedLists() << std::endl;
    std::cout << "Average number of nodes: " << getAvgNumOfNodes() << std::endl;
}





#endif // HASH_H
