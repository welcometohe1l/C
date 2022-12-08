#define  __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

errno_t print_error(errno_t errnum) {
    rsize_t size = strerrorlen_s(errnum) + 1;
    char *msg = malloc(size);
    int status = strerror_r(errnum, msg, size);
    if (msg != NULL && status == 0) {
        fputs(msg, stderr);
        return 0;
    } else {
        fputs("unknown error", stderr);
        return ENOMEM;
    }
}

int main(void) {
    print_error(ENOMEM);
    exit(1);
}