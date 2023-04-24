#include <stdlib.h>
#include <pthread.h>

#define SYNC_MAX_COUNT 10

void syncronization_point(void) {
    static pthread_mutex_t sync_lock = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t sync_cond = PTHREAD_COND_INITIALIZER;

    static int sync_count = 0;

    /* Блокировака доступа к счётчику */
    pthread_mutex_lock(&sync_lock);
    sync_count++;

    /* Проверка: следует ли продолжать ожидание */
    if (sync_count < SYNC_MAX_COUNT) {
        pthread_cond_wait(&sync_cond, &sync_lock);
    } else {
        /* Оповестить о достижении данной точки всеми */
        pthread_cond_broadcast(&sync_cond);
    }

    /* 
    Активизация взаимной блокировки - в противном случае,
    из процедуры сможет выйти только одна нить! 
    */
    pthread_mutex_unlock(&sync_lock);
}