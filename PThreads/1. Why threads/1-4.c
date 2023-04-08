#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

int do_one_thing(unsigned int *);
int do_another_thing(unsigned int *);
int do_wrap_up(unsigned int, unsigned int);

unsigned int r1 = 0, r2 = 0;

int main(void) 
{
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, (void *)do_one_thing, &r1)) {
        fputs("Thread was not created", stderr);
        return EXIT_FAILURE;
    }
    if (pthread_create(&thread2, NULL, (void *)do_another_thing, &r2)) {
        fputs("Thread was not created", stderr);
        return EXIT_FAILURE;
    }

    pthread_join(thread1, EXIT_SUCCESS);
    pthread_join(thread2, EXIT_SUCCESS);

    do_wrap_up(r1, r2);

    return 0;
}

// Implementations
int do_one_thing(unsigned int *pnum_times) {
    unsigned int i, j, x = 0;

    for (i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for (j = 0; j < 10000 && x < UINT_MAX; j++) {
            x++;
            printf("1: %d\n", x);
        }
        (*pnum_times)++;
    }

    return EXIT_SUCCESS;
}

 int do_another_thing(unsigned int *pnum_times) {
    unsigned int i, j, x = 0;

    for (i = 0; i < 4; i++) {
        printf("doing another thing\n");
        for (j = 0; j < 10000 && x < UINT_MAX; j++) {
            x++;
            printf("2: %d\n", x);
        }
        (*pnum_times)++;
    }

    return EXIT_SUCCESS;
}

int do_wrap_up(
    unsigned int one_times, 
    unsigned int another_times
) {
    unsigned int total;

    if (INT_MAX - one_times < another_times) {
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
