#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Data
int x = 0, y = 0, r1 = 0, r2 = 0;

// Functions
void test1_1(unsigned int id) {
    x = 1;
    atomic_thread_fence(memory_order_seq_cst);
    r1 = y;
    printf("%d - %d\n", id, r1);
}

void test1_2(unsigned int id) {
    y = 1;
    atomic_thread_fence(memory_order_seq_cst);
    r2 = x;
    printf("%d - %d\n", id, r2);
}

// Tests
void test1(void) {
    pthread_t thread1;
    pthread_t thread2;
    unsigned int thread1_id = 1;
    unsigned int thread2_id = 2;

    pthread_create(&thread1, NULL, (void *)test1_1, thread1_id);
    pthread_create(&thread2, NULL, (void *)test1_2, thread2_id);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test2(void) {
    uid_t id = getuid();
    printf("%d", id);
}

void test3(void) {
    #ifdef PATH_MAX
    FILE *f = fopen("hello.txt", "r");
}

// Main
int main(void) {
    test2();
}