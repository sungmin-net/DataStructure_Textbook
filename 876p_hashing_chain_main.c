#include <stdio.h>
#include <stdlib.h>

#include "867p_hashingdef.h"
#include "868p_hashinglinkedlist.h"
#include "869p_statichashing.h"

int main(int argc, char** argv) {

    HashTable* pHashTable = NULL;
    HashElement element1 = {"January", 1};
    HashElement element2 = {"February", 2};
    HashElement element3 = {"March", 3};
    HashElement element4 = {"April", 4};
    HashElement element5 = {"May", 5};
    HashElement element6 = {"June", 6};
    HashElement element7 = {"July", 7};
    HashElement element8 = {"August", 8};
    HashElement element9 = {"Septempber", 9};
    HashElement element10 = {"October", 10};
    HashElement element11 = {"November", 11};
    HashElement element12 = {"December", 12};

    HashElement* pElement1 = NULL;
    HashElement* pElement2 = NULL;

    pHashTable = createHashTable(13); // 13은 12보다 큰 소수
    if (pHashTable != NULL) {
        addElementHashTable(pHashTable, element1);
        addElementHashTable(pHashTable, element2);
        addElementHashTable(pHashTable, element3);
        addElementHashTable(pHashTable, element4);
        addElementHashTable(pHashTable, element5);
        addElementHashTable(pHashTable, element6);
        addElementHashTable(pHashTable, element7);
        addElementHashTable(pHashTable, element8);
        addElementHashTable(pHashTable, element9);
        addElementHashTable(pHashTable, element10);
        addElementHashTable(pHashTable, element11);
        addElementHashTable(pHashTable, element12);

        printf("해시 테이블 내용\n");
        displayHashTable(pHashTable);

        pElement1 = searchHashTable(pHashTable, "April");
        if (pElement1 != NULL) {
            printf("검색키-%s, 검색결과-%d\n", pElement1->aKey,
                    pElement1->value);
            deleteElementHashTable(pHashTable, "April");
            printf("검색키-%s 로 자료 삭제\n", "April");

            printf("해시 테이블 내용\n");
            displayHashTable(pHashTable);

            pElement2 = searchHashTable(pHashTable, "June");
            if (pElement2 != NULL) {
                printf("검색키-%s, 검색결과-%d\n", pElement2->aKey,
                        pElement2->value);
            }
        } else {
            printf("Not found\n");
        }

        deleteHashTable(pHashTable);
    }
    return 0;
}
