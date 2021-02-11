#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for quiz
#include "209p_linkedlist.h"
#include "211p_polylist.h"

int addPolyNodeLast(LinkedList* pList, float coef, int degree) {
    if (pList == NULL) {
        printf("Error, LinkedList is null. addPolyNodeLast()\n");
        return FAILED;
    }

    ListNode node = {0,};
    node.coef = coef;
    node.degree = degree;
    int length = getLinkedListLength(pList);
    return addLinkedListElement(pList, length, node);
}

LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB) {
    if (pListA == NULL || pListB == NULL) {
        printf("Error, LinkedList(s) is(are) null.\n");
        return NULL;
    }

    LinkedList* pReturn = createLinkedList();
    if (pReturn == NULL) {
        printf("�޸� �Ҵ� ����, polyAdd()\n");
        return NULL;
    }
    ListNode* pNodeA = pListA->headerNode.pLink;
    ListNode* pNodeB = pListB->headerNode.pLink;
    float coefSum = 0;
    // �� ���׽��� ������ ������ �̵��ϸ鼭 �ݺ�
    while (pNodeA != NULL && pNodeB != NULL) {
        int degreeA = pNodeA->degree;
        int degreeB = pNodeB->degree;
        if (degreeA > degreeB) {
            // A�� ���� > B�� ������ ���, ���׽� A�� ���� �̿��Ͽ�
            // ��� ���׽Ŀ� ���ο� ���� �߰�
            coefSum = pNodeA->coef;
            addPolyNodeLast(pReturn, coefSum, degreeA);
            // ���׽� A �� ���� ������ �̵�
            pNodeA = pNodeA->pLink;
        } else if (degreeA == degreeB) {
            // A�� ���� == B �� ������ ���, ���׽� A�� B �� ����� ���Ͽ�
            // ��� ���׽Ŀ� ���ο� ���� �߰�
            coefSum = pNodeA->coef + pNodeB->coef;
            addPolyNodeLast(pReturn, coefSum, degreeA);
            // ���׽� A�� B ��� ���� ������ �̵�
            pNodeA = pNodeA->pLink;
            pNodeB = pNodeB->pLink;
        } else {
            // A�� ���� < B �� ����
            // ���׽� B�� ���� �̿��Ͽ� ��� ���׽Ŀ� ���ο� ���� �߰�
            // ���׽� B�� ���� ������ �̵�
            coefSum = pNodeB->coef;
            addPolyNodeLast(pReturn, coefSum, degreeB);
            pNodeB = pNodeB->pLink;
        }
    }

    // ���׽�A�� ���� ���� �ִٸ�, ���� ������ ��� ���׽Ŀ� ���ο� �� �߰�
    while (pNodeA != NULL) {
        coefSum = pNodeA->coef;
        addPolyNodeLast(pReturn, coefSum, pNodeA->degree);
        pNodeA = pNodeA->pLink;
    }

    // ���׽�B�� ���� ���� �ִٸ�, ���� ������ ��� ���׽Ŀ� ���ο� �� �߰�
    while (pNodeB != NULL) {
        coefSum = pNodeB->coef;
        addPolyNodeLast(pReturn, coefSum, pNodeB->degree);
        pNodeB = pNodeB->pLink;
    }

    return pReturn;
}

LinkedList* polySub(LinkedList* pListA, LinkedList* pListB) {
    if (pListA == NULL || pListB == NULL) {
        printf("NULL ���׽��� ���޵Ǿ����ϴ�. polySub()\n");
        return NULL;
    }
    LinkedList* pReturn = createLinkedList();
    if (pReturn == NULL) {
        printf("�޸� �Ҵ� ����, ploySub()\n");
        return NULL;
    }
    ListNode* pNodeA = pListA->headerNode.pLink;
    ListNode* pNodeB = pListB->headerNode.pLink;
    float coefSub = 0;

    // �� ���׽��� ������ ������ �̵��ϸ鼭 �ݺ�
    while (pNodeA != NULL && pNodeB != NULL) {
        int degreeA = pNodeA->degree;
        int degreeB = pNodeB->degree;
        if (degreeA > degreeB) {
            // ���׽� A �� ������ Ŭ��, �״�� �ְ�, ���� ������ �̵�
            coefSub = pNodeA->coef;
            addPolyNodeLast(pReturn, coefSub, degreeA);
            pNodeA = pNodeA->pLink;
        } else if (degreeA == degreeB) {
            // ���׽� A�� B �� ������ ���� ��, ���� �����Ͽ� �ְ�, �Ѵ� �̵�
            coefSub = (pNodeA->coef) - (pNodeB->coef);
            addPolyNodeLast(pReturn, coefSub, degreeA);
            pNodeA = pNodeA->pLink;
            pNodeB = pNodeB->pLink;
        } else {
            // ���׽� B �� ������ ũ��, ���� �����Ͽ� �ְ�, ���� ������ �̵�
            coefSub = -(pNodeB->coef);
            addPolyNodeLast(pReturn, coefSub, degreeB);
            pNodeB = pNodeB->pLink;
        }
    }

    while (pNodeA != NULL) {
        // ���׽� A �� ����������, �״�� �ְ�, NULL ���� �̵�
        coefSub = pNodeA->coef;
        addPolyNodeLast(pReturn, coefSub, pNodeA->degree);
        pNodeA = pNodeA->pLink;
    }

    while (pNodeB != NULL) {
        // ���׽� B �� ���� ������, ��ȣ�� �ٲ� �ְ�, NULL ���� �̵�
        coefSub = -(pNodeB->coef);
        addPolyNodeLast(pReturn, coefSub, pNodeB->degree);
        pNodeB = pNodeB->pLink;
    }
    return pReturn;
}

void displayPolyList(LinkedList* pList) {
    if (pList == NULL) {
        printf("�� ���׽� �Դϴ�.");
    }
    int i = 0;
    for (i = 0 ; i < pList->currentElementCount ; i++) {
        ListNode* pNode = getLinkedListElement(pList, i);
        if (pNode != NULL) {
             printf("%4.1fx^%d", fabs(pNode->coef), pNode->degree);
             if (i == pList->currentElementCount - 1) {
                 printf("\n");
             } else if (pNode->coef >= 0) {
                 printf(" +");
             } else if (pNode->coef < 0) {
                 printf(" -");
             }
        }
    }
}

