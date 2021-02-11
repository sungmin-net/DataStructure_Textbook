#include <stdio.h>
#include <stdlib.h>

#include "237p_arraystack.h"

void displayArrayStack(ArrayStack* pStack) {
    if (pStack == NULL) {
        printf("Error, ArrayStack is null, displayArrayStack()\n");
        return;
    }

    int size = pStack->maxElementCount;
    int top = pStack->currentElementCount;
    int i = 0;

    printf("스택 크기 : %d, 현재 노드 개수 : %d\n", pStack->maxElementCount,
            pStack->currentElementCount);
    for (i = size - 1 ; i >= top; i--) {
        printf("[%d] - [Empty]\n", i);
    }
    for (i = top - 1 ; i >= 0 ; i--) {
        printf("[%d] - [%c]\n", i, pStack->pElement[i].data);
    }
}

int main(int argc, char* argv[]) {
    ArrayStack* pStack = createArrayStack(6);
    if (pStack == NULL) {
        printf("Error, createArrayStack() failed.\n");
        return FAILED;
    }

    ArrayStackNode node1 = {'A'};
    ArrayStackNode node2 = {'B'};
    ArrayStackNode node3 = {'C'};
    ArrayStackNode node4 = {'D'};

    pushArrayStack(pStack, node1);
    pushArrayStack(pStack, node2);
    pushArrayStack(pStack, node3);
    pushArrayStack(pStack, node4);
    displayArrayStack(pStack);

    ArrayStackNode* pNode = popArrayStack(pStack);
    if (pNode != NULL) {
        printf("Pop 값 - [%c]\n", pNode->data);
        free(pNode);
    } else {
        printf("공백(Empty) 스택\n");
    }
    displayArrayStack(pStack);

    pNode = peekArrayStack(pStack);
    if (pNode != NULL) {
        printf("Peek 값 - [%c]\n", pNode->data);
    } else {
        printf("공백(Empty) 스택\n");
    }
    displayArrayStack(pStack);
    deleteArrayStack(pStack);
    return 0;
}




