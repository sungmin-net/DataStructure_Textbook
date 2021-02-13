#include <stdio.h>
#include <stdlib.h>

void printArray(int value[], int count);
void mergeSortInternal(int value[], int buffer[], int start, int middle,
        int end);

// 병합 정렬
void mergeSort(int value[], int buffer[], int start, int end) {
    int middle = 0;
    if (start < end) {
        middle = (start + end) / 2;

        // 왼쪽 부분 집합과 오른쪽 부분 집합에 대해 순환적으로 병합 정렬 실행
        mergeSort(value, buffer, start, middle);
        mergeSort(value, buffer, middle + 1, end);

        // 병합 정렬이 완료된 두 개의 부분 집합의 병합. 이 때 병합을 위해
        // 배열의 크기 만큼 추가적인 메모리 공간이 필요하며, 이를 위해 버퍼를
        // 전달. 이 버터는 외부에서 전달받는다.
        mergeSortInternal(value, buffer, start, middle, end);

    }
}

void mergeSortInternal(int value[], int buffer[], int start, int middle,
        int end) {
    int i = 0; // 첫 번째 부분 집합의 원소를 가리키는 인덱스
    int j = 0; // 두 번째 부분 집합의 원소를 가리키는 인덱스
    int k = 0; // 결과 버퍼의 현재 위치를 가리키는 인덱스
    int t = 0;
    i = start;
    j = middle + 1;
    k = start;

    while (i <= middle && j <= end) {
        // 두 개의 부분 집합(start, middle) 및 (middle + 1, end) 를 대상으로
        // 루프를 돌면서 각 부분 집합 원소의 키 값을 비교
        if (value[ i ] <= value[ j ]) {
            // 만약 키 값이 작다면 해당 원소의 키 값을 복사
            buffer[ k ] = value[ i ];
            i++;
        } else {
            buffer[ k ] = value[ j ];
            j++;
        }
        k++;
    }
    // 위 루프를 빠져 나온 것은 두 개의 부분 집합 중 하나의 부분 집합이 모두
    // 복사되었다는 의미이므로, 원소가 남은 다른 부분 집합의 자료들을 복사
    // 해주어야 한다. 아래는 어느 부분 집합의 원소가 남았는 지 판단한 다음
    // 해당 부분 집합의 남은 원소들을 결과 버퍼에 복사한다.
    if (i > middle) {
        for (t = j ; t <= end ; t++, k++) {
            buffer[ k ] = value[ t ];
        }
    } else {
        for (t = i ; t <= middle ; t++, k++) {
            buffer[ k ] = value[ t ];
        }
    }

    // 정렬 결과가 저장된 버퍼의 내용을 최종적으로 복사한다.
    for (t = start ; t <= end ; t++) {
        value[ t ] = buffer[ t ];
    }

    printf("start-%d, middle-%d, end-%d, ", start, middle, end);
    for (t = start ; t <= end ; t++) {
        printf("%d ", value[ t ]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int values[] = {80, 50, 70, 10, 60, 20, 40, 30};
    int* pBuffer = NULL;

    printf("Before Sort\n");
    printArray(values, 8);

    pBuffer = (int*)malloc(sizeof(int) * 8);
    if (pBuffer != NULL) {
        mergeSort(values, pBuffer, 0, 7);
        free(pBuffer);
    }

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



