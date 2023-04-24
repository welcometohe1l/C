#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/_pthread/_pthread_attr_t.h>
#include <sys/_pthread/_pthread_condattr_t.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_pthread/_pthread_rwlock_t.h>
#include <sys/_pthread/_pthread_rwlockattr_t.h>
#include <sys/_pthread/_pthread_t.h>
#include <sys/resource.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <sys/types.h>

// Defines

// Data
typedef struct {
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
    unsigned int *counter;
    int thread_id;
} counter_s;

typedef struct {
    pthread_mutex_t *mutex;
    unsigned int *counter;
    unsigned int thread_id;
    pthread_t *thread_canceled;
} worker_s;

typedef struct {
    pthread_mutex_t *mutex;
    unsigned int *counter;
    unsigned int thread;
} routine_s;

typedef struct {
    pthread_mutex_t *mutex;
    int thread_id;
} test9_s;

typedef struct {
    int thread_id;
    atomic_uint *i;
} test10_s;

typedef struct {
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    unsigned int *counter;
    int thread_id; 
} test8_s;

typedef struct {
    pthread_rwlock_t *rwlock;
    unsigned int *counter;
    int thread_id;
} test7_s;

// Functions
void f1(void) {
    printf("Hello, world");
}

void increment_counter(counter_s *counter) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(counter->mutex);
        (*(counter->counter))++;
        printf("Thread %d: counter - %d\n", counter->thread_id, *(counter->counter));
        if (*(counter->counter) == 5) {
            // pthread_mutex_unlock(counter->mutex);
            pthread_cond_signal(counter->cond); 
        }
        pthread_mutex_unlock(counter->mutex);
    }
}

void watch_counter(counter_s *counter) {
    pthread_mutex_lock(counter->mutex);
    pthread_cond_wait(counter->cond, counter->mutex);
    printf("Thread %d: Counter is rerached 5\n", counter->thread_id);
    // pthread_mutex_unlock(counter->mutex);
}

void cancel_routine(worker_s *data) {
    pthread_mutex_unlock(data->mutex);
    printf("Thread1 was cancelled");
}

void worker1(worker_s *data) {
    struct __darwin_pthread_handler_rec __handler;
    pthread_t __self = pthread_self();
    __handler.__routine = (void *)cancel_routine;
    __handler.__arg = data;
    __handler.__next = __self->__cleanup_stack;
    __self->__cleanup_stack = &__handler;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(data->mutex);
        (*(data->counter))++;
        printf("Counter: %d\n", (*(data->counter)));
        if (*(data->counter) >= 5) {
            pthread_testcancel();
        }
        pthread_mutex_unlock(data->mutex);
    }
}

void worker2(worker_s *data) {
    pthread_cancel(*(data->thread_canceled));
}

void routine1(routine_s *data) {
    for (;*(data->counter) < 100;) {
        pthread_mutex_lock(data->mutex); 
        (*(data->counter))++;
        printf("Thread %d, counter: %d\n", data->thread, *(data->counter));
        pthread_mutex_unlock(data->mutex);
    }
}

void routine2(routine_s *data) {
    for (;*(data->counter) < 100;) {
        pthread_mutex_lock(data->mutex); 
        (*(data->counter))++;
        printf("Thread %d, counter: %d\n", data->thread, *(data->counter));
        pthread_mutex_unlock(data->mutex);
    }
}

void print_routine(int thread_id) {
    printf("Thread %d capture a mutex\n", thread_id);
}

void increment_routine(test10_s *data) {
    for (int j = 0; j < 10000; j++) {
        (*(data->i))++;
        printf("Thread %d: i = %d\n", data->thread_id, *(data->i));
    }
}

void test8_routine(test8_s *data) {
    for (;(*(data->counter)) < 100;) {
        pthread_mutex_lock(data->mutex);
        while (
            data->thread_id == 1 && (*(data->counter)) % 2 == 0
            ||
            data->thread_id == 2 && (*(data->counter)) % 2 != 0
        ) {
            pthread_cond_wait(data->cond, data->mutex);
        } 
        printf("Thread %d: counter = %d\n", data->thread_id, (*(data->counter)));
        (*(data->counter))++;
        pthread_mutex_unlock(data->mutex);
        pthread_cond_broadcast(data->cond);
    }
}

void test7_read_routine(test7_s *data) {
    for (int i = 0; i < 100; i++) {
        pthread_rwlock_rdlock(data->rwlock);
        printf("Read %d: counter = %d - %d\n", data->thread_id, *(data->counter), i);
        pthread_rwlock_unlock(data->rwlock);       
    }
}

void test7_write_routine(test7_s *data) {
    for (int i = 0; i < 100; i++) {
        pthread_rwlock_wrlock(data->rwlock);
        (*(data->counter))++;
        printf("Write %d: counter = %d - %d\n", data->thread_id, *(data->counter), i);
        pthread_rwlock_unlock(data->rwlock);
    }
}

// Tests
void test1(void) {
    pthread_mutex_t *mutexp = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutexp, NULL);
}

void test2(void) {
    unsigned int counter = 0;
    pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t counter_cond = PTHREAD_COND_INITIALIZER;

    pthread_t thread1;
    pthread_t thread2;

    int thread_ids[2] = {1, 2};

    counter_s s1 = {
        .thread_id = thread_ids[0],
        .counter = &counter,
        .cond = &counter_cond,
        .mutex = &counter_mutex
    };
    counter_s s2 = s1;
    s2.thread_id = thread_ids[1];

    pthread_create(
        &thread1, 
        NULL, 
        (void *)increment_counter, 
        &s1
    );
    pthread_create(
        &thread2,
        NULL,
        (void *)watch_counter,
        &s2
    );

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
}

void test3(void) {
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    unsigned int thread_ids[2] = {0, 1};
    unsigned int counter = 0;
    
    worker_s data1 = {
        .counter = &counter,
        .thread_id = thread_ids[0],
        .mutex = &mutex,
        .thread_canceled = &thread1
    };
    worker_s data2 = {
        .counter = &counter,
        .thread_id = thread_ids[1],
        .mutex = &mutex,
        .thread_canceled = &thread1
    };

    pthread_create(&thread1, NULL, (void *)worker1, &data1);
    pthread_create(&thread2, NULL, (void *)worker2, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test4(void) {
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    unsigned int thread_ids[2] = {0, 1};
    unsigned int counter = 0;
    
    routine_s data1 = {
        .counter = &counter,
        .thread = thread_ids[0],
        .mutex = &mutex,
    };
    routine_s data2 = {
        .counter = &counter,
        .thread = thread_ids[1],
        .mutex = &mutex,
    };

    pthread_create(&thread1, NULL, (void *)routine1, &data1);
    pthread_create(&thread2, NULL, (void *)routine2, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test5(void) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);     // Deadlock...

    pthread_mutex_unlock(&mutex);

    printf("lol kek");
}

void test6(void) {
    // pthread_mutex_t mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
    
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    puts("Lol kek");
}

void test7(void) {
    // Read/Write locks...
    pthread_rwlock_t lock1 = PTHREAD_RWLOCK_INITIALIZER;
    pthread_t thread_r1;
    pthread_t thread_r2;
    pthread_t thread_w1;

    unsigned int counter = 0;

    test7_s data1 = {
        .counter = &counter,
        .rwlock = &lock1,
        .thread_id = 1
    };
    test7_s data2 = {
        .counter = &counter,
        .rwlock = &lock1,
        .thread_id = 2
    };
    test7_s data3 = {
        .counter = &counter,
        .rwlock = &lock1,
        .thread_id = 3
    };

    pthread_create(&thread_r1, NULL, (void *)test7_read_routine, &data1);
    pthread_create(&thread_r2, NULL, (void *)test7_read_routine, &data2);
    pthread_create(&thread_w1, NULL, (void *)test7_write_routine, &data3);

    pthread_join(thread_r1, NULL);
    pthread_join(thread_r2, NULL);
    pthread_join(thread_w1, NULL);

}

void test8(void) {
    // Conditional variables
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_t thread1;
    pthread_t thread2;

    unsigned int counter = 0;

    test8_s data1 = {
        .cond = &cond,
        .counter = &counter,
        .mutex = &mutex,
        .thread_id = 1
    };
    test8_s data2 = {
        .cond = &cond,
        .mutex = &mutex,
        .counter = &counter,
        .thread_id = 2
    };

    pthread_create(&thread1, NULL, (void *)test8_routine, &data1);
    pthread_create(&thread2, NULL, (void *)test8_routine, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test9(void) {
    // Scheduling priorities...
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;

    pthread_attr_t attr1;
    pthread_attr_t attr2;
    pthread_attr_t attr3;
    pthread_attr_t attr4;
    pthread_attr_t attr5;

    pthread_attr_init(&attr1);

    test9_s data1 = {.mutex = &mutex, .thread_id = 1};
    test9_s data2 = {.mutex = &mutex, .thread_id = 2};
    test9_s data3 = {.mutex = &mutex, .thread_id = 3};
    test9_s data4 = {.mutex = &mutex, .thread_id = 4};
    test9_s data5 = {.mutex = &mutex, .thread_id = 5};

    pthread_create(&thread1, NULL, (void *)print_routine, &data1);
    pthread_create(&thread2, NULL, (void *)print_routine, &data2);
    pthread_create(&thread3, NULL, (void *)print_routine, &data3);
    pthread_create(&thread4, NULL, (void *)print_routine, &data4);
    pthread_create(&thread5, NULL, (void *)print_routine, &data5);   
}

void test10(void) {
    pthread_t thread1;
    pthread_t thread2;

    atomic_uint ui = 0;

    test10_s data1 = {
        .i = &ui,
        .thread_id = 1
    };
    test10_s data2 = {
        .i = &ui,
        .thread_id = 2
    };

    pthread_create(&thread1, NULL, (void *)increment_routine, &data1);
    pthread_create(&thread2, NULL, (void *)increment_routine, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void test11(void) {
    pthread_condattr_t cond_attr1;
    pthread_condattr_t cond_attr2;

    pthread_condattr_init(&cond_attr1);
    pthread_condattr_setpshared(&cond_attr1, PTHREAD_PROCESS_SHARED);

    pthread_condattr_init(&cond_attr2);

    int res1;
    int res2;

    pthread_condattr_getpshared(&cond_attr1, &res1);
    pthread_condattr_getpshared(&cond_attr2, &res2);

    printf("%d - %d", res1, res2);
}

void test12(void) {
    // Recursive mutexes...
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);

    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);

    printf("Hello, recursive mutex!");

    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
}

void test13(void) {
    
}

// Main
int main(void) {
    test7(); 
    return 0;
}
