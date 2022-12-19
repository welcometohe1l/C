#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sigrecord {
    int signum;
    char signame[10];
    char sigdesc[100];
} sigrecord;

int main(void) {
    int status = EXIT_SUCCESS;
    FILE *fp;
    sigrecord sigrec;
    char *f_name = "signals.txt";
    size_t size = sizeof(sigrecord);

    if ((fp = fopen("signals.txt", "rb")) == NULL) {
        fprintf(stderr, "Cannot open %s file.\n", f_name);
        return EXIT_FAILURE;
    }

    if (fseek(fp, size, SEEK_SET) != 0) {
        fprintf(stderr, "fseek() in %s file failed.\n", f_name);
        status = EXIT_FAILURE;
        goto close_files;
    }

    if (fread(&sigrec, size, 1, fp) != 1) {
        fprintf(stderr, "Cannot read from %s file.\n", f_name);
        status = EXIT_FAILURE;
        goto close_files;
    }

    printf(
        "Signal\n number = %d\n name = %s\n description = %s\n\n",
        sigrec.signum,
        sigrec.signame,
        sigrec.sigdesc
    );

    close_files:
    fclose(fp);
    return status;
}