#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "375p_linkedqueue.h"

void displayLinkedQueue(LinkedQueue* pQueue) {
    QueueNode* pNode = NULL;
    int i = 0;
    if (pQueue != NULL) {
        printf("현재 노드 개수 : %d\n", pQueue->currentElementCount);
        pNode = pQueue->pFrontNode;
        while (pNode != NULL) {
            printf("[%d]-[%c]\n", i, pNode->data);
            i++;
            pNode = pNode->pLink;
        }
    }
}

void enqueueLinkedQueueChar(LinkedQueue* pQueue, char data) {
    if (pQueue != NULL) {
        QueueNode node;
        node.data = data;
        if (enqueueLinkedQueue(pQueue, node) == FALSE) {
            printf("오류, enqueue 에 실패하였습니다. \n");
        }
    } else {
        printf("오류, Queue 가 NULL 입니다.\n");
        return;
    }
}


int main(int argc, char* argv[]) {
    LinkedQueue* pQueue = NULL;
    QueueNode* pNode = NULL;

    pQueue = createLinkedQueue();
    if (pQueue != NULL) {
        // 큐 초기화 : 'A', 'B', 'C', 'D' 추가
        enqueueLinkedQueueChar(pQueue, 'A');
        enqueueLinkedQueueChar(pQueue, 'B');
        enqueueLinkedQueueChar(pQueue, 'C');
        enqueueLinkedQueueChar(pQueue, 'D');

        displayLinkedQueue(pQueue);

        pNode = dequeueLinkedQueue(pQueue);
        if (pNode != NULL) {
            printf("Dequeue Value-[%c]\n", pNode->data);
            free(pNode);
        }
        displayLinkedQueue(pQueue);

        pNode = peekLinkedQueue(pQueue);
        if (pNode != NULL) {
            printf("Peek Value-[%c]\n", pNode->data);
        }
        displayLinkedQueue(pQueue);

        enqueueLinkedQueueChar(pQueue, 'E');
        displayLinkedQueue(pQueue);
    }
    return 0;
}
