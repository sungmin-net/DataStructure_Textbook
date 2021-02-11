#include <stdio.h>
#include <stdlib.h>

#include "165p_circularlist.h"

int main(int argc, char* argv[]) {

    CircularList* pList = createCircularList();
    CircularListNode node;
    if (pList != NULL) {
        node.data = 1;
        addCircularListElement(pList, 0, node);

        node.data = 5;
        addCircularListElement(pList, 1, node);

        node.data = 10;
        addCircularListElement(pList, 2, node);

        displayCircularList(pList);

        removeCircularListElement(pList, 0);
        displayCircularList(pList);

        deleteCircularList(pList);
    }
    return 0;
}
