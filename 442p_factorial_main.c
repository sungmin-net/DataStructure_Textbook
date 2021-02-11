#include <stdio.h>

int factorial(int n) {
    int ret = 0;
    if (n <= 1) {
        ret = 1;
    } else {
        ret = n * factorial(n - 1);
    }
    return ret;
}


int factorial_iter(int n) {
    int ret = 1;
    int i = 1;
    for ( i = n ; i > 1 ; i--) {
        ret = ret * i;
    }
    return ret;
}

void main(int argc, char** argv) {
    int input_value = 3;
    int result = 0;

    result = factorial(input_value);
    printf("%d! = %d\n", input_value, result);
}
