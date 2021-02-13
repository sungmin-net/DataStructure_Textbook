#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "850p_statichashing.h"

// 해시 테이블의 생성.
HashTable* createHashTable(int bucketSize) {
    HashTable* pReturn = NULL;

    if (bucketSize <= 0) {
        printf("버킷 크기는 0보다 커야 합니다.\n");
        return NULL;
    }

    pReturn = (HashTable*)malloc(sizeof(HashTable));
    if (pReturn != NULL) {
        pReturn->currentElementCount = 0;
        pReturn->bucketSize = bucketSize;
        pReturn->pElement = NULL;
    } else {
        printf("오류, 첫번째 메모리 할당, createHashTable()\n");
        return NULL;
    }

    pReturn->pElement = (HashElement*)malloc(sizeof(HashTable) * bucketSize);
    if (pReturn->pElement != NULL) {
        memset(pReturn->pElement, 0, sizeof(HashElement) * bucketSize);
    } else {
        if (pReturn != NULL) {
            free(pReturn);
        }
        printf("오류, 두번째 메모리 할당, createHashTable()\n");
        return NULL;
    }
    return pReturn;
}

// 자료의 추가
int addElementStaticHashTable(HashTable* pHashTable, HashElement element) {
    int ret = FALSE;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;
    int inc = 1;

    if (pHashTable == NULL) {
        printf("오류, NULL-해시 테이블입니다.\n");
        ret = FALSE;
        return ret;
    }

    bucketIndex = hashFunction(element.key, pHashTable->bucketSize);
    if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
        printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다.\n");
        ret = FALSE;
        return ret;
    }

    tempIndex = bucketIndex;
    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. 빈 주소 또는 삭제된 주소인지 점검
        if (isEmptyOrDeletedBucket(pElement) == TRUE) {
            pHashTable->pElement[ tempIndex ] = element;
            pHashTable->pElement[ tempIndex ].status = USED;
            pHashTable->currentElementCount++;
            ret = TRUE;
            break;
        } else {
            // 2. 빈 버킷을 찾지 못한 경우.
            // 2-1. 동일한 key 가 이미 존재하는 경우.
            if (strcmp(pElement->key, element.key) == 0) {
                printf("오류, 중복된 키-[%s]\n", element.key);
                ret = FALSE;
                break;
            } else {
                // 2-2. 동일하지 않은 key인 경우, 다음 버킷으로 이동.
                tempIndex = (tempIndex + inc) % pHashTable->bucketSize;
                // 해시 테이블의 모든 버킷이 모두 찬 경우.
                if (tempIndex == bucketIndex) {
                    printf("오류, 해시 테이블이 가득찼습니다.\n");
                    ret = FALSE;
                    break;
                }
            }
        }
    }
    while (tempIndex != bucketIndex);
    return ret;
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

// 문자열을 숫자로 변환.
unsigned int stringToInt(char* pKey) {
    unsigned int ret = 0;
    while (*pKey != NULL) {
        ret = (ret * 31) + (*pKey);
        *pKey++;
    }
    if (ret < 0) {
        ret = ret * (-1);
    }
    return ret;
}

// 빈 주소 혹은 삭제된 주소인지 점검.
int isEmptyOrDeletedBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY || pElement->status == DELETED) {
            ret = TRUE;
        }
    }
    return ret;
}

// 자료의 검색
HashElement* searchHashTable(HashTable* pHashTable, char* pKey) {
    HashElement* pReturn = NULL;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;

    if (pHashTable == NULL) {
        printf("오류, NULL 해시 테이블 입니다.\n");
        pReturn = NULL;
        return pReturn;
    }

    bucketIndex = hashFunction(pKey, pHashTable->bucketSize);
    if (bucketIndex < 0) {
        printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다.\n");
        pReturn = NULL;
    }

    tempIndex = bucketIndex;

    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. 빈 버킷을 찾은 경우. 검색 실패.
        if (isEmptyBucket(pElement) == TRUE) {
            printf("검색 실패. 검색키-[%s]는 존재하지 않습니다.\n", pKey);
            pReturn = NULL;
            break;
        } else {
            // 2-1. 동일한 키를 찾은 경우. 검색 성공
            if (pElement->status == USED && strcmp(pElement->key, pKey) == 0) {
                pReturn = pElement;
                break;
            } else {
                // 2-2. 동일하지 않은 key 인경우, 다음 주소로 이동.
                tempIndex = (tempIndex + 1) % pHashTable->bucketSize;
                // 해시테이블의 모든 버킷을 검사한 경우.
                if (tempIndex == bucketIndex) {
                    printf("검색 실패, 검색키-[%s]는 존재하지 않습니다.\n",
                            pKey);
                    pReturn = NULL;
                    break;
                }
            }
        }
    } while(tempIndex != bucketIndex);

    return pReturn;
}

// 빈 주소인지 점검.
int isEmptyBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY) {
            ret = TRUE;
        }
    }
    return ret;
}

// 자료의 삭제.
int deleteElementHashTable(HashTable* pHashTable, char* pKey) {
    int ret = FALSE;
    HashElement* pElement = NULL;

    if (pHashTable != NULL) {
        pElement = searchHashTable(pHashTable, pKey);
        if (pElement != NULL) {
            pElement->status = DELETED;
            pElement->key[ 0 ] = NULL;
            pElement->value = 0;
            pHashTable->currentElementCount--;
            ret = TRUE;
        } else {
            printf("삭제 실패, 검색키-[%s]는 존재하지 않습니다.\n", pKey);
        }
    }
    return ret;
}

// 해시 테이블의 삭제
void deleteHashTable(HashTable* pHashTable) {
    fflush(stdout);
    if (pHashTable != NULL) {
        fflush(stdout);
        if (pHashTable->pElement != NULL) {
            fflush(stdout);
            free(pHashTable->pElement);
        } else {
            fflush(stdout);
        }
        fflush(stdout);
        free(pHashTable);
    }
    printf("ff\n");
}

// 해시 테이블의 현재 자료의 개수
int getElementCountHashTable(HashTable* pHashTable) {
    int ret = 0;
    if (pHashTable != NULL) {
        ret = pHashTable->currentElementCount;
    }
    return ret;
}

// 해시 테이블의 내용 출력
void displayHashTable(HashTable* pHashTable) {
    int i = 0;
    int bucketIndex = 0;
    HashElement* pElement = NULL;

    if (pHashTable != NULL) {
        for (i = 0 ; i < pHashTable->bucketSize ; i++) {
            printf("[%d], ", i);
            pElement = &(pHashTable->pElement[ i ]);
            if (pElement->key[ 0 ] != NULL) {
                bucketIndex = hashFunction(pElement->key,
                        pHashTable->bucketSize);
                printf("%s, (%d->%d), [%d]\n", pElement->key, bucketIndex, i,
                        pElement->value);
            } else {
                printf("비었습니다.\n");
            }
        }
    } else {
        printf("NULL 해시 테이블입니다.\n");
    }
}
