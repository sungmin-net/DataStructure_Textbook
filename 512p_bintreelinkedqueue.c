#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "509p_bintree.h"
#include "511p_bintreelinkedqueue.h"

LinkedQueue* createLinkedQueue() {
    LinkedQueue* pReturn = NULL;

    pReturn = (LinkedQueue*)malloc(sizeof (LinkedQueue));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof (LinkedQueue));
    } else {
        printf("����, �޸� �Ҵ�, createLinkedQueue()\n");
    }

    return pReturn;
}

int enqueueLinkedQueue(LinkedQueue* pQueue, QueueNode element) {
    int ret = FALSE;
    QueueNode* pNode = NULL;

    if (pQueue != NULL) {
        pNode = (QueueNode*)malloc(sizeof (QueueNode));
        if (pNode != NULL) {
            *pNode = element;       // ���ο� �ڷᰪ ����
            pNode->pLink = NULL;    // ���� ��带 NULL �� ����

            if (isLinkedQueueEmpty(pQueue) == TRUE) {
                // ���� ť�� ���
                pQueue->pFrontNode = pNode;
                pQueue->pRearNode = pNode;
            } else {
                // ������ �ƴ� ť�� ���
                pQueue->pRearNode->pLink = pNode;
                pQueue->pRearNode = pNode;
            }
            pQueue->currentElementCount++;
            ret = TRUE;
        } else {
            printf("����, �޸� �Ҵ�, enqueueLinkedQueue()\n");
        }
    }
    return ret;
}

QueueNode* dequeueLinkedQueue(LinkedQueue* pQueue) {
    QueueNode* pReturn = NULL;
    if (pQueue != NULL) {
        if (isLinkedQueueEmpty(pQueue) == FALSE) {
            pReturn = pQueue->pFrontNode;
            pQueue->pFrontNode = pQueue->pFrontNode->pLink;
            pReturn->pLink = NULL;
            pQueue->currentElementCount--;
            if (isLinkedQueueEmpty(pQueue) == TRUE) {
                pQueue->pRearNode = NULL;
            }
        }
    }
    return pReturn;
}

QueueNode* peekLinkedQueue(LinkedQueue* pQueue) {
    QueueNode* pReturn = NULL;
    if (pQueue != NULL) {
        if (isLinkedQueueEmpty(pQueue) == FALSE) {
            pReturn = pQueue->pFrontNode;
        }
    }
    return pReturn;
}

void deleteLinkedQueue(LinkedQueue* pQueue) {
    QueueNode* pNode = NULL;
    QueueNode* pDelNode = NULL;
    if (pQueue != NULL) {
        pNode = pQueue->pFrontNode;
        while (pNode != NULL) {
            pDelNode = pNode;
            pNode = pNode->pLink;
            free(pDelNode);
        }
        free(pQueue);
    }
}

int isLinkedQueueFull(LinkedQueue* pQueue) {
    int ret = FALSE;
    return ret;
}

int isLinkedQueueEmpty(LinkedQueue* pQueue) {
    int ret = FALSE;
    if (pQueue != NULL) {
        if (pQueue->currentElementCount == 0) {
            ret = TRUE;
        }
    }
    return ret;
}
