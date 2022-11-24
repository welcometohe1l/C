#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iconv.h>
#include <errno.h>

#if __STDC_UTF_16__ != 1
#error "__STDC_UTF_16__" not defined
#endif

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "en_US.utf8");
    
    char input[] = u8"I love 📙";
    
    const size_t input_size = sizeof(input);
    size_t input_counter = input_size;
    size_t output_counter = input_size;

    char *p_input = input;
    
    uint16_t output[input_size];
    uint16_t *p_output = output;
    
    size_t code;
    iconv_t desc = iconv_open("UTF-16", "UTF-8");
    
    if (desc == (iconv_t)-1) {
        if (errno == EINVAL)
            fprintf(stderr, 0, 0, "Conversion of '%s' to UTF-16 not available");
        else
            perror("iconv_open");
    }

    puts(input);
    
    code = iconv(desc, &p_input, &input_counter, &p_output, &output_counter);
    iconv_close(desc);

    if (code == (size_t)-1) {
        if (errno == E2BIG)
            fprintf(stderr, 0, 0, "There is not sufficient room at *outbuf");
        if (errno == EILSEQ)
            fprintf(stderr, 0, 0, "An invalid multibyte sequence has been encountered in the input");
        if (errno == EINVAL)
            fprintf(stderr, 0, 0, "An incomplete multibyte sequence has been encountered in the input");
    }

    size_t output_size = p_output - output + 1;

    printf("Converted to %zu UTF-16 code units: [ ", output_size);

    for (size_t x = 0; x < output_size; ++x)
        printf("%#x ", output[x]);
    
    puts("]");
}