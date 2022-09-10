#include <stdio.h>
#include <stdlib.h>

// Data
typedef enum {
    integer = 0,
    floating = 1
} T;

typedef union {
    struct {
        T type;
    } n;
    struct {
        T type;
        int value;
    } ni;
    struct {
        T type;
        float value;
    } nf;
} U;

// Functions
void swap_U(U *arr, int size);
void fill_U(U *arr, int size);
void print_U(U *arr, int size);

// Main
int main(void) {
    int size = 10;
    U arr[size];

    fill_U(arr, size);
    print_U(arr, size);
    
    swap_U(arr, size);
    print_U(arr, size);
}

// Implementation
void fill_U(U *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i].n.type = (i % 2) > 0 ? integer : floating;
        if (arr[i].n.type == integer)
            arr[i].ni.value = i;
        else
            arr[i].nf.value = i + 0.5;
    }
}

void swap_U(U *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i].n.type == integer) {
            arr[i].n.type = floating;
            arr[i].nf.value = (float) arr[i].ni.value;
        } else {
            arr[i].n.type = integer;
            arr[i].ni.value = (int) arr[i].nf.value;
        }
    }
}

void print_U(U *arr, int size) {
    printf("Print:\n");
    for (int i = 0; i < size; i++) {
        if (arr[i].n.type == integer)
            printf("%d\n", arr[i].ni.value);
        else
            printf("%f\n", arr[i].nf.value);
    }
}