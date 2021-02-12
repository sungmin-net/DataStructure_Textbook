#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "548p_arrayheap.h"

ArrayMaxHeap* createArrayMaxHeap(int maxElementCount) {
    ArrayMaxHeap* pReturn = NULL;
    if (maxElementCount > 0) {
        pReturn = (ArrayMaxHeap*)malloc(sizeof(ArrayMaxHeap));
        if (pReturn != NULL) {
            pReturn->maxElementCount = maxElementCount;
            pReturn->currentElementCount = 0;

            pReturn->pElement = (HeapNode*)malloc(sizeof(HeapNode)
                    * (maxElementCount + 1));
            if (pReturn->pElement == NULL) {
                printf("오류, 2번째 메모리 할당, createArrayList()\n");
                free(pReturn);
                return NULL;
            }
            memset(pReturn->pElement, 0, sizeof(HeapNode)
                    * (maxElementCount + 1));
        } else {
            printf("오류, 메모리 할당, createArrayList()\n");
        }
    } else {
        printf("최대 원소 개수는 0보다 커야 합니다.\n");
    }
    return pReturn;
}

void insertArrayMaxHeapNode(ArrayMaxHeap* pHeap, HeapNode element) {
    int i = 0;
    if (pHeap != NULL) {
        if (pHeap->currentElementCount == pHeap->maxElementCount) {
            printf("오류, 힙이 가득 찼습니다.[%d], insertArrayMaxHeap()\n",
                    pHeap->maxElementCount);
            return;
        }

        pHeap->currentElementCount++;
        i = pHeap->currentElementCount;

        while((i != 1) && (element.key > pHeap->pElement[i/2].key)) {
            // 부모 노드와 키 값 비교와 이동
            pHeap->pElement[i] = pHeap->pElement[i/2];
            i /= 2;
        }
        pHeap->pElement[i] = element;
    }
}

HeapNode* extractArrayMaxHeapNode(ArrayMaxHeap* pHeap) {
    HeapNode* pReturn = NULL;
    HeapNode* pTemp = NULL;

    int i = 0;
    int parent = 0;
    int child = 0;

    if (pHeap != NULL && pHeap->currentElementCount > 0) {
        pReturn = (HeapNode*)malloc(sizeof(HeapNode));
        if (pReturn == NULL) {
            printf("오류, 메모리 할당, extractArrayMaxHeapNode()\n");
            return NULL;
        }
        *pReturn = pHeap->pElement[ 1 ];

        i = pHeap->currentElementCount;
        pTemp = &(pHeap->pElement[ i ]);
        pHeap->currentElementCount--;

        parent = 1; // 루프가 시작되는 곳은 루트 노드(인덱스1)와
        child = 2;  // 루프 노드의 왼쪽 자식 노드(인덱스2)
        while(child <= pHeap->currentElementCount) {
        	// 힙의 제일 마지막 위치에 있는 노드를 만날 때까지 루프
            if ((child < pHeap->currentElementCount) &&
                    pHeap->pElement[child].key < pHeap->pElement[child+1].key) {
                // 왼쪽 자식 노드보다 오른쪽 자식 노드의 키 값이 더 크다면,
                // 오른쪽 자식 노드가 비교 대상이 되도록 위치 인덱스 child 를
                // 수정한다.
                child ++;
            }
            if (pTemp->key >= pHeap->pElement[ child ].key) {
                // 앞서 설정한 히프의 제일 마지막 노드와 현재 노드의 키 값을
                // 비교. 만약, 마지막 노드의 키 값이 현재 노드 보다 더 크거나
                // 같다면, 루프를 빠져 나온다. 바로 이 위치에서 삽입하면 된다.
                break;
            }
            // 만약 그렇지 않다면, 현재 노드를 부모 노드의 위치로 한칸
            // 이동시키고, 다시 아래 레벨로 이동
            pHeap->pElement[ parent ] = pHeap->pElement[ child ];
            parent = child;
            child *= 2;
        } // end of while
        pHeap->pElement[ parent ] = *pTemp;
    }
    return pReturn;
}


void deleteArrayMaxHeap(ArrayMaxHeap* pHeap) {
    if (pHeap != NULL) {
        if (pHeap->pElement != NULL) {
            free(pHeap->pElement);
        }
        free(pHeap);
    }
}
