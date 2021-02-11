#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

typedef struct ArrayQueueNodeType {
    char data;
} ArrayQueueNode;

typedef struct ArrayQueueType {
    int maxElementCount;        // 최대 원소 개수
    int currentElementCount;    // 현재 원소의 개수
    int front;                  // front 의 위치
    int rear;                   // rear 의 위치
    ArrayQueueNode* pElement;   // 노드 저장을 위한 1차원 배열 포인터
} ArrayQueue;

ArrayQueue* createArrayQueue(int maxElementCount);
int enqueueArrayQueue(ArrayQueue* pQueue, ArrayQueueNode element);
ArrayQueueNode* dequeueArrayQueue(ArrayQueue* pQueue);
ArrayQueueNode* peekArrayQueue(ArrayQueue* pQueue);
void deleteArrayQueue(ArrayQueue* pQueue);
int isArrayQueueFull(ArrayQueue* pQueue);
int isArrayQueueEmpty(ArrayQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_
#define TRUE    1
#define FALSE   0
#endif
