#include <stdio.h>
#include <limits.h>

static void print_help(void) {
    printf("%s", "primetest num1 [num2 num3 ... numN]\n\n");
    printf("%s", "Test positive integers for primality. Supports testing");
    printf("%s [2-%llu].\n", "numbers in the range", ULLONG_MAX);
}