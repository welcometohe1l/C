#if defined (__STDC_WANT_LIB_EXT1__)
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void get_y_or_n(void) {
    char response[8];
    size_t len = sizeof(response);
    
    puts("Continue? [y] n: ");
    
    if (fgets(response, len, stdin))  {
        fputs("Something went wrong", stderr);
        return;
    }
    
    if (response[0] == 'n') {
        exit(0);
    }
}
