#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Functions
int isPasswordOk(void);

// Main
int main(void) {
    bool PwStatus;
    puts("Enter password: ");
    PwStatus = isPasswordOk();
    if (PwStatus == false) {
        puts("Access denied!");
        exit(-1);
    }
    puts("Access success!");
    return 0;
}

// Impl
int isPasswordOk(void) {
    char Password[12];
    scanf("%s", Password);
    return 0 == strcmp(Password, "goodpass");
}
