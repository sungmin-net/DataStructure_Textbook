#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "820p_seqsearch.h"

// 정렬되지 않은 배열의 순차 검색
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

// 오름 차순 정렬 배열의 순차 검색
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

// 배열의 내용을 출력
void showArray(int value[], int size) {
    int i = 0;
    printf("position, key\n");
    printf("-------------\n");
    for (i = 0 ; i < size ; i++) {
        printf("%d, %d\n", i, value[ i ]);
    }
}
