#include "isprime.h"

#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// Funcstions
static void print_help(void) {
    printf("%s", "primetest num1 [num2 num3 ... numN]\n\n");
    printf("%s", "Test positive integers for primality. Supports testing");
    printf("%s [2-%llu].\n", "numbers in the range", ULLONG_MAX);
}

static 
bool 
convert_arg(
    const char *arg, 
    unsigned long long *val
) {
    char *end;
    errno = 0;
    *val = strtoull(arg, &end, 10);

    if ((*val == ULLONG_MAX || *val == ULONG_MAX) && errno) return false;
    if (*val == 0 && errno) return false;
    if (end == arg) return false;

    if (*val <= 1) return false;
    return true;
}

static
unsigned long long *
convert_command_line_argc(
    int argc,
    char *argv[],
    size_t *num_args
) {
    *num_args = 0;

    if (argc <= 1) {
        print_help();
        return NULL;
    }

    unsigned long long *args = (unsigned long long *)malloc(sizeof(unsigned long long) * (argc - 1));
    bool failed_conversion = (args == NULL);

    for (int i = 1; i < argc && !failed_conversion; ++i) {
        unsigned long long one_arg;
        failed_conversion |= !convert_arg(argv[i], &one_arg);
        args[i - 1] = one_arg;
    }

    if (failed_conversion) {
        free(args);
        print_help();
        return NULL;
    }

    *num_args = argc - 1;
    return args;
}

// Main
int main(int argc, char *argv[]) {
    size_t num_args;
    unsigned long long *vals = convert_command_line_argc(argc, argv, &num_args);

    if (!vals) return EXIT_FAILURE;

    for (size_t i = 0; i < num_args; ++i) {
        printf(
            "%llu is %s.\n",
            vals[i],
            is_prime(vals[i], 100) ? "probably prime" : "not prime"
        );
    }

    free(vals);
    return EXIT_SUCCESS;
}
