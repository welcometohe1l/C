#include <setjmp.h>

jmp_buf buf;

void g(int n);
void h(int n);

int n = 6;

void f(void) {
    setjmp(buf);
    g(n);
}

void g(int n) {
    h(n);
}

void h(int n) {
    longjmp(buf, 2);
}