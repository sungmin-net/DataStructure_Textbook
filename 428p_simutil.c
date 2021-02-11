#include <stdio.h>
#include <stdlib.h>
#include "422p_simdef.h"
#include "423p_simlinkedqueue.h"
#include "426p_simutil.h"

void insertCustomer(int arrivalTime, int serviceTime, LinkedQueue* pQueue) {
    if (pQueue != NULL) {
        QueueNode node = {0,};
        node.data.status = ARRIVAL;
        node.data.arrivalTime = arrivalTime;
        node.data.serviceTime = serviceTime;
        node.data.startTime = 0;
        node.data.endTime = 0;
        enqueueLinkedQueue(pQueue, node);
    }
}

void processArrival(int currentTime, LinkedQueue* pArrivalQueue,
        LinkedQueue* pWaitQueue) {
    QueueNode* pArrivalNode = NULL;
    int isEmpty = FALSE;
    isEmpty = isLinkedQueueEmpty(pArrivalQueue);
    while (isEmpty == FALSE) {
        pArrivalNode = peekLinkedQueue(pArrivalQueue);

        if (pArrivalNode->data.arrivalTime == currentTime) {
            enqueueLinkedQueue(pWaitQueue, *pArrivalNode);
            printSimCustomer(currentTime, pArrivalNode->data);
            free(dequeueLinkedQueue(pArrivalQueue));
        } else {
            break;
        }
        isEmpty = isLinkedQueueEmpty(pArrivalQueue);
    }
}

QueueNode* processServiceNodeEnd(int currentTime, QueueNode* pServiceNode,
        int* pServiceUserCount, int* pTotalWaitTime) {
    int endTime = 0;
    int waitTime = 0;
    QueueNode* pReturn = NULL;

    if (pServiceNode == NULL || pServiceUserCount == NULL
            || pTotalWaitTime == NULL) {
        return NULL;
    }

    endTime = pServiceNode->data.startTime + pServiceNode->data.serviceTime;
    if (endTime <= currentTime) {
        waitTime = pServiceNode->data.startTime
                - pServiceNode->data.arrivalTime;
        (*pServiceUserCount)++;
        (*pTotalWaitTime) += waitTime;

        pServiceNode->data.status = END;
        pServiceNode->data.endTime = currentTime;
        printSimCustomer(currentTime, pServiceNode->data);

        free(pServiceNode);
        pReturn = NULL;
    } else {
        // do nothing
        pReturn = pServiceNode;
    }
    return pReturn;
}

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue* pWaitQueue) {
    QueueNode* pReturn = NULL;
    QueueNode* pServiceNode = NULL;
    int isEmpty = 0;

    if (pWaitQueue == NULL) {
        return NULL;
    }

    isEmpty = isLinkedQueueEmpty(pWaitQueue);
    if (isEmpty == FALSE) {
        pServiceNode = dequeueLinkedQueue(pWaitQueue);
        if (pServiceNode != NULL) {
            pServiceNode->data.status = START;
            pServiceNode->data.startTime = currentTime;
            printSimCustomer(currentTime, pServiceNode->data);
            pReturn = pServiceNode;
        }
    }
    return pReturn;
}

void printSimCustomer(int currentTime, SimCustomer customer) {
    printf("[%d], ", currentTime);
    switch(customer.status) {
    case ARRIVAL :
        printf("�� ����\n");
        break;
    case START :
        printf("���� ����");
        printf(", ���� : %d, ���ð� : %d\n", customer.arrivalTime,
                (customer.startTime - customer.arrivalTime));
        break;
    case END :
        printf("���� ����");
        printf(", ���� : %d, ���� : %d, ���ð� : %d, ���񽺽ð� : %d\n",
                customer.arrivalTime, customer.startTime,
                customer.startTime - customer.arrivalTime,
                customer.endTime - customer.startTime);
        break;
    }
}

void printWaitQueueStatus(int currentTime, LinkedQueue* pWaitQueue) {
    printf("[%d], ���� ��� �� �� : %d\n", currentTime,
            pWaitQueue->currentElementCount);
}

void printReport(LinkedQueue* pWaitQueue, int serviceUserCount,
        int totalWaitTime) {
    printf("REPORT\n");
    printf("���� �� �� : %d\n", serviceUserCount);
    if (serviceUserCount > 0) {
        printf("��� ��� �ð� : %f\n",
                ((float)totalWaitTime / (float)serviceUserCount));
    }
    printf("���� ��� ���� �� �� : %d\n", pWaitQueue->currentElementCount);
}
