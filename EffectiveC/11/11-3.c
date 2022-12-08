#include <assert.h>
#include <string.h>

#define ARRAYSIZE 14

char str[ARRAYSIZE];
static const char prefix[] = "Error No: ";

int main(void) {
    static_assert(
        sizeof(str) > sizeof(prefix),
        "str must be larger than prefix"
    );
    
    strcpy(str, prefix);
}

