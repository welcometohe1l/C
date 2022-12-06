#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct stack_type stack_type;

extern int stack_pop(stack_type *col);
extern int stack_push(stack_type *col, const void *data, size_t bytes);
extern int stack_create(stack_type **result);
extern int stack_remove(stack_type *col);

#endif