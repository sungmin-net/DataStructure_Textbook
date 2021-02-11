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

    // ����Ʈ �ʱ�ȭ : 1, 3, 5 �߰�.
    node.data = 1;
    addArrayListElement(pList, 0, node);

    node.data = 3;
    addArrayListElement(pList, 1, node);

    node.data = 5;
    addArrayListElement(pList, 2, node);
    displayArrayList(pList);

    // ù��° ���� ����.
    removeArrayListElement(pList, 0);
    displayArrayList(pList);

    arrayCount = getArrayListLength(pList);
    for(i = 0 ; i < arrayCount ; i++) {
        pValue = getArrayListElement(pList, i);
        printf("��ġ[%d] - %d\n", i, pValue->data);
    }

    deleteArrayList(pList);
    return 0;

}
