#ifndef _LINKED_CUEUE_
#define _LINKED_QUEUE_

typedef struct QueueNodeType {
    char data;
    struct QueueNodeType* pLink;
} QueueNode;

typedef struct LinkedQueueType {
    int currentElementCount;    // 현재 원소의 개수
    QueueNode* pFrontNode;      // Front 노드의 포인터
    QueueNode* pRearNode;       // Rear 노드의 포인터
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int enqueueLinkedQueue(LinkedQueue* pQueue, QueueNode element);
QueueNode* dequeueLinkedQueue(LinkedQueue* pQueue);
QueueNode* peekLinkedQueue(LinkedQueue* pQueue);
void deleteLinkedQueue(LinkedQueue* pQueue);
int isLinkedQueueFull(LinkedQueue* pQueue);
int isLinkedQueueEmpty(LinkedQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE    1
#define FALSE   0

#endif

