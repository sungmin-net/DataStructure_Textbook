#include <stdio.h>
#include <stdlib.h>

#include "186p_doublylist.h"

int main(int argc, char* argv[]) {
    DoublyList* pList = createDoublyList();
    DoublyListNode node;

    if (pList != NULL) {
        node.data = 1;
        addDoublyListElement(pList, 0, node);

        node.data = 3;
        addDoublyListElement(pList, 1, node);

        node.data = 4;
        addDoublyListElement(pList, 1, node);

        displayDoublyList(pList);

        removeDoublyListElement(pList, 1);
        displayDoublyList(pList);

        deleteDoublyList(pList);
    }
    return 0;
}
