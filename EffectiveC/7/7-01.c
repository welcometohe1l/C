#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

// Data

// Functions

// Tests
void test_1(void) {
    char string[] = "おい";
    char lol[] = "";
    printf("%s - %ld", string, sizeof(char) * strlen(string));
}

void test_2(void) {
    setlocale(LC_ALL, "ru-RU");
    char *s = "Привет! Как дела?";
    printf("%s", s);
}

void test_3(void) {
    wchar_t c = 10;
    printf("%d, %d, %ld", WCHAR_MAX, WCHAR_MIN, sizeof(c));
}

void test_4(void) {
    printf("Hello, World!\b\b\b\b");
    printf("10");
}

void test_5(void) {
    printf("\U0001F600");
}

void test_6(void) {
    wchar_t c = u'å';
    char c2 = 'a';
}

void test_7(void) {
    const char *s1 = "Lol kek";
    const char *s2 = "Ahahah";
    const char *s3;
    
    s3 = s1;
    s1 = s2;
    
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);

    s1 = (char *)NULL;

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);
}

void test_8(void) {
    const char s1[4] = "abcd";
    char s2[4] = "abc";
    printf("%s\n%s\n", s1, s2);

    s2[8] = 'A';

    for (int i = 0; i < 10; i++)
        printf("%#x ", s1[i]);
}

void test_9(void) {
    char nname[100] = "Vlad";
    size_t nname_size = sizeof(nname);

    wchar_t wname[100] = L"Vlad";
    size_t wname_size = sizeof(wname);

    printf("%zu - %zu", nname_size, wname_size);
}

void test_10(void) {
    wchar_t c = 'c';
    printf("%zu", sizeof c);  
}

void test_11(void) {
    char string[10] = "Hello!";
    *string = (char *)NULL;
    printf("%s", string);
}

// Main
int main(int argc, char *argv[]) {
    return 0;   
}