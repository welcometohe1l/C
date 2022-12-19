#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("fred.txt", "w+");
    if (fp == NULL) {
        fputs("Cannot open fred.txt file\n", stderr);
        return EXIT_FAILURE;
    }
    fputs("Some text", fp);
    if (fseek(fp, 0, SEEK_END) != 0) {
        fputs("Seek to end of file failed\n", stderr);
        return EXIT_FAILURE;
    }
    long int fpi = ftell(fp);
    if (fpi == -1L) {
        perror("[ERROR]");
        return EXIT_FAILURE;
    }
    printf("file position = %ld\n", fpi);
    if (fclose(fp) == EOF) {
        fputs("Failed to close file\n", stderr);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}