#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define LIMIT 10

void *dup_string(size_t size, char *str) {
    assert(size <= LIMIT && "size is larger than the expected limit");
    assert(str != NULL && "the caller muse ensure str is not null");
    return NULL;
}

int main(void) {
    // char *str = "Hello";
    dup_string(9, NULL);
}

