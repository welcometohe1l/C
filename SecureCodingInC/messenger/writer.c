#include "writer.h"

// Private
static int write_message(Message *msg, char *filename);

// Public
int write(char *filename) {
    Message *msg;

    if ((msg = create_message()) == NULL) {
        return EXIT_FAILURE;
    }

    if (write_message(msg, filename)) {
        return EXIT_FAILURE;
    }

    free(msg);
    return EXIT_SUCCESS;
}

// Implementation
static int write_message(Message *msg, char *filename) {
    FILE *f = fopen(filename, "ab+");

    if (f == NULL) {
        error_message("write_message() error: file was not opened");
        return EXIT_FAILURE;
    }

    if (fwrite(msg, msg->size, 1, f) != 1) {
        error_message("write_message() error: fwrite() error");
        return EXIT_FAILURE;
    }

    fflush(f);
    fclose(f);
    return EXIT_SUCCESS;
}
