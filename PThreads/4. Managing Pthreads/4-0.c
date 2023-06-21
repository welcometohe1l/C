#include <pthread/pthread_impl.h>
#include <pthread/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_key_t.h>

// Defines

#ifdef _POSIX_THREAD_ATTR_STACKSIZE
#endif

#ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
#endif

// Data sructures
typedef struct {
    int thread_id;
    unsigned int *counter;
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
} test8_s;

typedef struct {
    FILE *f;
    unsigned int id;
} test11_s;

// Global
pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t some_id;

// Functions
void test3_routine(int thread_id) {
    int arr[1024] = {0};
    printf("LOL %d\n", arr[0]);
}

void test4_routine(void) {
    printf("Hello, suka");
}

void test5_init(void) {
    printf("Hello, world!\n");
}

void test5_routine(int thread_id) {
    pthread_once(&once, (void *)test5_init);
    printf("Thread %d\n", thread_id);
}

void test6_routine(int thread_id) {
    int *i = (int *)malloc(sizeof(int));
    *i = thread_id;
    pthread_setspecific(some_id, (void *)i);
    printf("Thread %d\n", thread_id);
}

void test6_deinit(void *p) {
    free(p);
}

void test7_routine(void) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    for (int i = 0; i < 10000000; i++) {
        printf("Counter: %d\n", i);
    }
}

void test8_end(test8_s *data) {
    printf("Thread %d calls cleanup stack\n", data->thread_id);
    pthread_mutex_unlock(data->mutex);
    pthread_cond_signal(data->cond);
}

void test8_routine(test8_s *data) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
    pthread_cleanup_push((void *)test8_end, (void *)data);

    for (;;) {
        pthread_mutex_lock(data->mutex);
        if (
            *(data->counter) % 2 == 0 && data->thread_id == 1
            ||
            *(data->counter) % 2 != 0 && data->thread_id == 2
        ) {
            pthread_cond_wait(data->cond, data->mutex);
        }

        if (*(data->counter) == 10000) {
            pthread_mutex_unlock(data->mutex);
            pthread_cond_signal(data->cond);
            break;
        }

        *(data->counter) += 1;
        printf("Thread %d: counter %d\n", data->thread_id, *(data->counter));
        pthread_mutex_unlock(data->mutex);
        pthread_cond_signal(data->cond);
    }

    pthread_cleanup_pop(0);
}

void test11_routine(test11_s *s) {
    for (int i = 0; i < 10000; i++) {
        fprintf(s->f, "Thread: %d - %d\n", s->id, i);
    }
}

// Tests
void test1(void) {
    
}

void test2(void) {
    pthread_attr_t attr;
    size_t thread_stack_size;

    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &thread_stack_size);

    printf("%zu", thread_stack_size);
}

void test3(void) {
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, (void *)test3_routine, (void *)0);
    pthread_create(&thread2, NULL, (void *)test3_routine, (void *)1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread %d addr: %p\n", 1, pthread_get_stackaddr_np(thread1));
    printf("Thread %d addr: %p\n", 2, pthread_get_stackaddr_np(thread2));
}

void test4(void) {
    pthread_t thread1;
    pthread_attr_t detached_attr;

    pthread_attr_init(&detached_attr);
    pthread_attr_setdetachstate(&detached_attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&thread1, &detached_attr, (void *)test4_routine, NULL);

    pthread_attr_destroy(&detached_attr);
}

void test5(void) {
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, (void *)test5_routine, (void *)0);
    pthread_create(&thread2, NULL, (void *)test5_routine, (void *)1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test6(void) {
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, (void *)test6_routine, (void *)0);
    pthread_create(&thread2, NULL, (void *)test6_routine, (void *)1);

    pthread_key_create(&some_id, (void *)test6_deinit);
}

void test7(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, (void *)test7_routine, NULL);
    for (int i = 0; i < 10000; i++) {
        fprintf(stderr, "%d\n", i);
    }
    pthread_cancel(thread);
}

void test8(void) {
    pthread_t thread1;
    pthread_t thread2;
    unsigned int counter = 0;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    test8_s data1 = {
        .thread_id = 1,
        .cond = &cond,
        .mutex = &mutex, 
        .counter = &counter
    };

    test8_s data2 = {
        .thread_id = 2,
        .cond = &cond,
        .mutex = &mutex,
        .counter = &counter
    };

    pthread_create(&thread1, NULL, (void *)test8_routine, (void *)&data1);
    pthread_create(&thread2, NULL, (void *)test8_routine, (void *)&data2);

    pthread_cancel(thread1);
    pthread_cancel(thread2);

    for (int i = 0; i < 1000; i++) {
        printf("%d\n", i);
    }

    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);
}

void test9(void) {
    #ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
    #endif

    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    // pthread_attr_setschedparam(&attr, )
    pthread_create(&thread, &attr, NULL, NULL); 
}

void test10(void) {
    printf(
        "%d - %d", 
        sched_get_priority_max(SCHED_FIFO), 
        sched_get_priority_min(SCHED_FIFO)
    );
}

void test11(void) {
    pthread_t l_thread;
    pthread_t h_thread;
    pthread_attr_t l_attr;
    pthread_attr_t h_attr;
    struct sched_param l_param;
    struct sched_param h_param; 

    int max_prio = sched_get_priority_max(SCHED_FIFO);
    int min_prio = sched_get_priority_min(SCHED_RR);
    l_param.sched_priority = min_prio;
    h_param.sched_priority = max_prio;

    FILE *f = fopen("test11.txt", "w+");

    if (f == NULL) {
        printf("ERROR");
        return;
    }

    test11_s s1 = {
        .f = f,
        .id = 1
    };
    test11_s s2 = {
        .f = f,
        .id = 2
    };

    pthread_attr_init(&l_attr);
    pthread_attr_init(&h_attr);

    pthread_attr_setschedpolicy(&l_attr, SCHED_RR);
    pthread_attr_setschedpolicy(&h_attr, SCHED_FIFO);

    pthread_attr_setschedparam(&l_attr, &l_param);
    pthread_attr_setschedparam(&h_attr, &h_param);

    pthread_create(&l_thread, &l_attr, (void *)test11_routine, (void *)&s2);
    pthread_create(&h_thread, &h_attr, (void *)test11_routine, (void *)&s1);

    pthread_join(l_thread, NULL);
    pthread_join(h_thread, NULL);

    fclose(f);
}

// Main
int main(void) {
    test11();
    return 0;
}