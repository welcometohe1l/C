#include <stdio.h>
#include <pthread.h>

#define TCOUNT 10
#define WATCH_COUNT 12

// Variables
int count = 0;
int thread_ids[3] = {0, 1, 2};
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;

// Functions
void watch_count(int *idp) {
    pthread_mutex_lock(&count_mutex);
    while (count <= WATCH_COUNT) {                              // while() is necessary because of spurious wake ups
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf(
            "watch_count(): Thread %d, Count is %d\n", 
            *idp, 
            count
        );
    }
    pthread_mutex_unlock(&count_mutex);
}

void inc_count(int *idp) {
    for (int i = 0; i < TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        count++;
        printf(
            "inc_count(): Thread %d, old count %d, new count %d\n", 
            *idp, 
            count - 1, 
            count
        );
        if (count == WATCH_COUNT) {
            pthread_cond_signal(&count_threshold_cv);
        }
        pthread_mutex_unlock(&count_mutex);
    }
}

// Main
int main(void) {
    int i;
    pthread_t threads[3];

    pthread_create(&threads[0], NULL, (void *)inc_count, &thread_ids[0]);
    pthread_create(&threads[1], NULL, (void *)inc_count, &thread_ids[1]);
    pthread_create(&threads[2], NULL, (void *)watch_count, &thread_ids[2]);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
