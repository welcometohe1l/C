#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    const char * const name = argv[0] ? argv[0] : "";
    printf("%s - %d", name, argc);
}