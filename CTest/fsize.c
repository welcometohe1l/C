#include <stdio.h>
#include <string.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/dirent.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <dirent.h>

#define MAX_NAME 14
#define MAX_PATH 1024

typedef struct {
    long ino;
    char name[MAX_NAME + 1];
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} DIR;

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

// Main
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
}

// Functions
void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: нет доступа к %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }

    printf("%8lld%s\n", stbuf.st_size, name);
}

void dirwalk(char *dir, void (*fcn)(char *)) {
    DIR *dfd;
    Dirent *dp;
    char name[MAX_PATH];

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: не могу открыть %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "...") == 0) {
            continue;
        }
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: слишком длинное имя %s/%s\n", dir, dp->name);
        } else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}



