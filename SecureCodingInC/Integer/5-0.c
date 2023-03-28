#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <assert.h>
#include <fenv.h>

// Functions
int some_f(void) {
    return CHAR_MAX + 10;
}

// Tests
static void test_1(void) {
    uint16_t u8 = 10;
    for (int i = sizeof(u8) * 8; i > 0; i--) {
        (i % 8) == 0 ? printf(" ") : 0;
        printf("%d", (u8 >> i) & 1);
    }
}

static void test_2(void) {
    int8_t i_max = 127;
    int8_t i_min = -128;
    printf("%d - %d", ++i_max, --i_min);          // undefied behavior
}

static void test_3(void) {
    unsigned int *arr = calloc(100, sizeof(unsigned int));
    ptrdiff_t diff = (arr + 20) - arr;
    printf("%td - %ld", diff, sizeof diff);
    free(arr);
}

static void test_4(void) {
    unsigned char uc = UCHAR_MAX;   // 0xFF
    int i = ~uc; printf("%d - %c", i, i);       
}

static void test_5(void) {
    signed int i1 = -15;            // 4294967281
    unsigned int i2 = 1;
    unsigned int res = i1 + i2;
    printf("%u\n", res);

    for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--) {
        printf("%d", (res >> i) & 1);
    }
}

static void test_6(void) {
    int i = 513;
    unsigned char c = i;
    printf("%d", c);
}

static void test_7(void) {
    unsigned char i = UCHAR_MAX / 2 + 1;
    signed char a = i;

    for (int counter = sizeof(i) * 8 - 1; counter >= 0; counter--) {
        printf("%d", (i >> counter) & 1);
    }

    printf("\n");

    for (int counter = sizeof(a) * 8 - 1; counter >= 0; counter--) {
        printf("%d", (a >> counter) & 1);
    }

    printf("\n%u - %d", i, a);
}

static void test_8(void) {
    signed int si = 2;
    unsigned int ui = (unsigned int) si;

    printf("%u\n", ui);
    for (int counter = sizeof(ui) * 8 - 1; counter >= 0; counter--) {
        printf("%d", (ui >> counter) & 1);
    }
}

static void test_9(void) {
   unsigned short i1 = UCHAR_MAX;
   unsigned char i2 = i1; 

    for (int counter = sizeof(i1) * 8 - 1; counter >= 0; counter--) {
        printf("%d", (i1 >> counter) & 1);
    }
        
    printf("\n");

    for (int counter = sizeof(i2) * 8 - 1; counter >= 0; counter--) {
        printf("%d", (i2 >> counter) & 1);
    }
    
    printf("\n%d - %d", i1, i2);
}

static void test_10(void) {
    unsigned char c = 0b11111111;
    printf("%d\n", c);
    for (int counter = sizeof(c) * 8 - 1; counter >= 0; counter--) {
       printf("%d", (c >> counter) & 1);
    }
}

static void test_11(void) {
    signed int si = SCHAR_MAX + 1;
    signed char sc = si;
    for (int counter = sizeof(si) * 8 - 1; counter >= 0; counter--) {
       printf("%d", (si >> counter) & 1);
    }
    puts("");
    si = sc;
    for (int counter = sizeof(si) * 8 - 1; counter >= 0; counter--) {
       printf("%d", (si >> counter) & 1);
    }
}

static void test_12(void) {
    signed int si1, si2, sum;
    unsigned int usum = (unsigned int)si1 + si2;

    if ((usum ^ si1) & (usum ^ si2) & INT_MIN) {
        // Error
    } else {
        sum = si1 + si2;
    }
    
    printf("%d", sum);
}

static void test_13(void) {
    int i1 = INT_MAX;
    int i2 = INT_MAX;
    long long sum = i1 + i2;

    printf("%lld - %lu - %lu", sum, sizeof(i1), sizeof(sum));
}

static void test_14(void) {
    unsigned int i1 = UINT_MAX;
    unsigned int i2 = UINT_MAX;
    unsigned int result;

    static_assert(
        sizeof(unsigned long long) >= 2 * sizeof(unsigned int),
        "Unable to detect wrapping after multiplication"
    );

    unsigned int long long tmp = (unsigned long long)i1 * (unsigned long long)i2;

    if (tmp > UINT_MAX) {
        // Error
    } else {
        result = (unsigned int)tmp;
    }
    
    printf("%lu - %lu", sizeof(int), sizeof(int long));
    
}

static void test_15(void) {
    unsigned int i1 = UINT_MAX;
    unsigned int i2 = UINT_MAX;
    unsigned int result;

    if (i1 > UINT_MAX / i2) {
        // error
    } else {
        result = i1 * i2;
    }
}

static void test_16(void) {
    unsigned int i1 = 11;
    unsigned int i2 = 3;

    printf("%d", i1 / i2);
}

static void test_17(void) {
    signed int i = INT_MIN;
    signed int a = i / (-1);

    printf("%d - %d", i, a);
}

static void test_18(void) {
    signed long s1 = 10;
    signed long s2 = LONG_MAX;
    signed long result;
    
    if ((s2 == 0) || ((s1 == LONG_MIN) && (s2 == -1))) {
        // Error
    } else {
        result = s1 / s2;
    }
}

static void test_19(void) {
    signed long result = 100 % 0;
    printf("%ld", result);
}

static void test_20(void) {
    int i = INT_MIN + 1;
    printf("%d", i * (-1));
}

static void test_21(void) {
    int i = 1000;
    int s = -1;

    printf("%d", i >> s);
}

static void test_22(void) {
    int i = -180;
    printf("%d", i >> 1);
}

static void test_23(void) {
    int x = INT_MAX;
    int y = 0;

    scanf("%d", &y);
    x = x + 100 - y;

    printf("%d", x);
}

// Main
int main(void) {
    test_23();
}
