#include <stdio.h>
#include <stdlib.h>

#include "254p_linkedstack.h"

void displayLinkedStack(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, displayLinkedStack()\n");
        return;
    }
    printf("현재 노드 개수 : %d\n", pStack->currentElementCount);
    StackNode* pNode = pStack->pTopElement;
    int i = 1;
    while (pNode != NULL) {
        printf("[%d]-[%c]\n", pStack->currentElementCount - i, pNode->data);
        i++;
        pNode = pNode->pLink;
    }
}

int main(int argc, char* argv[]) {
    LinkedStack* pStack = NULL;
    StackNode* pNode = NULL;

    pStack = createLinkedStack();
    if (pStack != NULL) {
        StackNode node1 = {'A'};
        StackNode node2 = {'B'};
        StackNode node3 = {'C'};
        StackNode node4 = {'D'};

        pushLinkedStack(pStack, node1);
        pushLinkedStack(pStack, node2);
        pushLinkedStack(pStack, node3);
        pushLinkedStack(pStack, node4);
        displayLinkedStack(pStack);

        pNode = popLinkedStack(pStack);
        if (pNode != NULL) {
            printf("Pop - [%c]\n", pNode->data);
            free(pNode);
        } else {
            printf("Pop - NULL\n");
        }
        displayLinkedStack(pStack);

        pNode = peekLinkedStack(pStack);
        if (pNode != NULL) {
            printf("Peek - [%c]\n", pNode->data);
        } else {
            printf("Peek - NULL\n");
        }
        displayLinkedStack(pStack);
        deleteLinkedStack(pStack);
    }
    return 0;
}




