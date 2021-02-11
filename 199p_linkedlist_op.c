#include <stdio.h>
#include <stdlib.h>

#include "197p_linkedlist.h"
#include "197p_linkedlist_op.h"

void iterateLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null.\n");
        return;
    }
    ListNode* pNode = pList->headerNode.pLink;
    int count = 0;
    while (pNode != NULL) {
        printf("[%d], %d\n", count, pNode->data);
        count++;
        pNode = pNode->pLink;
    }
    printf("Node count : %d\n", count);
}

void concatLinkedList(LinkedList* pListA, LinkedList* pListB) {
    if (pListA == NULL) {
        printf("Error, first LinkedList is null.\n");
        return;
    }
    if (pListB == NULL) {
        printf("Error, second LinkedList is null.\n");
        return;
    }
    ListNode* pNodeA = pListA->headerNode.pLink;
    // 연결리스트 A 의 마지막 노드 찾기
    while (pNodeA->pLink != NULL) {
        pNodeA = pNodeA->pLink;
    }

    // 연결리스트A의 마지막 노드로 연결리스트B의 첫번째 노드로 연결 및 노드 개수 증가
    pNodeA->pLink = pListB->headerNode.pLink;
    pListA->currentElementCount += pListB->currentElementCount;

    // 연결리스트B의 첫번째 노드로 NULL 대입 및 노드 개수 0으로 재설정
    pListB->headerNode.pLink = NULL;
    pListB->currentElementCount = 0;
}

void reverseLinkedList(LinkedList* pList) {
    if (pList == NULL) {
        printf("Error, LinkedList is null.\n");
    }

    ListNode* pNode = pList->headerNode.pLink;
    ListNode* pCurrentNode = NULL;
    ListNode* pPrevNode = NULL;
    while (pNode != NULL) {
        pPrevNode = pCurrentNode;
        pCurrentNode = pNode;
        pNode = pNode->pLink;
        pCurrentNode->pLink = pPrevNode;
    }
    pList->headerNode.pLink = pCurrentNode;
}


