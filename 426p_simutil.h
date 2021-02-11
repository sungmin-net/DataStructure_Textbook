#ifndef _SIM_UTIL_
#define _SIM_UTIL_

// �� ���� ť�� �� �߰�
void insertCustomer(int arrivalTime, int processTime, LinkedQueue* pQueue);

// �� ���� ó��
void processArrival(int currentTime, LinkedQueue* pArrivalQueue,
        LinkedQueue* pWaitQueue);

// ���� ���� ó��
QueueNode* processServiceNodeStart(int currentTime, LinkedQueue* pWaitQueue);

// ���� ���� ó��
QueueNode* processServiceNodeEnd(int currentTime, QueueNode* pServiceNode,
        int* pServiceUserCount, int* pTotalWaitTime);

// ���� ���¸� ���.
void printSimCustomer(int currentTime, SimCustomer customer);

// ��⿭�� ���¸� ���
void printWaitQueueStatus(int currentTime, LinkedQueue* pWaitQueue);

// ���� �ùķ��̼� ���(���ġ) ���
void printReport(LinkedQueue* pWaitQueue, int serviceCount, int totalWaitTime);
#endif
