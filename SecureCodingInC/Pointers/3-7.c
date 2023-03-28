#include <stdio.h>
#include <stdlib.h>

// Listing
static void create(void) __attribute__ ((constructor));
static void destroy(void) __attribute__ ((destructor));

// Test
static void d1(void) __attribute__ ((destructor));
static void d2(void) __attribute__ ((destructor));

static void c1(void) __attribute__ ((constructor));
static void c2(void) __attribute__ ((constructor));

// Main
int main(void) {
    printf("create: %p.\n", (void *)create);
    printf("destroy: %p.\n", (void *)destroy);
    exit(EXIT_SUCCESS);
}

// Impl
void create(void) {
    puts("create called.\n");
}

void destroy(void) {
   puts("destroy calledd.\n");
}

// Test impl
void c1(void) {
    puts("c1\n");
}

void c2(void) {
    puts("c2\n");
}

void d1(void) {
    puts("d1\n");
}

void d2(void) {
    puts("d2\n");
}
