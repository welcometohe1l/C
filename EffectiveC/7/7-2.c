#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int main(int argc, char *argv[]) {
    char str1[] = "Here comes the sun";
    char *str2 = malloc(strlen(str1) + 1);

    wchar_t wstr1[] = L"Here comes the sun";
    wchar_t *wstr2 = malloc(wcslen(wstr1 + 1) * sizeof(wchar_t));

    printf("%zu - %zu", sizeof(wstr1), sizeof(str1));
}