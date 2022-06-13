#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

// CAT: Конкатенация .txt файлов
// TODO
// 1. Получить указатели на файлы из аргументов
// 2. Поочереди списать файлы в новый файл

#define FLAG_RESULT_FILE "-r"
#define FLAG_CONCATENATED_FILES "-c"

#define ERROR(message)      fprintf(stderr, "[ERROR]: %s", message); 
#define WARNING(message)    fprintf(stderr, "[WARNING]: %s", message);

// Structs
enum ERRORS {
    NO_RESULT_FILE_SPECIFIED,
    NO_CONCATENATED_FILES_SPECIFIED,
    CONCATENATED_FILES_NOT_FOUND,
    RESULT_FILE_WRONG_EXTENSION
};

struct FILES {
    int count;
    FILE files[];
};

// Interafces
char *get_error(enum ERRORS error);
void copy_file(FILE *f1, FILE *f2);
FILE *get_result_file(int argc, char *argv[]);
FILE **get_concatenated_files(int argc, char *argv[]);

// Prog
int main(int argc, char *argv[]) {
    // TODO
    // 1. Ищем файл результа
    // 2. Ищем конкатенируемые файлы
    // 3. Копируем одно в другое
}

// Implementations
void copy_file(FILE *f1, FILE *f2) {
    char c;
    while ((c = getc(f1)) != EOF)
        putc(c, f2);
}

char *get_error(enum ERRORS error) {
    switch (error) {
    case NO_RESULT_FILE_SPECIFIED:
        return "Не указан файл для вывода результат конкатенации.";
    case NO_CONCATENATED_FILES_SPECIFIED:
        return "Не указаны файлы для конкатенации.";
    case CONCATENATED_FILES_NOT_FOUND:
        return "Файлы для конкатенации не найдены.";
    }
}

bool check_extension(char *file) {
    // !!!
}

// !!!
FILE *get_result_file(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (
            strcmp(argv[i], FLAG_RESULT_FILE) == 0 
            && ++i < argc
            && arv) {
            return fopen(argv[++i], "r");
        }
    }

    ERROR(get_error(NO_RESULT_FILE_SPECIFIED));
    return NULL;
}

FILE **get_concatenated_files(int argc, char *argv[]) {

}