#include <stdio.h>
#include "power_divide.h"

int main() {
    int base = 2;
    int exponent = 10;
    int result = power_divide(base, exponent);
    printf("2^10 using dynamic library: %d\n", result);
    return 0;
}