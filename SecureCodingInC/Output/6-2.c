#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int average(int first, ...) {
    int count = 0, sum = 0, i = first;
    va_list list;

    va_start(list, first);
    while (i != -1) {
        sum += i;
        count++;
        i = va_arg(list, int);
    }

    va_end(list);
    return(sum ? (sum / count) : 0);
}

// Main
int main(void) {
    printf("%d", average(1, 3, 100, 34, -1));
}