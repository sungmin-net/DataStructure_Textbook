#include <stdio.h>
#include <stdlib.h>

#include "789p_linkedqueue.h"

void printArray(int value[], int count);

void radixSort(int value[], int count, int radix, int digit) {
    int i = 0;
    int bucket = 0;
    int d = 0;
    int factor = 1;
    LinkedQueue** ppQueue = NULL;
    QueueNode node = {0,};
    // ���(radix) ���� ��ŭ ���� ť�� �����ϱ� ���� �޸𸮸� �Ҵ��ϰ�, ����
    ppQueue = (LinkedQueue**)malloc(sizeof(LinkedQueue*) * radix);
    if (ppQueue == NULL) {
        printf("����, �޸� �Ҵ�, radixSort()\n");
        return;
    }
    // �� ����� �ش��ϴ� ��Ŷ(���� ť)�� ����. ��, ��Ŷ�� �����ϴ� ���߿�
    // ������ �߻����� ���, �̹� �Ҵ�� �޸𸮸� �����Ѵ�.
    for (bucket = 0 ; bucket < radix ; bucket++) {
        ppQueue[ bucket ] = createLinkedQueue();
        if (ppQueue[ bucket ] == NULL) {
            for (i = 0 ; i < bucket - 1 ; i++) {
                if (ppQueue[ i ] != NULL) {
                    deleteLinkedQueue(ppQueue[ i ]);
                }
            }
            free(ppQueue);
            printf("����, createLinkedQueue() in radixSort()\n");
            return;
        }
    }

    // �� �ڸ������� ������ ���鼭 �й� �� ���� ������ ����
    for (d = 0 ; d < digit ; d++) {
        for (i = 0 ; i < count ; i++) {
            node.data = value[ i ];
            enqueueLinkedQueue(ppQueue[ (value[ i ] / factor) % radix ], node);
        }
        i = 0;
        // �ڷ��� �й谡 �Ϸ�Ǹ� �� ��Ŷ���� ������ ���鼭 �ڷḦ ���� ����
        for (bucket = 0 ; bucket < radix ; bucket++) {
            while (isLinkedQueueEmpty(ppQueue[ bucket ]) == FALSE) {
                QueueNode* pNode = dequeueLinkedQueue(ppQueue[ bucket ]);
                if (pNode != NULL) {
                    value[ i ] = pNode->data;
                    i++;
                    free(pNode);
                }
            }
        }

        printf("\nDigit-%d, ", factor);
        printArray(value, count);
        factor = factor * radix;
    }

    // �Ҵ�� ��Ŷ(���� ť)�� �޸𸮸� ����. ��, ť���� �迭�̱� ������ ������
    // ���� ������ ��Ŷ�� �޸� ������Ű��, ��ü �޸𸮸� ����
    for (bucket = 0 ; bucket < radix ; bucket++) {
        deleteLinkedQueue(ppQueue[ bucket ]);
    }
    free(ppQueue);
}

int main(int argc, char** argv) {
    int values[] = {42, 60, 75, 81, 10, 23, 12, 18};
    printf("Before Sort\n");
    printArray(values, 8);

    radixSort(values, 8, 10, 2);
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

