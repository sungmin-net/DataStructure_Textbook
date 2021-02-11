#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "197p_linkedlist.h"

LinkedList* createLinkedList() {
	LinkedList* pReturn = (LinkedList*)malloc(sizeof(LinkedList));// �޸��Ҵ�
	if (pReturn == NULL) {
	    printf("Error, malloc(), createLinkedList()\n");
	    return NULL;
	}
	memset(pReturn, 0, sizeof(LinkedList));	// �Ҵ�� �޸� �ʱ�ȭ
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
	for (i = 0 ; i < position ; i++) {	// ��尡 �߰��� ��ġ�� �̵�
	    pPreNode = pPreNode->pLink;
	}

	pNewNode->pLink = pPreNode->pLink;	// �߰��� ���� ���� ��� ������ ��ũ �缳��
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
	} // pNode �� ������ ����� �ٷ� ���� ���
	pDelNode = pNode->pLink;	// ������ ���
	pNode->pLink = pDelNode->pLink;	// ������ ���� ���� ��� ������ ��ũ �缳��
	free(pDelNode);	// ������ ��� �޸� ����
	pList->currentElementCount--;	// ���� ��� ���� 1 ����
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
        printf("���Ұ� �����ϴ�.\n");
        return;
    }

    printf("���� ���� ���� : %d\n", pList->currentElementCount);
    int i = 0;
    for (i = 0 ; i < pList->currentElementCount ; i++) {
        printf("[%d], %d\n", i, getLinkedListElement(pList, i)->data);
    }
}
