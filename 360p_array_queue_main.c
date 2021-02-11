#include <stdio.h>
#include <stdlib.h>

#include "348p_arrayqueue.h"

void displayArrayQueue(ArrayQueue* pQueue) {
    int i = 0;
    if (pQueue != NULL) {
        printf("ť�� ũ�� : %d, ���� ��� ���� : %d\n",
                pQueue->maxElementCount,
                pQueue->currentElementCount);
        for (i = pQueue->front + 1 ; i <= pQueue->rear ; i++) {
            printf("[%d]-[%c]\n", i, pQueue->pElement[i].data);
        }
    }
}

int enqueueArrayQueueChar(ArrayQueue* pQueue, char data) {
    ArrayQueueNode node = {0,};
    node.data = data;
    return enqueueArrayQueue(pQueue, node);
}

int main(int argc, char* argv[]) {
    ArrayQueue* pQueue = NULL;
    ArrayQueueNode* pNode = NULL;

    pQueue = createArrayQueue(4);
    if (pQueue != NULL) {
        // ť �ʱ�ȭ : 'A', 'B', 'C', 'D' �߰�
        enqueueArrayQueueChar(pQueue, 'A');
        enqueueArrayQueueChar(pQueue, 'B');
        enqueueArrayQueueChar(pQueue, 'C');
        enqueueArrayQueueChar(pQueue, 'D');
        displayArrayQueue(pQueue);

        pNode = dequeueArrayQueue(pQueue);
        if (pNode != NULL) {
            printf("Dequeue Value-[%c]\n", pNode->data);
            free(pNode);
        }
        displayArrayQueue(pQueue);

        pNode = peekArrayQueue(pQueue);
        if (pNode != NULL) {
            printf("Peek Value-[%c]\n", pNode->data);
        }
        displayArrayQueue(pQueue);

        enqueueArrayQueueChar(pQueue, 'E');
        displayArrayQueue(pQueue);
    }
    return 0;
}
