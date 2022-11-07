#include <stdio.h>

// Main
int main(int argc, char *argv[]) {
    char avc[] = "avc";
    char xyz[] = "xyz";

    char *p;

    p = avc;
    printf("%c\n", ++*p);

    p = avc;
    printf("%c\n", *++p);

    p = xyz;
    printf("%c\n", *p++);
    printf("%c\n", *p);
}