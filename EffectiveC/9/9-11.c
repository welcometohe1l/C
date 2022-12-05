#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SIN(X) _Generic((X),  \
    float: sinf, \
    double: sin, \
    long double: sinl \
)(X)

int main(int argc, char **argv) {
    float f = SIN(1.573f);
    double d = SIN(3.3412);
}