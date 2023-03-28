#include <stdlib.h>
#include <limits.h>

// Sum signed integers
static void sum_test1(void) {
    signed int i1, i2, sum;

    if ((sum ^ i1) & (sum ^ i2) & INT_MIN) {
        // Error
    } else {
        sum = i1 + i2;
    }
}

static void sum_test2(void) {
    signed int i1, i2, sum;

    if (
        (i2 > 0 && i1 > INT_MAX - i2) 
        || (i2 < 0 && i1 < INT_MIN - i2)
    ) {
        // Error
    } else {
        sum = i1 + i2;
    }
}

