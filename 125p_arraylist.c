/*
 * arraylist.c
 *
 *  Created on: 2018. 1. 9.
 *      Author: Sungmin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "122p_arraylist.h"

ArrayList* createArrayList(int maxElementCount) {
    if (maxElementCount <= 0) {
        printf("Error, maxElementCount is 0 or less.\n");
        return NULL;

    }
	ArrayList* pReturn = (ArrayList*)malloc(sizeof(ArrayList));
	if (pReturn == NULL) {
	    printf("Error, malloc(), createArrayList()\n");
	    return NULL;
	}
	pReturn->maxElementCount = maxElementCount;
	pReturn->currentElementCount = 0;
	pReturn->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode)
	        * maxElementCount);
	if (pReturn->pElement == NULL) {
		printf("Error, second malloc(), createArrayList()\n");
		free(pReturn);
		return NULL;
	}
	memset(pReturn->pElement, 0, sizeof(ArrayListNode) * maxElementCount);
	return pReturn;
}

int addArrayListElement(ArrayList* pList, int position, ArrayListNode element) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, addArrayListElement()\n");
        return FALSE;
    }
    if (isArrayListFull(pList) == TRUE) {
        printf("Error, ArrayList is full. [%d]/[%d], addArrayListElement()\n",
                position, pList->maxElementCount);
        return FALSE;
    }
    if (position < 0 || position >= pList->maxElementCount) {
        printf("Error, out of index %d, addArrayListElement()\n", position);
        return FALSE;
    }
    int i = 0;
    for (i = pList->currentElementCount - 1 ; i >= position ; i--) {
        pList->pElement[i + 1] = pList->pElement[i];
    } // 기존 원소들을 오른쪽으로 한 칸씩 이동
    pList->pElement[position] = element; // 새로운 원소 추가
    pList->currentElementCount++;
    return TRUE;
}

int removeArrayListElement(ArrayList* pList, int position) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, removeArrayListElement()\n");
        return FALSE;
    }
    if (position < 0 || position >= pList->currentElementCount) {
        printf("Error, out of index %d, removeArrayListElement()\n", position);
        return FALSE;
    }
    int i = 0;
    for (i = position ; i < pList->currentElementCount - 1; i++) {
        pList->pElement[i] = pList->pElement[i+1];
    }
    pList->currentElementCount--;
    return TRUE;
}

ArrayListNode* getArrayListElement(ArrayList* pList, int position) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, getArrayListElement()\n");
        return NULL;
    }

    if (position < 0 || position >= getArrayListLength(pList)) {
        printf("Error, position %d is out of index, getArrayListElement()\n",
                position);
        return NULL;
    }

    return &(pList->pElement[ position ]);
}

void displayArrayList(ArrayList* pList) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, displayArrayList()\n");
        return;
    }

    printf("최대 원소 개수 : %d\n", pList->maxElementCount);
	printf("현재 원소 개수 : %d\n", pList->currentElementCount);

	int i = 0;
	for (i = 0 ; i < pList->currentElementCount ; i++) {
	    printf("[%d], %d\n", i, getArrayListElement(pList, i)->data);
	}

	i = pList->currentElementCount;
	for(; i < pList->maxElementCount ; i++) {
	    printf("[%d], Empty\n", i);
	}
}

int isArrayListFull(ArrayList* pList) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, isArrayListFull()\n");
    }

    if (pList->currentElementCount == pList-> maxElementCount) {
        return TRUE;
    }
    return FALSE;
}

int getArrayListLength(ArrayList* pList) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, getArrayListLength()\n");
        return 0;
    }
    return pList -> currentElementCount;
}

void deleteArrayList(ArrayList* pList) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, deleteArrayList()\n");
        return;
    }
    // 생성시에 최대 크기만큼 한번 할당한 pElement 의 메모리를 먼저 해제
    free(pList->pElement);
    free(pList);
}

int addArrayListElementFirst(ArrayList* pList, ArrayListNode element) {
	return addArrayListElement(pList, 0/*first element*/, element);
}

int addArrayListElementLast(ArrayList* pList, ArrayListNode element) {
    if (pList == NULL) {
        printf("Error, ArrayList is null, addArrayListElementLast()\n");
        return FALSE;
    }

    int position = getArrayListLength(pList);
    return addArrayListElement(pList, position, element);
}
