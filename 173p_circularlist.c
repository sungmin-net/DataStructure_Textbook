#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "165p_circularlist.h"

int addCircularListElement(CircularList* pList, int position,
		CircularListNode element) {
    if (pList == NULL) {
        printf("Error, CircularList is null. addCircularListElement()\n");
        return FAILED;
    }
    if (position < 0 || position > pList->currentElementCount) {
        printf("Error, position %d is out of index, addCircularListElement()\n",
                position);
        return FAILED;
    }
	CircularListNode* pNewNode = (CircularListNode*)malloc(
	        sizeof(CircularListNode));
	if (pNewNode == NULL) {
	    printf("Error, malloc(), addCircularListElement()\n");
	    return FAILED;
	}
	*pNewNode = element;
	pNewNode->pLink = NULL;

	int i = 0;
	CircularListNode* pPreNode = NULL;
	CircularListNode* pLastNode = NULL;

	if (position == 0) {
	    if (pList->currentElementCount == 0) {
	        // ���鸮��Ʈ���� ù��° ��带 �߰��ϴ� ���
	        pList->pLink = pNewNode;
	        pNewNode->pLink = pNewNode;
	    } else {	// ���� ����Ʈ�� �ƴ� �� ù��° ��带 �߰��ϴ� ���
	        pLastNode = pList->pLink;
	        while(pLastNode->pLink != pList->pLink) {
	            pLastNode = pLastNode->pLink;	// ������ ������ �̵�
	        }
	        pList->pLink = pNewNode;
	        pNewNode->pLink = pLastNode->pLink;
	        pLastNode->pLink = pNewNode;
	    }
    } else {
        // ������ �ƴ� ����Ʈ �߰��� ��带 �߰��ϴ� ���
        pPreNode = pList->pLink;
        // �߰��Ϸ��� ��ġ�� ���� ��带 ã�� ������ �̵�
        for (i = 0 ; i < position - 1 ; i++) {
            pPreNode = pPreNode->pLink;
        }
        pNewNode->pLink = pPreNode->pLink;
		pPreNode->pLink = pNewNode;
    }
	pList->currentElementCount++;
	return SUCCEEDED;
}

int removeCircularListElement(CircularList* pList, int position) {
    if (pList == NULL) {
        printf("Error, CircularList is null. removeCircularListElement()\n");
        return FAILED;
    }
    int currentCircularListLength = pList->currentElementCount;
    if (position < 0 || position > currentCircularListLength) {
        printf("Error, position %d is out of index, removeCircularListElement()\n",
                position);
        return FAILED;
    }
	CircularListNode* pPreNode = NULL;
	CircularListNode* pDelNode = NULL;
	CircularListNode* pLastNode = NULL;

	if (position == 0) {
	    pDelNode = pList->pLink;
	    if (pList->currentElementCount == 1) {
	        // ������ ����̸鼭 ���ÿ� ù ��° ��带 �����ϴ� ���
	        free(pDelNode);
	        pList->pLink = NULL;
	    } else {
	        // ������ ��尡 �ƴ� ù ��° ��带 �����ϴ� ���
	        pLastNode = pList->pLink;
	        while(pLastNode->pLink != pList->pLink) {
	            pLastNode = pLastNode->pLink;
	        }
	        pLastNode->pLink = pDelNode->pLink;
	        pList->pLink = pDelNode->pLink;
	        free(pDelNode);
	    }
	} else {
	    // ����Ʈ�� �߰� ��带 �����ϴ� ���
	    pPreNode = pList->pLink;
	    int i = 0;
	    for (i = 0 ; i < position - 1 ; i++) {
	        // ��ġ �ε����� position - 1 �� ������ �̵�
	        pPreNode = pPreNode->pLink;
	    }
		pDelNode = pPreNode->pLink;
		pPreNode->pLink = pDelNode->pLink;
		free(pDelNode);
	}
	pList->currentElementCount--;
	return SUCCEEDED;
}

CircularListNode* getCircularListElement(CircularList* pList, int position) {
    if (pList == NULL) {
        printf("Error, CircularList is null. getCircularListElement()\n");
        return NULL;
    }
    if (position < 0 || position > pList->currentElementCount) {
        printf("Error, position %d is out of index, getCircularListElement()\n",
                position);
        return NULL;
    }
	CircularListNode* pNode = pList->pLink;
	int i = 0;
	for(i = 0 ; i < position ; i++) {
	    pNode = pNode->pLink;
	}
	return pNode;
}


CircularList* createCircularList() {
	CircularList* pReturn = (CircularList*)malloc(sizeof(CircularList));
	if (pReturn == NULL) {
	    printf("Error, malloc(), createCircularList()\n");
	    return NULL;
	}
	memset(pReturn, 0, sizeof(CircularList));
	return pReturn;
}

void displayCircularList(CircularList* pList) {
    if (pList == NULL) {
        printf("Error, CircularList is null. getCircularListElement()\n");
        return;
    }

    int currentCircularListLength = pList->currentElementCount;
    if (currentCircularListLength == 0) {
        printf("���Ұ� �����ϴ�.\n");
    } else {
        printf("Current element count : %d\n", currentCircularListLength);
        int i = 0;
        for (i = 0 ; i < pList->currentElementCount ; i++) {
            printf("[%d], %d\n", i, getCircularListElement(pList, i)->data);
        }
    }
}

int getCircularListLength(CircularList* pList) {
    if (pList == NULL) {
        printf("Error, CircularList is null, getCircularListLength()\n");
        return FAILED;
    }

	return pList->currentElementCount;
}

void deleteCircularList(CircularList* pList) {
    if (pList == NULL) {
        printf("Error, CircularList is null, deleteCircularList()\n");
        return;
    }
    clearCircularList(pList);
	free(pList);
}

void clearCircularList(CircularList* pList) {
    if (pList == NULL) {
        printf("Error, CircularList is null, clearCircularList()\n");
        return;
    }

	while (pList->currentElementCount > 0) {
	    removeCircularListElement(pList, 0);
	}
}
