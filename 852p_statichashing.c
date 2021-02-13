#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "850p_statichashing.h"

// ÇØ½Ã Å×ÀÌºíÀÇ »ý¼º.
HashTable* createHashTable(int bucketSize) {
    HashTable* pReturn = NULL;

    if (bucketSize <= 0) {
        printf("¹öÅ¶ Å©±â´Â 0º¸´Ù Ä¿¾ß ÇÕ´Ï´Ù.\n");
        return NULL;
    }

    pReturn = (HashTable*)malloc(sizeof(HashTable));
    if (pReturn != NULL) {
        pReturn->currentElementCount = 0;
        pReturn->bucketSize = bucketSize;
        pReturn->pElement = NULL;
    } else {
        printf("¿À·ù, Ã¹¹øÂ° ¸Þ¸ð¸® ÇÒ´ç, createHashTable()\n");
        return NULL;
    }

    pReturn->pElement = (HashElement*)malloc(sizeof(HashTable) * bucketSize);
    if (pReturn->pElement != NULL) {
        memset(pReturn->pElement, 0, sizeof(HashElement) * bucketSize);
    } else {
        if (pReturn != NULL) {
            free(pReturn);
        }
        printf("¿À·ù, µÎ¹øÂ° ¸Þ¸ð¸® ÇÒ´ç, createHashTable()\n");
        return NULL;
    }
    return pReturn;
}

// ÀÚ·áÀÇ Ãß°¡
int addElementStaticHashTable(HashTable* pHashTable, HashElement element) {
    int ret = FALSE;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;
    int inc = 1;

    if (pHashTable == NULL) {
        printf("¿À·ù, NULL-ÇØ½Ã Å×ÀÌºíÀÔ´Ï´Ù.\n");
        ret = FALSE;
        return ret;
    }

    bucketIndex = hashFunction(element.key, pHashTable->bucketSize);
    if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
        printf("¿À·ù, Àß¸øµÈ ÇØ½¬ Å×ÀÌºí ÁÖ¼Ò°¡ °è»êµÇ¾ú½À´Ï´Ù.\n");
        ret = FALSE;
        return ret;
    }

    tempIndex = bucketIndex;
    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. ºó ÁÖ¼Ò ¶Ç´Â »èÁ¦µÈ ÁÖ¼ÒÀÎÁö Á¡°Ë
        if (isEmptyOrDeletedBucket(pElement) == TRUE) {
            pHashTable->pElement[ tempIndex ] = element;
            pHashTable->pElement[ tempIndex ].status = USED;
            pHashTable->currentElementCount++;
            ret = TRUE;
            break;
        } else {
            // 2. ºó ¹öÅ¶À» Ã£Áö ¸øÇÑ °æ¿ì.
            // 2-1. µ¿ÀÏÇÑ key °¡ ÀÌ¹Ì Á¸ÀçÇÏ´Â °æ¿ì.
            if (strcmp(pElement->key, element.key) == 0) {
                printf("¿À·ù, Áßº¹µÈ Å°-[%s]\n", element.key);
                ret = FALSE;
                break;
            } else {
                // 2-2. µ¿ÀÏÇÏÁö ¾ÊÀº keyÀÎ °æ¿ì, ´ÙÀ½ ¹öÅ¶À¸·Î ÀÌµ¿.
                tempIndex = (tempIndex + inc) % pHashTable->bucketSize;
                // ÇØ½Ã Å×ÀÌºíÀÇ ¸ðµç ¹öÅ¶ÀÌ ¸ðµÎ Âù °æ¿ì.
                if (tempIndex == bucketIndex) {
                    printf("¿À·ù, ÇØ½¬Å×ÀÌºíÀÌ °¡µæÃ¡½À´Ï´Ù.\n");
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

// ¹®ÀÚ¿­À» ¼ýÀÚ·Î º¯È¯.
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

// ºó ÁÖ¼Ò È¤Àº »èÁ¦µÈ ÁÖ¼ÒÀÎÁö Á¡°Ë.
int isEmptyOrDeletedBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY || pElement->status == DELETED) {
            ret = TRUE;
        }
    }
    return ret;
}

// ÀÚ·áÀÇ °Ë»ö
HashElement* searchHashTable(HashTable* pHashTable, char* pKey) {
    HashElement* pReturn = NULL;
    HashElement* pElement = NULL;
    int bucketIndex = 0;
    int tempIndex = 0;

    if (pHashTable == NULL) {
        printf("¿À·ù, NULL ÇØ½Ã Å×ÀÌºí ÀÔ´Ï´Ù.\n");
        pReturn = NULL;
        return pReturn;
    }

    bucketIndex = hashFunction(pKey, pHashTable->bucketSize);
    if (bucketIndex < 0) {
        printf("¿À·ù, Àß¸øµÈ ÇØ½¬ Å×ÀÌºí ÁÖ¼Ò°¡ °è»êµÇ¾ú½À´Ï´Ù.\n");
        pReturn = NULL;
    }

    tempIndex = bucketIndex;

    do {
        pElement = &(pHashTable->pElement[ tempIndex ]);
        // 1. ºó ¹öÅ¶À» Ã£Àº °æ¿ì. °Ë»ö ½ÇÆÐ.
        if (isEmptyBucket(pElement) == TRUE) {
            printf("°Ë»ö ½ÇÆÐ. °Ë»öÅ°-[%s]´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n", pKey);
            pReturn = NULL;
            break;
        } else {
            // 2-1. µ¿ÀÏÇÑ Å°¸¦ Ã£Àº °æ¿ì. °Ë»ö ¼º°ø
            if (pElement->status == USED && strcmp(pElement->key, pKey) == 0) {
                pReturn = pElement;
                break;
            } else {
                // 2-2. µ¿ÀÏÇÏÁö ¾ÊÀº key ÀÎ°æ¿ì, ´ÙÀ½ ÁÖ¼Ò·Î ÀÌµ¿.
                tempIndex = (tempIndex + 1) % pHashTable->bucketSize;
                // ÇØ½ÃÅ×ÀÌºíÀÇ ¸ðµç ¹öÅ¶À» °Ë»çÇÑ °æ¿ì.
                if (tempIndex == bucketIndex) {
                    printf("°Ë»ö ½ÇÆÐ, °Ë»öÅ°-[%s]´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n",
                            pKey);
                    pReturn = NULL;
                    break;
                }
            }
        }
    } while(tempIndex != bucketIndex);

    return pReturn;
}

// ºó ÁÖ¼ÒÀÎÁö Á¡°Ë.
int isEmptyBucket(HashElement* pElement) {
    int ret = FALSE;
    if (pElement != NULL) {
        if (pElement->status == EMPTY) {
            ret = TRUE;
        }
    }
    return ret;
}

// ÀÚ·áÀÇ »èÁ¦.
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
            printf("ì‚­ì œ ì‹¤íŒ¨, ê²€ìƒ‰í‚¤-[%s]ëŠ” ì¡´ìž¬í•˜ì§€ ì•ŠìŠµë‹ˆë‹¤.\n", pKey);
        }
    }
    return ret;
}

// ÇØ½Ã Å×ÀÌºíÀÇ »èÁ¦
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

// ÇØ½Ã Å×ÀÌºíÀÇ ÇöÀç ÀÚ·áÀÇ °³¼ö
int getElementCountHashTable(HashTable* pHashTable) {
    int ret = 0;
    if (pHashTable != NULL) {
        ret = pHashTable->currentElementCount;
    }
    return ret;
}

// ÇØ½Ã Å×ÀÌºíÀÇ ³»¿ë Ãâ·Â
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
                printf("ºñ¾ú½À´Ï´Ù.\n");
            }
        }
    } else {
        printf("NULL ÇØ½Ã Å×ÀÌºíÀÔ´Ï´Ù.\n");
    }
}
