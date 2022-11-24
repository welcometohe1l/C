#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *s = "Hello, World!";
    size_t s_size = strlen(s) + 1;
    char *heap_s = (char *)malloc(s_size * sizeof(char));
    if (heap_s) {
        strcpy(heap_s, s);
        printf("%s", heap_s);
    } else {
        fprintf(stderr, "Memory allocation error!");
    }
    free(heap_s);
}