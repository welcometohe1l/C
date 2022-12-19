#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <wchar.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

// Data
typedef struct {
    unsigned char age;
    char first_name[20];
    char second_name[20];
} Human;

// Functions
int ser_human(Human h) {
    int size = sizeof(h);
    char const *f_n = "Human.png";
    FILE *f = fopen(f_n, "wb");
    
    if (f == NULL) {
        fprintf(stderr, "Cannot open %s file.", f_n);
        return EXIT_FAILURE;
    }

    if (fwrite((void *)&h, size, 1, f) != 1) {
        fprintf(stderr, "Cannot write to %s file.", f_n);
        return EXIT_FAILURE;
    }

    if (fclose(f) == EOF) {
        fprintf(stderr, "Cannot close %s file.", f_n);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Human *des_human(void) {
    int size = sizeof(Human);
    Human *h = (Human *)malloc(size);
    char const *f_n = "Human.png";
    FILE *f = fopen(f_n, "rb");

    if (f == NULL) {
        fprintf(stderr, "Cannot open %s file.\n", f_n);
        return NULL;
    }

    if (fread(h, size, 1, f) != 1) {
        fprintf(stderr, "Cannot read a data from the %s file.\n", f_n);
        return NULL;
    }

    h->age = 10;

    if (fclose(f) == EOF) {
        fprintf(stderr, "Cannot close %s file.\n", f_n);
        return NULL;
    }

    return h;
}

// Tests
void test_1(void) {
    FILE *f_w = fopen("file.txt", "a+");   
    if (!f_w) {
        fprintf(stderr, "File was not open!");
        return;
    }
    fputs("\nKek", f_w);
    fclose(f_w);
}

void test_2(void) {
    char *c = u8"MAZFK\n";
    const wchar_t *w = L"MAZFK\n";

    fprintf(stdout, "%s", c);
    fwprintf(stdout, L"%s", w);
}

void test_3(void) {
    char c;
    int i = 0;
    FILE *out = fopen("test1.txt", "w");
    while ((c = getchar()) != EOF && c != '\n' && i++ < 10)
        if (fputc(c, out) == EOF)
            fprintf(stderr, "Char '%c' has not been print!", c);
    fclose(out);
}

void test_4(void) {
    FILE *f1 = fopen("f1.txt", "a");
    printf("%ld\n", ftell(f1));

    fseek(f1, 0, SEEK_SET);
    printf("%ld\n", ftell(f1));

    fputs("Loh", f1);
    fclose(f1);
}

void test_5(void) {
    char a[100];
    FILE *f1 = fopen("f1.txt", "r");
    FILE *f2 = fopen("f2.txt", "a+");

    if (f1 == NULL) {
        fputs("f1.txt cannot be open", stderr);
        return;
    }
    if (f2 == NULL) {
        fputs("f2.txt cannot be open", stderr);
        return;
    }
    if (fgets(a, 100, f1) == NULL) {
        fputs("fputs error", stderr);
        return;
    }
    if (fputs(a, f2) == EOF) {
        perror("fputs()");
        return;
    }
    fclose(f1);
    fclose(f2);
}

int test_6(void) {
    const char *new_name = "Sun.png";
    if (rename("f1.txt", new_name)) {
        fputs("Cannot rename f1.txt file to Sun.png", stderr);
        return EXIT_FAILURE;
    }
    if (remove(new_name)) {
        fputs("Cannot remove f1.txt file\n", stderr);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int test_7(void) {
    int str_size = 10;
    char str[str_size];
    const char *f_name = "f1.txt";

    FILE *f_w = fopen(f_name, "w+");
    FILE *f_r = fopen(f_name, "r");

    if (f_w == NULL || f_r == NULL) {
        fputs("File has not been create and open", stderr);
        return EXIT_FAILURE;
    }
    if (fputs("Hello, World!", f_w) == EOF) {
        fprintf(stderr, "Cannot write to the file %s", f_name);
        return EXIT_FAILURE;
    }
    if (fflush(f_w) == EOF) {
        fprintf(stderr, "Cannot fflush() the file %s", f_name);
        return EXIT_FAILURE;
    }
    if (fgets(str, str_size, f_r) == NULL) {
        fprintf(stderr, "Cannot read string from the file %s", f_name);
        return EXIT_FAILURE;
    }

    printf("%s\n", str);

    fclose(f_w);
    fclose(f_r);

    return EXIT_SUCCESS;
}

int test_8(void) {
    char str[100];
    FILE *f = tmpfile();

    if (fputs("LOL", f) == EOF) {
        fputs("ERROR", stderr);
        return EXIT_FAILURE;
    }
    rewind(f);
    if (fflush(f) == EOF) {
        fputs("EROOR", stderr);
        return EXIT_FAILURE;
    }
    if (fgets(str, 100, f) == NULL) {
        fputs("EROOR", stderr);
        return EXIT_FAILURE;
    }
    
    printf("%s", str);

    fclose(f);
    return EXIT_SUCCESS;
}

int test_9(void) {
    char *cat_name = "LOL";
    if (!mkstemp(cat_name)) {
        fputs("ERROR", stderr);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int test_10(void) {
    Human *h_d;
    Human h_s = {
        .age = 24,
        .first_name = "Vlad",
        .second_name = "Merkulov"
    };

    if (ser_human(h_s)) {
        fputs("Serialize error occured.\n", stderr);
        return EXIT_FAILURE;
    }

    if ((h_d = des_human()) == NULL) {
        fputs("Deserialize error occured.\n", stderr);
        return EXIT_FAILURE;
    }

    printf(
        "%s\n%s\n%d\n",
        h_d->first_name,
        h_d->second_name,
        h_d->age
    );

    free(h_d);
    return EXIT_SUCCESS;
}

static void test_11(void) {
    FILE *f = fopen("test1.txt", "w+");

    if (!f) {
        fputs("File is not open", stderr);
        return;
    }
    
    const char *str = "Hello, world!";
    const unsigned long len = strlen(str);
    char s[len];
    
    if (fwrite(str, sizeof(char), len, f) < len) {
        fputs("Not all characters are writed", stderr);
        return;
    }
    if (fseek(f, 0, SEEK_SET)) {
        fputs("fseek() is failed", stderr);
        return;
    }
    if (fread(s, sizeof(char), len, f) < len) {
        fputs("Not all characters are readed", stderr);
        return;
    }
    if (fclose(f) == EOF) {
        fputs("File didn't close", stderr);
        return;
    }

    fprintf(stdout, "The readed string is: %s\n", s);
}

static void test_12(void) {
    int buf_size = 100;
    
    char buf[buf_size];
    
    memset(buf, '\0', buf_size);
    
    FILE *f = fopen("test1.txt", "r+");
    
    if (!f) {
        fputs("File didn't open", stderr);
        return;
    }
    if (fseek(f, -3, SEEK_END)) {
        fputs("fseek() failed", stderr);
        return;
    }
    if (fwrite("kek", sizeof(char), 3, f) < 3) {
        fputs("Writing failed", stderr);
        return;
    }
    if (fseek(f, 0, SEEK_SET)) {
        fputs("fseek() failed", stderr);
        return;
    }
    if (fgets(buf, buf_size, f) == NULL && !feof(f)) {
        fputs("fgets() failed", stderr);
        return;
    }
    if (fclose(f)) {
        fputs("File didn't close", stderr);
        return;
    }

    fprintf(stdout, "The new string is: %s", buf);
}

static void test_13(void) {
    long int count_of_characters;
    char const *f_name = "test2.txt";

    FILE *f = fopen(f_name, "r");
    
    if (!f) {
        fputs("Something went wrong", stderr);
        return;
    }

    if (fseek(f, 0, SEEK_END)) {
        fputs("Something went wrong", stderr);
        return;
    }

    if ((count_of_characters = ftell(f)) == -1L) {
        perror("Tell: ");
        return;
    }

    fclose(f);
    fprintf(stdout, "The count of characters in file %s: %ld\n", f_name, count_of_characters);
}

static void test_14(void) {
    fpos_t pos = 3;
    int buf_size = 100;
    char buf[buf_size];
    
    FILE *f = fopen("test2.txt", "r+");
    memset(buf, 0, buf_size);

    if (!f) {
        fputs("Something went wrong", stderr);
        return;
    }

    if (fsetpos(f, &pos) != 0) {
        fputs("Something went wrong", stderr);
        return;
    }

    if (fwrite("kek", sizeof(char), 3, f) != 3) {
        fputs("Something went wrong", stderr);
        return;
    }

    pos = 0;

    if (fsetpos(f, &pos) != 0) {
        fputs("Something went wrong", stderr);
        return;
    }    

    fread(buf, sizeof(char), 100, f);

    fclose(f);
    printf("%s", buf);
}

// Main
int main(void) {
    test_14();
}
