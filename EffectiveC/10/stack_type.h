#ifndef STACK_TYPE_H
#define STACK_TYPE_H

#include "stack.h"

struct node_type {
    void *data;
    size_t size;
    struct node_type *next;
};

struct stack_type {
    size_t num_elements;
    struct node_type *head;
};

#endif