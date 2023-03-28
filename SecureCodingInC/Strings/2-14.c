#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Functions
int overlap_msg(
    char *s1, 
    rsize_t s1len, 
    char *s2, 
    rsize_t s2len
);

// Impl
errno_t strcpy_s(
    char * restrict s1,
    rsize_t s1max,
    const char * restrict s2 
) {
    errno_t rc = -1;
    const char *msg;
    rsize_t s2len = strnlen(s2, s1max);
    // Проверка ограничений в рантайме
    if (
        s1 != NULL
        && s2 != NULL
        && s1max <= RSIZE_MAX
        && s1max != 0       
        && s1max > strnlen(s2, s1max)
        && overlap_msg(s1, s1max, s2, s2len)
    ) {
        while ((*s1++ = *s2++)) rc = 0;
    } else {
        // Нарушение ограничения в рантайме,
        // делаем целевую строку пустой
        if (
            (s1 != NULL) && (s1max > 0)
            && lte_rsizemax(s1max)
        ) {
            s1[0] = NULLCHAR;
        }
        // Вызов обработчика
        __rtct_fail(__func__, msg, NULL);
    }

    return rc;
}

int overlap_msg(
    char *s1, 
    rsize_t s1len, 
    char *s2, 
    rsize_t s2len
) {
    if (s1 == NULL || s2 == NULL) {
        return EXIT_FAILURE;
    }

    if (
        (s1 > s2 && s2 + s2len < s1)
        || (s1 < s2 && s1 + s1len < s2)
    ) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}