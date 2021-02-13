#include <stdio.h>
#include <stdlib.h>

void shellInsertionSort(int value[], int start, int end, int interval);
void printArray(int value[], int count);

// 쉘 정렬
void shellSort(int value[], int count) {
    int i = 0;
    int interval = 0;

    interval = count / 2;  // 초기 간격은 자료 개수의 1/2로 설정
    while (interval >= 1) { // 간격이 1이 될 때까지 루프
        for (i = 0 ; i < interval ; i++) {
        	// 주어진 간격으로 삽입 정렬.
            shellInsertionSort(value, i, count - 1, interval);
        }
        printf("Interval - %d\n", interval);
        printArray(value, count);

        interval = interval / 2; // 기존의 간격을 1/2로 줄인다
    }
}

void shellInsertionSort(int value[], int start, int end, int interval) {
    int i = 0;
    int item = 0;
    int index = 0;

    for (i = start + interval ; i <= end ; i = i + interval) {
        // 정렬의 범위가 start + interval 부터 end 까지.
        item = value[ i ];  // 삽입정렬의 키와 위치 초기화
        index = i - interval;
        while ((index >= start) && item < value[ index ]) {
            // 내부 루프를 돌면서 삽입할 위치를 찾는다. 기존 정렬된 부분 집합의
            // 제일 뒷자리로부터 시작하여 제일 첫 자료(index >= start)까지
            // 루프를 돌면서, 정렬할 자료의 키 값(item) 보다 키 값이 작은
            // 자료(item < value[ index ])를 찾을 때 루프가 종료된다. 단,
            // 내부 루프를 돌기 위해 각 단계별로 자료를 오른쪽으로 간격만큼
            // 이동시키고, 인덱스 값을 간격 만큼 감소시킨다.
            value[ index + interval ] = value[ index ];
            index = index - interval;
        }
        value[ index + interval ] = item; // 찾은 위치에 정렬할 값을 삽입
    }
}

int main(int argc, char** argv) {
    int values[] = {80, 50, 70, 10, 60, 20, 40, 30};

    printf("Before Sort\n");
    printArray(values, 8);

    shellSort(values, 8);

    printf("After Sort\n");
    printArray(values, 8);

    return 0;
}

void printArray(int value[], int count) {
    int i = 0;
    for (i = 0 ; i < count ; i++) {
        printf("%d ", value[ i ]);
    }
    printf("\n");
}
