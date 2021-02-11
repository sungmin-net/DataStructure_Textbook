#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "197p_linkedlist.h"

LinkedList* createLinkedList() {
	LinkedList* pReturn = (LinkedList*)malloc(sizeof(LinkedList));// 메모리할당
	if (pReturn == NULL) {
	    printf("Error, malloc(), createLinkedList()\n");
	    return NULL;
	}
	memset(pReturn, 0, sizeof(LinkedList));	// 할당된 메모리 초기화
	return pReturn;
}

int addLinkedListElement(LinkedList* pList, int position, ListNode element) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, addLinkedListElement()\n");
        return FALSE;
    }
    if (position < 0 || position > pList->currentElementCount) {
        printf("Error, position %d is out of index, addLinkedListElement()\n",
                position);
        return FALSE;
    }
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if (pNewNode == NULL) {
	    printf("Error, malloc(), addLinkedListElement()\n");
	}
	*pNewNode = element;
	pNewNode->pLink = NULL;
	ListNode* pPreNode = &(pList->headerNode);
	int i = 0;
	for (i = 0 ; i < position ; i++) {	// 노드가 추가될 위치로 이동
	    pPreNode = pPreNode->pLink;
	}

	pNewNode->pLink = pPreNode->pLink;	// 추가된 노드와 기존 노드 사이의 링크 재설정
	pPreNode->pLink = pNewNode;
	pList->currentElementCount++;

	return TRUE;
}


int removeLinkedListElement(LinkedList* pList, int position) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, removeLinkedListElement()\n");
        return FALSE;
    }
    if (position < 0 || position >= getLinkedListLength(pList)) {
        printf("Error, Position %d is out of index, removeLinkedListElement()\n",
                position);
        return FALSE;
    }

	ListNode* pNode = &(pList->headerNode);
	ListNode* pDelNode = NULL;
	int i = 0;
	for (i = 0 ; i < position ; i++) {
	    pNode = pNode->pLink;
	} // pNode 는 제거할 노드의 바로 이전 노드
	pDelNode = pNode->pLink;	// 제거할 노드
	pNode->pLink = pDelNode->pLink;	// 제거할 노드와 기존 노드 사이의 링크 재설정
	free(pDelNode);	// 제거할 노드 메모리 해제
	pList->currentElementCount--;	// 현재 노드 개수 1 감소
	return TRUE;
}

ListNode* getLinkedListElement(LinkedList* pList, int position) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, getLinkedListElement()\n");
        return NULL;
    }
    if (position < 0 || position >= pList->currentElementCount) {
        printf("Error, position %d is out of index, getLinkedListElement()\n",
                position);
        return NULL;
    }

	int i = 0;
	ListNode* pReturn = &(pList->headerNode);
	for (i = 0 ; i <= position ; i++) {
	    pReturn = pReturn->pLink;
	}
	return pReturn;
}

void deleteLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, deleteLinkedList()\n");
        return;
    }
    clearLinkedList(pList);
	free(pList);
}

void clearLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, clearLinkedList()\n");
        return;
    }
    if (pList->currentElementCount <= 0) {
        printf("Error, LinkedList has no element, clearLinkedList()\n");
        return;
    }
    while (pList->currentElementCount != 0) {
        removeLinkedListElement(pList, 0);
    }
}

int getLinkedListLength(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, getLinkedListLength()\n");
        return FALSE;
    }

	return pList->currentElementCount;
}

int isEmptyLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, isEmptyLinkedList()\n");
        return FAILED;
    }

    if (pList->currentElementCount != 0){
        return FALSE;
    }

	return TRUE;
}

void displayLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null, displayLinkedList()\n");
        return;
    }

    if (pList->currentElementCount == 0) {
        printf("원소가 없습니다.\n");
        return;
    }

    printf("현재 원소 개수 : %d\n", pList->currentElementCount);
    int i = 0;
    for (i = 0 ; i < pList->currentElementCount ; i++) {
        printf("[%d], %d\n", i, getLinkedListElement(pList, i)->data);
    }
}
