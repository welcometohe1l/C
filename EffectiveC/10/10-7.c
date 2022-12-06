#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
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