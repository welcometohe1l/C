#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *first, *second, *third;
    
    first = malloc(666);
    second = malloc(12);
    third = malloc(12);

    strcpy(first, argv[1]);

    free(first);
    free(second);
    free(third);

    return 0;
}