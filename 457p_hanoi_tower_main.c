#include <stdio.h>

void hanoi_tower(int n, char from, char temp, char to) {
    if (n == 1) {
        printf("���� 1�� %c���� %c�� �Ű���ϴ�.\n", from, to);
    } else {
        hanoi_tower(n-1, from, to, temp);
        printf("���� %d�� %c���� %c�� �Ű���ϴ�.\n", n, from, to);
        hanoi_tower(n-1, temp, from, to);
    }
}

void main(int argc, char** argv) {
    char from = 'A';
    char temp = 'B';
    char to = 'C';

    hanoi_tower(4, from, temp, to);
}