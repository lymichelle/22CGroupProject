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
        HashNode<T> **htable, **top;
        int tableSize = 25;
        int numOfBlocksInHashFilled = 0;
        int numOfCollisions = 0;

        int hashFunc(string key);
        int rehashFunc(string key, string response);
        void rehashInsert(string key, T data);
        void insert(string key, T data);
        bool remove(string key);
        int Search(string key);
        bool getEntry(string key, T & data);
        void traverseHashTable(void visit(HashNode<T>*));
<<<<<<< HEAD
        void traverseHashTable(ostream& out);
=======
        bool isPrime(int x);
        int resizeTable();
        void getLoadFactor();
        void showStatistics();
>>>>>>> 9dc4d25403051d0c7c887f1871ad69b6a48c8069
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

<<<<<<< HEAD
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
=======
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
    while (isPrime(newTableSize) = 0)
    {
        cout << "not prime" << endl;
        resizeTable();
    }
    tableSize = newTableSize;
}

template <class T>
int Hash<T>::rehashFunc(string key, string response)
{
    cout << "What's your favorite ice cream flavor?" << endl;

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
            cout << key << " inserted" << endl;
    }
}

template <class T>
void Hash<T>::getLoadFactor()
{
    return static_cast<float>(numOfBlocksInHashFilled/tableSize);
}

template <class T>
void Hash<T>::showStatistics()
{
    std::cout << "Load Factor: " << numOfBlocksInHashFilled << "/" << tableSize << std::endl;
    std::cout << "Number of collisions: " << numOfCollisions << std::endl;
}


>>>>>>> 9dc4d25403051d0c7c887f1871ad69b6a48c8069
#endif // HASH_H
