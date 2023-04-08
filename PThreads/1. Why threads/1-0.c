#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Data
unsigned int d1 = 0;

pthread_mutex_t d1_m = PTHREAD_MUTEX_INITIALIZER;

// Functions
void f1(FILE *f) {
    for (;;) {
        pthread_mutex_lock(&d1_m);
        if (d1 < 100000) {
            d1++;
            fprintf(f, "\nf1: %d", d1);
            pthread_mutex_unlock(&d1_m); 
        } else {
            pthread_mutex_unlock(&d1_m);
            break;
        }
    }
}

void f2(FILE *f) {
    for (;;) {
        pthread_mutex_lock(&d1_m);
        if (d1 < 100000) {
            d1++;
            fprintf(f, "\nf2: %d", d1);
            pthread_mutex_unlock(&d1_m); 
        } else {
            pthread_mutex_unlock(&d1_m);
            break;
        }
    }
}

// Tests
void test1(void) {
    FILE *f = fopen("1-0.txt", "wa+");

    if (!f) {
        fputs("File was not opened", stderr);
        return;
    }

    pthread_t thread1, thread2;
    int thread1_err, thread2_err;

    if ((thread1_err = pthread_create(
        &thread1, 
        NULL, 
        (void *)f1, 
        f))
    ) {
        fprintf(stderr, "\nError: pthread_create, %s", strerror(thread1_err));
        exit(1);
    } 
    
    if ((thread2_err = pthread_create(
        &thread1, 
        NULL, 
        (void *)f2, 
        f))
    ) {
        fprintf(stderr, "\nError: pthread_create, %s", strerror(thread2_err));
        exit(1);
    }

    pthread_join(thread1, NULL);
    fputs("\nЕбать тебя в рот!", f);
    pthread_join(thread2, NULL);

    fclose(f);
}

// Main
int main(void) {
    test1();
}
