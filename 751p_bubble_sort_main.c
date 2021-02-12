#include <stdio.h>
#include <stdlib.h>

void printArray(int value[], int count);

// ��������
void bubbleSort(int value[], int count) {
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = count - 1 ; i >= 0 ; i--) {
    	// 전체 개수보다 1 적은 회수(count - 1)만큼 루프를 돈다. 정렬의 마지막에
    	// 남는 자료는 최대 자료이기 때문에 추가 정렬이 필요 없다.
        for (j = 0 ; j < i ; j++) {
        	// 정렬되지 않은 자료들을 대상으로 이웃한 두 자료를 비교하여
        	// 앞의 자료가 뒤의 자료보다 크면 값을 교환
            if (value[ j ] > value[ j + 1 ]) {
                temp = value[ j ];
                value[ j ] = value[ j + 1 ];
                value[ j + 1 ] = temp;
            }
        }
        printf("Step-%d, ", count - i);
        printArray(value, count);
    }
}

void printArray(int value[], int count) {
    int i = 0;
    for (i = 0 ; i < count ; i++) {
        printf("%d ", value[ i ]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int values[] = {80, 50, 70, 10, 60, 20, 40, 30};

    printf("Before Sort\n");
    printArray(values, 8);

    bubbleSort(values, 8);

    printf("\nAfter Sort\n");
    printArray(values, 8);

    return 0;
}
