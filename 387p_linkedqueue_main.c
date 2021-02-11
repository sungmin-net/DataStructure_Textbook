#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "375p_linkedqueue.h"

void displayLinkedQueue(LinkedQueue* pQueue) {
    QueueNode* pNode = NULL;
    int i = 0;
    if (pQueue != NULL) {
        printf("���� ��� ���� : %d\n", pQueue->currentElementCount);
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
            printf("����, enqueue �� �����Ͽ����ϴ�. \n");
        }
    } else {
        printf("����, Queue �� NULL �Դϴ�.\n");
        return;
    }
}


int main(int argc, char* argv[]) {
    LinkedQueue* pQueue = NULL;
    QueueNode* pNode = NULL;

    pQueue = createLinkedQueue();
    if (pQueue != NULL) {
        // ť �ʱ�ȭ : 'A', 'B', 'C', 'D' �߰�
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
