#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "789p_linkedqueue.h"

LinkedQueue* createLinkedQueue() {
    LinkedQueue* pReturn = NULL;

    pReturn = (LinkedQueue*)malloc(sizeof (LinkedQueue));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof (LinkedQueue));
    } else {
        printf("오류, 메모리 할당, createLinkedQueue()\n");
    }

    return pReturn;
}

int enqueueLinkedQueue(LinkedQueue* pQueue, QueueNode element) {
    int ret = FALSE;
    QueueNode* pNode = NULL;

    if (pQueue != NULL) {
        pNode = (QueueNode*)malloc(sizeof (QueueNode));
        if (pNode != NULL) {
            *pNode = element;       // 새로운 자료값 대입
            pNode->pLink = NULL;    // 다음 노드를 NULL 로 지정
            if (isLinkedQueueEmpty(pQueue) == TRUE) {
            	// 공백 큐의 경우
                pQueue->pFrontNode = pNode;
                pQueue->pRearNode = pNode;
            } else {
            	// 공백이 아닌 큐의 경우
                pQueue->pRearNode->pLink = pNode;
                pQueue->pRearNode = pNode;
            }
            pQueue->currentElementCount++;
            ret = TRUE;
        } else {
            printf("오류, 메모리 할당, enqueueLinkedQueue()\n");
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
