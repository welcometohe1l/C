#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Functions
int some_func(int a, int b) {
    return a + b;
}

int f_1(int a, int b) {
    printf("%d\n", a + b);
    return a + b;
}

void f_2(int a, int b) {
    printf("%d\n", a * b);
}

// Test
void test_1(int f(int a, int b)) {
    printf("%d", f(10, 20));
}

void test_2(void) {
    for (int i = 0; i < 100; i++) {
        int a = 5;
        printf("%d\n", a++ * a++);
    }
}

void test_3(void) {
    int *p = (int *) malloc(sizeof(int));

    if (!p) 
        printf("Warning!\n");
    else
        printf("Succession!\n");

    p = NULL;

    if (!p) 
        printf("Warning!\n");
    else
        printf("Succession!\n");
}

void test_4(void) {
    float a = 5 / 1.20;
    int b = 5 % 2;

    printf("%f, %d", 5 / 1.20, b);
}

void test_5(void) {
    int a = 10;
    int b = -10;

    if (0 != a % 2)
        printf("It isn't odd\n");
    else
        printf("It's odd\n");

    if (b % 2 != 0)
        printf("It isn't odd\n");
    else
        printf("It's odd\n");
}

void test_6(void) {
    unsigned char c1 = UCHAR_MAX;
    unsigned char c2 = ~c1;
    printf("%hhu - %hhu", c1, c2);
}

void test_7(void) {
    long i = 1;
    i = i << 63;
    printf("%lu\n", sizeof(i) * CHAR_BIT);
    printf("%ld\n", i);
}

void test_8(void) {
    long int i1 = 100;
    long unsigned int i2 = -100;

    printf("%ld, %lu", i1 >> 32, i2++ >> 32);
}

void test_9(void) {
    double i = 2;
    printf("%f", pow(i, 7));
}

void test_10(void) {
    int a = 0;
    int b = -1;

    if ((a += 1) && (b += 2)) {
        printf("%d", a);
    }
}

void test_11(void) {
    int a = 10;
    int *p = &a;

    if (p && *p == 10)
        printf("%d", *p);
}

void test_12(void) {
    double a = 10.3;
    double *p = &a;

    int s = *p + a;
    printf("%d", s);  
}

void test_13(void) {
    int a = 0.3 + 0.5;
    printf("%d", a);
}

void test_14(void) {
    int a = 10;
    a == 10 ? f_2(3, 2) : 1 + 2;
}

void test_15(void) {
    printf("%ld", PTRDIFF_MAX);
}

// Main
int main(int argc, char *argv[]) {
    test_15();
}