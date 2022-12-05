#include <stdlib.h>

enum Names {
    #define NAME(x) x,
    #include "9-1.h"
    #undef NAME
};

int main(void) {
    enum Names name = first;
    switch (name) {
        #define NAME(x) case x: break;
        #include "9-1.h"
        #undef NAME
    }
}