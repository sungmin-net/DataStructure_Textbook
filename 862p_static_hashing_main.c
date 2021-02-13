#include <stdio.h>
#include <stdlib.h>

#include "850p_statichashing.h"

int main(int argc, char** argv) {
    HashTable* pHashTable = NULL;
    HashElement element1 = {"january", 1};
    HashElement element2 = {"february", 2};
    HashElement element3 = {"march", 3};
    HashElement element4 = {"april", 4};
    HashElement element5 = {"may", 5};
    HashElement element6 = {"june", 6};
    HashElement element7 = {"july", 7};
    HashElement element8 = {"august", 8};
    HashElement element9 = {"september", 9};
    HashElement element10 = {"october", 10};
    HashElement element11 = {"november", 11};
    HashElement element12 = {"december", 12};
    HashElement* pElement = NULL;
    HashElement* pElement2 = NULL;

    //  해시테이블 생성
    pHashTable = createHashTable(13);
    if (pHashTable != NULL) {
        addElementStaticHashTable(pHashTable, element1);
        addElementStaticHashTable(pHashTable, element2);
        addElementStaticHashTable(pHashTable, element3);
        addElementStaticHashTable(pHashTable, element4);
        addElementStaticHashTable(pHashTable, element5);
        addElementStaticHashTable(pHashTable, element6);
        addElementStaticHashTable(pHashTable, element7);
        addElementStaticHashTable(pHashTable, element8);
        addElementStaticHashTable(pHashTable, element9);
        addElementStaticHashTable(pHashTable, element10);
        addElementStaticHashTable(pHashTable, element11);
        addElementStaticHashTable(pHashTable, element12);

        printf("해시테이블 내용:\n");
        displayHashTable(pHashTable);

        pElement = searchHashTable(pHashTable, "april");
        if (pElement != NULL) {
            printf("검색키-%s, 검색 결과 - %d\n", pElement->key,
                    pElement->value);
            deleteElementHashTable(pHashTable, "april");
            printf("검색키[%s] 로 자료 삭제\n", "april");

            printf("해시테이블 내용:\n");
            displayHashTable(pHashTable);

            pElement2 = searchHashTable(pHashTable, "april");
            if (pElement2 != NULL) {
                printf("검색키-%s, 검색 결과-%d\n", pElement2->key,
                        pElement2->value);
            }

            pElement2 = searchHashTable(pHashTable, "june");
            if (pElement2 != NULL) {
                printf("검색키-%s, 검색 결과-%d\n", pElement2->key,
                        pElement2->value);
            }
        } else {
            printf("Not found\n");
        }

        deleteHashTable(pHashTable);
    }
    return 0;
}
