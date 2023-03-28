#include "messenger.h"
#include "message.h"
#include "reader.h"
#include "writer.h"
#include <stddef.h>
#include <stdio.h>

// Gobal
#define filename "top_secret.merkulov"

int main(void) {

    write(filename);
    puts("\n");
    read(filename);

    return 0;
}
