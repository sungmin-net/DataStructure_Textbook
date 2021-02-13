#ifndef _STATIC_HASHING_CHAIN_
#define _STATIC_HASHING_CHAIN_

typedef struct HashTableType {
    int bucketSize;
    int currentElementCount;
    struct LinkedListType** ppElement;
} HashTable;

HashTable* createHashTable(int bucketSize);
int addElementHashTable(HashTable* pHashTable, HashElement element);
int deleteElementHashTable(HashTable* pHashTable, char* pKey);
int hashFunction(char* pKey, int bucketSize);
unsigned int stringToInt(char* pKey);
HashElement* searchHashTable(HashTable* pHashTable, char* pKey);
LinkedList* searchBucket(HashTable* pHashTable, char* pKey);
HashElement* searchSlot(LinkedList* pList, char* pKey, int* pPoisition);
void deleteHashTable(HashTable* pHashTable);
void displayHashTable(HashTable* pHashTable);

#endif

#ifndef _COMMON_HASHING_DEF_
#define _COMMON_HASHING_DEF_

#define TRUE        1
#define FALSE       0

#endif
