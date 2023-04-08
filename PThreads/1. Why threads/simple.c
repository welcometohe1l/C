#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Functions
int do_one_thing(unsigned int *);
int do_another_thing(unsigned int *);
int do_wrap_up(unsigned int,unsigned int);

// Variables
unsigned int r1 = 0, r2 = 0;

// Main
extern int main(void) {
    do_one_thing(&r1);
    do_another_thing(&r2);
    do_wrap_up(r1, r2);    
    
    return 0;
}

// Implementations
int do_one_thing(unsigned int *pnum_times) {
    unsigned int i, j, x;

    for (i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for (j = 0; j < 100000; j++) {
            if (x + i >= INT_MAX - i) {
                *pnum_times = 0;
                return EXIT_FAILURE;
            } 
            x = x + i;
        }
        (*pnum_times)++;
    }

    return EXIT_SUCCESS;
}

int do_another_thing(unsigned int *pnum_times) {
    unsigned int i, j, x;

    for (i = 0; i < 4; i++) {
        printf("doing another thing\n");
        for (j = 0; j < 100000; j++) {
            if (x + i >= INT_MAX - i) {
               *pnum_times = 0;
               return EXIT_FAILURE; 
            } 
            x = x + i;
        }
        (*pnum_times)++;
    }

    return EXIT_SUCCESS;
}

int do_wrap_up(unsigned int one_times, unsigned int another_times) {
    unsigned int total;

    if (INT_MAX - one_times > another_times) {
        return EXIT_FAILURE;
    }

    total = one_times + another_times;

    printf(
        "wrap up: one thing %d, another %d, total %d\n", 
        one_times,
        another_times,
        total
    );

    return EXIT_SUCCESS;
}
