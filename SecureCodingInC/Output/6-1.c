#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage(char *pname) {
    char usageStr[1024];
    snprintf(usageStr, 1024, "Usage: %s <target>\n", pname);
    printf(usageStr);
}

int main(int argc, char *argv[]) {
    if (argc > 0 && argc< 2) {
        usage(argv[0]);
        exit(-1);
    }
}
