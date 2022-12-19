#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const char *pathname = "test1.txt";
    
    if ((fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode)) == -1) {
        fprintf(stderr, "Can't open %s.\n", pathname);
        exit(1);
    }

    FILE * f = fdopen(fd, "a");
    fputs("Hello, World!", f);
    
    fclose(f);
}