#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "290p_exprdef.h"
#include "292p_exprlinkedstack.h"

LinkedStack* createLinkedStack() {
    LinkedStack *pReturn = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedStack));
    } else {
        printf("Error, malloc(), createLinkedStack()\n");
        return NULL;
    }
    return pReturn;
}

int pushLinkedStack(LinkedStack* pStack, StackNode element) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, pushLinkedStack()\n");
        return FAILED;
    }

    StackNode* pNode = (StackNode*)malloc(sizeof(StackNode));
    if (pNode == NULL) {
        printf("Error, malloc(), pushLinkedStack()\n");
        return FAILED;
    }

    memset(pNode, 0, sizeof(StackNode));
    *pNode = element;
    pNode->pLink = pStack->pTopElement;
    pStack->pTopElement = pNode;
    pStack->currentElementCount++;

    return SUCCEEDED;
}

StackNode* popLinkedStack(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, popLinkedStack()\n");
        return NULL;
    }

    if (isLinkedStackEmpty(pStack) == TRUE) {
        printf("Error, LinkedStack is Empty, popLinkedStack()\n");
        return NULL;
    }


    StackNode* pReturn = pStack->pTopElement;
    pStack->pTopElement = pReturn->pLink;
    pReturn->pLink = NULL; // 반환 노드의 다음 노드로 NULL 입력(주. 스택과 변환값 분리)
    pStack->currentElementCount--;

    return pReturn;
}

StackNode* peekLinkedStack(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, peekLinkedStack()\n");
        return NULL;
    }

    if (isLinkedStackEmpty(pStack) == TRUE) {
        printf("Error, LinkedStack is empty, peekLinkedStack()\n");
        return NULL;
    }

    return pStack->pTopElement;
}

void deleteLinkedStack(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, deleteLinkedStack()\n");
        return;
    }

    StackNode* pNode = pStack->pTopElement;
    StackNode* pDelNode = NULL;
    while (pNode != NULL) {
        pDelNode = pNode;
        pNode = pNode->pLink;
        free(pDelNode);
    }
    free(pStack);
}

int isLinkedStackFull(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, isLinkedStackFull()\n");
        return FAILED;
    }
    StackNode testNode = {0,};
    if (pushLinkedStack(pStack, testNode) == FAILED) {
        return TRUE;
    }
    StackNode* pTestNode = popLinkedStack(pStack);
    if (pTestNode == NULL) {
        printf("Error, cannot remove testNode, isLinkedStackFull()\n");
    }
    free(pTestNode);

    return FALSE;
}

int isLinkedStackEmpty(LinkedStack* pStack) {
    if (pStack == NULL) {
        printf("Error, LinkedStack is null, isLinkedStackEmpty()\n");
        return FAILED;
    }

    if (pStack->currentElementCount == 0) {
        return TRUE;
    }

    return FALSE;
}

