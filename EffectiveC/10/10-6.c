#include <stdbool.h>

bool is_prime(unsigned long long n, unsigned int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    unsigned long long d = n - 1;
    while (d % 2 == 0) d /= 2;

    for (; k != 0; --k)
        if (!miller_rabin_test(d, n)) 
            return false;

    return true;
}

