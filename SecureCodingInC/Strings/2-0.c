#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

// Macros
#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif

#define error_message(x) fprintf(stderr, "%s(%d): " #x, __FUNCTION_NAME__, __LINE__)


// Data
typedef struct {
    time_t time;
    size_t len;
    wchar_t mes[];
} Message;

// Generics
#define print_bits(x) _Generic((x), \
    int: print_bits_i(x), \
    char: print_bits_c(x) \
)

// Functions
static void print_bits_c(char c) {
    for (int i = sizeof(char) * 8 - 1; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

static void print_bits_i(int c) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

static void printsize(char *str1, char *str2) {
    printf("%ld - %ld", sizeof str1, sizeof str2);
}

// Tests
static void test_1(void) {
    char c = '\0';
    char zero = 0;
    int i = 0;

    print_bits(c);
    print_bits(i);
    print_bits(zero); 
}

static void test_2(void) {
    char narrow_str[] = "z\u00df\u6c34\U0001f34c";
    // or "zß水🍌"
    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t warr[29];
    setlocale(LC_ALL, "en_US.utf8");
    swprintf(
        warr, 
        sizeof warr/sizeof *warr,
        L"Converted from UTF-8: '%s'", 
        narrow_str);
    wprintf(L"%ls\n", warr);
}

static void test_3(void) {
    const char * const s = "\U0001F600\U0001f601";
    printf("%s", s);
}

static void test_4(void) {
    static int a = 0;
    a += 1;
    printf("%p - %d\n", (void *)&a, a);
}

static void test_5(void) {
    char *s = "H\0B";
    printf("%s\n", s);
    for (int i = 0; i < 3; i++)
        printf("%c", s[i]);
}

static void test_6(void) {
    char c = 'c';
    size_t size_c1 = sizeof('c');
    size_t size_c2 = sizeof(c);

    printf(
        "%ld == %ld? %s",
        size_c1, 
        size_c2, 
        size_c1 == size_c2 ? "yes" : "no"
    );
}

static void test_7(void) {
    wchar_t c = L'c';
    size_t size_c1 = sizeof(L'c');
    size_t size_c2 = sizeof(c);

    printf(
        "%ld == %ld? %s",
        size_c1, 
        size_c2, 
        size_c1 == size_c2 ? "yes" : "no"
    );
}

static void test_8(void) {
    int arr[3] = {0, 1, 2};
    char *str1 = "He";
    char str2[] = "He";
    printf("%ld - %ld  - %ld", sizeof(arr), sizeof(str1), sizeof(str2));
}

static void test_9(void) {
    wchar_t *w = L"0123456789";
    int size = (wcslen(w) + 1) * sizeof(wchar_t);
    printf("%d", size);
}

static void test_10(void) {
    wchar_t *mes = L"Hello, world!";
    size_t len = wcslen(mes) + 1;
    size_t size = len * sizeof(wchar_t);

    size_t size_b = sizeof(Message) + size;

    Message *sms1 = malloc(size_b);

    wcscpy(sms1->mes, mes);
    sms1->time = time(NULL);
    sms1->len = len;

    FILE *f = fopen("wchar.txt", "wb+x");
    
    if (f == NULL) {
        error_message("File not opened");
    }

    if (fwrite(sms1, size_b, 1, f) != 1) {
        error_message("Write error");
    }
    
    free(sms1);
    fclose(f);
}

static void test_11(void) {
    size_t size = 20;
    char buffer[size];

    snprintf(buffer, size, "%s - %d", "Hello", 10);
    printf("%s", buffer);
}

static void test_12(void) {
    char str[] = "012";
    printf("%ld - %ld", sizeof(str), strlen(str));
}

static void test_13(void) {
    char *buf = NULL;
    size_t size;
    FILE *f = fopen("text.txt", "r+");

    if (f == NULL) {
        fclose(f);
        error_message("fclose() failed");
        return;
    }

    while (getline(&buf, &size, f) > 0) {
        printf("\n%s", buf);
    }

    fclose(f);
    free(buf);
}

static void test_14(void) {
    size_t cap = 10;
    char str[cap];
    char c;
    char *p = str;

    // static_assert(cap < RSIZE_MAX, "wtf?");
    clearerr(stdin);

    while (
        (c = getchar()) != '\n' 
        && (unsigned long)(p - str) != cap - 1 
        && !feof(stdin)
        && !ferror(stdin)
    ) {
        *p++ = c;
    }

    if (feof(stdin)) {
        error_message("feof() error");
        return;
    }

    if (ferror(stdin)) {
        error_message("ferror() error");
        return;
    }

    *p = '\0';
    printf("%ld - %s", strlen(str), str);
}

static void test_15(void) {
    char *buf = NULL;
    size_t size;

    clearerr(stdin);

    if (getline(&buf, &size, stdin) < 0 || ferror(stdin)) {
        error_message("getline() error");
        return;
    }

    printf("%ld - %s", strlen(buf), buf);
    free(buf);
}

static void test_16(void) {
    size_t size = 10;
    char *buf = malloc(size);

    clearerr(stdin);

    if (getline(&buf, &size, stdin) < 0 || ferror(stdin)) {
        error_message("getline() error");
        return;
    }

    printf("%ld - %s\n", strlen(buf), buf);
    free(buf);
}

static void test_17(void) {
    char *src = "Hello, world";
    size_t size = strlen(src) + 1;
    char *dst = (char *)malloc(size);

    strlcpy(dst, src, size);

    printf("%s - %s", dst, src);
}

static void test_18(void) {
    char *str1 = (char *)malloc(4);
    strlcpy(str1, "123", 4);
    char *str2 = "45678";

    size_t size = strlcat(str1, str2, strlen(str1) + strlen(str2) + 1);

    printf("%s - %s - %ld", str1, str2, size);
}

static void test_19(void) {
    char *str = "Hello, world";
    char *str2 = strndup(str, strlen(str) + 1);

    printf("%s - %s", str, str2);
    free(str2);
}

static void test_20(void) {
    char *str1 = "Hello";
    char str2[] = "Hello";

    printf("%ld - %ld\n", sizeof str1, sizeof str2);
    printsize(str1, str2);
}

static void test_21(void) {
    long int i = 16;
    i = i << 66;
    printf("%ld", i);
}

// Main
int main(void) {
    test_21();
}
