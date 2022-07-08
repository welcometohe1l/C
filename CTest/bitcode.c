// TODO
// 1. Заменить 4 функции получения битов одной
// 2. Выделять только нужное количество динамическоц памяяти

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLAG_POS    1
#define VALUE_POS   2

#define MAX_STRING  99

#define FLAG_INT    "-i"
#define FLAG_CHAR   "-c"
#define FLAG_LONG   "-l"
#define FLAG_STRING "-s"

enum FLAGS {
    INT = 0,
    CHAR = 1,
    LONG = 2,
    STRING = 3
};

// Functions
char *get_bits_i(int value);
char *get_bits_c(char value);
char *get_bits_l(long value);
char *get_bits_s(char *value);

int get_value_i(char value[]);
char get_value_c(char value[]);
char *get_value_s(char value[]);
double get_value_d(char value[]);

int get_settings(char flag[]);

// Main
// 1. Получить настройки
// 2. В зависимости от настроек распарсить данные
int main(int argc, char *argv[]) {
    char *p;
    int settings = get_settings(argv[FLAG_POS]);
    void *pv = malloc(MAX_STRING + 1);

    switch (settings) {
        case INT:
            sscanf(argv[VALUE_POS], "%d", (int *)pv);
            p = get_bits_i(*(int *)pv);
            break;
        case CHAR:
            sscanf(argv[VALUE_POS], "%c", (char *)pv);
            p = get_bits_c(*(char *)pv);
            break;
        case LONG:
            sscanf(argv[VALUE_POS], "%ld", (long *)pv);
            p = get_bits_l(*(long *)pv);
            break;
        case STRING:
            sscanf(argv[VALUE_POS], "%99s", (char *)pv);
            p = get_bits_s((char *)pv);
            break;
        default:
            exit(0);
    }

    printf("Result: %s", p);

    free(p);
    free(pv);
}

// Implementations
int get_settings(char flag[]) {
    if (strcmp(FLAG_INT, flag) == 0) {
        return INT;
    } else if (strcmp(FLAG_CHAR, flag) == 0) {
        return CHAR;
    } else if (strcmp(FLAG_LONG, flag) == 0) {
        return LONG;
    } else if (strcmp(FLAG_STRING, flag) == 0) {
        return STRING;
    } else {
        perror("Флаг не передан");
        return -1;
    }
}

char *get_bits_i(int value) {
    int size = sizeof(int) * 8 - 1;
    char *result = (char *) malloc(size + 1);

    for (int i = size; i >= 0; i--) {
        result[size - i] = ((value >> i) & 1) + '0';
    }

    result[size + 1] = '\0';

    return result;
}

char *get_bits_l(long value) {
    int size = sizeof(long) * 8 - 1;
    char *result = (char *) malloc(size + 1);

    for (int i = size; i >= 0; i--) {
        result[size - i] = ((value >> i) & 1) + '0';
    }

    result[size + 1] = '\0';

    return result;
}

char *get_bits_c(char value) {
    int size = sizeof(char) * 8 - 1;
    char *result = (char *) malloc(size + 1);

    for (int i = size; i >= 0; i--) {
        result[size - i] = ((value >> i) & 1) + '0';
    }

    result[size + 1] = '\0';

    return result;
}

char *get_bits_s(char* value) {
    int len = strlen(value);
    char *result = (char *) malloc(len * 8 * sizeof(char));

    for (int i = 0; i < len; i++) {
        strcat(result, get_bits_c(value[i]));
    }
    
    return result;
}