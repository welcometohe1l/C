#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/signal.h>

pthread_t stats_thread;
pthread_mutex_t stats_lock = PTHREAD_MUTEX_INITIALIZER;

void *report_stats(void *p) {
    sigset_t sigs_to_catch;
    int caught;

    sigemptyset(&sigs_to_catch);
    sigaddset(&sigs_to_catch, SIGUSR1);

    for (;;) {
        sigwait(&sigs_to_catch, &caught);

        /* Proceed to lock mutex and display statistics */
        pthread_mutex_lock(&stats_lock);
        display_stats();
        pthread_mutex_unlock(&stats_lock);
    }

    return NULL;
}

int main(void) {
    sigset_t sigs_to_block;

    /* 
    Set main thread's signal mask to block SIGUSR1 
    All other threads will inherit mask and have it blocked too
    */

    sigemptyset(&sigs_to_block);
    sigaddset(&sigs_to_block, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &sigs_to_block, NULL);

    pthread_create(&stats_thread, NULL, report_stats, NULL);
}