#include <stdlib.h>
#include <assert.h>

struct packed {
    unsigned int i;
    char *p;
};

static_assert(
    sizeof(struct packed) == sizeof(unsigned int) + sizeof(char *),
    "Struct packed must not have any padding"
);