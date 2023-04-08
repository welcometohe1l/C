#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

void do_one_thing(unsigned int *);
void do_another_thing(unsigned int *);
void do_wrap_up(unsigned int, unsigned int);

unsigned int r1 = 0, r2 = 0, r3 = 0;
pthread_mutex_t r3_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) 
{
    pthread_t thread1, thread2;

    if (argc >= 2) {
        r3 = atoi(argv[1]);
    }

    pthread_create(&thread1, NULL, (void *)do_one_thing, &r1);
    pthread_create(&thread2, NULL, (void *)do_another_thing, &r2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    do_wrap_up(r1, r2);

    return 0;
}

// Implementations
void do_one_thing(unsigned int *pnum_times) {
    unsigned int i, j, x;

    pthread_mutex_lock(&r3_mutex);
    if (r3 > 0) {
        x = r3;
        r3--;
    } else {
        x = 1;
    }
    pthread_mutex_unlock(&r3_mutex);
    
    for (i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for (j = 0; j < 10000 && x < UINT_MAX; j++) {
            x++;
            printf("1: %d\n", x);
        }
        (*pnum_times)++;
    }
}

 void do_another_thing(unsigned int *pnum_times) {
    unsigned int i, j, x = 0;

    for (i = 0; i < 4; i++) {
        printf("doing another thing\n");
        for (j = 0; j < 10000 && x < UINT_MAX; j++) {
            x++;
            printf("2: %d\n", x);
        }
        (*pnum_times)++;
    }
}

void do_wrap_up(
    unsigned int one_times, 
    unsigned int another_times
) {
    unsigned int total;

    if (INT_MAX - one_times < another_times) {
        fputs("Some error", stderr);
        return;
    }

    total = one_times + another_times;

    printf(
        "wrap up: one thing %d, another %d, total %d\n", 
        one_times,
        another_times,
        total
    );
}
