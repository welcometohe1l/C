#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

// Возможно переполнение в стеке
void foo(void *arg, size_t len) {
    char buff[100];
    long val = 10;
    long *ptr = malloc(sizeof(long));
    
    memcpy(buff, arg, len);
    
    *ptr = val;
    
    return;
}