#define  __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

char *get_error(errno_t errnum) {
    rsize_t size = strerrorlen_s(errnum) + 1;
    char *msg = malloc(size);
    if (msg != NULL) {
        errno_t status = strerror_r(errnum, msg, size);
        if (status != 0) {
            memcpy(msg, "unknown error", size - 1);
        }
    }
    return msg;
}