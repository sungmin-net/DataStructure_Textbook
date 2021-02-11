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
    // ���Ḯ��Ʈ A �� ������ ��� ã��
    while (pNodeA->pLink != NULL) {
        pNodeA = pNodeA->pLink;
    }

    // ���Ḯ��ƮA�� ������ ���� ���Ḯ��ƮB�� ù��° ���� ���� �� ��� ���� ����
    pNodeA->pLink = pListB->headerNode.pLink;
    pListA->currentElementCount += pListB->currentElementCount;

    // ���Ḯ��ƮB�� ù��° ���� NULL ���� �� ��� ���� 0���� �缳��
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


