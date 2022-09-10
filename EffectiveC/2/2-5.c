#include <stdio.h>
#include <stdlib.h>

int j;                              // file scope of j begins

void f(int i) {                     // block scope of i begins
    int j = 1;                      // block scope of j begins
    i++;                            // i refers to the function parameter
    for (int i = 0; i < 2; i++) {   // block scope of loop-local i begins
        int j = 2;                  // block scope of the inner j begins; hides outer j
        printf("%d\n", j);          // inner j is in scope, prints 2
    }                               // block sope of the inner i and j ends 
    printf("%d\n", j);              // the outer j is in scope, print 1
}                                   // the block scope of i andd j ends

void g(int j);                      // j has function prototype scope; hides file-scope j

int main(int argc, char **argv) {
    f(10);
}