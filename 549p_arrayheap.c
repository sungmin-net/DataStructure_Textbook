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
                printf("����, 2��° �޸� �Ҵ�, createArrayList()\n");
                free(pReturn);
                return NULL;
            }
            memset(pReturn->pElement, 0, sizeof(HeapNode)
                    * (maxElementCount + 1));
        } else {
            printf("����, �޸� �Ҵ�, createArrayList()\n");
        }
    } else {
        printf("�ִ� ���� ������ 0���� Ŀ�� �մϴ�.\n");
    }
    return pReturn;
}

void insertArrayMaxHeapNode(ArrayMaxHeap* pHeap, HeapNode element) {
    int i = 0;
    if (pHeap != NULL) {
        if (pHeap->currentElementCount == pHeap->maxElementCount) {
            printf("����, ���� ���� á���ϴ�.[%d], insertArrayMaxHeap()\n",
                    pHeap->maxElementCount);
            return;
        }

        pHeap->currentElementCount++;
        i = pHeap->currentElementCount;

        while((i != 1) && (element.key > pHeap->pElement[i/2].key)) {
            // �θ� ���� Ű �� �񱳿� �̵�
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
            printf("����, �޸� �Ҵ�, bringArrayMaxHeapNode()\n");
            return NULL;
        }
        *pReturn = pHeap->pElement[ 1 ];

        i = pHeap->currentElementCount;
        pTemp = &(pHeap->pElement[ i ]);
        pHeap->currentElementCount--;

        parent = 1; // ������ ���۵Ǵ� ���� ��Ʈ ���(�ε���1)��
        child = 2;  // ���� ����� ���� �ڽ� ���(�ε���2)
        while(child <= pHeap->currentElementCount) {
            // ���� ���� ������ ��ġ�� �ִ� ��带 ���� ������ ����
            if ((child < pHeap->currentElementCount) &&
                    pHeap->pElement[child].key < pHeap->pElement[child+1].key) {
                // ���� �ڽ� ��庸�� ������ �ڽ� ����� Ű ���� �� ũ�ٸ�,
                // ������ �ڽ� ��尡 �� ����� �ǵ��� ��ġ �ε��� child ��
                // �����Ѵ�.
                child ++;
            }
            if (pTemp->key >= pHeap->pElement[ child ].key) {
                // �ռ� ������ ������ ���� ������ ���� ���� ����� Ű ����
                // ��. ����, ������ ����� Ű ���� ���� ��� ���� �� ũ�ų�
                // ���ٸ�, ������ ���� ���´�. �ٷ� �� ��ġ���� �����ϸ� �ȴ�.
                break;
            }
            // ���� �׷��� �ʴٸ�, ���� ��带 �θ� ����� ��ġ�� ��ĭ
            // �̵���Ű��, �ٽ� �Ʒ� ������ �̵�
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
