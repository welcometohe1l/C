#define SOME 1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Tests
void test_1(void) {
    #ifdef SOME
    puts("Hello, world!");
    #else
    #error SOME is not defined
    #endif
}

void test_2(void) {
    printf("%ld\n%s", __STDC_VERSION__, __DATE__);
}

// Main
int main(void) {
    test_2();
}