#include <stdio.h>
#include <stdlib.h>

#include "799p_arrayheap.h"

void printArrayHeap(int value[], int count);

// 힙정렬
void heapSort(int value[], int count) {
    int i = 0;
    ArrayHeap* pHeap = NULL;

    pHeap = createArrayHeap(8); // 힙을 생성하고 이를 검증한다.
    if (pHeap != NULL) {
        HeapNode node;
        // 입력받은 자료를 최소 입에 삽입
        for (i = 0 ; i < count ; i++) {
            node.key = value[ i ];
            insertArrayMinHeapNode(pHeap, node);
        }
        // 입력 자료의 개수만큼 최소 입에서 추출 연산. 예제는 자료 개수가 8개
        // 이기때문에 8번 추출 연산 실행
        for (i = 0 ; i < count ; i++) {
            HeapNode* pNode = extractArrayMinHeapNode(pHeap);

            if (pNode != NULL) {
                value[ i ] = pNode->key; // 최소 힙에서 반환받은 자료를 저장
                free(pNode); // 최소 힙에서 반환받은 노드를 메모리 해제
            }
        }
        // 최소 힙을 삭제
        deleteArrayHeap(pHeap);
    } else {
        printf("오류, heapSort()\n");
        return;
    }
}

int main(int argc, char** argv) {
    int values[] = {10, 50, 70, 80, 60, 20, 40, 30};
    printf("Before Sort\n");
    printArray(values, 8);

    heapSort(values, 8);

    printf("\nAfter Sort\n");
    printArray(values, 8);
    return 0;
}

void printArray(int value[], int count) {
    int i = 0;
    for (i = 0 ; i < count ; i++) {
        printf("%d ", value[ i ]);
    }
}
