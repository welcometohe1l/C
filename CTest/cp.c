#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

#define W_PERMS 0777

int main(int argc, char *argv[]) {
    int f1, f2, n;
    char buf[BUFSIZ];
    
    if (argc != 3) {
        perror("Неправильное кол-во аргументов");
        exit(1);
    } if ((f1 = open(argv[1], O_RDONLY)) == -1) {
        perror("File reading error");
        exit(1);
    } if ((f2 = creat(argv[2], W_PERMS)) == -1) {
        perror("File writing error");
        exit(1);
    }
 
    while ((n = read(f1, buf, BUFSIZ)) > 0) {
        if (write(f2, buf, n) != n) {
            perror("Ошибка записи в файл");
            exit(1);
        }
    }
}