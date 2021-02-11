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
	        // 공백리스트에서 첫번째 노드를 추가하는 경우
	        pList->pLink = pNewNode;
	        pNewNode->pLink = pNewNode;
	    } else {	// 공백 리스트가 아닐 때 첫번째 노드를 추가하는 경우
	        pLastNode = pList->pLink;
	        while(pLastNode->pLink != pList->pLink) {
	            pLastNode = pLastNode->pLink;	// 마지막 노드까지 이동
	        }
	        pList->pLink = pNewNode;
	        pNewNode->pLink = pLastNode->pLink;
	        pLastNode->pLink = pNewNode;
	    }
    } else {
        // 공백이 아닌 리스트 중간에 노드를 추가하는 경우
        pPreNode = pList->pLink;
        // 추가하려는 위치의 이전 노드를 찾을 때까지 이동
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
	        // 마지막 노드이면서 동시에 첫 번째 노드를 제거하는 경우
	        free(pDelNode);
	        pList->pLink = NULL;
	    } else {
	        // 마지막 노드가 아닌 첫 번째 노드를 제거하는 경우
	        pLastNode = pList->pLink;
	        while(pLastNode->pLink != pList->pLink) {
	            pLastNode = pLastNode->pLink;
	        }
	        pLastNode->pLink = pDelNode->pLink;
	        pList->pLink = pDelNode->pLink;
	        free(pDelNode);
	    }
	} else {
	    // 리스트의 중간 노드를 삭제하는 경우
	    pPreNode = pList->pLink;
	    int i = 0;
	    for (i = 0 ; i < position - 1 ; i++) {
	        // 위치 인덱스가 position - 1 인 노드까지 이동
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
        printf("원소가 없습니다.\n");
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
