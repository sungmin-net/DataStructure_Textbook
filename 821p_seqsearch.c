#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "820p_seqsearch.h"

// ���ĵ��� ���� �迭�� ���� �˻�
int sequentialSearchNotSorted(int value[], int size, int key) {
    int ret = FAIL;
    int i = 0;

    for (i = 0 ; i < size && value[ i ] != key; i++) {
        // do nothing
    }

    if (i < size) {
        ret = i;
    }
    return ret;
}

// ���� ���� ���� �迭�� ���� �˻�
int sequentialSearchAscendingSorted(int value[], int size, int key) {
    int ret = FAIL;

    int i = 0;
    for (i = 0 ; i < size && value[ i ] < key; i++) {
        // do nothing
    }
    if (i < size && value[ i ] == key) {
        ret = i;
    }
    return ret;
}

// �迭�� ������ ���
void showArray(int value[], int size) {
    int i = 0;
    printf("position, key\n");
    printf("-------------\n");
    for (i = 0 ; i < size ; i++) {
        printf("%d, %d\n", i, value[ i ]);
    }
}
