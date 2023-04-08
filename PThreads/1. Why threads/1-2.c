#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

int do_one_thing(unsigned int *);
int do_another_thing(unsigned int *);
int do_wrap_up(unsigned int,unsigned int);

unsigned int shared_mem_id;
unsigned int *shared_mem_ptr;
unsigned int *r1p;
unsigned int *r2p;

extern int main(void) {
    pid_t child1_pid;
    pid_t child2_pid;
    int status;
    
    /* Initialize sharerd memeory segment */
    shared_mem_id = shmget(IPC_PRIVATE, 2 * sizeof(unsigned int), 0660);
    shared_mem_ptr = (unsigned int *)shmat(shared_mem_id, (void *)0, 0);

    r1p = shared_mem_ptr;
    r2p = (shared_mem_ptr + 1);

    *r1p = 0;
    *r2p = 0;

    if ((child1_pid = fork()) == 0) {
        /* First child */
        do_one_thing(r1p);
        exit(0);
    }

    /* Parent */

    if ((child2_pid = fork()) == 0) {
        /* Second child */
        do_another_thing(r2p);
        exit(0);
    }

    /* Parent */
    waitpid(child1_pid, &status, 0);
    waitpid(child2_pid, &status, 0);

    do_wrap_up(*r1p, *r2p);

    printf("\n%d - %d", child1_pid, child2_pid);
    
    return 0;
}

// Implementations
int do_one_thing(unsigned int *pnum_times) {
    unsigned int i, j, x = 0;

    for (i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for (j = 0; j < 10000; j++) {
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
        for (j = 0; j < 10000; j++) {
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
