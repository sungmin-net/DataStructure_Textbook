#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "186p_doublylist.h"

DoublyList* createDoublyList() {
    DoublyList* pReturn = (DoublyList*)malloc(sizeof(DoublyList));
    if (pReturn == NULL) {
        printf("Error, malloc(), createDoublyList()\n");
        return NULL;
    }

    memset(pReturn, 0, sizeof(DoublyList));
    pReturn->headerNode.pPrev = &(pReturn->headerNode);
    pReturn->headerNode.pNext = &(pReturn->headerNode);

    return pReturn;
}

int addDoublyListElement(DoublyList* pList, int position,
        DoublyListNode element) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, addDoublyListElement()\n");
        return FAILED;
    }

    if (position < 0 || position > pList->currentElementCount) {
        printf("Error, position %d is out of index, addDoublyListElement()\n",
                position);
        return FAILED;
    }

    DoublyListNode* pNewNode = (DoublyListNode*)malloc(sizeof(DoublyListNode));
    if (pNewNode == NULL) {
        printf("Error, malloc(), addDoublyListElement()\n");
        return FAILED;
    }
    *pNewNode = element;
    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;

    DoublyListNode* pPreNode = &(pList->headerNode);
    int i = 0;
    for (i = 0; i < position ; i++) {
        pPreNode = pPreNode->pNext;
    }
    pNewNode->pPrev = pPreNode;
    pNewNode->pNext = pPreNode->pNext;
    pPreNode->pNext = pNewNode;
    pNewNode->pNext->pPrev = pNewNode;

    pList->currentElementCount++;

    return SUCEEDED;
}

int removeDoublyListElement(DoublyList* pList, int position) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, removeDoublyListElement()\n");
        return FAILED;
    }

    int currentElementCount = pList->currentElementCount;
    if (position < 0 || position > currentElementCount) {
        printf("Error, position %d is out of index, removeDoublyListElement()\n",
                position);
        return FAILED;
    }

    DoublyListNode* pPreNode = &(pList->headerNode);
    int i = 0;
    for (i = 0 ; i < position ; i++) {
            pPreNode = pPreNode->pNext;
    }
    DoublyListNode* pDelNode = pPreNode->pNext;

    pPreNode->pNext = pDelNode->pNext;
    pDelNode->pNext->pPrev = pPreNode;
    free(pDelNode);

    pList->currentElementCount--;

    return SUCEEDED;
}

DoublyListNode* getDoublyListElement(DoublyList* pList, int position) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, getDoublyListElement()\n");
        return NULL;
    }

    int currentElementCount = pList->currentElementCount;
    if (position < 0 || position > currentElementCount) {
        printf("Error, position %d is out of index, getDoublyListElement()\n",
                position);
        return NULL;
    }

    DoublyListNode* pReturn = pList->headerNode.pNext;
    int i = 0;
    for (i = 0 ; i < position ; i++) {
        pReturn = pReturn->pNext;
    }

    return pReturn;
}

void displayDoublyList(DoublyList* pList) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, displayDoublyList()\n");
        return;
    }
    int currentElementCount = pList->currentElementCount;
    if (currentElementCount == 0) {
        printf("원소가 없습니다.\n");
    } else {
        printf("현재 노드 개수 : %d\n", currentElementCount);
        int i = 0;
        for (i = 0 ; i < currentElementCount; i++) {
            printf("[%d], %d\n", i, getDoublyListElement(pList, i)->data);
        }
    }
}

void deleteDoublyList(DoublyList* pList) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, deleteDoublyList()\n");
        return;
    }
    clearDoublyList(pList);
    free(pList);
}

void clearDoublyList(DoublyList* pList) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, clearDoublyList()\n");
        return;
    }
    while (pList->currentElementCount > 0) {
        removeDoublyListElement(pList, 0);
    }
}

int getDoublyListLength(DoublyList* pList) {
    if (pList == NULL) {
        printf("Error, DoublyList is null, getDoublyListLength()\n");
        return FAILED;
    }
    return pList->currentElementCount;
}

