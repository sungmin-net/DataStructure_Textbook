#include <stdio.h>
#include <stdlib.h>

int paritionQuickSort(int value[], int start, int end);
void printArray(int value[], int count);

// 퀵정렬.
void quickSort(int value[], int start, int end) {
    int pivot = 0;
    if (start < end) {
        // 정렬 시작 위치와 끝 위치를 비교하여 퀵 정렬을 수행할지 결정한다.
        // 시작 위치가 끝 위치와 같거나 크다면 퀵 정렬을 종료한다.
        pivot = partitionQuickSort(value, start, end);
        // 분할 정복을 위해 리턴된 피봇 위치를 이용하여 왼쪽 부분 집합과 오른쪽
        // 부분 집합에 대해 각각 함수 quickSort() 를 재귀적으로 호출한다.
        quickSort(value, start, pivot - 1);
        quickSort(value, pivot + 1, end);
    }
}

int partitionQuickSort(int value[], int start, int end) {
    int pivot = 0;
    int temp = 0;
    int left = 0;
    int right = 0;
    right = end;
    pivot = end;    // pivot 의 초기 위치는 right 와 동일하다.

    while (left < right) {
    	// left 가 right 의 왼쪽에 있을 동안 루프를 실행
        while((value[ left ] < value[ pivot ]) && (left < right)) {
        	// left 는 pivot 보다 큰 값을 찾기 위해 오른쪽으로 이동. 단, right
            // 보다 더 오른쪽으로 이동할 수 없다.
            left++;
        }
        while ((value[ right ] >= value[ pivot ]) && (left < right)) {
            // right 는 pivot 보다 더 작은 값을 찾기 위해 왼쪽으로 이동. 단,
            // left 보다 더 왼쪽으로 이동할 수 없다.
            right--;
        }
        if (left < right) {
            // left 와 right 의 위치가 적합하다면, 두 위치의 자료를 교환
            temp = value[ left ];
            value[ left ] = value[ right ];
            value[ right ] = temp;

            printf("start-[%d], end-[%d], pivot-[%d], in-loop, ", start, end,
                    value[ pivot ]);
            printArray(value, end - start + 1);
        }
    }
    // pivot 위치의 값과 right 위치의 값을 교환
    temp = value[ pivot ];
    value[ pivot ] = value[ right ];
    value[ right ] = temp;

    printf("start-[%d], end-[%d], pivot-[%d], out-loop, ", start, end,
            value[ right ]);
    printArray(value, end - start + 1);
    return right; // 최종 pivot 위치인 right 를 반환
}

int main(int argc, char** argv) {
    int values[] = {80, 50, 70, 10, 60, 20, 40, 30};
    printf("Before sort\n");
    printArray(values, 8);

    quickSort(values, 0, 7);

    printf("\nAfter sort\n");
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

