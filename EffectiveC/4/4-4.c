#include <stdio.h>
#include <stdlib.h>

// Data
int glob;

int f(void) {
    return glob + 10;
}

int g(void) {
    glob = 42;
    return glob;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

// Main
int main(void) {

    // Wrong, because the call order isn't defined explicitly
    // when functions called within function designator.
    max(f(), g());

    // Correct
    int f_val = f();
    int g_val = g();
    max(f_val, g_val);
}