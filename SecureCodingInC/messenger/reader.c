#include "reader.h"
#include <malloc/_malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// TODO
// 1. Открывваем файл
// 2. Считываем весь файл (кол-во байт)
// 3. Декодируем его
// 4. Принтим результат

// Public
int read(char *filename) {
    Message msg_l;

    FILE *f = fopen(filename, "rb+");

    if (!f) {
        error_message("fopen() error");
        return EXIT_FAILURE;
    }

    if (fseek(f, 0, SEEK_SET)) {
        error_message("fseek() error");
        return EXIT_FAILURE;
    }

    for (
        int count = 0; 
        count < 100 && fread(&msg_l, sizeof(Message), 1, f) == 1;
        count++
    ) {
        Message *msg_d = malloc(msg_l.size);

        msg_d->size = msg_l.size;
        msg_d->time = msg_l.time;
        msg_d->text_len = msg_l.text_len;

        if (fread(&msg_d->text, sizeof(char), msg_l.text_len, f) != msg_l.text_len) {
            error_message("fread() errro");
            return EXIT_FAILURE;
        }

        printf(
            "\n%ld - %zu - %zu\n%s", 
            msg_d->time, 
            msg_d->size, 
            msg_d->text_len, 
            msg_d->text
        );
    }

    fclose(f);
    return EXIT_SUCCESS;
}
