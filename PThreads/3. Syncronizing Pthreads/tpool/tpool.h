#ifndef TPOOL_H
#define TPOOL_H

#include <pthread.h>

/* Data types */
typedef struct tpool_work {
    void (*routine)(void *arg);
    void *arg;
    struct tpool_work *next;
} tpool_work_t;

typedef struct tpool {
    /* pool characterisistics */
    int num_threads;
    int max_queue_size;

    int do_not_block_when_full;
    /* pool state */
    pthread_t *threads;
    int cur_queue_size;
    tpool_work_t *queue_head;
    tpool_work_t *queue_tail;
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;
    pthread_cond_t queue_empty;
    int queue_closed;
    int shutdown;
} *tpool_t;

/* Routines */
void tpool_init(
    tpool_t *tpoolp,
    int num_worker_threads,
    int max_queue_size,
    int do_not_block_when_full
);

int tpool_add_work(
    tpool_t tpool,
    void *routine,
    void *arg
);

int tpool_destroy(tpool_t tpool, int finish);

#endif
