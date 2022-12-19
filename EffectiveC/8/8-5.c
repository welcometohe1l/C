#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Functiosn
int create_signals(void) {
    char *f_name = "signals.txt";
    FILE *f = fopen(f_name, "w+");
    if (f == NULL) {
        fprintf(stderr, "The file %s has not been create", f_name);
        return EXIT_FAILURE;
    }

    fputs("1 HUP Hangup\n", f);
    fputs("2 QUIT Interrupt\n", f);
    fputs("3 INT Quit\n", f);
    fputs("4 ILL Illegal instruction\n", f);
    fputs("5 TRAP Trace trap\n", f);
    fputs("6 ABRT Abort\n", f);
    fputs("7 EMT EMT Trap\n", f);
    fputs("8 FPE Floating-point exception\n", f);

    if (fclose(f) == EOF) {
        fprintf(stderr, "The file %s has not been close", f_name);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Main
int main(void) {
    // Preconditons
    if (create_signals()) {
        fputs("File has not been created", stderr);
        return EXIT_FAILURE;
    }

    // Programm
    int status = EXIT_SUCCESS;
    FILE *in;

    struct sigrecord {
        int signum;
        char signame[10];
        char sigdesc[100];
    } sigrec;

    if ((in = fopen("signals.txt", "r")) == NULL) {
        fputs("Cannot open signals.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        int n = fscanf(
            in,
            "%d%9s%*[ \t]%99[^\n]",
            &sigrec.signum,
            sigrec.signame,
            sigrec.sigdesc
        );
        if (n == 3) {
            printf(
                "Signal\n number = %d\n name = %s\n description = %s\n\n",
                sigrec.signum,
                sigrec.signame,
                sigrec.sigdesc
            );
        } else if (n != EOF) {
            fputs("Failed to match signum, signame of sigdesc\n", stderr);
            status = EXIT_FAILURE;
            break;
        } else {
            break;
        }
    } while (1);

    if (fclose(in) == EOF) {
        fputs("Failed to close file\n", stderr);
        status = EXIT_FAILURE;
    }

    return status;
}