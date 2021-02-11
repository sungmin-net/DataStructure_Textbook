#include <stdio.h>
#include <stdlib.h>

#include "146p_linkedlist.h"

int main(int argc, char* argv[]) {
    LinkedList *pList = NULL;
    ListNode node;

    pList = createLinkedList();
    if (pList != NULL) {
        node.data = 1;
        addLinkedListElement(pList, 0, node);

        node.data = 3;
        addLinkedListElement(pList, 1, node);

        node.data = 5;
        addLinkedListElement(pList, 2, node);
        displayLinkedList(pList);

        removeLinkedListElement(pList, 0);
        displayLinkedList(pList);

        deleteLinkedList(pList);
    }
    return 0;
}
