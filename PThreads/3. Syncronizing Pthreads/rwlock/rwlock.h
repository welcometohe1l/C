#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

#define pthread_rdwattr_default NULL;

typedef struct rdwr_var {
    int readers_reading;
    int writer_writing;
    pthread_mutex_t mutex;
    pthread_cond_t lock_free;
} pthread_rdwr_t;

typedef void *pthread_rdwrattr_t;

int pthread_rdwr_init(pthread_rdwr_t *rdwrp, pthread_rdwrattr_t *attrp);
int pthread_rdwr_rlock(pthread_rdwr_t *rdwrp);
int pthread_rdwr_wlock(pthread_rdwr_t *rdwrp);
int pthread_rdwr_runlock(pthread_rdwr_t *rdwrp);
int pthread_rdwr_wunlock(pthread_rdwr_t *rdwrp);

#endif