
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

static 
unsigned long long 
*convert_command_line_argc(
    int argc,
    const char *argv[],
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
