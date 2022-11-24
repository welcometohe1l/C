#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>

char *gets_s(char *dest, unsigned int max_size) {
    char c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (--max_size > 0) {
            *dest++ = c;
        } else {
            *dest = '\0';
            return dest;
        } 
    }
    return dest;
}

int main(int argc, char **argv) {
    unsigned int size = 10;
    char string[size];
    gets_s(string, size);
    printf("%s\n", string);
}