#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef _POSIX_THREAD_PRIO_INHERIT
#endif

int main(void) {
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &attr);
}