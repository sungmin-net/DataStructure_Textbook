#include <stdio.h>
#include <string.h>

void main(int arc, char **argv) {
	int i = 0, size = 0;
	int key1[3] = {3, 5, 7};
	int key2[3] = {0,};

	char string1[] = "value";
	char string2[100] = {0,};

	key2[0] = 3;
	key2[1] = 5;
	key2[2] = 7;

	size = sizeof(key1) / sizeof(int);

	printf("key1�� ������ ���� : %d\n", size);
	for(i = 0 ; i < size ; i++) {
		printf("%d->%d\n", i, key1[i]);
	}

	size = sizeof(key2) / sizeof(int);
	printf("key2�� ������ ���� : %d\n", size);
	for(i = 0 ; i < size ; i++) {
		printf("%d->%d\n", i, key2[i]);
	}

	size = sizeof(string1) / sizeof(char);
	printf("string1�� ������ ���� : %d\n", size);
	printf("string1 : %s\n", string1);

	strcpy(string2, "strcpy�� �����ϱ�");
	size = sizeof(string2) / sizeof(char);
	printf("string2�� ������ ���� : %d\n", size);
	printf("string2 : %s\n", string2);

}
