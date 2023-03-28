#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Functions
bool s_m(
    signed long long s1, 
    signed long long s2, 
    signed long long type_min, 
    signed long long type_max
);

// Main
int main(void) {
    signed int i1 = INT_MAX;
    signed int i2 = INT_MAX;
    signed int result;

    if (s_m(i1, i2, INT_MIN, INT_MAX)) {
        result = i1 * i2;
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

// Impl
bool s_m(
    signed long long s1, 
    signed long long s2, 
    signed long long type_min, 
    signed long long type_max
) {
    if (s1 > 0) {
        if (s2 > 0) {
            if (s1 > (type_max / s2)) {
                return false;
            }
        } else {
            if (s2 < (type_min / s1)) {
                return false;
            }
        }
    } else {
        if (s2 > 0) {
            if (s1 < (type_min / s2)) {
                return false;
            }
        } else {
            if ((s1 != 0) && (s2 < (type_min / s1))) {
                return false;
            }
        }
    }
    
    return true;
}
