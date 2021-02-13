#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct HeapElementType {
    int key;
    char element;
} HeapNode;

typedef struct ArrayHeapType {
    int maxElementCount;        // 최대 노드 개수
    int currentElementCount;    // 현재 노드 개수
    HeapNode* pElement;
} ArrayHeap;

// 공통
ArrayHeap* createArrayHeap(int maxElementCount);
void deleteArrayHeap(ArrayHeap* pArrayHeap);

// 최대 heap
void insertArrayMaxHeapNode(ArrayHeap* pArrayHeap, HeapNode element);
HeapNode* extractArrayMaxHeapNode(ArrayHeap* pArrayHeap);

// 최소 heap
void insertArrayMinHeapNode(ArrayHeap* pArrayHeap, HeapNode element);
HeapNode* extractArrayMinHeapNode(ArrayHeap* pArrayHeap);

// heap 출력
void displayArrayHeap(ArrayHeap* pList);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE 1
#define FALSE 0

#endif
