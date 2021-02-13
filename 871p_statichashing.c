#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "867p_hashingdef.h"
#include "868p_hashinglinkedlist.h"
#include "869p_statichashing.h"

int addElementLastLinkedList(LinkedList* pList, HashElement element) {
    int ret = FALSE;
    ListNode node = {0,};
    int position = 0;
    if (pList != NULL) {
        position = getLengthLinkedList(pList);
        node.data = element;
        ret = addElementLinkedList(pList, position, node);
    }
    return ret;
}

// 해시 테이블의 생성
HashTable* createHashTable(int bucketSize) {
    HashTable* pReturn = NULL;
    int i = 0;
    int j = 0;

    if (bucketSize <= 0) {
        printf("버킷 크기는 0보다 커야 합니다.\n");
        return NULL;
    }

    pReturn = (HashTable*)malloc(sizeof(HashTable));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(HashTable));
        pReturn->bucketSize = bucketSize;
    } else {
        printf("오류, 첫 번째 메모리 할당, createHashTable()\n");
        return NULL;
    }

    pReturn->ppElement = (LinkedList**)malloc(sizeof(LinkedList*) * bucketSize);
    if (pReturn->ppElement != NULL) {
        memset(pReturn->ppElement, 0, sizeof(LinkedList*) * bucketSize);
        for (i = 0 ; i < bucketSize ; i++) {
            pReturn->ppElement[ i ] = createLinkedList();
            if (pReturn->ppElement[ i ] == NULL) {
                for (j = 0 ; j < i - 1 ; j++) {
                    if (pReturn->ppElement[ j ] != NULL) {
                        free(pReturn->ppElement[ j ]);
                    }
                }
                if (pReturn->ppElement != NULL) {
                    free(pReturn->ppElement);
                }
                if (pReturn != NULL) {
                    free(pReturn);
                }
                break;
            }
        }
    } else {
        if (pReturn != NULL) {
            free(pReturn);
        }
        printf("Error, second malloc(), createHashTable()\n");
        return NULL;
    }
    return pReturn;
}

// 자료의 추가
int addElementHashTable(HashTable* pHashTable, HashElement element) {
    int ret = FALSE;
    LinkedList* pList = NULL;
    if (pHashTable != NULL) {
        pList = searchBucket(pHashTable, element.aKey);
        if (pList != NULL) {
            addElementLastLinkedList(pList, element);
            pHashTable->currentElementCount++;
            ret = TRUE;
        } else {
            printf("잘못된 해시테이블 주소가 계산되었습니다. addElementHashTable()\n");
        }
    }
    return ret;
}

LinkedList* searchBucket(HashTable* pHashTable, char* pKey) {
    LinkedList* pReturn = NULL;
    int bucketIndex = 0;
    if (pHashTable != NULL) {
        bucketIndex = hashFunction(pKey, pHashTable->bucketSize);
        if (bucketIndex >= 0) {
            pReturn = pHashTable->ppElement[ bucketIndex ];
        } else {
            printf("오류, 잘못된 해시테이블 주소가 계산되었습니다. searchBucket()\n");
        }
    } else {
        printf("오류, null 테이블입니다. searchBucket()\n");
    }
    return pReturn;
}

int hashFunction(char* pKey, int bucketSize) {
    int ret = -1;
    unsigned int temp_key = 0;
    if (pKey == NULL) {
        return ret;
    }

    temp_key = stringToInt(pKey);
    if (bucketSize > 0) {
        ret = temp_key % bucketSize;
    }
    return ret;
}

unsigned int stringToInt(char* pKey) {
    unsigned int ret = 0;
    while (*pKey != '\0') {
        ret = (ret * 31) + (*pKey);
        *pKey++;
    }
    if (ret < 0) {
        ret = ret * (-1);
    }
    return ret;
}

HashElement* searchHashTable(HashTable* pHashTable, char* pKey) {
    HashElement * pReturn = NULL;
    LinkedList* pList = NULL;
    int position = 0;

    pList = searchBucket(pHashTable, pKey);
    if (pList != NULL) {
        pReturn = searchSlot(pList, pKey, &position);
    }
    return pReturn;
}

HashElement* searchSlot(LinkedList* pList, char* pKey, int* pPosition) {
    HashElement* pReturn = NULL;
    HashElement* pElement = NULL;
    ListNode* pNode = NULL;
    int position = 0;

    if (pList != NULL &&& pPosition != NULL) {
        pNode = getElementLinkedList(pList, 0);
        while(pNode != NULL) {
            if (strcmp(pNode->data.aKey, pKey) == 0) {
                pReturn = &(pNode->data);
                *pPosition = position;
                break;
            }
            pNode = pNode->pLink;
            position++;
        }
        if (pReturn == NULL) {
            printf("검색 실패, 검색키-[%s]는 존재하지 않습니다. searchSlot()\n",
                    pKey);
        }
    }
    return pReturn;
}

int deleteElementHashTable(HashTable* pHashTable, char* pKey) {
    int ret = FALSE;

    HashElement* pElement = NULL;
    LinkedList* pList = NULL;
    int position = 0;

    pList = searchBucket(pHashTable, pKey);
    if (pList != NULL) {
        pElement = searchSlot(pList, pKey, &position);
        if (pElement != NULL) {
            removeElementLinkedList(pList, position);
            pHashTable->currentElementCount--;
            ret = TRUE;
        }
    }
    return ret;
}

void deleteHashTable(HashTable* pHashTable) {
    int i = 0;
    if (pHashTable != NULL) {
        for (i = 0 ; i < pHashTable->bucketSize ; i++) {
            deleteLinkedList(pHashTable->ppElement[ i ]);
        }
        if (pHashTable->ppElement != NULL) {
            free(pHashTable->ppElement);
        }
        free(pHashTable);
    }
}

void displayHashTable(HashTable* pHashTable) {
    int i = 0;
    int j = 0;
    int slotSize = 0;
    LinkedList* pList = NULL;
    ListNode* pNode = NULL;
    HashElement* pElement = NULL;

    if (pHashTable != NULL) {
        for (i = 0 ; i < pHashTable->bucketSize ; i++) {
            printf("[%d]", i);
            pList = pHashTable->ppElement[ i ];
            slotSize = getLengthLinkedList(pList);
            if (slotSize == 0) {
                printf(", Empty\n");
            } else {
                for (j = 0 ; j < slotSize ; j++) {
                    pNode = getElementLinkedList(pList, j);
                    if (pNode != NULL) {
                        pElement = &(pNode->data);
                        printf(", (%s, %d) ", pElement->aKey, pElement->value);
                    }
                }
                printf("\n");
            }
        }
    }
}
