#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdalign.h>
#include <assert.h>
#include <stdbool.h>

// Structures
typedef struct {
    char age;
    char grow;
} Person;

typedef struct {
    long l;
    char *s;
    int i;
} Home;

typedef struct {
    int size;
    int arr[];
} Array;

// Tests
void test_1(void) {
    int *i1 = malloc(sizeof(int));
    int *i2 = i1;

    *i1 = 10;
    *i2 = 20;

    free(i1);
    printf("%d", *i2);
}

void test_2(void) {
    int size = 10;
    char *s = malloc(size);

    if (!s) 
        return;

    strncpy(s, "12345\0", size + 1);
    printf("%s", s);
    free(s); 
}

void test_3(void) {
    void *obj = malloc(sizeof(Person));
    Person *pp = obj;
    char *ip = obj;

    Person p = {10, 20};
    
    *pp = p;
    *ip = CHAR_MAX;
    
    printf("%d\n\n", *ip);
    printf("%d\n", pp->age);
    printf("%d\n", pp->grow);
}

void test_4(void) {
    int size = sizeof(Person);
    void *obj = malloc(size);
    Person p = {10, 1};

    memcpy(obj, &p, size);
    printf("%d", ((Person *)obj)->age);
}

void test_5(void) {
    // printf("align: %ld, size: %lu", alignof(Home), sizeof(Home));
    Home *h1 = (Home *)aligned_alloc(16, 16 * sizeof(Home));
    Home *h2 = (Home *)aligned_alloc(16, sizeof(Home));

    if (!h1) printf("No h1");
    if (!h2) printf("No h2");
}

void test_6(void) {
    int size = 4;
    void *arr = malloc(size * sizeof(int));
    int *int_arr = (int *)arr;
    long *long_arr = (long *)arr;

    for (int i = 0; i < size; i++)
        int_arr[i] = 0;

    for (int i = 0; i < size; i++)
        printf("INT [%d] - %d - %p\n", i, int_arr[i], &int_arr[i]);

    for (int i = 0; i < size / 2; i++)
        printf("LONG [%d] - %ld - %p\n", i, long_arr[i],  &long_arr[i]);   
}

void test_7(void) {
    int size = 4;
    int *arr = (int *)calloc(size, sizeof(int));

    for (int i = 0; i < size; i++)
        printf("INT [%d] - %d - %p\n", i, arr[i], &arr[i]);
}

void test_8(void) {
    int *arr1 = (int *)calloc(4, sizeof(int));
    int *arr2;

    if ((arr2 = realloc(arr1, 6)) != NULL)
        arr1 = arr2;
}

void test_9(void) {
    char *string = "Hello!";
    int size = strlen(string);
    char *msg[size * 2];
    *msg = "Lol kek";
    printf("%s", *msg);
}

void test_10(void) {
    int size = 10;
    printf("%lu", sizeof(int[size]));
}

// Main
int main(int argc, char **argv) {
    test_10();
}