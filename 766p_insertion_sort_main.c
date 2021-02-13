#include <stdio.h>
#include <stdlib.h>

void printArray(int value[], int count);

// 삽입 정렬.
void insertionSort(int value[], int count) {
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 1 ; i < count ; i++) { // 두번째 자료부터 전체 자료 개수 만큼 루프
        temp = value[ i ]; // 정렬할 자료의 키(value[i])와 위치(i)로 초기화.
        j = i;
        while ( (j > 0) && value[ j - 1 ] > temp) {
        	// 내부 루프를 돌면서 합입할 위치를 찾는다. 즉, 기존 정렬된 부분
        	// 집합의 제일 뒤 자료부터 시작하여 제일 첫 자료(j > 0)까지 루프를
        	// 돌면서, 정렬할 자료의 키 값(temp)보다 키 값이 작은 자료를 찾을
        	// 때(value[j-1] > temp) 루프가 중단된다.
            value[ j ] = value[ j - 1 ]; // 내부 루프를 돌기 위해 각 단계별로
            							 // 자료를 오른쪽으로 한 칸씩 이동
            j = j - 1; // 인덱스 값을 감소
        }

        value[ j ] = temp;  // 찾은 위치에 정렬할 자료를 삽입

        printf("Step-%d, ", i);
        printArray(value, count);
    }
}


int main(int argc, char** argv) {
    int values[] = {80, 50, 70, 10, 60, 20, 40, 30};
    int* pBuffer = NULL;

    printf("Before sort\n");
    printArray(values, 8);

    insertionSort(values, 8);

    printf("After sort\n");
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
