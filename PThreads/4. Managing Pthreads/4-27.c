#include <pthread/sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifdef _POSIX_THREAD_PRIO_PROTECT
#endif

int main(void) {
    pthread_mutex_t m1;
    pthread_mutexattr_t mutexattr_prioceiling;
    int mutex_protocol, high_prio;
    
    high_prio = sched_get_priority_max(SCHED_FIFO);

    pthread_mutexattr_init(&mutexattr_prioceiling);
    pthread_mutexattr_getprotocol(&mutexattr_prioceiling, &mutex_protocol);
    pthread_mutexattr_setprotocol(&mutexattr_prioceiling, PTHREAD_PRIO_PROTECT);
    pthread_mutexattr_setprioceiling(&mutexattr_prioceiling, high_prio);
    pthread_mutex_init(&m1, &mutexattr_prioceiling);
}
