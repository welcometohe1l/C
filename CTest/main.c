#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>

// Data
jmp_buf ebuf;
int error_value = 0;

// Macros
#define TRY if ((error_value = setjmp(ebuf)) == 0)
#define CATCHALL else
#define CATCH(NUM) else if (error_value == NUM)
#define THROW(NUM) longjmp(ebuf, NUM)

// Functions
int sum(int a, ...);
char *strssub(char *s1, char *s2);

// Main
int main(int argc, char *argv[]) {
    struct tm time;
    printf("%d", time.tm_hour);
}
    
// Implementations
int sum(int a, ...) {
    va_list list; 
    int result = a, value;

    va_start(list, a);

    while((value = va_arg(list, int)) != 0)
        result += value;

    va_end(list);
    return result;
}

char *strssub(char *s1, char *s2) {
    if (strlen(s1) == 0 || strlen(s2) == 0)
        return NULL;
    
    char *c;
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    for (int i = 0; i < l1; i++) {
        if (s1[i] == s2[0]) {
            c = &s1[i];
            for (int j = 0; j < l2; j++, i++) {
                if (s1[i] != s2[j])
                    break;
                if (j == l2 - 1)
                    return c;
            }
            i--;
        }
    }

    return NULL;
}