#ifndef _STATIC_HASHING_CHAIN_
#define _STATIC_HASHING_CHAIN_

#define HASH_KEY_SIZE 30

typedef enum HashElementStatusType {
    EMPTY = 0,
    USED,
    DELETED
} HashElementStatus;

typedef struct HashElementType {
    char key[ HASH_KEY_SIZE + 1 ];
    int value;
    HashElementStatus status;
} HashElement;

typedef struct HashTableType {
    int bucketSize;
    int currentElementCount;
    HashElement* pElement;
} HashTable;

HashTable* createHashTable(int bucketSize);
int addElementStaticHashTable(HashTable* pHashTable, HashElement element);
int deleteElementHashTable(HashTable* pHashTable, char* key);
int hashFunction(char* pKey, int bucketSize);
unsigned int stringToInt(char* pKey);
int isEmptyBucket(HashElement* pElement);
int isEmptyOrDeletedBucket(HashElement* pElement);

// 자료의 검색.
HashElement* searchHashTable(HashTable* pHashTable, char* key);

// 해시 테이블 내용의 표시
void displayHashTable(HashTable* pHashTable);

// 해시 테이블의 현재 자료의 개수
int getElementCountHashTable(HashTable* pHashTable);

// 해시 테이블의 삭제
void deleteHashTable(HashTable* pHashTable);

#endif

#ifndef _COMMON_HASHING_DEF_
#define _COMMON_HASHING_DEF_

#define TRUE        1
#define FALSE       0

#endif
