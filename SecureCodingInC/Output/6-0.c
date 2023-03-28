#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// TODO
// 1. Протестировать cut_addr 
// 2. Изменить revert_addr используя cut_addr

// Functions
char *cut_addr(char *addr, size_t size) {
    if (!addr || size - 2 > size || size - 2 == 0) {
        return NULL;
    }
    
    char *buff = (char *)calloc(size - 1, sizeof(char));
    
    if (!buff) {
        return NULL;
    }

    for (size_t i = 0; i < size - 2; i++) {
        buff[i] = addr[i + 2];
    }

    buff[size - 1] = '\0';

    return buff;
}

char *revert_addr(char *addr, size_t size) {
    if (!addr || size == 0 || size > 16) {
        return NULL;
    }

    size_t new_size = size + 1;
    char *buff = (char *)calloc(new_size, sizeof(char));

    if (!buff) {
        return NULL;
    }

    for (
        size_t i = size - 1, counter = 0; 
        counter < new_size;
        i--, counter++ 
    ) {
        if (counter % 2 == 0) {
            buff[counter] = addr[i - 1];
        } else {
            buff[counter] = addr[i + 1];
        }
    }

    buff[new_size - 1] = '\0';

    return buff;
}

char *separate_addr(char *addr, size_t size) {
    size_t new_size = size * 2 + 1;
    char *buff = (char *)calloc(new_size, sizeof(char));

    if (!buff) {
        return NULL;
    }

    for (size_t i = 0, j = 0; i < new_size; i++, j++) {
        if (j % 2 == 0) {
            buff[i] = '\\';
            buff[i + 1] = 'x';
            i += 2;
        }
       buff[i] = addr[j]; 
    }

    buff[new_size - 1] = '\0';

    return buff;
}

char *create_format_str(char *addr, size_t size) {
    size_t new_size = size + 8 + 1;
    char *format_str = strncat(addr, "%x%x%x%s", new_size);
    if (!format_str) {
        printf("Error");
        exit(-1);
    }
    return format_str;
}

void test_addr(char *addr) {
    printf("\n");
    char *kek = addr;
    printf(kek, 1, 2, 3);
}

// Tests
static void test_1(void) {
    size_t input_size = 512;
    char input[input_size];
    int a = 1, b = 2, c = 3;
    
    fgets(input, input_size, stdin);
    printf(input, a, b, c);
    printf("%p - %p - %p", &a, &b, &c);
}

static void test_2(void) {
    char a[] = {'H', 'e', 'l', 'l', 'o'};
    size_t max_str_size = 128;
    char ptr_str[max_str_size];

    printf("%x", &a);
    snprintf(ptr_str, 128, "%x", &a);

    // char *cutted_addr = cut_addr(ptr_str, strlen(ptr_str));
    // if (!cutted_addr) {
    //     return;
    // }
    
    // printf("\n%s", cutted_addr);
    
    // char *reverted_addr = revert_addr(ptr_str, strlen(ptr_str));

    // if (!reverted_addr) {
    //     return;
    // }

    // printf("\n%s", reverted_addr);

    char *separated_str = separate_addr(ptr_str, strlen(ptr_str));
    if (!separated_str) {
        return;
    }
    
    printf("\n%s", separated_str);

    char *format_str = create_format_str(separated_str, strlen(separated_str));
    test_addr(format_str);
    
    // free(cutted_addr);
    free(separated_str);
    // free(reverted_addr);
}

static void test_3(void) {
    int i;
    printf("Hello%n\n", (int *)&i);
}

static void test_4(void) {
    int long long arr[3] = {1, 2, 3};
    printf("%d%p%p%p%p%p%p%p%p%p%p", 10);
    long long int arr1[3] = {1, 2, 3};
    
    for (size_t i = 0; i < 3; i++) {
        printf("\n%p - %p", &arr[i], &arr1[i]);
    }
}

static void test_5(void) {
    
}

// Main
int main(void) {
    test_5();
}
