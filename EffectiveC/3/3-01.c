#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>


// Functions
unsigned int abs_1(int i) {
    return (i >= 0) ? i : -(unsigned)i;
}

// Tests
void test_1(void) {
    signed char a = -127;
    for (int i = sizeof(a) * 8 - 1; i >= 0; i--)
        printf("%d", (a >> i) & 1);
    printf(" - %d\n", a);
}

void test_2(void) {
    printf("%u", abs_1(INT_MIN));
}

void test_3(void) {
    unsigned i = -1;                // UINT_MAX
    printf("%u", i);
}

void test_4(void) {
    unsigned i = UINT_MAX + 1;      // 0 (well-defined behavior)
    printf("%u", i);
}

void test_5(void) {
    signed i = INT_MAX + 1;         // undefined behavior
    printf("%u", i);
}

void test_6(void) {
    long l = 2;
    int b = 10;
    int i = b + l;
    printf("%d", i);
}

void test_7(void) {
    unsigned int i = UINT_MAX;
    char c = -1;
    if (c == i)
        printf("Hello!");
}

void test_8(void) {
    long double d = 0.1e-10L;
    printf("%Lf", d);
}

void test_9(void) {
    long double d = 0.3f;
    printf("%Lf", d);
}

void test_10(void) {
    char a = 'a';
    for (int i = sizeof(char) * 8 - 1; i >= 0; i--)
        printf("%d", (a >> i) & 1);
}

void test_11(void) {
    double a = -10;
    double b = a / 0;
    printf("%f", b);
}

void test_12(void) {
    float f = 1e-37f;
    switch (__fpclassifyf(f)) {
        case FP_INFINITE:   printf("Inf"); break;
        case FP_NAN:        printf("NaN"); break;
        case FP_NORMAL:     printf("Normal"); break;
        case FP_SUBNORMAL:  printf("Subnormal"); break;
        case FP_ZERO:       printf("Zero"); break;
        default:            printf("unknown"); break;
    }
    printf("\n%f", f);
}

void test_13(void) {
    printf("%f\n", FLT_MIN);
    printf("%f\n", FLT_MAX);
}

void test_14(void) {
    int s1 = INT_MAX;
    int s2 = 1;
    long result = (long)s1 + s2;
    printf("%ld", result);
}

void test_15(void) {
    int i = INT_MAX;
    short s = i;
    printf("%d", s);
}

// Main
int main(void) {
    test_15(); 
}