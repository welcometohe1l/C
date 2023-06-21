#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void r1(char *fname, int x, char **bufp) {
    double temp;
    int fd;

    temp = sqrt(x);
    fd = open(fname, O_CREAT | O_RDWR, 0666);

    pthread_mutex_lock(&count_lock);
    count++;
    pthread_mutex_unlock(&count_lock);

    *bufp = (char *)malloc(256);
}

// Спорно
void r2(char *fname, int x, char **bufp) {
    double temp;
    int i, reads;
    int start = 0, end = LOCAL_COUNT_MAX;
    int fd;

    
    for (i = start; i < end; i++) {
        fd = open(fname, O_CREAT | O_RDWR, 0666);
        pthread_mutex_lock(&count_lock);
        x = x + count;
        temp = sqrt(x);
        if (temp == THRESHOLD)
            count++;
        pthread_mutex_unlock(&count_lock);
    }
    
}