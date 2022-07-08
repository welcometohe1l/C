#include <stdio.h>
#include <setjmp.h>
#include <stdarg.h>

// Data
jmp_buf ebuf;
int error_value = 0;

// Macros
#define TRY if ((error_value = setjmp(ebuf)) == 0)
#define CATCHALL else
#define CATCH(NUM) else if (error_value == NUM)
#define THROW(NUM) longjmp(ebuf, NUM)

// Functions
int sum(int first, ...);

// Main
int main(void) {
    TRY
        printf("%d", sum(0, 2, 3, 4, 0));
    CATCH(1)
        printf("The first argument: 0");
    CATCH(2)
        printf("The first argument: 1");
    CATCHALL
        printf("Undefined exception!");
}

// Implementation
int sum(int first, ...) {
    va_list argc;
    int result = first, value;

    if (first == 0)
        THROW(1);
    else if (first == 1)
        THROW(2);

    va_start(argc, first);
    while ((value = va_arg(argc, int)) != 0)
        result += value;
    
    va_end(argc);
    return result;
}