#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buf = NULL;
    size_t size = 0;
    FILE *stream;

    stream = open_memstream(&buf, &size);
    
    if (stream == NULL) {
        free(buf);
        fclose(stream);
        return EXIT_FAILURE;
    }

    fprintf(stream, "Hello, ");
    fflush(stream);
    printf("\n%s - %ld", buf, size);

    fprintf(stream, "world");
    fflush(stream);
    printf("\n%s - %ld", buf, size);

    fputs(" lol", stream);
    fflush(stream);
    printf("\n%s - %ld", buf, size);

    fseek(stream, 0, SEEK_SET);
    fprintf(stream, "Suka");
    fflush(stream);
    printf("\n%s - %ld", buf, size);

    fclose(stream);
    stream = open_memstream(&buf, &size);
    
    if (stream == NULL) {
        free(buf);
        fclose(stream);
        return EXIT_FAILURE;
    }
    fprintf(stream, "Suka");
    fflush(stream);
    printf("\n%s - %ld", buf, size);

    fclose(stream);
    free(buf);
}
