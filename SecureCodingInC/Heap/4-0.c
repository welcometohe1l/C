#include <stdlib.h>
#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>
#include <limits.h>

// Tests
static void test_1(void) {
    int a = -10;
    int vla[a];    // Error
    vla[0] = 10;
}

static void test_2(void) {
    int *i = (int *)malloc(0);
    *i = 10;
    printf("%d", *i);           // wtf???
}

static void test_3(void) {
    size_t max_align = alignof(max_align_t);
    printf("%ld", max_align);
}

// Main
int main(void) {
    test_3();
}
