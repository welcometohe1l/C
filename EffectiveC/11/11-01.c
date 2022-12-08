#include <assert.h>
#include <stdlib.h>

// Tests
static void test_1(void) {
    int a = 10;
    int b = 20;
    static_assert(a > b, "Something wrong!");
}

// Main
int main(void) {

}