#include <stdio.h>
#include <stdlib.h>

#include "197p_linkedlist.h"
#include "197p_linkedlist_op.h"

int main(int argc, char* argv[]) {
    LinkedList* pListA = NULL;
    LinkedList* pListB = NULL;
    ListNode node;

    pListA = createLinkedList();
    pListB = createLinkedList();
    if (pListA != NULL && pListB != NULL) {
        node.data = 1;
        addLinkedListElement(pListA, 0, node);
        node.data = 2;
        addLinkedListElement(pListA, 1, node);
        node.data = 3;
        addLinkedListElement(pListA, 2, node);
        node.data = 4;
        addLinkedListElement(pListB, 0, node);
        node.data = 5;
        addLinkedListElement(pListB, 1, node);

        iterateLinkedList(pListA);
        iterateLinkedList(pListB);

        // ����ƮB�� ����ƮA�� �����̱�.
        concatLinkedList(pListA, pListB);
        printf("After concatLinkedList()\n");
        iterateLinkedList(pListA);
        iterateLinkedList(pListB);

        // ����Ʈ A�� ���� �����
        reverseLinkedList(pListA);
        printf("After reverseLinkedList()\n");
        iterateLinkedList(pListA);

        deleteLinkedList(pListA);
        deleteLinkedList(pListB);
    }
    return 0;
}

