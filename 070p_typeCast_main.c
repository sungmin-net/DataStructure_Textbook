#include <stdio.h>

void main(int arc, char** argv) {
	int i = 100;
	float f = 101.12f;
	i = (int)f;
	printf("%d, %3.2f\n", i, f);
}
