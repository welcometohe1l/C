#include <stdio.h>

// Functions
int foo(int a) {
    if (a > 0)
        return -a;    // WTF? This is only a warning, not an error.
}

// Tests
void test_1(void) {
    int i = 0;
    loop:
    if (i++ < 10) {
        printf("%d\n", i);
        goto loop;
    }
}

void test_2(void) {
    foo(-1);
}

// Main
int main(int argc, char *argv[]) {
    test_2();
}