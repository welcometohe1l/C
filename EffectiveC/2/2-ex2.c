#include <stdio.h>
#include <stdlib.h>

// Functions
int first(void) {
    printf("first");
    return 1;
}

int second(void) {
    printf("second");
    return 2;
}

int third(void) {
    printf("third");
    return 3;
}

// Main
int main(int argc, char *argv[]) {
    int index = *argv[1] - '0';
    int (*function[3])(void) = {first, second, third};
    return argc == 2 && index >= 0 && index <= 2 ? function[index]() : EXIT_FAILURE; 
}