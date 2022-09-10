#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdalign.h>

// Data
typedef struct {
    short int number;
    short int region;
    char c1;
    char c2;
    char c3;
} Usual;

typedef struct {
    unsigned int number: 10;
    unsigned int region: 10;
    unsigned int c1: 4;          // index one of the available letter 
    unsigned int c2: 4;          // from 0 to 12 corresponding to 
    unsigned int c3: 4;          // А, Б, В, Г, Д, Е, Ж, З, И, К, Л, М
} Unusual;

typedef struct {
    int i;
    double d;
    char c;
} Test;

int a = 10;
Usual usual = {198, 10, 1, 2, 3};
Unusual unusual = {198, 10, 1, 2, 3};

// Define
#define SIZEOF(x) printf("size: %lu\n", sizeof(x));
#define ALIGNOF(x) printf("align: %lu\n", alignof(x));
#define OFFSETOF(x, y) printf("offset: %lu\n", offsetof(x, y));

// Functions
int *static_sd(void) {
    static int a = 10;
    return &a;
}

int *automatic_sd(void) {
    int a = 10;
    return &a;
}

// Tests
void test_1(void) {
    int a1 = a;
    int a2 = *static_sd();
    int a3 = *automatic_sd();

    printf("%d - %d - %d\n", a1, a2, a3);
    printf("%d - %d - %d\n", a1, a2, a3);
}

void test_2(int a, int *pa) {
    printf("%p - %p - %p", &a, pa, &pa);
}

void test_3(void) {
    int a = 0;
    
    start:

    a++;
    printf("%d\n", a);

    if (a < 10) 
        goto start;
}

void test_4(void) {
    typedef struct {
        double d;
        char c;
    } s;

    printf("offset: %lu\n", offsetof(s, d));
    printf("align: %lu, size: %lu", alignof(s), sizeof(s));
}

void test_5(void) {
    typedef struct {
        int i;
        char c;
    } Inner;

    typedef struct {
        Inner i1;
        Inner i2;
        char c;
    } Outer;

    SIZEOF(Inner);
    ALIGNOF(Inner);
}

void test_6(void) {
    unusual.c1 = 1;
    unusual.c2 = 2;
    unusual.c3 = 3;

    unusual.c1 = unusual.c2 + 1;
    unusual.c2 = unusual.c3 + 1;
    unusual.c3 = unusual.c1 + 1;

    unusual.region = 10;
    unusual.number = 20;

    unusual.region = unusual.number + 1;
    unusual.number = unusual.region + 1;
}

void test_7(void) {
    usual.c1 = 1;
    usual.c2 = 2;
    usual.c3 = 3;

    usual.c1 = unusual.c2 + 1;
    usual.c2 = unusual.c3 + 1;
    usual.c3 = unusual.c1 + 1;

    usual.region = 10;
    usual.number = 20;

    usual.region = unusual.number + 1;
    usual.number = unusual.region + 1;
}

void test_8(void) {
    typedef struct {
        double d;
        int i;
        char c;
    } s;

    SIZEOF(s);
    ALIGNOF(s);
}

// Test
void speed_test(void (*f)(void)) {
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
        f();
    clock_t end = clock();
    printf("%Lg sec.\n", (end - start) / (long double) CLOCKS_PER_SEC);
}

// Main
int main(void) {
    test_8();
}