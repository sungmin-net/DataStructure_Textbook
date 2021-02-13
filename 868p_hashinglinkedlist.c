#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "867p_hashingdef.h"
#include "868p_hashinglinkedlist.h"

LinkedList* createLinkedList() {
    LinkedList* pReturn = NULL;
    pReturn = (LinkedList*)malloc(sizeof(LinkedList));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedList));
    } else {
        printf("오류, 메모리할당, createLinkedList()\n");
        return NULL;
    }
    return pReturn;
}

int addElementLinkedList(LinkedList* pList, int position, ListNode element) {
    int ret = FALSE;
    int i = 0;
    ListNode* pPreNode = NULL;
    ListNode* pNewNode = NULL;
    if (pList != NULL) {
        if (position >= 0 && position <= pList->currentElementCount) {
            pNewNode = (ListNode*)malloc(sizeof(ListNode));
            if (pNewNode != NULL) {
                *pNewNode = element;
                pNewNode->pLink = NULL;
                pPreNode = &(pList->headerNode);
                for (i = 0 ; i < position ; i++) {
                    pPreNode = pPreNode->pLink;
                }
                pNewNode->pLink = pPreNode->pLink;
                pPreNode->pLink = pNewNode;
                pList->currentElementCount++;
                ret = TRUE;
            } else {
                printf("오류, 메모리할당 addElementLinkedList()\n");
                return ret;
            }
        } else {
            printf("오류, 위치인덱스-[%d], addElementLinkedList()\n", position);
        }
    }
    return ret;
}

int removeElementLinkedList(LinkedList* pList, int position) {
    int ret = FALSE;
    int i = 0;
    int listCount = 0;
    ListNode* pNode = NULL;
    ListNode* pDelNode = NULL;
    if (pList!= NULL) {
        listCount = getLengthLinkedList(pList);
        if (position >= 0 && position < listCount) {
            pNode = &(pList->headerNode);
            for (i = 0 ; i < position ; i++) {
                pNode = pNode->pLink;
            }
            pDelNode = pNode->pLink;
            pNode->pLink = pDelNode->pLink;
            free(pDelNode);
            pList->currentElementCount--;
            ret = TRUE;
        } else {
            printf("오류, 위치인덱스-[%d], removeElementLinkedList()\n",
                    position);
        }
    }
    return ret;
}

ListNode* getElementLinkedList(LinkedList* pList, int position) {
    ListNode* pReturn = NULL;
    int i = 0;
    ListNode* pNode = NULL;
    if (pList != NULL) {
        if (position >= 0 && position < pList->currentElementCount) {
            pNode = &(pList->headerNode);
            for (i = 0 ; i <= position ; i++) {
                pNode = pNode->pLink;
            }
            pReturn = pNode;
        }
    }
    return pReturn;
}

void deleteLinkedList(LinkedList* pList) {
    if (pList != NULL) {
        clearLinkedList(pList);
        free(pList);
    }
}

void clearLinkedList(LinkedList* pList) {
    if (pList != NULL) {
        while (pList->currentElementCount > 0) {
            removeElementLinkedList(pList, 0);
        }
    }
}

int getLengthLinkedList(LinkedList* pList) {
    int ret = 0;
    if (pList != NULL) {
        ret = pList->currentElementCount;
    }
    return ret;
}

int isEmpty(LinkedList* pList) {
    int ret = FALSE;
    if (pList != NULL) {
        if (pList->currentElementCount == 0) {
            ret = TRUE;
        }
    }
    return ret;
}





