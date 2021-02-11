#include <stdio.h>

int fib(int n) {
    int ret = 0;
    if (n == 0) {
        ret = 0;
    } else if (n == 1) {
        ret = 1;
    } else {
        ret = fib(n-1) + fib(n-2);
    }
    return ret;
}

int fib_iter(int n) {
    int ret = 0;
    if (n < 2) {
        ret = n;
    } else {
        int i = 0;
        int temp = 0;
        int current = 1;
        int last = 0;
        for (i = 2 ; i <= n ; i++) {
            temp = current;
            current += last;
            last = temp;
        }
        ret = current;
    }
    return ret;
}

int main(int argc, char** argv) {
    printf("fib(5) = %d\n", fib(5));
    printf("fib_iter(5) = %d\n", fib_iter(5));
    return 0;
}


