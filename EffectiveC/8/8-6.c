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

    if ((fp = fopen("signals.txt", "wb")) == NULL) {
        fprintf(stderr, "Cannot open %s file.\n", f_name);
        return EXIT_FAILURE;
    }

    sigrecord sigrec30 = { 
        .signum = 30, 
        .signame = "USR1", 
        .sigdesc = "user-defined signal 1" 
    };
    sigrecord sigrec31 = { 
        .signum = 31, 
        .signame = "USR2", 
        .sigdesc = "user-defined signal 2" 
    };

    size_t size = sizeof(sigrecord);

    if (fwrite(&sigrec30, size, 1, fp) != 1) {
        fprintf(stderr, "Cannot write sigrec30 to %s file.\n", f_name);
        goto close_files;
    }

    if (fwrite(&sigrec31, size, 1, fp) != 1) {
        fprintf(stderr, "Cannot write sigrec31 to %s file.\n", f_name);
        goto close_files;
    }

    close_files:
    if (fclose(fp) == EOF) {
        fprintf(stderr, "Failed to close %s file.\n", f_name);
        status = EXIT_FAILURE;
    }
    
    return status;
}