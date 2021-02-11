#include <stdio.h>
#include <stdlib.h>

#include "122p_arraylist.h"

int main(int argc, char* argv[]) {

    ArrayList* pList = createArrayList(6);
    if (pList == NULL) {
        printf("Error, main().");
        return 0;
    }

    int i = 0;
    int arrayCount = 0;
    ArrayListNode *pValue = NULL;
    ArrayListNode node;

    // 리스트 초기화 : 1, 3, 5 추가.
    node.data = 1;
    addArrayListElement(pList, 0, node);

    node.data = 3;
    addArrayListElement(pList, 1, node);

    node.data = 5;
    addArrayListElement(pList, 2, node);
    displayArrayList(pList);

    // 첫번째 원소 제거.
    removeArrayListElement(pList, 0);
    displayArrayList(pList);

    arrayCount = getArrayListLength(pList);
    for(i = 0 ; i < arrayCount ; i++) {
        pValue = getArrayListElement(pList, i);
        printf("위치[%d] - %d\n", i, pValue->data);
    }

    deleteArrayList(pList);
    return 0;

}
