#if defined (__STDC_WANT_LIB_EXT1__)
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *str = NULL;
    size_t str_len;

    if (getline(&str, &str_len, stdin) < 0) {
        free(str);
        return EXIT_FAILURE;
    }

    printf("\n%ld - %s\n", str_len, str);

    free(str);
    return EXIT_SUCCESS;
}

int get_y_or_n(void) {
    char *response = NULL;
    size_t len;
    
    puts("Continue? [y] n: ");
    
    if (
        getline(&response, &len, stdin) < 0 || 
        len && (response[0] == 'n')
    ) {
        free(response);
        return EXIT_FAILURE;
    }

    free(response);
    return EXIT_SUCCESS;
}
