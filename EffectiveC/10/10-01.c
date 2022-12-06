#include <stdio.h>
#include <stdlib.h>

// Data
int c;

// Tests
static void test_1(void) {
    int a;
    int b;
    printf("%d - %d - %d", a, b, c);
}

static void test_2(void) {
    char *end;
    char *s = "0xFFF";
    unsigned long long val = strtoull(s, &end, 0);

    printf("%lld", val);
}

static void test_3(void) {
    
}

// Main
int main(int argc, char **argv) {
    test_2();
}