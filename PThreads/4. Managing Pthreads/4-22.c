#include <pthread/sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main(void) {
    pthread_attr_t custom_sched_attr;
    int fifo_max_prio, fifo_min_prio;
    struct sched_param fifo_param;

    pthread_attr_init(&custom_sched_attr);
    pthread_attr_setinheritsched(&custom_sched_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&custom_sched_attr, SCHED_FIFO);

    fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
    fifo_min_prio = sched_get_priority_min(SCHED_FIFO);
    fifo_param.sched_priority = fifo_max_prio;

    pthread_attr_setschedparam(&custom_sched_attr, &fifo_param);
    pthread_create(&(threads[i]), &custom_sched_attr, NULL, NULL);
}