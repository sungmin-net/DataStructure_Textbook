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
        printf("메모리 할당 오류, polyAdd()\n");
        return NULL;
    }
    ListNode* pNodeA = pListA->headerNode.pLink;
    ListNode* pNodeB = pListB->headerNode.pLink;
    float coefSum = 0;
    // 두 다항식이 마지막 노드까지 이동하면서 반복
    while (pNodeA != NULL && pNodeB != NULL) {
        int degreeA = pNodeA->degree;
        int degreeB = pNodeB->degree;
        if (degreeA > degreeB) {
            // A의 차수 > B의 차수인 경우, 다항식 A의 항을 이용하여
            // 결과 다항식에 새로운 항을 추가
            coefSum = pNodeA->coef;
            addPolyNodeLast(pReturn, coefSum, degreeA);
            // 다항식 A 의 다음 항으로 이동
            pNodeA = pNodeA->pLink;
        } else if (degreeA == degreeB) {
            // A의 차수 == B 의 차수인 경우, 다항식 A와 B 의 계수를 더하여
            // 결과 다항식에 새로운 항을 추가
            coefSum = pNodeA->coef + pNodeB->coef;
            addPolyNodeLast(pReturn, coefSum, degreeA);
            // 다항식 A와 B 모두 다음 항으로 이동
            pNodeA = pNodeA->pLink;
            pNodeB = pNodeB->pLink;
        } else {
            // A의 차수 < B 의 차수
            // 다항식 B의 항을 이용하여 결과 다항식에 새로운 항을 추가
            // 다항식 B의 다음 항으로 이동
            coefSum = pNodeB->coef;
            addPolyNodeLast(pReturn, coefSum, degreeB);
            pNodeB = pNodeB->pLink;
        }
    }

    // 다항식A에 남은 항이 있다면, 남은 항으로 결과 다항식에 새로운 항 추가
    while (pNodeA != NULL) {
        coefSum = pNodeA->coef;
        addPolyNodeLast(pReturn, coefSum, pNodeA->degree);
        pNodeA = pNodeA->pLink;
    }

    // 다항식B에 남은 항이 있다면, 남은 항으로 결과 다항식에 새로운 항 추가
    while (pNodeB != NULL) {
        coefSum = pNodeB->coef;
        addPolyNodeLast(pReturn, coefSum, pNodeB->degree);
        pNodeB = pNodeB->pLink;
    }

    return pReturn;
}

LinkedList* polySub(LinkedList* pListA, LinkedList* pListB) {
    if (pListA == NULL || pListB == NULL) {
        printf("NULL 다항식이 전달되었습니다. polySub()\n");
        return NULL;
    }
    LinkedList* pReturn = createLinkedList();
    if (pReturn == NULL) {
        printf("메모리 할당 오류, ploySub()\n");
        return NULL;
    }
    ListNode* pNodeA = pListA->headerNode.pLink;
    ListNode* pNodeB = pListB->headerNode.pLink;
    float coefSub = 0;

    // 두 다항식이 마지막 노드까지 이동하면서 반복
    while (pNodeA != NULL && pNodeB != NULL) {
        int degreeA = pNodeA->degree;
        int degreeB = pNodeB->degree;
        if (degreeA > degreeB) {
            // 다항식 A 의 차수가 클때, 그대로 넣고, 다음 차수로 이동
            coefSub = pNodeA->coef;
            addPolyNodeLast(pReturn, coefSub, degreeA);
            pNodeA = pNodeA->pLink;
        } else if (degreeA == degreeB) {
            // 다항식 A와 B 의 차수가 같을 때, 빼기 연산하여 넣고, 둘다 이동
            coefSub = (pNodeA->coef) - (pNodeB->coef);
            addPolyNodeLast(pReturn, coefSub, degreeA);
            pNodeA = pNodeA->pLink;
            pNodeB = pNodeB->pLink;
        } else {
            // 다항식 B 의 차수가 크면, 빼기 연산하여 넣고, 다음 차수로 이동
            coefSub = -(pNodeB->coef);
            addPolyNodeLast(pReturn, coefSub, degreeB);
            pNodeB = pNodeB->pLink;
        }
    }

    while (pNodeA != NULL) {
        // 다항식 A 가 남아있으면, 그대로 넣고, NULL 까지 이동
        coefSub = pNodeA->coef;
        addPolyNodeLast(pReturn, coefSub, pNodeA->degree);
        pNodeA = pNodeA->pLink;
    }

    while (pNodeB != NULL) {
        // 다항식 B 가 남아 있으면, 부호를 바꿔 넣고, NULL 까지 이동
        coefSub = -(pNodeB->coef);
        addPolyNodeLast(pReturn, coefSub, pNodeB->degree);
        pNodeB = pNodeB->pLink;
    }
    return pReturn;
}

void displayPolyList(LinkedList* pList) {
    if (pList == NULL) {
        printf("빈 다항식 입니다.");
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

