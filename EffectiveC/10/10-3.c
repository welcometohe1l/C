// Преобразует строковый аргумент arg в значение unsigned long long
// на которое ссылается val
// Возвращает true, если преобразование аргументова было успешным,
// и false, если нет

#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool convert_arg(const char *arg, unsigned long long *val) {
    char *end;
    errno = 0;
    *val = strtoull(arg, &end, 10);

    if ((*val == ULLONG_MAX || *val == ULONG_MAX) && errno) return false;
    if (*val == 0 && errno) return false;
    if (end == arg) return false;

    if (*val <= 1) return false;
    return true;
}