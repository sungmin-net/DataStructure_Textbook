#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "850p_statichashing.h"

// �ؽ� ���̺��� ����.
HashTable* createHashTable(int bucketSize) {
    HashTable* pReturn = NULL;

    if (bucketSize <= 0) {
        printf("��Ŷ ũ��� 0���� Ŀ�� �մϴ�.\n");
        return NULL;
    }

    pReturn = (HashTable*)malloc(sizeof(HashTable));
    if (pReturn != NULL) {
        pReturn->currentElementCount = 0;
        pReturn->bucketSize = bucketSize;
        pReturn->pElement = NULL;
    } else {
        printf("����, ù��° �޸� �Ҵ�, createHashTable()\n");
        return NULL;
    }

    pReturn->pElement = (HashElement*)malloc(sizeof(HashTable) * bucketSize);
    if (pReturn->pElement != NULL) {
        memset(pReturn->pElement, 0, sizeof(HashElement) * bucketSize);
    } else {
        if (pReturn != NULL) {
            free(pReturn);
        }
        printf("����, �ι�° �޸� �Ҵ�, createHashTable()\n");
        return NULL;
    }
    return pReturn;
}

// �ڷ��� �߰�
int addElementStaticHashTable(HashTable* pHashTable, HashElement element) {
    int ret = FALSE;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;
    int inc = 1;

    if (pHashTable == NULL) {
        printf("����, NULL-�ؽ� ���̺��Դϴ�.\n");
        ret = FALSE;
        return ret;
    }

    bucketIndex = hashFunction(element.key, pHashTable->bucketSize);
    if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
        printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�.\n");
        ret = FALSE;
        return ret;
    }

    tempIndex = bucketIndex;
    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. �� �ּ� �Ǵ� ������ �ּ����� ����
        if (isEmptyOrDeletedBucket(pElement) == TRUE) {
            pHashTable->pElement[ tempIndex ] = element;
            pHashTable->pElement[ tempIndex ].status = USED;
            pHashTable->currentElementCount++;
            ret = TRUE;
            break;
        } else {
            // 2. �� ��Ŷ�� ã�� ���� ���.
            // 2-1. ������ key �� �̹� �����ϴ� ���.
            if (strcmp(pElement->key, element.key) == 0) {
                printf("����, �ߺ��� Ű-[%s]\n", element.key);
                ret = FALSE;
                break;
            } else {
                // 2-2. �������� ���� key�� ���, ���� ��Ŷ���� �̵�.
                tempIndex = (tempIndex + inc) % pHashTable->bucketSize;
                // �ؽ� ���̺��� ��� ��Ŷ�� ��� �� ���.
                if (tempIndex == bucketIndex) {
                    printf("����, �ؽ� ���̺��� ����á���ϴ�.\n");
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

// ���ڿ��� ���ڷ� ��ȯ.
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

// �� �ּ� Ȥ�� ������ �ּ����� ����.
int isEmptyOrDeletedBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY || pElement->status == DELETED) {
            ret = TRUE;
        }
    }
    return ret;
}

// �ڷ��� �˻�
HashElement* searchHashTable(HashTable* pHashTable, char* pKey) {
    HashElement* pReturn = NULL;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;

    if (pHashTable == NULL) {
        printf("����, NULL �ؽ� ���̺� �Դϴ�.\n");
        pReturn = NULL;
        return pReturn;
    }

    bucketIndex = hashFunction(pKey, pHashTable->bucketSize);
    if (bucketIndex < 0) {
        printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�.\n");
        pReturn = NULL;
    }

    tempIndex = bucketIndex;

    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. �� ��Ŷ�� ã�� ���. �˻� ����.
        if (isEmptyBucket(pElement) == TRUE) {
            printf("�˻� ����. �˻�Ű-[%s]�� �������� �ʽ��ϴ�.\n", pKey);
            pReturn = NULL;
            break;
        } else {
            // 2-1. ������ Ű�� ã�� ���. �˻� ����
            if (pElement->status == USED && strcmp(pElement->key, pKey) == 0) {
                pReturn = pElement;
                break;
            } else {
                // 2-2. �������� ���� key �ΰ��, ���� �ּҷ� �̵�.
                tempIndex = (tempIndex + 1) % pHashTable->bucketSize;
                // �ؽ����̺��� ��� ��Ŷ�� �˻��� ���.
                if (tempIndex == bucketIndex) {
                    printf("�˻� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�.\n",
                            pKey);
                    pReturn = NULL;
                    break;
                }
            }
        }
    } while(tempIndex != bucketIndex);

    return pReturn;
}

// �� �ּ����� ����.
int isEmptyBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY) {
            ret = TRUE;
        }
    }
    return ret;
}

// �ڷ��� ����.
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
            printf("���� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�.\n", pKey);
        }
    }
    return ret;
}

// �ؽ� ���̺��� ����
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

// �ؽ� ���̺��� ���� �ڷ��� ����
int getElementCountHashTable(HashTable* pHashTable) {
    int ret = 0;
    if (pHashTable != NULL) {
        ret = pHashTable->currentElementCount;
    }
    return ret;
}

// �ؽ� ���̺��� ���� ���
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
                printf("������ϴ�.\n");
            }
        }
    } else {
        printf("NULL �ؽ� ���̺��Դϴ�.\n");
    }
}
