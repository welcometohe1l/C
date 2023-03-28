#include <stdio.h>

void good_function(const char *str) {
    printf("%s", str);
}

int main(void) {
    static void (*funcPtr)(const char *str);
    funcPtr = good_function;
    (void)(*funcPtr)("hi ");
    good_function("there!\n");
    return 0;
}